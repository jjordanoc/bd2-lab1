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
        outFile.open(filename, ios::app | ios::binary);
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
            infile.seekg(pos * sizeof(tmp));
            infile >> tmp;
        } else {
            cerr << "No se pudo abrir el archivo\n";
        }
        return tmp;
    }
};

int main() {
}