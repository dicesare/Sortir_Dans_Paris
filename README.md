# Paris API Manager

## Table of Contents

1. [Introduction](#introduction)
2. [Features](#features)
3. [Technologies](#technologies)
4. [And about the doc](#documentation)
5. [Getting Started](#getting-started)
   - Prerequisites
   - Installation
   - [Usage](#usage)
6. [Architecture](#architecture)
7. [Contributing](#contributing)
8. [License](#license)
9. [Contact](#contact)

---

## Introduction

The Paris API Manager is designed to interact with the "What to do in Paris?" public API, providing a clean, structured interface for retrieving event data and notifying relevant observers.

---

## Features

- Retrieve events from the Paris API.
- Notify registered observers of new events.
- Daily event retrieval.
- Generate graphs illustrating various event statistics.

---

## Technologies

- C++
- `libcurl` library for HTTP requests.
- `nlohmann::json` library for JSON format management.
- Doxygen (for code documentation)

---

## And about the doc

Code documentation is generated with Doxygen. [See section below](#documentation) for details on how to generate and consult documentation.

---

## Getting Started

### Prerequisites

- C++ Compiler (C++11 or higher recommended)
- `libcurl` library
- Library `nlohmann::json`

### Installation

1. Clone the
   ```bash
   git clone https://github.com/dicesare/Sortir_Dans_Paris.git
    ```

2. Go to the project directory and compile :
     ```bash
     cd path_to_the_directory
     make
     ```

### Usage


1. Start the program.

2. Follow the on-screen instructions to interact with the API and display events.
  (To include a time either --thread or -T)

  for a request every x seconds


  ```bash
  ./sortirDansParis -T 5sec
  ```

  for a request every x minutes

  ```bash
  ./sortirDansParis --thread 20min
  ```

  for a request all x hours

  ```bash
  ./sortirDansParis -T 5hr
  ```
  by default, if you don't specify a duration, it's an hourly request

  ## Architecture

Refer to the `docs/` folder for complete architecture and code documentation generated using Doxygen.

### Project Structure
```
Linux_emb/
|-- sortirDansParis/
|   |-- include/
|   |   |-- connectApi/
|   |   |-- gdGeneration/
|   |   |-- fileManagement/
|   |   |-- service/
|   |   |-- storage/
|   |-- src/
|   |   |-- connectApi/
|   |   |-- gdGeneration/
|   |   |-- fileManagement/
|   |   |-- service/
|   |   |-- storage/
|   |-- main.cpp
|   |-- CMakeLists.txt
```

---
## Documentation

La documentation du code est générée avec Doxygen. Voici comment générer et consulter la documentation.

### Installation de Doxygen

Si vous utilisez Ubuntu, vous pouvez installer Doxygen en utilisant la commande suivante :

```bash
sudo apt-get install doxygen
```

### Générer la Documentation

1. Placez-vous à la racine du projet où se trouve le fichier `Doxyfile`.
2. Exécutez la commande suivante :

```bash
doxygen Doxyfile
```

Cela générera la documentation dans le répertoire que vous aurez spécifié dans le champ `OUTPUT_DIRECTORY` de votre fichier `Doxyfile`.

### Lire la Documentation

#### Documentation HTML

1. Accédez au répertoire contenant la documentation (généralement un sous-dossier nommé `html`).
2. Ouvrez le fichier `index.html` avec votre navigateur web.

#### Documentation LaTeX

1. Accédez au répertoire contenant la documentation LaTeX (généralement un sous-dossier nommé `latex`).
2. Utilisez un éditeur LaTeX pour compiler les fichiers en PDF ou exécutez `pdflatex` en ligne de commande.

### Utilisation de Doxywizard

Si vous préférez utiliser une interface graphique :

1. Ouvrez Doxywizard.
2. Utilisez l'option "Fichier > Ouvrir..." pour ouvrir un fichier `Doxyfile` existant.
3. Cliquez sur "Run doxygen" pour générer la documentation.

## Contributing

Contributions are always welcome! See `CONTRIBUTING.md` for ways to get started. Please adhere to this project's `CODE_OF_CONDUCT.md`.

---

## License

This project is licensed under the MIT License - see the `LICENSE` file for details.

---

## Contact

- Antony COCO - [LinkedIn](https://www.linkedin.com/in/antonycoco/)
- Email - antony.coco.pro@gmail.com

---
