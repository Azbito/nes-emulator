#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

class Logger {
private:
    std::ofstream logFile;
    bool shouldRegisterDate = true;

    std::string getCurrentTime() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        char buffer[26];
        ctime_s(buffer, sizeof(buffer), &now_time);
        buffer[24] = '\0';
        return std::string(buffer);
    }

public:
    Logger(const std::string& filename) {
        logFile.open(filename + ".log", std::ios::app);
        if (!logFile.is_open()) {
            std::cerr << "Erro ao abrir o arquivo de log!" << std::endl;
        }
    }

    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void log(const std::string& message) {
        if (logFile.is_open() && shouldRegisterDate) {
            logFile << "[" << getCurrentTime() << "] " << message << std::endl;
            return;
        }

        logFile << message;
    }

    void turnOffRegisterDate() {
        shouldRegisterDate = false;
    }
};
