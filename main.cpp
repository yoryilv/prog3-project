#include "CPelicula.h"
#include "CTrie.h"
#include "CManejoPeliculas.h"

void mostrarMenu() {
    cout << "\n***** Menu Principal de Streaming *****\n";
    cout << "1. Buscar pelicula por titulo\n";
    cout << "2. Buscar pelicula por tag\n";
    cout << "3. Ver peliculas 'Ver mas tarde'\n";
    cout << "4. Ver peliculas con 'Like'\n";
    cout << "5. Salir\n";
    cout << "Ingrese su opcion: ";
}

int main() {
    vector<Pelicula*> peliculas = leerCSV("mpst_full_data.csv");
    Trie* triePeliculas = Trie::getInstance();
    unordered_map<string, vector<int>> mapTags;

    int i = 0;
    for (const auto& pelicula : peliculas) {
        triePeliculas->insertar(pelicula->titulo, i);
        istringstream tagStream(pelicula->tags);
        string tag;
        while (getline(tagStream, tag, ',')) {
            mapTags[tag].push_back(i);
        }
        ++i;
    }

    int op;
    do {
        mostrarMenu();
        cin >> op;
        switch (op) {
            case 1:
                buscarPorTitulo(*triePeliculas, peliculas);
                break;
            case 2:
                buscarPorTag(mapTags, peliculas);
                break;
            case 3:
                mostrarVerMasTarde(peliculas);
                break;
            case 4:
                mostrarLikes(peliculas);
                break;
            case 5:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (op != 5);

    // Limpieza de memoria
    for (auto pelicula : peliculas) delete pelicula;

    return 0;
}
