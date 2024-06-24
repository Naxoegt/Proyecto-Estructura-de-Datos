#include <bits/stdc++.h> 
#include <chrono>
#include <fstream>
using namespace std; 
using namespace std::chrono;

// Función para comprimir una cadena utilizando el algoritmo LZ78
vector<int> comprimir(const string &s1) { 
    unordered_map<string, int> tabla; 

    for (int i = 0; i <= 255; i++) { 
        string ch = ""; 
        ch += char(i); 
        tabla[ch] = i; 
    } 

    string p = "", c = ""; 
    p += s1[0]; 
    int codigo = 256; 
    vector<int> codigos_salida; 

    for (int i = 0; i < s1.length(); i++) { 
        if (i != s1.length() - 1) 
            c += s1[i + 1]; 

        if (tabla.find(p + c) != tabla.end()) { 
            p = p + c; 
        } else { 
            codigos_salida.push_back(tabla[p]); 
            tabla[p + c] = codigo; 
            codigo++; 
            p = c; 
        } 
        c = ""; 
    } 

    codigos_salida.push_back(tabla[p]); 
    return codigos_salida; 
} 

// Función para descomprimir una secuencia de códigos utilizando el algoritmo LZ78
void descomprimir(const vector<int> &op) { 
    unordered_map<int, string> tabla; 

    for (int i = 0; i <= 255; i++) { 
        string ch = ""; 
        ch += char(i); 
        tabla[i] = ch; 
    } 

    int anterior = op[0], n; 
    string s = tabla[anterior]; 
    string c = ""; 
    c += s[0]; 
    cout << s; 
    int contador = 256; 

    for (int i = 0; i < op.size() - 1; i++) { 
        n = op[i + 1]; 

        if (tabla.find(n) == tabla.end()) { 
            s = tabla[anterior]; 
            s = s + c; 
        } else { 
            s = tabla[n]; 
        } 

        cout << s; 
        c = ""; 
        c += s[0]; 
        tabla[contador] = tabla[anterior] + c; 
        contador++; 
        anterior = n; 
    } 
} 

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

    string s((istreambuf_iterator<char>(archivo)), istreambuf_iterator<char>());
    archivo.close();


    const int repeticiones = 20;
    double tiempoTotalCompresion = 0;
    vector<int> codigos_salida;

    // Repetir la compresión 20 veces para medir el tiempo promedio
    for (int i = 0; i < repeticiones; i++) {
        auto inicio = high_resolution_clock::now();
        codigos_salida = comprimir(s);
        auto fin = high_resolution_clock::now();
        tiempoTotalCompresion += duration<double, milli>(fin - inicio).count();
    }

    // Calcular el tiempo promedio de compresión
    double tiempoPromedioCompresion = tiempoTotalCompresion / repeticiones;

    // Calcular el tamaño final del texto comprimido
    int tamanioFinal = codigos_salida.size() * sizeof(int) * 8;

    // Mostrar los resultados
    cout << "\n\nTiempo promedio de compresion: " << tiempoPromedioCompresion << " ms" << endl;
    cout << "Tamanio final del texto comprimido: " << tamanioFinal << " bits" << endl;

    return 0;
}
