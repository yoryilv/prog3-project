#include "CPelicula.h"
#include "CManejoPeliculas.h"
#include "CMovieTitleMap.h"

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
    CMovieTitleMap* titleMap = CMovieTitleMap::getInstance();
    unordered_map<string, vector<int>> mapTags;
    auto& map = CMovieTitleMap::getInstance()->getMap();

    for (int i = 0; i < peliculas.size(); ++i) {
        titleMap->insertar(peliculas[i]->titulo, i);
        istringstream tagStream(peliculas[i]->tags);
        string tag;
        while (getline(tagStream, tag, ',')) mapTags[tag].push_back(i);
    }

    int op;
    do {
        mostrarMenu();
        cin >> op;
        switch (op) {
            case 1:
                buscarPorTitulo(map, peliculas);
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
