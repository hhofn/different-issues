#include <vector>
#include <map>

struct OracleData {
    int year;
    std::string area_name;
    double emission_value;
};

struct MongoDBData {
    int year;
    std::vector<std::pair<std::string, double>> area_emissions;
};

// Sample function to fetch CO2 data from Oracle
std::vector<OracleData> fetchCO2Data() {
    std::vector<OracleData> data;
    // Logic to fetch data using OCI functions
    // For demonstration purposes, let's add some dummy data
    data.push_back({2021, "Area1", 5000.0});
    data.push_back({2021, "Area2", 6000.0});
    data.push_back({2022, "Area1", 5500.0});
    // ...
    return data;
}

// Transform the data from Oracle format to MongoDB format
std::vector<MongoDBData> transformData(const std::vector<OracleData>& oracleData) {
    std::map<int, std::vector<std::pair<std::string, double>>> transformation;

    for (const auto& entry : oracleData) {
        transformation[entry.year].push_back({entry.area_name, entry.emission_value});
    }

    std::vector<MongoDBData> mongoData;
    for (const auto& [year, areas] : transformation) {
        mongoData.push_back({year, areas});
    }

    return mongoData;
}

// Function to connect and push data to MongoDB
void migrateToMongoDB(const std::vector<MongoDBData>& mongoData) {
    // ... (existing MongoDB connection setup)

    for (const auto& entry : mongoData) {
        bsoncxx::builder::stream::document document{};
        document << "year" << entry.year;

        bsoncxx::builder::stream::array areas;
        for (const auto& [area_name, emission_value] : entry.area_emissions) {
            areas << bsoncxx::builder::stream::open_document
                  << "area" << area_name
                  << "emission" << emission_value
                  << bsoncxx::builder::stream::close_document;
        }
        document << "areas" << areas;
        coll.insert_one(document.view());
    }
}

int main() {
    connectToOracle();
    std::vector<OracleData> oracleData = fetchCO2Data();
    std::vector<MongoDBData> transformedData = transformData(oracleData);
    migrateToMongoDB(transformedData);
    return 0;
}
