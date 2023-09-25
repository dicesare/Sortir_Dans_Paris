cmake_policy(SET CMP0074 NEW)
cmake_minimum_required(VERSION 3.5)

project(sortirDansParis LANGUAGES CXX)

set(CMAKE_FIND_ROOT_PATH /home/antony_c/autre/buildroot-2023.08/output/host/aarch64-buildroot-linux-gnu/sysroot/)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CURL_NO_CURL_CMAKE ON)
set(CURL_ROOT /home/antony_c/autre/buildroot-2023.08/output/host/aarch64-buildroot-linux-gnu/sysroot/usr/)
set(nlohmann_json_DIR /home/antony_c/autre/buildroot-2023.08/output/host/aarch64-buildroot-linux-gnu/sysroot/usr/include/)
set(GD_INCLUDE_DIR /home/antony_c/autre/buildroot-2023.08/output/build/gd-2.3.3/src/)
set(GD_LIBRARY /home/antony_c/autre/buildroot-2023.08/output/build/gd-2.3.3/src/.libs/libgd.so)

# Déclarez les bibliothèques additionnelles à utiliser
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

# Vérifie que GD a été trouvé
if(NOT GD_INCLUDE_DIR)
  message(FATAL_ERROR "GD include directory not found")
endif()

if(NOT GD_LIBRARY)
  message(FATAL_ERROR "GD library not found")
endif()

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

# Ajouter les dossiers include des bibliothèques additionnelles
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CURL_INCLUDE_DIRS} 
    ${nlohmann_json_INCLUDE_DIRS} 
    ${GD_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/include/connectApi
    ${PROJECT_SOURCE_DIR}/include/fileManagement
    ${PROJECT_SOURCE_DIR}/include/storage
    ${PROJECT_SOURCE_DIR}/include/service
    ${PROJECT_SOURCE_DIR}/include/gdGeneration
)

# Liez votre exécutable avec la bibliothèque cURL
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES} ${nlohmann_json_LIBRARIES} ${GD_LIBRARY})

install(TARGETS sortirDansParis
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
