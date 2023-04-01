#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct Alumno {
    char codigo[5];
    char nombre[11];
    char apellidos[20];
    char carrera[15];
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
    stream << p.codigo << " ";
    stream << p.nombre << " ";
    stream << p.apellidos << " ";
    stream << p.carrera << " ";
    stream << "\n";
    stream << flush;
    return stream;
}

istream &operator>>(istream &stream, Alumno &p) {
    stream.read(p.codigo, 5);
    p.codigo[4] = '\0';
    stream.read(p.nombre, 11);
    p.nombre[10] = '\0';
    stream.read(p.apellidos, 20);
    p.apellidos[19] = '\0';
    stream.read(p.carrera, 15);
    p.carrera[14] = '\0';
    stream.get();
    return stream;
}

class FixedRecord {
    string filename;

public:
    FixedRecord(const string &filename) : filename(filename) {}


    vector<Alumno> load() {
        ifstream infile;
        infile.open(filename);
        vector<Alumno> alumnos;

        if (infile.is_open()) {
            while (!infile.eof()) {
                Alumno tmp;
                infile >> tmp;
                alumnos.push_back(tmp);
            }
            infile.close();
        } else {
            cerr << "No se pudo abrir el archivo\n";
        }
        return alumnos;
    }

    void add(Alumno record) {
        ofstream outFile;
        outFile.open(filename, ios::app);
        if (outFile.is_open()) {
            outFile << record;
            outFile.close();

        } else {
            cerr << "No se pudo abrir el archivo\n";
        }
    }

    Alumno readRecord(int pos) {
        ifstream infile(filename);
        Alumno tmp;
        if (infile.is_open()) {
            infile.seekg(pos * sizeof(Alumno));
            infile >> tmp;
        } else {
            cerr << "No se pudo abrir el archivo\n";
        }
        return tmp;
    }
};


int main() {
    FixedRecord fixedRecord("../datos1.txt");
    vector<Alumno> alumnos = fixedRecord.load();
    for (auto &tmp: alumnos) {
        cout << "Codigo:" << tmp.codigo << endl;
        cout << "Nombre:" << tmp.nombre << endl;
        cout << "Apellidos:" << tmp.apellidos << endl;
        cout << "Carrera:" << tmp.carrera << endl;
    }
        Alumno alumno;
        cout << "Codigo: ";
        readFromConsole(alumno.codigo, 5);
        cout << "Nombre: ";
        readFromConsole(alumno.nombre, 11);
        cout << "Apellidos: ";
        readFromConsole(alumno.apellidos, 20);
        cout << "Carrera: ";
        readFromConsole(alumno.carrera, 15);
        fixedRecord.add(alumno);
        Alumno segundo = fixedRecord.readRecord(1);
        cout << "Codigo:" << segundo.codigo << endl;
        cout << "Nombre:" << segundo.nombre << endl;
        cout << "Apellidos:" << segundo.apellidos << endl;
        cout << "Carrera:" << segundo.carrera << endl;
    return 0;
}
