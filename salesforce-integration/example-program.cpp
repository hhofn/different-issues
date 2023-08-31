#include <iostream>
#include <cpr/cpr.h>

int main() {
    const std::string SALESFORCE_LOGIN_URL = "https://login.salesforce.com/services/oauth2/token";
    const std::string CLIENT_ID = "YOUR_SALESFORCE_CLIENT_ID";
    const std::string CLIENT_SECRET = "YOUR_SALESFORCE_CLIENT_SECRET";
    const std::string USERNAME = "YOUR_SALESFORCE_USERNAME";
    const std::string PASSWORD = "YOUR_SALESFORCE_PASSWORD_CONCATENATED_WITH_SECURITY_TOKEN";
    const std::string GRANT_TYPE = "password";
    
    auto response = cpr::Post(cpr::Url{SALESFORCE_LOGIN_URL},
                            cpr::Payload{
                                {"grant_type", GRANT_TYPE},
                                {"client_id", CLIENT_ID},
                                {"client_secret", CLIENT_SECRET},
                                {"username", USERNAME},
                                {"password", PASSWORD}
                            });

    if (response.status_code != 200) {
        std::cout << "Error during authentication: " << response.text << std::endl;
        return 1;
    }

    // Extract access token and instance URL from the response (for simplicity, we're not doing actual JSON parsing)
    std::string accessToken = "YOUR_EXTRACTED_ACCESS_TOKEN";  // Extract from response.text
    std::string instanceUrl = "YOUR_EXTRACTED_INSTANCE_URL";  // Extract from response.text

    auto userDetailsResponse = cpr::Get(cpr::Url{instanceUrl + "/services/data/v52.0/chatter/users/me"},
                            cpr::Header{
                                {"Authorization", "Bearer " + accessToken}
                            });

    if (userDetailsResponse.status_code != 200) {
        std::cout << "Error fetching user details: " << userDetailsResponse.text << std::endl;
        return 1;
    }

    std::cout << "User Details: " << userDetailsResponse.text << std::endl;

    return 0;
}
