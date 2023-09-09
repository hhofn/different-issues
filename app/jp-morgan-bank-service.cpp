#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

std::size_t callback(const char* in, std::size_t size, std::size_t num, std::string* out) {
    const std::size_t totalBytes(size * num);
    out->append(in, totalBytes);
    return totalBytes;
}

nlohmann::json getAccountDetails(const std::string& accessToken) {
    CURL* curl = curl_easy_init();
    nlohmann::json jsonResponse;

    if (curl) {
        const std::string url = "https://api.jpmorgan.com/account/details"; // Hypothetical endpoint
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // For demonstration only, don't disable SSL verification in production

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, ("Authorization: Bearer " + accessToken).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            jsonResponse = nlohmann::json::parse(response);
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    return jsonResponse;
}

int main() {
    std::string accessToken = "YOUR_ACCESS_TOKEN"; // You'd typically get this after an OAuth2 authentication process
    nlohmann::json accountDetails = getAccountDetails(accessToken);

    // Display account details (based on hypothetical response structure)
    std::cout << "Account ID: " << accountDetails["accountId"] << std::endl;
    std::cout << "Balance: " << accountDetails["balance"] << std::endl;

    return 0;
}
