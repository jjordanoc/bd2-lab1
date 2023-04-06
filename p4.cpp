#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

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
        Matricula result;
        if (infile.is_open() && headerFile.is_open()) {
            headerFile.seekg(pos * sizeof(int));
            int recordPos;
            headerFile.read((char *) &recordPos, sizeof(int));
            infile.seekg(recordPos);
            infile >> result;
            infile.close();
            headerFile.close();
        } else {
            cerr << "No se pudo abrir el archivo\n";
        }
        return result;
    }
};

int main() {
    BinaryVariableRecord binaryVariableRecord("../binary-variable.bin", "../binary-variable-header.bin");
    binaryVariableRecord.add(Matricula("0001", 1, 5500.5, "Es alto"));
    binaryVariableRecord.add(Matricula("0002", 3, 55000.610, "Es muy alto"));
    binaryVariableRecord.add(Matricula("0003", 5, -3.14159265, "Es mas alto que el monte everest"));
    auto res = binaryVariableRecord.load();
    for (const auto &m: res) {
        cout << "codigo: " << m.codigo << endl;
        cout << "ciclo: " << m.ciclo << endl;
        cout << "mensualidad: " << m.mensualidad << endl;
        cout << "observaciones: " << m.observaciones << endl;
    }
    // read 2nd record in O(1) time
    auto m = binaryVariableRecord.readRecord(1);
    cout << "codigo: " << m.codigo << endl;
    cout << "ciclo: " << m.ciclo << endl;
    cout << "mensualidad: " << m.mensualidad << endl;
    cout << "observaciones: " << m.observaciones << endl;
}