# Paris API Manager

## Table of Contents

1. [Introduction](#introduction)
2. [Features](#features)
3. [Technologies](#technologies)
4. [And about the doc](#And about the doc)
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

Code documentation is generated with Doxygen. Here's how to generate and consult the documentation.

### Installing Doxygen

If you're using Ubuntu, you can install Doxygen using the following command:

```bash
sudo apt-get install doxygen
```

### Generate documentation

1. Go to the project root where the `Doxyfile` file is located.
2. Run the following command:

```bash
doxygen Doxyfile
```

This will generate the documentation in the directory you specify in the `OUTPUT_DIRECTORY` field of your `Doxyfile` file.

### Read documentation

#### HTML documentation

1. Go to the directory containing the documentation (usually a sub-folder named `html`).
2. Open the `index.html` file in your web browser.

#### LaTeX documentation

1. Go to the directory containing the LaTeX documentation (usually a sub-folder named `latex`).
2. Use a LaTeX editor to compile PDF files, or run `pdflatex` from the command line.

### Using Doxywizard

If you prefer to use a graphical interface :

1. Open Doxywizard.
2. Use the "File > Open..." option to open an existing `Doxyfile`.
3. Click on "Run doxygen" to generate the documentation.

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
