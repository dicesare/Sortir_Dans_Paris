cmake_minimum_required(VERSION 3.5)

project(sortirDansParis LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Déclarez que vous voulez trouver la bibliothèque cURL
find_package(CURL REQUIRED)

# Indiquez au compilateur d'inclure le répertoire d'en-têtes de cURL
include_directories(${CURL_INCLUDE_DIRS})

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include/connectApi)

# Récupérer tous les fichiers .cpp du dossier 'src/connectApi'
file(GLOB SOURCES "src/connectApi/*.cpp")

# Ajouter manuellement le fichier main.cpp
list(APPEND SOURCES "main.cpp")

# Création de l'exécutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Liez votre exécutable avec la bibliothèque cURL
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})

install(TARGETS sortirDansParis
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
