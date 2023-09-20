#include "../../include/connectApi/apiHandler.h"

APIHandler::APIHandler() : baseUrl("https://opendata.paris.fr/api/explore/v2.1/catalog/datasets/que-faire-a-paris-/records?") {}

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

void APIHandler::fetchData()
{

	std::string queryUrl = baseUrl + "select=id%2Ctags&limit=100";
	std::map<std::string, nlohmann::json> allEventIds;

	int offset = 0;
	while (true) {
		std::string urlWithOffset = queryUrl + "&offset=" + std::to_string(offset);
		std::map<std::string, nlohmann::json> eventIds = makeRequest(urlWithOffset);
		if (eventIds.empty()) {
			break;
		}
		allEventIds.insert(eventIds.begin(), eventIds.end());
		offset += 100;
	}
	notifyObservers(allEventIds); // Suppose Observable::notifyObservers takes std::map

}

std::map<std::string, nlohmann::json> APIHandler::fetchTodaysEvents()
{
	// Obtenez la date du jour au format YYYY-MM-DD
	std::time_t t = std::time(nullptr);
	char buffer[11];
	std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", std::localtime(&t));
	std::string currentDate(buffer);

	std::string encodedWhere = "&where=%28date_start%3C%3D%22" + currentDate + "%22%20AND%20date_end%3E%3D%22" + currentDate + "%22%29";

	std::string queryUrl = baseUrl + "select=id%2Cdate_start%2Cdate_end%2Caddress_zipcode" + encodedWhere + "&limit=100";

	std::map<std::string, nlohmann::json> allEventIds;

	int offset = 0;
	while (true) {
		std::string urlWithOffset = queryUrl + "&offset=" + std::to_string(offset);
		std::map<std::string, nlohmann::json> eventIds = makeRequest(urlWithOffset);
		if (eventIds.empty()) {
			break;
		}
		allEventIds.insert(eventIds.begin(), eventIds.end());
		offset += 100;
	}
	for (Observer* observer : observers) {
		observer->removeExpiredEvents();
	}
	return allEventIds;
}

std::map<std::string, nlohmann::json> APIHandler::makeRequest(const std::string& url) {
	CURL* curl;
	CURLcode res;
	std::string readBuffer;
	std::map<std::string, nlohmann::json> eventIds;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);  // Your existing WriteCallback function
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			curl_easy_cleanup(curl);
			curl_global_cleanup();
			return eventIds;  // Return empty map on error
		}

		auto jsonResponse = nlohmann::json::parse(readBuffer);
		if (jsonResponse.contains("results") && jsonResponse["results"].is_array()) {
			for (const auto& event : jsonResponse["results"]) {
				if (event.is_object()) {
					std::string id;
					nlohmann::json otherFields;
					for (auto it = event.begin(); it != event.end(); ++it) {
						if (it.key() == "id") {
							id = it.value().get<std::string>();
						}
						else {
							otherFields[it.key()] = it.value();
						}
					}
					if (!id.empty()) {
						eventIds[id] = otherFields;
					}
				}
			}
		}

		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();

	return eventIds;
}
