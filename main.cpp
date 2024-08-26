#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Función para leer el archivo de resultados
vector<string> readResultFile(const string& filename) {
    vector<string> lines;
    ifstream file(filename);
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    } else {
        cerr << "No se pudo abrir el archivo: " << filename << endl;
    }

    return lines;
}

// Función para escribir en archivo binario
void writeToBinaryFile(const vector<string>& lines, const string& filename) {
    ofstream file(filename, ios::binary);

    if (file.is_open()) {
        for (const auto& line : lines) {
            size_t length = line.length();
            file.write(reinterpret_cast<const char*>(&length), sizeof(length));
            file.write(line.c_str(), length);
        }
        file.close();
    } else {
        cerr << "No se pudo crear el archivo binario: " << filename << endl;
    }
}

// Función para leer y mostrar el archivo binario
void readAndDisplayBinaryFile(const string& filename) {
    ifstream file(filename, ios::binary);

    if (file.is_open()) {
        while (file.peek() != EOF) {
            size_t length;
            file.read(reinterpret_cast<char*>(&length), sizeof(length));

            string line(length, '\0');
            file.read(&line[0], length);

            cout << line << endl;
        }
        file.close();
    } else {
        cerr << "No se pudo abrir el archivo binario: " << filename << endl;
    }
}

int main() {
    string resultFileName = "result_output.txt";
    string binaryFileName = "result_output.bin";

    // 1. Leer el archivo de resultados
    vector<string> resultLines = readResultFile(resultFileName);

    // 2. Escribir en archivo binario
    writeToBinaryFile(resultLines, binaryFileName);

    // 3. Leer y mostrar el archivo binario
    cout << "Contenido del archivo binario:" << endl;
    readAndDisplayBinaryFile(binaryFileName);

    return 0;
}