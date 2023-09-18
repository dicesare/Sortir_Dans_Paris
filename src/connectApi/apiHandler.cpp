#include "../../include/connectApi/apiHandler.h"

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void APIHandler::fetchData()
{
	CURL *curl;
	CURLcode res;
	std::string readBuffer;

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://opendata.paris.fr/api/records/1.0/search/?dataset=que-faire-a-paris-");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		res = curl_easy_perform(curl);

		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		else {
			// std::cout << string(300, '=') << std::endl;
			// std::cout << "Data received: \n" << readBuffer << std::endl;
			// Notify observers with the received data
			notifyObservers(readBuffer);
		}

		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();
}