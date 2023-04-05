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

    ostringstream zip() {
        char *charBuf = new char[recordSize()];
        ostringstream buffer(charBuf, ios::binary);
        cout << "pos:" << buffer.tellp() << endl;
        string::size_type codigoLength = codigo.length();
        buffer.write((char *) &codigoLength, sizeof(codigoLength));
        cout << "content: " << buffer.str() << endl;
        buffer.write(codigo.c_str(), codigoLength + 1);
        cout << "content: " << buffer.str() << endl;
        buffer.write((char *) &ciclo, sizeof(int));
        cout << "content: " << buffer.str() << endl;
        buffer.write((char *) &mensualidad, sizeof(float));
        cout << "content: " << buffer.str() << endl;
        string::size_type observacionesLength = observaciones.length();
        buffer.write((char *) &observacionesLength, sizeof(observacionesLength));
        cout << "content: " << buffer.str() << endl;
        buffer.write(observaciones.c_str(), observacionesLength + 1);
        cout << "content: " << buffer.str() << endl;
        cout << "pos:" << buffer.tellp() << endl;
        cout << "real size:" << recordSize() << endl;
//        int i;
//        char *tmpPtr = buffer;
//        string::size_type codigoLength = codigo.length();
//        cout << "wrote: " << sprintf_s(tmpPtr, sizeof(codigoLength), "%s", (char *) &codigoLength) << endl;
//        cout << "content: "<< tmpPtr << endl;
//        tmpPtr += sizeof(codigoLength);
//        cout << "wrote: " << sprintf_s(tmpPtr, codigoLength + 1, "%s", (char *) codigo.c_str())<< endl;
//        cout << "content: "<< tmpPtr << endl;
//        tmpPtr += codigoLength + 1;
//        cout << "wrote: " << sprintf_s(tmpPtr, sizeof(int), "%s", (char *) &ciclo)<< endl;
//        cout << "content: "<< tmpPtr << endl;
//        tmpPtr += sizeof(int);
//        cout << "wrote: " << sprintf_s(tmpPtr, sizeof(float) , "%s", (char *) &mensualidad)<< endl;
//        cout << "content: "<< tmpPtr << endl;
//        tmpPtr += sizeof(float);
//        auto observacionesLength = observaciones.length();
//        cout << "wrote: " << sprintf_s(tmpPtr, sizeof(observacionesLength), "%s", (char *) &observacionesLength)<< endl;
//        cout << "content: "<< tmpPtr << endl;
//        tmpPtr += sizeof(observacionesLength);
//        cout << "wrote: " << sprintf_s(tmpPtr, observacionesLength + 1, "%s", (char *) observaciones.c_str())<< endl;
//        cout << "content: "<< tmpPtr << endl;
//        cout << "i:" << i << endl;
//        printf_s( "Output:\n%s\ncharacter count = %d\n", buffer, i);
        return buffer;
    }

    void unzip(char *packedRegister) {
//        char *charBuf = new char[recordSize()];
        istringstream buffer(packedRegister, ios::binary);
        cout << packedRegister << endl;
        buffer.seekg(0);
        string::size_type codigoLength;
        cout << buffer.tellg() << endl;
        buffer.read((char *) &codigoLength, sizeof(codigoLength));
//        buffer.seekg(sizeof(codigoLength) + 1);
        cout << "codigo length: "<< codigoLength << endl;
        cout << buffer.tellg() << endl;
        char *codigoBuffer = new char[codigoLength+1];
        buffer.read(codigoBuffer, codigoLength);
        cout << buffer.tellg() << endl;
        codigoBuffer[codigoLength] = 0;
        cout <<"codigo buffer: "<< codigoBuffer << endl;
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
    auto zip = matricula.zip();
    cout << zip.str() << endl;
    cout << endl << matricula.recordSize() << endl;
    Matricula matricula2;
    auto tmp = zip.str();
    char *c = (char *) tmp.c_str();
    matricula2.unzip(c);
    cout << "codigo:" << matricula2.codigo << endl;
}