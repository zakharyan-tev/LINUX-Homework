#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <algorithm>

void initialize(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input-file>\n";
        std::exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("cant open the input file");
        std::exit(EXIT_FAILURE);
    }

    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("cant dup fd");
        close(fd);
        std::exit(EXIT_FAILURE);
    }

    close(fd);
}

int main(int argc, char** argv)
{
    initialize(argc, argv);

    std::string input;
    if (!(std::cin >> input)) {
        std::cerr << "Error reading input or empty input\n";
        return EXIT_FAILURE;
    }

    std::reverse(input.begin(), input.end());
    std::cout << input << '\n';
    return 0;
}
