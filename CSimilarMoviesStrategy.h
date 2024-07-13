#ifndef PROYECTO_PROGRA_CSIMILARMOVIESSTRATEGY_H
#define PROYECTO_PROGRA_CSIMILARMOVIESSTRATEGY_H

#include "CPelicula.h"
#include <vector>

template<typename T>
class SimilarMoviesStrategy {
public:
    virtual vector<T*> findSimilar(const vector<T*>& allMovies, const T* baseMovie) const = 0;
    virtual ~SimilarMoviesStrategy() {}
};

#endif //PROYECTO_PROGRA_CSIMILARMOVIESSTRATEGY_H
