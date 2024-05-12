#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Estructura para representar una palabra con su traducción y funcionalidad
struct Palabra {
    string palabra;
    string traduccion;
    string funcionalidad;
};

// Función para agregar una nueva palabra al archivo
void agregarPalabra(const Palabra& nuevaPalabra, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo, ios::app);
    if (archivo.is_open()) {
        archivo << nuevaPalabra.palabra << "," << nuevaPalabra.traduccion << "," << nuevaPalabra.funcionalidad << endl;
        archivo.close();
        cout << "Palabra agregada correctamente." << endl;
    } else {
        cerr << "Error al abrir el archivo." << endl;
    }
}

// Función para leer todas las palabras desde el archivo
vector<Palabra> leerPalabras(const string& nombreArchivo) {
    vector<Palabra> palabras;
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            size_t pos1 = linea.find(",");
            size_t pos2 = linea.find(",", pos1 + 1);
            string palabra = linea.substr(0, pos1);
            string traduccion = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            string funcionalidad = linea.substr(pos2 + 1);
            palabras.push_back({palabra, traduccion, funcionalidad});
        }
        archivo.close();
    } else {
        cerr << "Error al abrir el archivo." << endl;
    }
    return palabras;
}

// Función para actualizar una palabra en el archivo
void actualizarPalabra(const Palabra& palabraActualizada, const string& nombreArchivo) {
    vector<Palabra> palabras = leerPalabras(nombreArchivo);
    ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        for (const Palabra& p : palabras) {
            if (p.palabra == palabraActualizada.palabra) {
                archivo << palabraActualizada.palabra << "," << palabraActualizada.traduccion << "," << palabraActualizada.funcionalidad << endl;
            } else {
                archivo << p.palabra << "," << p.traduccion << "," << p.funcionalidad << endl;
            }
        }
        archivo.close();
        cout << "Palabra actualizada correctamente." << endl;
    } else {
        cerr << "Error al abrir el archivo." << endl;
    }
}

// Función para eliminar una palabra del archivo
void eliminarPalabra(const string& palabraEliminar, const string& nombreArchivo) {
    vector<Palabra> palabras = leerPalabras(nombreArchivo);
    ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        for (const Palabra& p : palabras) {
            if (p.palabra != palabraEliminar) {
                archivo << p.palabra << "," << p.traduccion << "," << p.funcionalidad << endl;
            }
        }
        archivo.close();
        cout << "Palabra eliminada correctamente." << endl;
    } else {
        cerr << "Error al abrir el archivo." << endl;
    }
}

// Función para imprimir una palabra
void imprimirPalabra(const Palabra& p) {
    cout << "Palabra: " << p.palabra << endl;
    cout << "Traducción: " << p.traduccion << endl;
    cout << "Funcionalidad: " << p.funcionalidad << endl;
}

// Función principal
int main() {
    const string nombreArchivo = "palabras.txt";
    vector<Palabra> palabras;

    // Leer palabras desde el archivo
    palabras = leerPalabras(nombreArchivo);

    // Menú de opciones
    int opcion;
    do {
        cout << "\nSeleccione una opción:" << endl;
        cout << "1. Agregar palabra" << endl;
        cout << "2. Actualizar palabra" << endl;
        cout << "3. Eliminar palabra" << endl;
        cout << "4. Mostrar todas las palabras" << endl;
        cout << "0. Salir" << endl;
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer del salto de línea

        switch (opcion) {
            case 1: {
                Palabra nuevaPalabra;
                cout << "Ingrese la palabra: ";
                getline(cin, nuevaPalabra.palabra);
                cout << "Ingrese la traducción: ";
                getline(cin, nuevaPalabra.traduccion);
                cout << "Ingrese la funcionalidad: ";
                getline(cin, nuevaPalabra.funcionalidad);
                agregarPalabra(nuevaPalabra, nombreArchivo);
                break;
            }
            case 2: {
                string palabraActualizar;
                cout << "Ingrese la palabra que desea actualizar: ";
                getline(cin, palabraActualizar);
                Palabra palabraActualizada;
                cout << "Ingrese la nueva traducción: ";
                getline(cin, palabraActualizada.traduccion);
                cout << "Ingrese la nueva funcionalidad: ";
                getline(cin, palabraActualizada.funcionalidad);
                actualizarPalabra(palabraActualizada, nombreArchivo);
                break;
            }
            case 3: {
                string palabraEliminar;
                cout << "Ingrese la palabra que desea eliminar: ";
                getline(cin, palabraEliminar);
                eliminarPalabra(palabraEliminar, nombreArchivo);
                break;
            }
            case 4: {
                for (const Palabra& p : palabras) {
                    imprimirPalabra(p);
                    cout << endl;
                }
                break;
            }
            case 0: {
                cout << "Saliendo del programa..." << endl;
                break;
            }
            default: {
                cout << "Opción no válida. Por favor, seleccione una opción válida." << endl;
                break;
            }
        }
    } while (opcion != 0);

    return 0;
}
