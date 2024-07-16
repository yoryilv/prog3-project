# Programación III: Proyecto Final (2024-1)

## Integrantes
- Jorge Piero Matias Leandro Vásquez
- Jose Armando Arias Romero
- Wilder Emanuel Bañon Hualpa
- Angie Kelly Rodriguez González

## Video explicativo del proyecto
El video se encuentra [aquí](https://youtu.be/bO9lR-D4Po8)

## Plataforma de Streaming

El objetivo del proyecto final es implementar una plataforma de streaming. Un programa que administre la búsqueda y visualización de la sinopsis de películas. Para ello, se implementan las siguientes operaciones:

### Funcionalidades Principales
- **Cargar base de datos:** Leer la base de datos en formato .csv.
- **Búsqueda de películas:** Permitir la búsqueda de películas por título y por tag.
- **Visualización de sinopsis:** Mostrar la sinopsis de la película seleccionada.
- **Marcado de películas:** Permitir marcar películas con 'Like' o 'Ver más tarde'.
- **Recomendación de películas:** Mostrar películas similares a las marcadas con 'Like' basadas en los tags de las mismas.

### Uso del Proyecto
#### Menú Principal
El programa muestra un menú con las siguientes opciones:
1. Buscar película por título.
2. Buscar película por tag.
3. Ver películas 'Ver más tarde'.
4. Ver películas con 'Like'.
5. Ver películas similares a las marcadas con 'Like'.
6. Salir del programa.

#### Ejemplos de Uso
- **Búsqueda por título:** Ingrese el título o parte del título de la película que desea buscar.
- **Búsqueda por tag:** Ingrese el tag (por ejemplo, 'cult', 'horror') para buscar películas asociadas.
- **Marcado de películas:** Después de seleccionar una película, puede marcarla con 'Like' o 'Ver más tarde'.

## Estructura del Proyecto


- `main.cpp`: Archivo principal que contiene el flujo del programa.
- `CPelicula.h`: Definición de la clase `Pelicula` y funciones relacionadas a la carga de archivos.
- `CManejoPeliculas.h`: Funciones para manejar la búsqueda por título o tags y visualización de películas.
- `CMovieTitleMap.h`: Implementación del patrón Singleton para manejar el mapa de títulos de películas.
- `CMovieExplorer.h`: Explorador de películas que utiliza estrategias para encontrar películas similares.
- `CTagBasedSimilarMovies.h`: Estrategia basada en tags para encontrar películas similares.
- `CSimilarMoviesStrategy.h`: Clase base para implementar estrategias de películas similares.

## Software y Técnicas Utilizadas

### Programación Concurrente
Se utiliza la programación concurrente para la lectura eficiente del archivo CSV mediante el uso de múltiples hilos (`std::thread`) y mutex (`std::mutex`) para la sincronización de acceso a los datos compartidos.

### Programación Genérica
El proyecto hace uso extensivo de plantillas (`template`) para definir clases y funciones genéricas que puedan trabajar con diferentes tipos de datos.

### Patrones de Diseño
- **Singleton**: Implementado en la clase `CMovieTitleMap` para asegurar que solo haya una instancia del mapa de títulos de películas en todo el programa.
- **Factory**: Utilizado en la clase `PeliculaFactory` para la creación de objetos `Pelicula` a partir de los datos leídos del archivo CSV.
- **Strategy**: Implementado en las clases `CSimilarMoviesStrategy` y `CTagBasedSimilarMovies` para definir diferentes estrategias de búsqueda de películas similares basados en los tags.

## Referencias Bibliográficas

- Meyers, S. (2005). **Effective C++: 55 Specific Ways to Improve Your Programs and Designs** (3rd Edition). Addison-Wesley Professional.
- Gamma, E., Helm, R., Johnson, R., & Vlissides, J. (1994). **Design Patterns: Elements of Reusable Object-Oriented Software**. Addison-Wesley Professional.
- Stroustrup, B. (2013). **The C++ Programming Language** (4th Edition). Addison-Wesley Professional.
- ISO/IEC. (2017). **ISO/IEC 14882:2017: Programming Languages - C++**. International Organization for Standardization.

### Licencia
Este proyecto está licenciado bajo la Licencia MIT. Consulte el archivo `LICENSE` para obtener más detalles.