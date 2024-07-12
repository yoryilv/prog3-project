#ifndef PROYECTO_PROGRA_CPELICULA_H
#define PROYECTO_PROGRA_CPELICULA_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
using namespace std;

class Pelicula {
public:
    string imdb_id, titulo, plot_synopsis, tags, split, synopsis_source;
    bool like, watch_later;

    virtual void display() const {
        cout << "Título: " << titulo << "\nSinopsis: " << plot_synopsis << endl;
    }

    virtual ~Pelicula() {}
};

class PeliculaFactory {
public:
    static Pelicula* crearPelicula(const vector<string>& campos) {
        if (campos.size() == 6) {
            Pelicula* p = new Pelicula();
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
        return nullptr;
    }
};

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

vector<Pelicula*> leerCSV(const string& nombreArchivo) {
    vector<Pelicula*> peliculas;
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return peliculas;
    }

    string linea;
    getline(archivo, linea); // Ignorar la primera línea de encabezado
    while (getline(archivo, linea)) {
        vector<string> campos = separarCSV(archivo, linea);
        Pelicula* pelicula = PeliculaFactory::crearPelicula(campos);
        if (pelicula != nullptr) peliculas.push_back(pelicula);
        else cout << "Error en formato de línea: " << linea << endl;
    }

    archivo.close();
    return peliculas;
}

#endif // PROYECTO_PROGRA_CPELICULA_H
