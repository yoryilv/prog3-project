#ifndef PROYECTO_PROGRA_CPELICULA_H
#define PROYECTO_PROGRA_CPELICULA_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <thread>
#include <mutex>
using namespace std;

template<typename T>
class Pelicula {
public:
    T imdb_id, titulo, plot_synopsis, tags, split, synopsis_source;
    bool like, watch_later;
};

typedef Pelicula<std::string> PeliculaEspecifica;

template<typename T>
class PeliculaFactory {
public:
    static Pelicula<T>* crearPelicula(const vector<string>& campos) {
        if (campos.size() != 6) return nullptr;
        auto* p = new Pelicula<T>();
        p->imdb_id = campos[0];
        p->titulo = campos[1];
        p->plot_synopsis = campos[2];
        p->tags = campos[3];
        p->split = campos[4];
        p->synopsis_source = campos[5];
        p->like = false;
        p->watch_later = false;
        return p;
    }
};

// Función para separar los campos del CSV
vector<string> separarCSV(ifstream& archivo, string& linea) {
    vector<string> campos;
    string campo;
    bool inQuotes = false;

    for (char c : linea) {
        if (c == '"') inQuotes = !inQuotes;
        else if (c == ',' && !inQuotes) {
            campos.push_back(campo);
            campo.clear();
        }
        else campo += c;
    }

    while (inQuotes && getline(archivo, linea)) {
        campo += ' ';
        for (char c : linea) {
            if (c == '"') inQuotes = !inQuotes;
            else if (c == ',' && !inQuotes) {
                campos.push_back(campo);
                campo.clear();
            }
            else campo += c;
        }
    }
    campos.push_back(campo);
    return campos;
}

// Función para leer una porción del archivo CSV
template<typename T>
void leerCSVPorcion(const string& nombreArchivo, int inicio, int fin, vector<Pelicula<T>*>& peliculas, mutex& mtx) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    archivo.seekg(inicio);

    string linea;
    getline(archivo, linea); // Salta la cabecera si es necesario

    while (archivo.tellg() < fin && getline(archivo, linea)) {
        vector<string> campos = separarCSV(archivo, linea);
        Pelicula<T>* pelicula = PeliculaFactory<T>::crearPelicula(campos);
        if (pelicula) {
            lock_guard<mutex> guard(mtx);
            peliculas.push_back(pelicula);
        }
        else cerr << "Error procesando línea: " << linea << endl;
    }

    archivo.close();
}

template<typename T>
vector<Pelicula<T>*> leerCSV(const string& nombreArchivo, int numThreads) {
    vector<Pelicula<T>*> peliculas;
    ifstream archivo(nombreArchivo, ios::ate);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return peliculas;
    }

    int fileSize = archivo.tellg();
    archivo.close();

    int chunkSize = fileSize / numThreads;
    vector<thread> threads;
    mutex mtx;

    for (int i = 0; i < numThreads; ++i) {
        int inicio = i * chunkSize;
        int fin = (i == numThreads - 1) ? fileSize : (i + 1) * chunkSize;

        threads.emplace_back(leerCSVPorcion<T>, nombreArchivo, inicio, fin, ref(peliculas), ref(mtx));
    }

    for (auto& t : threads) t.join();

    return peliculas;
}

#endif //PROYECTO_PROGRA_CPELICULA_H
