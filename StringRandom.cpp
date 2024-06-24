#include <iostream>
#include <fstream> // Incluimos la biblioteca para trabajar con archivos
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Función para generar una cadena aleatoria de una longitud dada
string generarCadenaAleatoria(int longitud) {
    string caracteres = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string cadenaAleatoria = "";
    int n = caracteres.size();

    // Semilla para el generador de números aleatorios
    srand(time(0));

    for (int i = 0; i < longitud; i++) {
        cadenaAleatoria += caracteres[rand() % n];
    }

    return cadenaAleatoria;
}

int main() {
    int longitud;

    // Preguntar al usuario por la longitud de la cadena
    cout << "Ingrese la longitud de la cadena de texto: ";
    cin >> longitud;

    // Generar la cadena aleatoria
    string cadenaAleatoria = generarCadenaAleatoria(longitud);

    // Crear un archivo de texto llamado "cadena_aleatoria.txt"
    ofstream archivo("cadena_aleatoria.txt");
    if (archivo.is_open()) {
        archivo << cadenaAleatoria << endl;
        archivo.close();
        cout << "Cadena aleatoria guardada en el archivo 'cadena_aleatoria.txt'." << endl;
    } else {
        cout << "Error al abrir el archivo para escritura." << endl;
        return 1;
    }

    return 0;
}
