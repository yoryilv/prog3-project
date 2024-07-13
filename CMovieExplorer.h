#ifndef PROYECTO_PROGRA_CMOVIEEXPLORER_H
#define PROYECTO_PROGRA_CMOVIEEXPLORER_H

#include "CSimilarMoviesStrategy.h"
#include <iostream>
#include <vector>
#include <unordered_set>

class MovieExplorer {
private:
    const SimilarMoviesStrategy* strategy;  // Estrategia para encontrar peliculas similares
    vector<Pelicula*> movies;          // Lista de peliculas disponibles

public:
    // Constructor: inicializa con una estrategia y una lista de peliculas
    MovieExplorer(const SimilarMoviesStrategy* strategy, const vector<Pelicula*>& movies)
            : strategy(strategy), movies(movies) {}

    // Establece una nueva estrategia para buscar peliculas similares
    void setStrategy(const SimilarMoviesStrategy* newStrategy) {strategy = newStrategy;}

    // Muestra las peliculas similares a las que el usuario ha dado "Like"
    void showSimilarToAllLiked() const {
        unordered_set<string> allTags;  // Para almacenar todos los tags unicos de los "Likes"
        vector<Pelicula*> similarMovies;  // Para almacenar todas las peliculas similares encontradas

        // Recopilar todos los tags unicos
        for (const auto& movie : movies) {
            if (movie->like) {
                istringstream tagStream(movie->tags);
                string tag;
                while (getline(tagStream, tag, ',')) {
                    allTags.insert(tag);
                }
            }
        }

        // Buscar peliculas que coincidan con cualquier tag de todos los tags recopilados
        for (const auto& movie : movies) {
            for (const auto& tag : allTags) {
                if (movie->tags.find(tag) != string::npos && find(similarMovies.begin(), similarMovies.end(), movie) == similarMovies.end()) {
                    similarMovies.push_back(movie);
                }
            }
        }

        // Mostrar peliculas similares con paginacion
        int currentIndex = 0;
        bool continuar = true;
        while (continuar && currentIndex < similarMovies.size()) {
            int nextIndex = min(currentIndex + 5, int(similarMovies.size()));
            cout << "-------------------------------------------------------\n";
            cout << "Peliculas similares basadas en 'Likes' totales:\n";
            for (int i = currentIndex; i < nextIndex; ++i)
                cout << i+1 << ") " << similarMovies[i]->titulo << "\n";

            currentIndex += 5;
            if (currentIndex < similarMovies.size()) {
                cout << "-------------------------------------------------------\n";
                cout << "-Seleccionar-" << endl;
                cout << "[s] Siguientes 5 peliculas" << endl;
                cout << "[n] Regresar al menu" << endl;
                cout << "Eleccion:";
                char decision;
                cin >> decision;
                if (decision != 's' && decision != 'S') continuar = false;
            }
            else continuar = false;  // No mas peliculas para mostrar
        }
        cout << "\n";
    }

};

#endif //PROYECTO_PROGRA_CMOVIEEXPLORER_H
