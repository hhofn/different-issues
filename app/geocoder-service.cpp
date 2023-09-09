#include <iostream>
#include <unordered_map>
#include <string>
#include <utility>

class GeocoderService {
public:
    GeocoderService() {
        // Sample data
        data["New York"] = std::make_pair(40.7128, -74.0060);
        data["Los Angeles"] = std::make_pair(34.0522, -118.2437);
        data["London"] = std::make_pair(51.5074, -0.1278);
    }

    std::pair<double, double> geocode(const std::string& placeName) {
        auto it = data.find(placeName);
        if (it != data.end()) {
            return it->second;
        }
        return std::make_pair(0.0, 0.0); // Not found
    }

    std::string reverseGeocode(double latitude, double longitude) {
        for (const auto& entry : data) {
            if (entry.second.first == latitude && entry.second.second == longitude) {
                return entry.first;
            }
        }
        return "Unknown Location";
    }

private:
    std::unordered_map<std::string, std::pair<double, double>> data;
};

int main() {
    GeocoderService geocoder;

    // Geocoding
    std::string placeName;
    std::cout << "Enter place name for geocoding (e.g., New York): ";
    std::getline(std::cin, placeName);
    auto coordinates = geocoder.geocode(placeName);
    if (coordinates.first != 0.0 || coordinates.second != 0.0) {
        std::cout << placeName << " is located at Latitude: " << coordinates.first
                  << ", Longitude: " << coordinates.second << std::endl;
    } else {
        std::cout << "Location not found." << std::endl;
    }

    // Reverse Geocoding
    double latitude, longitude;
    std::cout << "\nEnter latitude and longitude for reverse geocoding (e.g., 40.7128 -74.0060): ";
    std::cin >> latitude >> longitude;
    std::string location = geocoder.reverseGeocode(latitude, longitude);
    std::cout << "The location at Latitude: " << latitude << ", Longitude: " << longitude
              << " is " << location << std::endl;

    return 0;
}
