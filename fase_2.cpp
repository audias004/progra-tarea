#include <iostream>
#include <map>
#include <sstream>
#include <string>

using namespace std;

// Función para traducir una línea de código según el diccionario
string traducirLinea(const string& linea, const map<string, string>& diccionario) {
    stringstream ss(linea);
    string palabra, traduccion, resultado;
    while (ss >> palabra) {
        // Reemplazar la palabra según el diccionario, si está definida
        if (diccionario.count(palabra)) {
            traduccion = diccionario.at(palabra);
        } else {
            traduccion = palabra;
        }
        resultado += traduccion + " ";
    }
    return resultado;
}

int main() {
    // Definir el diccionario con las palabras a traducir
    map<string, string> diccionario = {
        {"int", "entero"},
        {"string", "cadena"},
        {"cout", "cout"},
        {"cin", "cin"},
        {"if", "si"},
        {"else", "entonces"},
        {"exit", "salir"},
        {"return", "retorno"}
    };

    // Leer el texto multilínea
    string linea, codigo;
    cout << "Ingrese el código C++ (termine con una línea en blanco):\n";
    while (getline(cin, linea) && !linea.empty()) {
        codigo += linea + "\n";
    }

    // Traducir y mostrar el código línea por línea
    stringstream codigoTraducido;
    stringstream ss(codigo);
    while (getline(ss, linea)) {
        codigoTraducido << traducirLinea(linea, diccionario) << endl;
    }

    // Imprimir el código traducido
    cout << "Código traducido:\n" << codigoTraducido.str();

    return 0;
}
