#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

struct Alumno
{
    string nombre;
    string apellidos;
    string carrera;
    float mensualidad;
};


class VariableRecord {
    string filename;

public:
    VariableRecord(const string &filename) : filename(filename) {}
    vector<Alumno> load() {
        vector<Alumno> alumnos;
        ifstream infile(filename);
        if (infile.is_open()) {
            string line;
            while (!infile.eof()) {
                Alumno alumno;
                getline(infile, alumno.nombre, '|');
                getline(infile, alumno.apellidos, '|');
                getline(infile, alumno.carrera, '|');
                string mensualidadStr;
                getline(infile, mensualidadStr, '\n');
                if (!infile.eof()) {
                    alumno.mensualidad = stof(mensualidadStr);
                    alumnos.push_back(alumno);
                }

            }

        } else {
            cerr << "No se pudo abrir el archivo\n";
        }
        return alumnos;
    }
};

int main() {
    VariableRecord variableRecord("../datos2.txt");
    auto alumnos = variableRecord.load();
    for (auto &a : alumnos) {
        cout << a.nombre << endl;
        cout << a.apellidos << endl;
        cout << a.carrera << endl;
        cout << a.mensualidad << endl;
    }
}