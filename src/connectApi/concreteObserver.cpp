#include "../../include/connectApi/concreteObserver.h"

void ConcreteObserver::update(const std::string &message)
{
	std::cout << string(300, '=') << std::endl;
	std::cout << "ConcreteObserver got message: \n" << message << std::endl;
}