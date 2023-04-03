#include <fstream>
#include <iostream>
#include <vector>

using namespace std;


struct Alumno {
    char codigo[5];
    char nombre[11];
    char apellidos[20];
    char carrera[15];

    int ciclo;
    float mensualidad;
    int del;
};

void readFromConsole(char buffer[], int size) {
    string temp;
    cin >> temp;
    for (int i = 0; i < size; i++)
        buffer[i] = (i < temp.size()) ? temp[i] : ' ';
    buffer[size - 1] = '\0';
    cin.clear();
}

ostream &operator<<(ostream &stream, Alumno &p) {
    stream.write((char *) &p, sizeof(p));
    stream << "\n";
    stream << flush;
    return stream;
}

istream &operator>>(istream &stream, Alumno &p) {
    stream.read((char *) &p, sizeof(p));
    stream.get();
    return stream;
}

class FixedRecord {
    string filename;

public:
    FixedRecord(const string &filename) : filename(filename) {}


    vector<Alumno> load() {
        ifstream infile;
        infile.open(filename, ios::binary);
        vector<Alumno> alumnos;

        if (infile.is_open()) {
            while (!infile.eof()) {
                Alumno tmp;
                infile >> tmp;
                if (!infile.eof()) {
                    alumnos.push_back(tmp);
                }
            }
            infile.close();
        } else {
            cerr << "No se pudo abrir el archivo\n";
        }
        return alumnos;
    }

    void add(Alumno record) {
        fstream file;
        file.open(filename, ios::ate | ios::binary | ios::in | ios::out);
        if (file.is_open()) {
            Alumno header;
            file >> header;
            if (header.del != -1) {
                int lastDeletedPos = header.del;
                file.seekg(lastDeletedPos * sizeof(Alumno));
                Alumno lastDeletedRegister;
                file >> lastDeletedRegister;
                header.del = lastDeletedRegister.del;
                file.seekg(0);
                file << header;
                file.seekg(lastDeletedPos * sizeof(Alumno));
            }
            else {
                file.seekg(ios::end);
            }
            file << record;
            file.close();

        } else {
            cerr << "No se pudo abrir el archivo\n";
        }
    }

    Alumno readRecord(int pos) {
        ifstream infile(filename);
        Alumno tmp;
        if (infile.is_open()) {
            infile.seekg(pos * sizeof(tmp));
            infile >> tmp;
            infile.close();
        } else {
            cerr << "No se pudo abrir el archivo\n";
        }
        return tmp;
    }

    bool deleteRecord(int pos) {
        if (pos <= 0) return false;
        fstream file(filename,ios::in | ios::out | ios::ate);
        if (file.is_open()) {
            file.seekg(0);
            Alumno header;
            file >> header;
            file.seekg(pos * sizeof(Alumno));
            file << header;
            file.seekg(0);
            Alumno newHeader;
            newHeader.del = pos;
            file << newHeader;
            file.close();
        } else {
            cerr << "No se pudo abrir el archivo\n";
        }
        return true;
    }
};

int main() {
    FixedRecord fixedRecord("../datos4.bin");
    Alumno header;
    header.del = -1;
    fixedRecord.add(header);
    for (int i = 0; i < 1; ++i) {
        Alumno alumno;
        cout << "Codigo: ";
        readFromConsole(alumno.codigo, 5);
        cout << "Nombre: ";
        readFromConsole(alumno.nombre, 11);
        cout << "Apellidos: ";
        readFromConsole(alumno.apellidos, 20);
        cout << "Carrera: ";
        readFromConsole(alumno.carrera, 15);
        cout << "Ciclo: ";
        cin >> alumno.ciclo;
        cout << "Mensualidad: ";
        cin >> alumno.mensualidad;
        fixedRecord.add(alumno);
    }
    vector<Alumno> alumnos = fixedRecord.load();
    for (auto &tmp: alumnos) {
        cout << "Codigo:" << tmp.codigo << endl;
        cout << "Nombre:" << tmp.nombre << endl;
        cout << "Apellidos:" << tmp.apellidos << endl;
        cout << "Carrera:" << tmp.carrera << endl;
        cout << "Ciclo:" << tmp.ciclo << endl;
        cout << "Mensualidad:" << tmp.mensualidad << endl;
    }
    //    Alumno segundo = fixedRecord.readRecord(1);
    //    cout << "Codigo:" << segundo.codigo << endl;
    //    cout << "Nombre:" << segundo.nombre << endl;
    //    cout << "Apellidos:" << segundo.apellidos << endl;
    //    cout << "Carrera:" << segundo.carrera << endl;
    return 0;
}