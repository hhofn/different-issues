#include <iostream>
#include <string>
#include <curl/curl.h>

std::size_t callback(const char* in, std::size_t size, std::size_t num, std::string* out) {
    const std::size_t totalBytes(size * num);
    out->append(in, totalBytes);
    return totalBytes;
}

std::string getCustomerDetails(const std::string& customerId) {
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        const std::string url = "https://YOUR_NETSUITE_ENDPOINT/services/NetSuitePort_2021_1"; // Replace with your actual endpoint
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // For demonstration only, don't disable SSL verification in production

        // Construct the SOAP request body (this is a very basic example)
        std::string soapBody = R"(
            <soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/" xmlns:urn="urn:messages_2021_1.platform.webservices.netsuite.com">
                <soapenv:Header>
                    <urn:tokenPassport>YOUR_TOKEN_PASSPORT_DETAILS_HERE</urn:tokenPassport>
                </soapenv:Header>
                <soapenv:Body>
                    <urn:get>
                        <urn:baseRef type="customer" internalId=")" + customerId + R"(" xmlns:platformCore="urn:core_2021_1.platform.webservices.netsuite.com"/>
                    </urn:get>
                </soapenv:Body>
            </soapenv:Envelope>
        )";

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, soapBody.c_str());

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: text/xml");
        headers = curl_slist_append(headers, "SOAPAction: get");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    return response;
}

int main() {
    std::string customerId = "12345"; // Replace with your actual customer ID
    std::string customerDetails = getCustomerDetails(customerId);

    // For simplicity, we're just printing the raw SOAP response.
    // In a real-world scenario, you'd want to parse this XML response to extract the data you need.
    std::cout << "Customer Details:\n" << customerDetails << std::endl;

    return 0;
}
