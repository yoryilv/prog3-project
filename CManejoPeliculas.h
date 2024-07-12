#ifndef PROYECTO_PROGRA_CMANEJOPELICULAS_H
#define PROYECTO_PROGRA_CMANEJOPELICULAS_H
#include "CPelicula.h"
#include "CMovieTitleMap.h"
#include <algorithm>

void mostrarDetallesPelicula(Pelicula* pelicula) {
    cout << "Título: " << pelicula->titulo << "\n";

    // Recortar la sinopsis si es más larga de 50 caracteres
    string sinopsisPreview = pelicula->plot_synopsis;
    if (sinopsisPreview.length() > 700) {
        sinopsisPreview = sinopsisPreview.substr(0, 700) + "...";
    }
    cout << "Sinopsis: " << sinopsisPreview << "\n";

    cout << "[1] Like [2] Ver más tarde [3] Volver\n";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            pelicula->like = true;
            cout << "Has marcado la película como 'Like'.\n";
            break;
        case 2:
            pelicula->watch_later = true;
            cout << "Película añadida a 'Ver más tarde'.\n";
            break;
        default:
            break;
    }
}

void mostrarResultados(const vector<int>& indices, const vector<Pelicula*>& peliculas) {
    int count = 0;
    for (int index : indices) {
        cout << "ID: " << index << " - Titulo: " << peliculas[index]->titulo << "\n";
        if (++count >= 5) break;
    }
    cout << "Seleccione una pelicula por ID para mas detalles, 'n' para los siguientes 5, o 'q' para salir: ";
}

int obtenerAccionUsuario() {
    string input;
    cin >> input;
    if (input == "n") return -1;  // Indica mostrar siguientes 5
    if (input == "q") return -2;  // Indica salir
    return stoi(input);  // Convierte el input a un indice
}

void buscarPorTitulo(const unordered_map<string, vector<int>>& map, const vector<Pelicula*>& peliculas) {
    string inputTitulo;
    cout << "Ingresa titulo de la pelicula: ";
    cin.ignore();  // Ignorar el '\n' restante en el buffer
    getline(cin, inputTitulo);

    vector<int> resultados;  // Almacena todos los indices encontrados
    for (const auto& pair : map) {
        if (pair.first.find(inputTitulo) != string::npos) {
            resultados.insert(resultados.end(), pair.second.begin(), pair.second.end());
        }
    }

    if (resultados.empty()) {
        cout << "No se encontro peliculas con ese titulo.\n";
        return;
    }

    int currentIndex = 0;
    bool continuar = true;
    while (continuar && currentIndex < resultados.size()) {
        int nextIndex = min(currentIndex + 5, (int)resultados.size());
        vector<int> toDisplay(resultados.begin() + currentIndex, resultados.begin() + nextIndex);
        mostrarResultados(toDisplay, peliculas);

        cout << "Seleccione una pelicula por ID para mas detalles, 'n' para los siguientes 5, o 'q' para salir: ";
        string decision;
        cin >> decision;
        if (decision == "n") currentIndex += 5;
        else if (decision == "q") continuar = false;
        else {
            try {
                int peliculaId = stoi(decision);
                if (peliculaId >= 0 && peliculaId < peliculas.size() && find(toDisplay.begin(), toDisplay.end(), peliculaId) != toDisplay.end()) {
                    mostrarDetallesPelicula(peliculas[peliculaId]);
                    break;
                }
                else cout << "ID no valido. Intente nuevamente.\n";
            }
            catch (const std::exception& e) {cout << "Entrada no valida. Intente nuevamente.\n";}
        }
    }
}



void buscarPorTag(unordered_map<string, vector<int>>& mapTags, const vector<Pelicula*>& peliculas) {
    string tag;
    cout << "Ingrese tag: ";
    cin.ignore();  // Ignorar el '\n' restante en el buffer
    getline(cin, tag);

    auto it = mapTags.find(tag);
    if (it == mapTags.end()) {
        cout << "No encontrado con ese tag.\n";
        return;
    }

    vector<int>& resultados = it->second;
    int currentIndex = 0;
    bool continuar = true;

    while (continuar && currentIndex < resultados.size()) {
        vector<int> toDisplay(resultados.begin() + currentIndex, resultados.begin() + min(currentIndex + 5, (int)resultados.size()));
        mostrarResultados(toDisplay, peliculas);
        int action = obtenerAccionUsuario();

        if (action == -1) {  // 'n' para mas resultados
            currentIndex += 5;
            continue;
        } else if (action == -2) {  // 'q' para salir
            break;
        } else if (action >= 0 && action < resultados.size()) {  // Seleccionar pelicula
            mostrarDetallesPelicula(peliculas[resultados[action]]);
            break;
        }
    }
}



void mostrarVerMasTarde(const vector<Pelicula*>& peliculas) {
    cout << "\nPeliculas en 'Ver mas tarde':\n";
    for (const auto& pelicula : peliculas) {
        if (pelicula->watch_later) cout << pelicula->titulo << endl;
    }
}

void mostrarLikes(const vector<Pelicula*>& peliculas) {
    cout << "\nPeliculas con 'Like':\n";
    for (const auto& pelicula : peliculas) {
        if (pelicula->like) cout << pelicula->titulo << endl;
    }
}

#endif //PROYECTO_PROGRA_CMANEJOPELICULAS_H
