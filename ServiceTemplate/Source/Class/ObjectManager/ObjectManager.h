#pragma once
#include <map>
#include <string>
#include <mutex>
#include <memory>
#include <optional>
#include <vector>

template<typename T>
class Manager {
public:
    static std::map<std::string, std::shared_ptr<T>> storage;
    static std::mutex mtx;

public:
    // Get shared_ptr by idreq
    static std::shared_ptr<T> get(const std::string& id) {
        std::lock_guard<std::mutex> lock(mtx);
        auto it = storage.find(id);
        if (it != storage.end()) {
            return it->second;
        }
        return nullptr;
    }

    // Add new object with shared_ptr
    static bool add(const std::string& id, std::shared_ptr<T> obj) {
        std::lock_guard<std::mutex> lock(mtx);
        auto result = storage.insert({ id, obj });
        return result.second; // true if inserted, false if key exists
    }

    // Add new object by creating shared_ptr
    template<typename... Args>
    static bool addNew(const std::string& id, Args&&... args) {
        auto obj = std::make_shared<T>(std::forward<Args>(args)...);
        return add(id, obj);
    }

    // Set object (add or update)
    static void set(const std::string& id, std::shared_ptr<T> obj) {
        std::lock_guard<std::mutex> lock(mtx);
        storage[id] = obj;
    }

    // Set new object by creating shared_ptr
    template<typename... Args>
    static void setNew(const std::string& id, Args&&... args) {
        auto obj = std::make_shared<T>(std::forward<Args>(args)...);
        set(id, obj);
    }

    // Update existing object
    static bool update(const std::string& id, std::shared_ptr<T> obj) {
        std::lock_guard<std::mutex> lock(mtx);
        auto it = storage.find(id);
        if (it != storage.end()) {
            it->second = obj;
            return true;
        }
        return false;
    }

    // Update existing object by creating new shared_ptr
    template<typename... Args>
    static bool updateNew(const std::string& id, Args&&... args) {
        auto obj = std::make_shared<T>(std::forward<Args>(args)...);
        return update(id, obj);
    }

    // Delete object
    static bool del(const std::string& id) {
        std::lock_guard<std::mutex> lock(mtx);
        return storage.erase(id) > 0;
    }

    // Check if exists
    static bool exists(const std::string& id) {
        std::lock_guard<std::mutex> lock(mtx);
        return storage.find(id) != storage.end();
    }

    // Get size
    static size_t size() {
        std::lock_guard<std::mutex> lock(mtx);
        return storage.size();
    }

    // Clear all
    static void clear() {
        std::lock_guard<std::mutex> lock(mtx);
        storage.clear();
    }

    // Get all keys
    static std::vector<std::string> keys() {
        std::lock_guard<std::mutex> lock(mtx);
        std::vector<std::string> result;
        for (const auto& pair : storage) {
            result.push_back(pair.first);
        }
        return result;
    }

    // Get all objects
    static std::vector<std::shared_ptr<T>> values() {
        std::lock_guard<std::mutex> lock(mtx);
        std::vector<std::shared_ptr<T>> result;
        for (const auto& pair : storage) {
            result.push_back(pair.second);
        }
        return result;
    }

    // Get reference count of object
    static long useCount(const std::string& id) {
        std::lock_guard<std::mutex> lock(mtx);
        auto it = storage.find(id);
        if (it != storage.end()) {
            return it->second.use_count();
        }
        return 0;
    }

    // Execute function on object if exists
    template<typename Func>
    static bool execute(const std::string& id, Func&& func) {
        auto obj = get(id);
        if (obj) {
            func(obj);
            return true;
        }
        return false;
    }

    // Execute function on object if exists (with return value)
    template<typename Func>
    static auto executeWith(const std::string& id, Func&& func) -> std::optional<decltype(func(std::declval<std::shared_ptr<T>>()))> {
        auto obj = get(id);
        if (obj) {
            return func(obj);
        }
        return std::nullopt;
    }
};