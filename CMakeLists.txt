cmake_minimum_required(VERSION 3.27)
project(proyecto_progra)

set(CMAKE_CXX_STANDARD 17 -pthread)

add_executable(proyecto_progra main.cpp
        CPelicula.h
        CManejoPeliculas.h
        CMovieTitleMap.h
        CSimilarMoviesStrategy.h
        CTagBasedSimilarMovies.h
        CMovieExplorer.h
)
