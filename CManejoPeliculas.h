#ifndef PROYECTO_PROGRA_CMANEJOPELICULAS_H
#define PROYECTO_PROGRA_CMANEJOPELICULAS_H
#include "CPelicula.h"
#include "CTrie.h"

void mostrarResultados(const vector<int>& indices, const vector<Pelicula*>& peliculas) {
    int count = 0;
    for (int index : indices) {
        if (count >= 5) break;
        cout << "ID: " << index << " - Titulo: " << peliculas[index]->titulo << "\n";
        count++;
    }
}

void buscarPorTitulo(Trie& trie, const vector<Pelicula*>& peliculas) {
    string titulo;
    cout << "Ingrese el titulo de la pelicula: ";
    cin.ignore();  // Ignorar el '\n' restante en el buffer
    getline(cin, titulo);

    vector<int> resultados = trie.buscar(titulo);
    if (resultados.empty()) {
        cout << "No se encontraron peliculas con ese titulo.\n";
    }
    else mostrarResultados(resultados, peliculas);
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
