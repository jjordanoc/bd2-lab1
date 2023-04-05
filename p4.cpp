#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include  <sstream>
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
        return sizeof(codigo.length() + 1) + sizeof(string) + sizeof(int) + sizeof(float) + sizeof(observaciones.length() + 1) + sizeof(string);
    }

    char *zip() {
        char *buffer = new char[recordSize()];
//        ostringstream outStringStream(buffer, ios::binary);
//        cout << "pos:" << outStringStream.tellp() << endl;
//        auto codigoLength = codigo.length();
//        outStringStream.write((char *) &codigoLength, sizeof(codigoLength));
//        outStringStream.write(codigo.c_str(), codigoLength + 1);
//        outStringStream.write((char *) &ciclo, sizeof(int));
//        outStringStream.write((char *) &mensualidad, sizeof(float));
//        auto observacionesLength = observaciones.length();
//        outStringStream.write((char *) &observacionesLength, sizeof(observacionesLength));
//        outStringStream.write(observaciones.c_str(), observacionesLength + 1);
//        cout << "pos:" << outStringStream.tellp() << endl;
//        int i;
        char *tmpPtr = buffer;
        string::size_type codigoLength = codigo.length();
        sprintf_s(tmpPtr, sizeof(codigoLength), "%s", (char *) &codigoLength);
        tmpPtr += sizeof(codigoLength);
        sprintf_s(tmpPtr, codigoLength + 1, "%s", (char *) codigo.c_str());
        tmpPtr += codigoLength + 1;
        sprintf_s(tmpPtr, sizeof(int), "%s", (char *) &ciclo);
        tmpPtr += sizeof(int);
        sprintf_s(tmpPtr, sizeof(float) , "%s", (char *) &mensualidad);
        tmpPtr += sizeof(float);
        auto observacionesLength = observaciones.length();
        sprintf_s(tmpPtr, sizeof(observacionesLength), "%s", (char *) &observacionesLength);
        tmpPtr += sizeof(observacionesLength);
        sprintf_s(tmpPtr, observacionesLength + 1, "%s", (char *) observaciones.c_str());
//        cout << "i:" << i << endl;
//        printf_s( "Output:\n%s\ncharacter count = %d\n", buffer, i);
        return buffer;
    }

    void unzip(char *zippedRecord, size_t zippedRecordSize) {
        istringstream strbuff(zippedRecord);
        string::size_type codigoLength;
        strbuff.read((char *) &codigoLength, sizeof(codigoLength));
        cout << codigoLength << endl;
        char *codigoBuffer = new char[codigoLength+1];
        strbuff.read(codigoBuffer, codigoLength + 1);
        codigoBuffer[codigoLength] = 0;
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