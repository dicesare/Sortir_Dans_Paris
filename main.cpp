#include <iostream>
#include <string>

#include "include/connectApi/apiHandler.h" // Incluez le fichier d'en-tête de APIHandler
#include "include/connectApi/concreteObserver.h" // Incluez le fichier d'en-tête de ConcreteObserver


int main() {
    ConcreteObserver observer1;
    ConcreteObserver observer2;

    APIHandler apiHandler; // Créez une instance de APIHandler
    apiHandler.addObserver(&observer1);
    apiHandler.addObserver(&observer2);

    // Appel à l'API et notification des observateurs
    apiHandler.fetchData();

    return 0;
}
