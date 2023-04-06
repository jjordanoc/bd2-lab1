#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

struct Position{
    char posicion[5];
    char tamano[5];
};

class Header{
    string filename;


public:
    Header(const string &filename) : filename(filename) {}

    void add(Position newPosition){
        ofstream file;
        file.open(filename, ios::app);
        if(file.is_open()){
            file << newPosition.posicion << " ";
            file << newPosition.tamano << " ";
            file << "\n";
            file << flush;
            file.close();
        }
        else{
            cerr << "No se pudo abrir el archivo\n";
        }
    }

    Position readRecord(int pos){
        ifstream infile(filename);
        Position readPosition;
        if(infile.is_open()){
            infile.seekg(pos * sizeof(Position) + 2 * pos);
            infile.read(readPosition.posicion, 5);
            readPosition.posicion[4] = '\0';
            infile.read(readPosition.tamano, 5);
            readPosition.tamano[4] = '\0';
            infile.close();

        }
        else{
            cerr << "No se pudo abrir el archivo\n";
        }

        return readPosition;
    }
};


struct Alumno
{
    string nombre;
    string apellidos;
    string carrera;
    float mensualidad;

    size_t recordSize(){
        return size(nombre) + size(apellidos) + size(carrera) + sizeof(mensualidad) + 7;
    }
};

void readFromConsole(char buffer[], int size) {
    string temp;
    cin >> temp;
    for (int i = 0; i < size; i++)
        buffer[i] = (i < temp.size()) ? temp[i] : ' ';
    buffer[size - 1] = '\0';
    cin.clear();
}

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

    void add(Alumno record){
        Header header("../header2.txt");
        ofstream file;
        file.open(filename, ios::app);

        if(file.is_open()){
            file << record.nombre << "|";
            file << record.apellidos << "|";
            file << record.carrera << "|";
            file << float(record.mensualidad+0.00) << "\n";
            file.close();

            int recordLength = record.recordSize();
            string newTamano = to_string(recordLength);

            // get the last tamano of a register in header2.txt
            ifstream file;
            file.open("../header2.txt");
            file.seekg(-12,ios::end);
            Position newPos;
            file.read(newPos.posicion,5);
            newPos.posicion[4] = '\0';
            file.read(newPos.tamano, 5);
            newPos.tamano[4] = '\0';
            file.close();


            string newPosicion = to_string(stoi(newPos.posicion) + stoi(newPos.tamano));

            for(int i = 0; i < 4; ++i){
                newPos.posicion[i] = ' ';
                newPos.tamano[i] = ' ';
            }

            for(int i = 0; i < size(newPosicion); ++i){
                newPos.posicion[i] = newPosicion[i];
            }

            for(int i = 0; i < size(newTamano); ++i){
                newPos.tamano[i] = newTamano[i];
            }

            newPos.posicion[4] = '\0';
            newPos.tamano[4] = '\0';

            header.add(newPos);

        }
        else{
            cerr << "No se pudo abrir el archivo\n";
        }

    }

    Alumno readRecord(int pos){
        Header header("../header2.txt");
        ifstream file("../datos2.txt");
        Position readPosition;
        Alumno readStudent;

        if(file.is_open()){
            readPosition = header.readRecord(pos);
            file.seekg(stof(readPosition.posicion) + pos);
            getline(file, readStudent.nombre, '|');
            getline(file, readStudent.apellidos, '|');
            getline(file, readStudent.carrera, '|');
            string mensualidadStr;
            getline(file, mensualidadStr, '\n');
            readStudent.mensualidad = stof(mensualidadStr);

            file.close();
        }
        else{
            cerr << "No se pudo abrir el archivo\n";
        }

        return readStudent;
    }
};


int main() {
    VariableRecord variableRecord("../datos2.txt");
    Header header("../header2.txt");

    bool flag = true;

    while(flag){

        cout << "=====================\n";
        cout << "load(l)\n";
        cout << "read(r)\n";
        cout << "add(a)\n";
        cout << "exit(e)\n";
        char op;
        cout << "elige operacion: ";
        cin >> op;
        if (op == 'l') {
            vector<Alumno> alumnos = variableRecord.load();
            for(const auto alumno: alumnos){
                cout << alumno.nombre << endl;
                cout << alumno.apellidos << endl;
                cout << alumno.carrera << endl;
                cout << alumno.mensualidad << endl;
            }
        } else if (op == 'r') {
            int pos;
            cout << "Inserte posicion del alumno: ";
            cin >> pos;
            Alumno alumno = variableRecord.readRecord(pos);
            cout << alumno.nombre << endl;
            cout << alumno.apellidos << endl;
            cout << alumno.carrera << endl;
            cout << alumno.mensualidad << endl;
        } else if (op == 'a'){

            Alumno alumno;
            cout << "Nombre: "; cin >> alumno.nombre;
            cout << "Apellidos: "; cin >> alumno.apellidos;
            cout << "Carrera: "; cin >> alumno.carrera;
            cout << "Mensualidad: "; cin >> alumno.mensualidad;
            alumno.mensualidad = float(alumno.mensualidad/1.0 + 0.01);

            variableRecord.add(alumno);

        } else if (op == 'e'){
            flag = false;
        }
    }

}