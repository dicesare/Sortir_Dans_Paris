cmake_minimum_required(VERSION 3.5)

project(sortirDansParis LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Déclarez les bibliothèques additionnelles à utiliser
find_package(CURL REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

# Find the GD library
find_path(GD_INCLUDE_DIR NAMES gd.h)
find_library(GD_LIBRARY NAMES gd)

# Vérifie que GD a été trouvé
if(NOT GD_INCLUDE_DIR)
  message(FATAL_ERROR "GD include directory not found")
endif()

if(NOT GD_LIBRARY)
  message(FATAL_ERROR "GD library not found")
endif()

# Indiquez au compilateur d'inclure le répertoire d'en-têtes des librairies
include_directories(${CURL_INCLUDE_DIRS})
include_directories(${nlohmann_json_INCLUDE_DIRS})
include_directories(${GD_INCLUDE_DIR})

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include/connectApi)
include_directories(${PROJECT_SOURCE_DIR}/include/fileManagement)
include_directories(${PROJECT_SOURCE_DIR}/include/storage)
include_directories(${PROJECT_SOURCE_DIR}/include/service)
include_directories(${PROJECT_SOURCE_DIR}/include/gdGeneration)

# Récupérer tous les fichiers .cpp de chaque dossier spécifique
file(GLOB API_SOURCES "src/connectApi/*.cpp")
file(GLOB FILE_SOURCES "src/fileManagement/*.cpp")
file(GLOB STORAGE_SOURCES "src/storage/*.cpp")
file(GLOB SERVICE_SOURCES "src/service/*.cpp")
file(GLOB GDGENERATION_SOURCES "src/gdGeneration/*.cpp")

# Ajouter tous ces fichiers à une seule variable SOURCES
list(APPEND SOURCES ${API_SOURCES} ${FILE_SOURCES} ${STORAGE_SOURCES} ${SERVICE_SOURCES} ${GDGENERATION_SOURCES})

# Ajouter manuellement le fichier main.cpp
list(APPEND SOURCES "main.cpp")


# Création de l'exécutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Liez votre exécutable avec la bibliothèque cURL
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES} ${nlohmann_json_LIBRARIES} ${GD_LIBRARY})

install(TARGETS sortirDansParis
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
