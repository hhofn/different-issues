#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <random>
#include <openssl/sha.h>

class User {
public:
    User(const std::string& username, const std::string& hashedPassword, const std::string& salt)
        : username(username), hashedPassword(hashedPassword), salt(salt) {}

    std::string getUsername() const { return username; }
    std::string getHashedPassword() const { return hashedPassword; }
    std::string getSalt() const { return salt; }

private:
    std::string username;
    std::string hashedPassword;
    std::string salt;
};

class AuthService {
public:
    bool registerUser(const std::string& username, const std::string& password) {
        if (users.find(username) != users.end()) {
            return false; // User already exists
        }
        std::string salt = generateSalt();
        std::string hashedPassword = hashPassword(password, salt);
        users[username] = User(username, hashedPassword, salt);
        return true;
    }

    bool authenticate(const std::string& username, const std::string& password) {
        auto it = users.find(username);
        if (it != users.end()) {
            std::string hashedPassword = hashPassword(password, it->second.getSalt());
            return hashedPassword == it->second.getHashedPassword();
        }
        return false;
    }

    bool authorize(const std::string& username, const std::string& action) {
        if (username == "admin" && action == "deleteUser") {
            return true;
        }
        return false;
    }

private:
    std::unordered_map<std::string, User> users;

    std::string generateSalt() {
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<> distribution(0, 255);
        std::stringstream ss;
        for (int i = 0; i < 16; ++i) {
            ss << static_cast<char>(distribution(generator));
        }
        return ss.str();
    }

    std::string hashPassword(const std::string& password, const std::string& salt) {
        std::string saltedPassword = password + salt;
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, saltedPassword.c_str(), saltedPassword.size());
        SHA256_Final(hash, &sha256);
        std::stringstream ss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
        }
        return ss.str();
    }
};

int main() {
    AuthService authService;

    // Registration
    std::string username, password;
    std::cout << "Register:\nUsername: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    if (authService.registerUser(username, password)) {
        std::cout << "Registration successful!\n";
    } else {
        std::cout << "Username already exists!\n";
    }

    // Authentication
    std::cout << "Login:\nUsername: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    if (authService.authenticate(username, password)) {
        std::cout << "Login successful!\n";
    } else {
        std::cout << "Invalid credentials!\n";
    }

    // Authorization (simple example)
    std::string action = "deleteUser";
    if (authService.authorize(username, action)) {
        std::cout << "You are authorized to " << action << ".\n";
    } else {
        std::cout << "You are not authorized to " << action << ".\n";
    }

    return 0;
}
