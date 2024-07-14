#ifndef PROYECTO_PROGRA_CMANEJOPELICULAS_H
#define PROYECTO_PROGRA_CMANEJOPELICULAS_H
#include "CPelicula.h"
#include "CMovieTitleMap.h"
#include <algorithm>
#include <cctype>

template<typename T>
void mostrarDetallesPelicula(T* pelicula) {
    cout << "-------------------------------------------------------\n";
    cout << "Titulo: " << pelicula->titulo << "\n";

    cout << endl;
    // Recortar la sinopsis si es mas larga de 700 caracteres
    string sinopsisPreview = pelicula->plot_synopsis;
    if (sinopsisPreview.length() > 700) {
        sinopsisPreview = sinopsisPreview.substr(0, 700) + "...";
    }
    cout << "Sinopsis: " << sinopsisPreview << "\n";

    cout << "-------------------------------------------------------\n";

    cout << "-Seleccionar-" << endl;
    cout << "[1] Like" << endl;
    cout << "[2] Ver mas tarde" << endl;
    cout << "[3] Regresar al menu\n";
    cout << "Eleccion:";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            pelicula->like = true;
            cout << "Has marcado la pelicula como 'Like'.\n";
            break;
        case 2:
            pelicula->watch_later = true;
            cout << "Pelicula anadida a 'Ver mas tarde'.\n";
            break;
        default:
            break;
    }
}

template<typename T>
void mostrarResultados(const vector<int>& indices, const vector<T*>& peliculas) {
    int count = 0;
    cout << "-------------------------------------------------------\n";
    for (int index : indices) {
        cout << "ID: " << index << " - Titulo: " << peliculas[index]->titulo << "\n";
        if (++count >= 5) break;
    }
}

string capitalize(string str) {
    bool capitalizeNext = true;

    for (char& c : str) {
        if (isspace(c)) capitalizeNext = true;
        else if (capitalizeNext) {
            c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
            capitalizeNext = false;
        }
        else c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }
    return str;
}


template<typename T>
void buscarPorTitulo(const unordered_map<string, vector<int>>& map, const vector<T*>& peliculas) {
    string inputTitulo;
    cout << "-------------------------------------------------------\n";
    cout << "Ingresa titulo de la pelicula: ";
    cin.ignore();  // Ignorar el '\n' restante en el buffer
    getline(cin, inputTitulo);

    inputTitulo = capitalize(inputTitulo);  // Capitalizar el titulo ingresado

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
        mostrarResultados<T>(toDisplay, peliculas);

        cout << "-------------------------------------------------------\n";
        cout << "-Seleccionar-" << endl;
        cout << "[ID] Ver mas detalles de la pelicula" << endl;
        cout << "[n] Siguientes 5 peliculas" << endl;
        cout << "[q] Regresar al menu" << endl;
        cout << "Eleccion: ";
        string decision;
        cin >> decision;
        if (decision == "n") currentIndex += 5;
        else if (decision == "q") continuar = false;
        else {
            try {
                int peliculaId = stoi(decision);
                if (peliculaId >= 0 && peliculaId < peliculas.size() && find(toDisplay.begin(), toDisplay.end(), peliculaId) != toDisplay.end()) {
                    mostrarDetallesPelicula<T>(peliculas[peliculaId]);
                    break;
                }
                else cout << "ID no valido. Intente nuevamente.\n";
            }
            catch (const exception& e) { cout << "Entrada no valida. Intente nuevamente.\n"; }
        }
    }
}

template<typename T>
void buscarPorTag(unordered_map<string, vector<int>>& mapTags, const vector<T*>& peliculas) {
    string tag;
    cout << "-------------------------------------------------------\n";
    cout << "Ingrese tag: ";
    cin.ignore();  // Ignorar el '\n' restante en el buffer
    getline(cin, tag);

    auto it = mapTags.find(tag);
    if (it == mapTags.end()) {
        cout << "-------------------------------------------------------\n";
        cout << "No encontrado con ese tag.\n";
        return;
    }

    vector<int>& resultados = it->second;
    int currentIndex = 0;
    bool continuar = true;

    while (continuar && currentIndex < resultados.size()) {
        vector<int> toDisplay(resultados.begin() + currentIndex, resultados.begin() + min(currentIndex + 5, (int)resultados.size()));
        mostrarResultados<T>(toDisplay, peliculas); // Usar la funcion mostrarResultados para tipos template

        cout << "-------------------------------------------------------\n";
        cout << "-Seleccionar" << endl;
        cout << "[ID] Ver mas detalles de la pelicula" << endl;
        cout << "[n] Siguientes 5 peliculas" << endl;
        cout << "[q] Regresar al menu" << endl;
        cout << "Eleccion: ";
        string decision;
        cin >> decision;
        if (decision == "n") currentIndex += 5;
        else if (decision == "q") continuar = false;
        else {
            try {
                int peliculaId = stoi(decision);
                if (peliculaId >= 0 && peliculaId < peliculas.size() && find(toDisplay.begin(), toDisplay.end(), peliculaId) != toDisplay.end()) {
                    mostrarDetallesPelicula<T>(peliculas[peliculaId]); // Asegurate de que mostrarDetallesPelicula tambien sea template
                    break;
                }
                else cout << "ID no valido. Intente nuevamente.\n";
            }
            catch (const exception& e) {cout << "Entrada no valida. Intente nuevamente.\n";}
        }
    }
}


template<typename T>
void mostrarVerMasTarde(const vector<T*>& peliculas) {
    cout << "-------------------------------------------------------";
    cout << "\nPeliculas en 'Ver mas tarde':\n";
    for (const auto& pelicula : peliculas) {
        if (pelicula->watch_later) cout << pelicula->titulo << endl;
    }
}

template<typename T>
void mostrarLikes(const vector<T*>& peliculas) {
    cout << "-------------------------------------------------------";
    cout << "\nPeliculas con 'Like':\n";
    for (const auto& pelicula : peliculas) {
        if (pelicula->like) cout << pelicula->titulo << endl;
    }
}

#endif //PROYECTO_PROGRA_CMANEJOPELICULAS_H
