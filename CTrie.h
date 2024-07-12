#ifndef TRIE_H
#define TRIE_H

#include <map>
#include <vector>
#include <string>
#include <memory>

// Clase NodoTrie para almacenar los hijos y marcar el final de una palabra
class NodoTrie {
public:
    map<char, unique_ptr<NodoTrie>> hijos;
    bool esFinalDePalabra;
    vector<int> indicesPeliculas;

    NodoTrie() : esFinalDePalabra(false) {}
};

// Clase Trie con implementación del patrón Singleton
class Trie {
private:
    static Trie* instance;
    unique_ptr<NodoTrie> raiz;

    // Constructor privado
    Trie() : raiz(make_unique<NodoTrie>()) {}

public:
    // Método para acceder a la instancia del Singleton
    static Trie* getInstance() {
        if (instance == nullptr) instance = new Trie();
        return instance;
    }

    // Destructor
    ~Trie() {}

    // Eliminar las copias para asegurar la unicidad del Singleton
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;

    // Método para insertar un título en el Trie
    void insertar(const string& palabra, int index) {
        NodoTrie* actual = raiz.get();
        for (char c : palabra) {
            if (actual->hijos.find(c) == actual->hijos.end()) {
                actual->hijos[c] = make_unique<NodoTrie>();
            }
            actual = actual->hijos[c].get();
        }
        actual->esFinalDePalabra = true;
        actual->indicesPeliculas.push_back(index);
    }

    // Método para buscar un título en el Trie
    vector<int> buscar(const string& palabra) {
        NodoTrie* actual = raiz.get();
        for (char c : palabra) {
            if (actual->hijos.find(c) == actual->hijos.end()) return {};  // Título no encontrado
            actual = actual->hijos[c].get();
        }
        return actual->esFinalDePalabra ? actual->indicesPeliculas : vector<int>{};
    }
};

// Inicialización del puntero estático
Trie* Trie::instance = nullptr;

#endif // TRIE_H
