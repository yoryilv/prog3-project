#ifndef PROYECTO_PROGRA_CPELICULA_H
#define PROYECTO_PROGRA_CPELICULA_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
using namespace std;

struct Pelicula {
    string imdb_id, titulo, plot_synopsis, tags, split, synopsis_source;
    bool like, watch_later;
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

vector<Pelicula> leerCSV(const string& nombreArchivo) {
    vector<Pelicula> peliculas;
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return peliculas;
    }

    string linea;

    getline(archivo, linea);
    int i = 0;
    while (getline(archivo, linea)) {
        i += 1;
        vector<string> campos = separarCSV(archivo, linea);

        if (campos.size() == 6) {
            peliculas.emplace_back(Pelicula{
                    campos[0],
                    campos[1],
                    campos[2],
                    campos[3],
                    campos[4],
                    campos[5],
                    false,
                    false
            });
        }
        else cout << "Error en formato de linea: " << linea << endl;
    }

    archivo.close();
    return peliculas;
}

#endif //PROYECTO_PROGRA_CPELICULA_H
