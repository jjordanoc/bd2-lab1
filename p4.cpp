#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
bool read;

struct Matricula {
    string codigo;
    int ciclo;
    float mensualidad;
    string observaciones;

    Matricula() = default;

    Matricula(const string &codigo, int ciclo, float mensualidad, const string &observaciones) : codigo(codigo), ciclo(ciclo), mensualidad(mensualidad), observaciones(observaciones) {}
};


ostream &operator<<(ostream &stream, Matricula &m) {
    // codigo
    int codigoLength = m.codigo.length();
    stream.write((char *) &codigoLength, sizeof(int));
    stream.write(m.codigo.c_str(), codigoLength);
    // ciclo
    stream.write((char *) &m.ciclo, sizeof(int));
    // mensualidad
    stream.write((char *) &m.mensualidad, sizeof(float));
    // observaciones
    int observacionesLength = m.observaciones.length();
    stream.write((char *) &observacionesLength, sizeof(int));
    stream.write(m.observaciones.c_str(), observacionesLength);
    return stream;
}

istream &operator>>(istream &stream, Matricula &m) {
    // codigo
    int codigoLength;
    stream.read((char *) &codigoLength, sizeof(int));
    if (stream.eof()) return stream;
    char codigoBuff[codigoLength + 1];
    stream.read(codigoBuff, codigoLength);
    codigoBuff[codigoLength] = '\0';
    m.codigo = codigoBuff;
    // ciclo
    stream.read((char *) &m.ciclo, sizeof(int));
    // mensualidad
    stream.read((char *) &m.mensualidad, sizeof(float));
    // observaciones
    int observacionesLength;
    stream.read((char *) &observacionesLength, sizeof(int));
    char observacionesBuff[observacionesLength + 1];
    stream.read(observacionesBuff, observacionesLength);
    observacionesBuff[observacionesLength] = '\0';
    m.observaciones = observacionesBuff;
    return stream;
}

class BinaryVariableRecord {
    string filename;
    string headerFilename;

public:
    BinaryVariableRecord(const string &filename, const string &headerFilename) : filename(filename), headerFilename(headerFilename) {}
    vector<Matricula> load() {
        vector<Matricula> result;
        ifstream infile(filename, ios::binary);
        if (infile.is_open()) {
            while (!infile.eof()) {
                Matricula tmp;
                infile >> tmp;
                if (!infile.eof()) {
                    result.push_back(tmp);
                }
            }
            infile.close();
        } else {
            cerr << "No se pudo abrir el archivo\n";
        }
        return result;
    }
    void add(Matricula record) {
        ofstream outfile(filename, ios::binary | ios::app | ios::ate);
        ofstream headerFile(headerFilename, ios::binary | ios::app);
        if (outfile.is_open() && headerFile.is_open()) {
            int recordPos = outfile.tellp();
            outfile << record;
            headerFile.write((char *) &recordPos, sizeof(int));
            outfile.close();
            headerFile.close();
        } else {
            cerr << "No se pudo abrir el archivo\n";
        }
    }

    Matricula readRecord(int pos) {
        ifstream infile(filename, ios::binary);
        ifstream headerFile(headerFilename, ios::binary);
        read = true;
        Matricula result;
        if (infile.is_open() && headerFile.is_open()) {
            headerFile.seekg(pos * sizeof(int));
            int recordPos;
            headerFile.read((char *) &recordPos, sizeof(int));
            if (headerFile.tellg() != -1) {
                infile.seekg(recordPos);
                infile >> result;
            } else {
                cerr << "No se puede acceder a esa posicion\n";
                read = false;
            }
            infile.close();
            headerFile.close();
        } else {
            cerr << "No se pudo abrir el archivo\n";
        }
        return result;
    }
};

void menu(){
    BinaryVariableRecord binaryVariableRecord("../binary-variable.bin", "../binary-variable-header.bin");
    bool exit = false;
    while(!exit) {
        cout << "load(l)\n";
        cout << "read(r)\n";
        cout << "add(a)\n";
        cout << "exit(e)\n";
        char op;
        cout << "elige operacion: ";
        cin >> op;
        if (op == 'l') {
            vector<Matricula> matriculas = binaryVariableRecord.load();
            for (const auto &m: matriculas) {
                cout << "codigo: " << m.codigo << endl;
                cout << "ciclo: " << m.ciclo << endl;
                cout << "mensualidad: " << m.mensualidad << endl;
                cout << "observaciones: " << m.observaciones << endl;
            }
        } else if (op == 'r') {
            int pos;
            cout << "pos: ";
            cin >> pos;
            auto m = binaryVariableRecord.readRecord(pos);
            if (read) {
                cout << "codigo: " << m.codigo << endl;
                cout << "ciclo: " << m.ciclo << endl;
                cout << "mensualidad: " << m.mensualidad << endl;
                cout << "observaciones: " << m.observaciones << endl;
            }

        } else if (op == 'a'){
            Matricula matricula;
            cout << "codigo: "; cin >> matricula.codigo;
            cout << "ciclo: "; cin >> matricula.ciclo;
            cout << "mensualidad: "; cin >> matricula.mensualidad;
            cout << "observaciones: "; cin.ignore();
            getline(cin, matricula.observaciones);
            binaryVariableRecord.add(matricula);
        } else if (op == 'e'){
            exit = true;
        }
    }

}

int main() {
    menu();
}