#include "pch.h"
#include "ObjectManager.h"
// Static member definitions
template<typename T>
std::map<std::string, std::shared_ptr<T>> Manager<T>::storage;

template<typename T>
std::mutex Manager<T>::mtx;

// Usage examples:
/*
#include <iostream>

// Define your data types
struct User {
    std::string name;
    int age;
    std::string email;

    User(const std::string& n, int a, const std::string& e)
        : name(n), age(a), email(e) {}

    void print() const {
        std::cout << "User: " << name << ", Age: " << age << ", Email: " << email << std::endl;
    }
};

struct Config {
    std::string key;
    std::string value;

    Config(const std::string& k, const std::string& v) : key(k), value(v) {}
};

// Define managers
using UserManager = Manager<User>;
using ConfigManager = Manager<Config>;
using StringManager = Manager<std::string>;

int main() {
    // Method 1: Create shared_ptr manually
    auto user1 = std::make_shared<User>("John", 25, "john@email.com");
    UserManager::add("user1", user1);

    // Method 2: Create object directly in manager
    UserManager::addNew("user2", "Jane", 30, "jane@email.com");

    // Get and use objects
    auto user = UserManager::get("user1");
    if (user) {
        user->print();
        std::cout << "Reference count: " << user.use_count() << std::endl;
    }

    // Execute function on object
    UserManager::execute("user2", [](auto userPtr) {
        userPtr->age = 31;
        userPtr->print();
    });

    // Execute with return value
    auto email = UserManager::executeWith("user1", [](auto userPtr) {
        return userPtr->email;
    });
    if (email) {
        std::cout << "Email: " << *email << std::endl;
    }

    // Config management
    ConfigManager::setNew("db_config", "database_url", "localhost:5432");

    // String management
    StringManager::addNew("session_123", "active_session_data");

    // Check reference counts
    std::cout << "User1 ref count: " << UserManager::useCount("user1") << std::endl;

    return 0;
}
*/