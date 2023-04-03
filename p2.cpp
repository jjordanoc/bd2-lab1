#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
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
    stream << flush;
    return stream;
}

istream &operator>>(istream &stream, Alumno &p) {
    stream.read((char *) &p, sizeof(p));
    return stream;
}

class FixedRecord {
    string filename;

public:
    FixedRecord(const string &filename) : filename(filename) {
        ofstream createFile;
        createFile.open(filename, ios::binary | ios::app);
        createFile.close();
        ifstream infile;
        infile.open(filename, ios::binary);

        if (infile.is_open()) {
            infile.seekg(0);
            Alumno header;
            infile >> header;
            if (strcmp(header.codigo, "xxxx") != 0) {
                infile.close();
                ofstream outfile;
                outfile.open(filename, ios::binary | ios::app);
                for (int i = 0; i < 4; ++i) {
                    header.codigo[i] = 'x';
                }
                header.codigo[4] = '\0';
                header.del = -1;
                outfile << header;
                outfile.close();
            }
            else {
                infile.close();
            }
        } else {
            cerr << "No se pudo abrir el archivo\n";
        }
    }


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
            file.seekg(0);
            Alumno header;
            file >> header;
            if (header.del != -1) {
                int lastDeletedPos = header.del;
                file.seekg(lastDeletedPos * sizeof(Alumno));
                Alumno lastDeletedRegister;
                file >> lastDeletedRegister;
                header.del = lastDeletedRegister.del;
                file.seekp(0);
                file << header;
                file.seekp(lastDeletedPos * sizeof(Alumno));
            } else {
                file.seekp(0, ios::end);
            }
            file << record;
            file.close();

        } else {
            cerr << "No se pudo abrir el archivo\n";
        }
    }

    Alumno readRecord(int pos) {
        ifstream infile(filename, ios::binary);
        Alumno tmp;
        if (infile.is_open()) {
            infile.seekg(pos * sizeof(Alumno));
            infile >> tmp;
            infile.close();
        } else {
            cerr << "No se pudo abrir el archivo\n";
        }
        return tmp;
    }

    bool deleteRecord(int pos) {
        if (pos <= 0) return false;
        fstream file(filename, ios::in | ios::out | ios::ate | ios::binary);
        if (file.is_open()) {
            file.seekg(0);
            Alumno header;
            file >> header;
            file.seekp(pos * sizeof(Alumno));
            file << header;
            file.seekp(0);
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
    FixedRecord fixedRecord("../datos5.bin");
//    for (int i = 0; i < 2; ++i) {
//        Alumno alumno;
//        cout << "Codigo: ";
//        readFromConsole(alumno.codigo, 5);
//        cout << "Nombre: ";
//        readFromConsole(alumno.nombre, 11);
//        cout << "Apellidos: ";
//        readFromConsole(alumno.apellidos, 20);
//        cout << "Carrera: ";
//        readFromConsole(alumno.carrera, 15);
//        cout << "Ciclo: ";
//        cin >> alumno.ciclo;
//        cout << "Mensualidad: ";
//        cin >> alumno.mensualidad;
//        fixedRecord.add(alumno);
//    }
    vector<Alumno> alumnos = fixedRecord.load();
    for (auto &tmp: alumnos) {
        cout << "Codigo:" << tmp.codigo << endl;
        cout << "Nombre:" << tmp.nombre << endl;
        cout << "Apellidos:" << tmp.apellidos << endl;
        cout << "Carrera:" << tmp.carrera << endl;
        cout << "Ciclo:" << tmp.ciclo << endl;
        cout << "Mensualidad:" << tmp.mensualidad << endl;
        cout << "Del:" << tmp.del << endl;
    }
    Alumno primero = fixedRecord.readRecord(1);
    cout << "Codigo:" << primero.codigo << endl;
    cout << "Nombre:" << primero.nombre << endl;
    cout << "Apellidos:" << primero.apellidos << endl;
    cout << "Carrera:" << primero.carrera << endl;
    cout << "Ciclo:" << primero.ciclo << endl;
    cout << "Mensualidad:" << primero.mensualidad << endl;
    cout << "Del:" << primero.del << endl;
    return 0;
}