#ifndef APIHANDLER_H
#define APIHANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>

#include "observable.h"

class APIHandler : public Observable {
public:
    void fetchData();
};

#endif // APIHANDLER_H
