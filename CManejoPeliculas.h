#ifndef PROYECTO_PROGRA_CMANEJOPELICULAS_H
#define PROYECTO_PROGRA_CMANEJOPELICULAS_H
#include "CPelicula.h"
#include "CMovieTitleMap.h"
#include <algorithm>

void mostrarResultados(const vector<int>& indices, const vector<Pelicula*>& peliculas) {
    int count = 0;
    for (int index : indices) {
        if (count >= 5) break;
        cout << "ID: " << index << " - Titulo: " << peliculas[index]->titulo << "\n";
        count++;
    }
}

void buscarPorTitulo(const unordered_map<string, vector<int>>& map, const vector<Pelicula*>& peliculas) {
    string inputTitulo;
    cout << "Ingrese titulo de pelicula: ";
    cin.ignore();  // Ignorar el '\n' restante en el buffer
    getline(cin, inputTitulo);

    bool encontrado = false;
    int count = 0;  // Contador para total de peliculas mostradas

    for (const auto& pair : map) {
        if (pair.first.find(inputTitulo) != string::npos) {
            if (count >= 5) break;  // Detiene si ya mostro 5 peliculas
            encontrado = true;

            // Calcular cuantas peliculas mas se pueden mostrar
            int restantes = min(static_cast<int>(pair.second.size()), 5 - count);
            vector<int> limitedIndices(pair.second.begin(), pair.second.begin() + restantes);
            mostrarResultados(limitedIndices, peliculas);

            count += restantes;
        }
    }
    if (!encontrado) cout << "No se encontro peliculas con ese titulo.\n";
}


void buscarPorTag(unordered_map<string, vector<int>>& mapTags, const vector<Pelicula*>& peliculas) {
    string tag;
    cout << "Ingrese tag: ";
    cin.ignore();  // Ignorar el '\n' restante en el buffer
    getline(cin, tag);

    auto it = mapTags.find(tag);
    if (it == mapTags.end()) {
        cout << "No se encontro peliculas con ese tag.\n";
    }
    else mostrarResultados(it->second, peliculas);
}

void mostrarVerMasTarde(const vector<Pelicula*>& peliculas) {
    cout << "\nPeliculas en 'Ver mas tarde':\n";
    for (const auto& pelicula : peliculas) {
        if (pelicula->watch_later) cout << pelicula->titulo << endl;
    }
}

void mostrarLikes(const vector<Pelicula*>& peliculas) {
    cout << "\nPeliculas con 'Like':\n";
    for (const auto& pelicula : peliculas) {
        if (pelicula->like) cout << pelicula->titulo << endl;
    }
}

#endif //PROYECTO_PROGRA_CMANEJOPELICULAS_H
