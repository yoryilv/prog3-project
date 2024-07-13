#ifndef PROYECTO_PROGRA_CMOVIEEXPLORER_H
#define PROYECTO_PROGRA_CMOVIEEXPLORER_H

#include "CSimilarMoviesStrategy.h"
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

template<typename T>
class MovieExplorer {
private:
    const SimilarMoviesStrategy<T>* strategy;  // Estrategia para encontrar películas similares
    vector<T*> movies;                         // Lista de películas disponibles

public:
    // Constructor: inicializa con una estrategia y una lista de películas
    MovieExplorer(const SimilarMoviesStrategy<T>* strategy, const vector<T*>& movies)
            : strategy(strategy), movies(movies) {}

    // Establece una nueva estrategia para buscar películas similares
    void setStrategy(const SimilarMoviesStrategy<T>* newStrategy) {
        strategy = newStrategy;
    }

    // Muestra las películas similares a las que el usuario ha dado "Like"
    void showSimilarToAllLiked() const {
        unordered_set<string> allTags;  // Para almacenar todos los tags únicos de los "Likes"
        vector<T*> similarMovies;       // Para almacenar todas las películas similares encontradas

        // Recopilar todos los tags únicos
        for (const auto& movie : movies) {
            if (movie->like) {
                istringstream tagStream(movie->tags);
                string tag;
                while (getline(tagStream, tag, ',')) {
                    allTags.insert(tag);
                }
            }
        }

        // Buscar películas que coincidan con cualquier tag de todos los tags recopilados
        for (const auto& movie : movies) {
            for (const auto& tag : allTags) {
                if (movie->tags.find(tag) != string::npos && find(similarMovies.begin(), similarMovies.end(), movie) == similarMovies.end()) {
                    similarMovies.push_back(movie);
                }
            }
        }

        // Mostrar películas similares con paginación
        int currentIndex = 0;
        bool continuar = true;
        while (continuar && currentIndex < similarMovies.size()) {
            int nextIndex = min(currentIndex + 5, int(similarMovies.size()));
            cout << "-------------------------------------------------------\n";
            cout << "Películas similares basadas en 'Likes' totales:\n";
            for (int i = currentIndex; i < nextIndex; ++i)
                cout << i+1 << ") " << similarMovies[i]->titulo << "\n";

            currentIndex += 5;
            if (currentIndex < similarMovies.size()) {
                cout << "-------------------------------------------------------\n";
                cout << "-Seleccionar-" << endl;
                cout << "[s] Siguientes 5 películas" << endl;
                cout << "[n] Regresar al menú" << endl;
                cout << "Elección:";
                char decision;
                cin >> decision;
                if (decision != 's' && decision != 'S') continuar = false;
            }
            else continuar = false;  // No más películas para mostrar
        }
        cout << "\n";
    }
};

#endif // PROYECTO_PROGRA_CMOVIEEXPLORER_H
