#ifndef PROYECTO_PROGRA_CSIMILARMOVIESSTRATEGY_H
#define PROYECTO_PROGRA_CSIMILARMOVIESSTRATEGY_H

#include "CPelicula.h"
#include <vector>

class SimilarMoviesStrategy {
public:
    virtual vector<Pelicula*> findSimilar(const vector<Pelicula*>& allMovies, const Pelicula* baseMovie) const = 0;
    virtual ~SimilarMoviesStrategy() {}
};


#endif //PROYECTO_PROGRA_CSIMILARMOVIESSTRATEGY_H
