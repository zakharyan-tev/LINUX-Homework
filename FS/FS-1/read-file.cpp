#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
	if(argc != 2) {
        perror("Wrong args");
        exit(EXIT_FAILURE);
    }

    const char* filePath = argv[1];

    std::ifstream file(filePath, std::ios::in | std::ios::binary);
    if (!file) {
        std::cerr << "Error: Cannot open file " << filePath << std::endl;
        return 1;
    }

    const size_t bufferSize = 1024;
    char buffer[bufferSize];

    while (file.read(buffer, bufferSize) || file.gcount() > 0) {
        std::cout.write(buffer, file.gcount());
    }

    file.close();
    return 0; 
}
