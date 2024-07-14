#ifndef PROYECTO_PROGRA_CMOVIETITLEMAP_H
#define PROYECTO_PROGRA_CMOVIETITLEMAP_H
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <memory>
using namespace std;

class CMovieTitleMap {
private:
    static unique_ptr<CMovieTitleMap> instance;
    unordered_map<string, vector<int>> titleMap;

    // Constructor privado
    CMovieTitleMap() {}

public:
    static CMovieTitleMap* getInstance() {
        if (instance == nullptr) instance = unique_ptr<CMovieTitleMap>(new CMovieTitleMap());
        return instance.get();
    }

    // Eliminar copias para asegurar la unicidad del Singleton
    CMovieTitleMap(const CMovieTitleMap&) = delete;
    CMovieTitleMap& operator=(const CMovieTitleMap&) = delete;

    // Método para manejar el mapa
    void insertar(const string& titulo, int index) {titleMap[titulo].push_back(index);}

    const unordered_map<string, vector<int>>& getMap() const {return titleMap;}
};

unique_ptr<CMovieTitleMap> CMovieTitleMap::instance = nullptr;

#endif //PROYECTO_PROGRA_CMOVIETITLEMAP_H
