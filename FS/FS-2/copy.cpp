#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <source_file> <destination_file>" << std::endl;
        return 1;
    }

    const char* sourcePath = argv[1];
    const char* destPath   = argv[2];

    std::ifstream src(sourcePath, std::ios::in | std::ios::binary);
    if (!src) {
        std::cerr << "Error: Cannot open source file " << sourcePath << std::endl;
        return 1;
    }
  
    std::ofstream dst(destPath, std::ios::out | std::ios::binary | std::ios::trunc);
    if (!dst) {
        std::cerr << "Error: Cannot open destination file " << destPath << std::endl;
        return 1;
    }
  
    const size_t bufferSize = 4096;
    char buffer[bufferSize];
    while (src.read(buffer, bufferSize) || src.gcount() > 0) {
        dst.write(buffer, src.gcount());
    }

    src.close();
    dst.close();

    return 0;
}
