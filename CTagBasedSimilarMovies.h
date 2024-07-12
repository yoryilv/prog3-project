#ifndef PROYECTO_PROGRA_CTAGBASEDSIMILARMOVIES_H
#ifndef PROYECTO_PROGRA_CTAGBASEDSIMILARMOVIES_H
#define PROYECTO_PROGRA_CTAGBASEDSIMILARMOVIES_H

#include "CSimilarMoviesStrategy.h"
#include <sstream>

class TagBasedSimilarMovies : public SimilarMoviesStrategy {
public:
    vector<Pelicula*> findSimilar(const vector<Pelicula*>& allMovies, const Pelicula* baseMovie) const override{
        vector<Pelicula*> similarMovies;
        vector<string> baseTags;
        string tag;
        stringstream ss(baseMovie->tags);

        while (getline(ss, tag, ',')) baseTags.push_back(tag);

        for (const auto& movie : allMovies) {
            for (const auto& baseTag : baseTags) {
                if (movie->tags.find(baseTag) != string::npos && movie != baseMovie) {
                    similarMovies.push_back(movie);
                    break;
                }
            }
        }

        return similarMovies;
    }
};


#endif //PROYECTO_PROGRA_CTAGBASEDSIMILARMOVIES_H
