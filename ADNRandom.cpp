#include <iostream>
#include <fstream> // Incluimos la biblioteca para trabajar con archivos
#include <string>
#include <cstdlib>
#include <ctime>

bool is_valid_base(char base) {
    switch (std::toupper(base)) {
        case 'A':
        case 'C':
        case 'G':
        case 'T':
            return true;
        default:
            return false;
    }
}

std::string generateDNA(int length) {
    std::string dna;
    srand(time(nullptr));

    for (int i = 0; i < length; ++i) {
        char base = "ACGT"[rand() % 4];
        dna += base;
    }

    return dna;
}

int main() {
    int length;
    std::cout << "Ingrese la longitud deseada de la cadena de ADN: ";
    std::cin >> length;

    if (length <= 0) {
        std::cout << "Longitud invalida. Debe ser mayor que 0." << std::endl;
        return 1;
    }

    std::string dnaSequence = generateDNA(length);

    // Crear un archivo de texto llamado "secuencia_adn.txt"
    std::ofstream archivo("secuencia_adn.txt");
    if (archivo.is_open()) {
        archivo << dnaSequence << std::endl;
        archivo.close();
        std::cout << "Secuencia de ADN guardada en el archivo 'secuencia_adn.txt'." << std::endl;
    } else {
        std::cout << "Error al abrir el archivo para escritura." << std::endl;
        return 1;
    }

    return 0;
}
