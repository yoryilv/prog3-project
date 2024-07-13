#ifndef PROYECTO_PROGRA_CTAGBASEDSIMILARMOVIES_H
#define PROYECTO_PROGRA_CTAGBASEDSIMILARMOVIES_H

#include "CSimilarMoviesStrategy.h"
#include <sstream>
#include <vector>
#include <string>

template<typename T>
class TagBasedSimilarMovies : public SimilarMoviesStrategy<T> {
public:
    vector<T*> findSimilar(const vector<T*>& allMovies, const T* baseMovie) const override {
        vector<T*> similarMovies;
        vector<string> baseTags;
        string tag;
        stringstream ss(baseMovie->tags);

        // Separar tags de la película base
        while (getline(ss, tag, ',')) baseTags.push_back(tag);

        // Buscar películas similares basándose en los tags
        for (const auto& movie : allMovies) {
            for (const auto& baseTag : baseTags) {
                if (movie->tags.find(baseTag) != string::npos && movie != baseMovie) {
                    similarMovies.push_back(movie);
                    break; // Si encuentra una coincidencia, agrega la película y rompe el bucle interior
                }
            }
        }

        return similarMovies;
    }
};

#endif // PROYECTO_PROGRA_CTAGBASEDSIMILARMOVIES_H
