#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Matricula {
    string codigo;
    int ciclo;
    float mensualidad;
    string observaciones;

    Matricula() {}

    Matricula(const string &codigo, int ciclo, float mensualidad, const string &observaciones) : codigo(codigo), ciclo(ciclo), mensualidad(mensualidad), observaciones(observaciones) {}

    size_t recordSize() {
        return sizeof(codigo.length()) + sizeof(string) + sizeof(int) + sizeof(float) + sizeof(observaciones.length()) + sizeof(string);
    }

    char *zip() {
        char *buffer = new char[recordSize()];
//        int i;
        char *tmpPtr = buffer;
        auto codigoLength = codigo.length();
//        i = sprintf_s(buffer, sizeof(codigoLength), "%s", (char *) &codigoLength);
        sprintf_s(tmpPtr, codigoLength, "%s", (char *) codigo.c_str());
        tmpPtr += codigoLength;
        sprintf_s(tmpPtr, sizeof(int), "%s", (char *) &ciclo);
        tmpPtr += sizeof(int);
        sprintf_s(tmpPtr, sizeof(float), "%s", (char *) &mensualidad);
        tmpPtr += sizeof(float);
        auto observacionesLength = observaciones.length();
        sprintf_s(tmpPtr, sizeof(observacionesLength), "%s", (char *) &observacionesLength);
        tmpPtr += sizeof(observacionesLength);
        sprintf_s(tmpPtr, observacionesLength, "%s", (char *) observaciones.c_str());
//        cout << "i:" << i << endl;
//        printf_s( "Output:\n%s\ncharacter count = %d\n", buffer, i);
        return buffer;
    }

    void unzip(char *zippedRecord, size_t zippedRecordSize) {
        int i;
        size_t codigoLength;
        i = sprintf_s((char *) &codigoLength, sizeof(codigoLength), "%s", zippedRecord);
        char *codigoBuffer = new char[codigoLength];
        i += sprintf_s(codigoBuffer, codigoLength, "%s", zippedRecord + i);
        codigo = codigoBuffer;
    }
};

class BinaryVariableRecord {
    string filename;

public:
    BinaryVariableRecord(const string &filename) : filename(filename) {}
    vector<Matricula> load() {
        vector<Matricula> result;
        ifstream infile(filename, ios::binary);
    }
};

int main() {
    Matricula matricula("0001", 1, 5500.2, "Es alto");
    char *zip = matricula.zip();
    for (int i = 0; i < matricula.recordSize(); ++i) {
        cout << zip[i];
    }
    cout << endl << matricula.recordSize();
    Matricula matricula2;
    matricula2.unzip(zip, matricula.recordSize());
    cout << "codigo:" << matricula2.codigo << endl;
}