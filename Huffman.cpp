#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <bitset>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Nodo del arbol de Huffman
struct NodoHuffman {
    char dato;
    int frecuencia;
    NodoHuffman *izquierda, *derecha;
    NodoHuffman(char dato, int frecuencia) : dato(dato), frecuencia(frecuencia), izquierda(nullptr), derecha(nullptr) {}
    NodoHuffman(char dato, int frecuencia, NodoHuffman* izquierda, NodoHuffman* derecha) : 
        dato(dato), frecuencia(frecuencia), izquierda(izquierda), derecha(derecha) {}
};

// Comparador para la cola de prioridad
struct Comparar {
    bool operator()(NodoHuffman* l, NodoHuffman* r) {
        return (l->frecuencia > r->frecuencia);
    }
};

// Funcion para construir el arbol de Huffman y generar los codigos
void generarCodigos(NodoHuffman* raiz, string str, unordered_map<char, string> &codigoHuffman) {
    if (raiz == nullptr)
        return;
    if (!raiz->izquierda && !raiz->derecha) {
        codigoHuffman[raiz->dato] = str;
    }
    generarCodigos(raiz->izquierda, str + "0", codigoHuffman);
    generarCodigos(raiz->derecha, str + "1", codigoHuffman);
}

// Funcion para codificar el texto
string codificar(const string& texto, unordered_map<char, string> &codigoHuffman) {
    string textoCodificado = "";
    for (char c : texto) {
        textoCodificado += codigoHuffman[c];
    }
    return textoCodificado;
}

// Funcion para decodificar el texto
string decodificar(const string& textoCodificado, NodoHuffman* raiz) {
    string textoDecodificado = "";
    NodoHuffman* actual = raiz;
    for (int i = 0; i < textoCodificado.size(); i++) {
        if (textoCodificado[i] == '0')
            actual = actual->izquierda;
        else
            actual = actual->derecha;

        if (!actual->izquierda && !actual->derecha) {
            textoDecodificado += actual->dato;
            actual = raiz;
        }
    }
    return textoDecodificado;
}

// Funcion principal para probar la codificacion y decodificacion de Huffman
int main() {
    string nombreArchivo;
    cout << "Ingrese el nombre del archivo de texto: ";
    cin >> nombreArchivo;

    // Leer el contenido del archivo
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    string texto((istreambuf_iterator<char>(archivo)), istreambuf_iterator<char>());
    archivo.close();

    // Contar la frecuencia de cada simbolo del texto
    unordered_map<char, int> frecuencia;
    for (char c : texto) {
        frecuencia[c]++;
    }

    // Crear una cola de prioridad para construir el arbol de Huffman
    priority_queue<NodoHuffman*, vector<NodoHuffman*>, Comparar> pq;

    // Crear un nodo hoja para cada simbolo y anadirlo a la cola de prioridad
    for (auto par : frecuencia) {
        pq.push(new NodoHuffman(par.first, par.second));
    }

    // Iterar hasta que haya mas de un nodo en la cola
    while (pq.size() != 1) {
        // Eliminar los dos nodos de mayor prioridad (menor frecuencia)
        NodoHuffman *izquierda = pq.top(); pq.pop();
        NodoHuffman *derecha = pq.top(); pq.pop();

        // Crear un nuevo nodo interno con estos dos nodos como hijos y con una frecuencia igual a la suma de ambos nodos
        int suma = izquierda->frecuencia + derecha->frecuencia;
        pq.push(new NodoHuffman('\0', suma, izquierda, derecha));
    }

    // El nodo restante es la raiz del arbol de Huffman
    NodoHuffman* raiz = pq.top();

    // Generar los codigos de Huffman a partir del arbol de Huffman y almacenarlos en un mapa
    unordered_map<char, string> codigoHuffman;
    generarCodigos(raiz, "", codigoHuffman);

    // Variables para medir el tiempo y tamaño
    double tiempoTotalCodificacion = 0;
    string textoCodificado;
    const int repeticiones = 20;

    // Repetir la codificación 20 veces para medir el tiempo promedio
    for (int i = 0; i < repeticiones; i++) {
        auto inicio = high_resolution_clock::now();
        textoCodificado = codificar(texto, codigoHuffman);
        auto fin = high_resolution_clock::now();
        tiempoTotalCodificacion += duration<double, milli>(fin - inicio).count();
    }

    // Calcular el tiempo promedio de codificación
    double tiempoPromedioCodificacion = tiempoTotalCodificacion / repeticiones;

    // Calcular el tamaño del texto codificado
    int tamanioFinal = textoCodificado.size();

    // Decodificar el texto
    string textoDecodificado = decodificar(textoCodificado, raiz);

    // Mostrar los resultados
    cout << "Tiempo promedio de codificacion: " << tiempoPromedioCodificacion << " ms" << endl;
    cout << "Tamanio final del texto codificado: " << tamanioFinal << " bits" << endl;

    return 0;
}
