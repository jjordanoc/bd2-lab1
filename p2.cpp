#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;
bool read;


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
                if (!infile.eof() and strcmp(tmp.codigo, "xxxx") != 0) {
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
        read = true;
        if (infile.is_open()) {
            infile.seekg(pos * sizeof(Alumno));
            infile >> tmp;
            if (infile.tellg() == -1 or strcmp(tmp.codigo, "xxxx") == 0) {
                cerr << "No se puede acceder a esa posicion\n";
                read = false;
            }
            infile.close();
        } else {
            cerr << "No se pudo abrir el archivo\n";
        }
        return tmp;
    }

    bool deleteRecord(int pos) {
        if (pos <= 0) {
            cerr << "No es posible eliminar esa posicion\n";
            return false;
        }
        fstream file(filename, ios::in | ios::out | ios::ate | ios::binary);
        if (file.is_open()) {
            file.seekg(0);
            Alumno header;
            file >> header;
            file.seekp(pos * sizeof(Alumno));
            Alumno tmp;
            file >> tmp;
            file.seekp(pos * sizeof(Alumno));
            if (file.tellp() == -1 or strcmp(tmp.codigo, "xxxx") == 0) {
                cerr << "No es posible eliminar esa posicion\n";
            } else {
                file << header;
                file.seekp(0);
                Alumno newHeader;
                for (int i = 0; i < 4; ++i) {
                    newHeader.codigo[i] = 'x';
                }
                newHeader.codigo[4] = '\0';
                newHeader.del = pos;
                file << newHeader;
            }
            file.close();
        } else {
            cerr << "No se pudo abrir el archivo\n";
        }
        return true;
    }
};

void menu(){
    FixedRecord fixedRecord("../datos5.bin");
    bool exit = false;
    while(!exit) {
        cout << "load(l)\n";
        cout << "read(r)\n";
        cout << "add(a)\n";
        cout << "delete(d)\n";
        cout << "exit(e)\n";
        char op;
        cout << "elige operacion: ";
        cin >> op;
        if (op == 'l') {
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
        } else if (op == 'r') {
            int pos;
            cout << "pos: ";
            cin >> pos;
            Alumno alumno = fixedRecord.readRecord(pos);
            if (read) {
                cout << "Codigo:" << alumno.codigo << endl;
                cout << "Nombre:" << alumno.nombre << endl;
                cout << "Apellidos:" << alumno.apellidos << endl;
                cout << "Carrera:" << alumno.carrera << endl;
                cout << "Ciclo:" << alumno.ciclo << endl;
                cout << "Mensualidad:" << alumno.mensualidad << endl;
                cout << "Del:" << alumno.del << endl;
            }

        } else if (op == 'a'){
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
        } else if (op == 'd') {
            cout << "pos: ";
            int pos;
            cin >> pos;
            fixedRecord.deleteRecord(pos);
        } else if (op == 'e'){
            exit = true;
        }
    }
}

int main() {
    menu();
    return 0;
}