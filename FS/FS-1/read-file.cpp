#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }

    const char* filePath = argv[1];

    std::ifstream file(filePath, std::ios::in | std::ios::binary);

    if (!file) {
        std::cerr << "Error: Cannot open file " << filePath << std::endl;
        return 1;
    }

    const size_t bufferSize = 1024;
    char buffer[bufferSize + 1]; 
  
    while (file.read(buffer, bufferSize) || file.gcount() > 0) {
        buffer[file.gcount()] = '\0'; 
        std::cout << buffer;
    }

    file.close();
    return 0;
}
