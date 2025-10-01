#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <tuple>
#include <mutex>

class ErrorHandler {
public:
    enum class Severity { INFO, WARNING, ERROR, FATAL };

    struct Error {
        int id;
        Severity severity;
        std::string message;
        std::string file;
        int line;
        int count = 1; // deduplication counter
    };

    // Scoped, type-safe error IDs
    struct ErrorID {
    static constexpr int NO_ERROR         = 0;

    // Backend-specific errors
    // GLFW: 10–19
    static constexpr int GLFW_INIT_FAIL   = 10;
    static constexpr int GLFW_MISSING     = 11;
    static constexpr int GLFW_WINDOW_FAIL = 12;

    // SDL: 20–29
    static constexpr int SDL_INIT_FAIL    = 20;
    static constexpr int SDL_MISSING      = 21;

    // Win32: 30–39
    static constexpr int Win32_INIT_FAIL  = 30;
    static constexpr int Win32_MISSING    = 31;

    // Generic/system-level errors: 100–199
    static constexpr int UNKNOWN_BACKEND  = 100;
    static constexpr int CONFIG_LOAD_FAIL = 101;
    static constexpr int RESOURCE_MISSING = 102;
    // ...more generic errors up to 199
};


    // Singleton
    static ErrorHandler& Instance() {
        static ErrorHandler instance;
        return instance;
    }

    // Enable logging to a file
    void SetLogFile(const std::string& filename) {
        std::lock_guard<std::mutex> lock(mutex_);
        logFile_.open(filename, std::ios::out | std::ios::app);
        if (!logFile_) {
            std::cerr << "[ERROR] Could not open log file: " << filename << std::endl;
        }
    }

    // Report an error (thread-safe & deduplicates automatically)
    void Report(int id, Severity sev, const std::string& msg, const std::string& file, int line) {
        auto key = std::make_tuple(id, file, line, msg);

        std::lock_guard<std::mutex> lock(mutex_);
        auto it = errors.find(key);
        if (it != errors.end()) {
            it->second.count++;
        } else {
            errors[key] = { id, sev, msg, file, line, 1 };
        }

        // Print immediately
        Print(errors[key]);
    }

    // Print all stored errors
    void DumpAll() const {
        std::lock_guard<std::mutex> lock(mutex_);
        std::cerr << "\n=== Error Report ===\n";
        for (const auto& [key, err] : errors) {
            Print(err);
        }
    }

private:
    ErrorHandler() = default;
    ~ErrorHandler() {
        if (logFile_.is_open()) logFile_.close();
    }

    using ErrorKey = std::tuple<int, std::string, int, std::string>;
    mutable std::mutex mutex_;
    std::map<ErrorKey, Error> errors; // <-- change from unordered_map to map
    mutable std::ofstream logFile_;

    void Print(const Error& err) const {
        static const char* sevNames[] = { "INFO", "WARNING", "ERROR", "FATAL" };
        std::string output = "[" + std::string(sevNames[static_cast<int>(err.severity)]) + "] "
                            + "ID=" + std::to_string(err.id)
                            + " (" + err.file + ":" + std::to_string(err.line) + "): "
                            + err.message
                            + " [x" + std::to_string(err.count) + "]";

        std::cerr << output << std::endl;
        if (logFile_.is_open()) {
            logFile_ << output << std::endl;
        }
    }
};

using ErrorID = ErrorHandler::ErrorID;
using Severity = ErrorHandler::Severity;

// Macro for convenience — injects __FILE__ and __LINE__
#define REPORT_ERROR(ID, SEV, MSG) \
    ErrorHandler::Instance().Report(ID, SEV, MSG, __FILE__, __LINE__)

#define REPORT_ERROR_IF(CONDITION, ID, SEV, MSG) \
    do { \
        if (CONDITION) { \
            ErrorHandler::Instance().Report(ID, SEV, MSG, __FILE__, __LINE__); \
        } \
    } while(0)