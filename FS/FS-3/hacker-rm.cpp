#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file-to-erase>\n";
        return 1;
    }

    const char* path = argv[1];

    struct stat st;
    if (stat(path, &st) != 0) {
        std::cerr << "Error: cannot access file\n";
        return 1;
    }
    if (!S_ISREG(st.st_mode)) {
        std::cerr << "Error: not a regular file\n";
        return 1;
    }

    std::ifstream in(path, std::ios::binary | std::ios::ate);
    if (!in) {
        std::cerr << "Error: cannot open file for reading\n";
        return 1;
    }
    std::streamsize size = in.tellg();
    in.close();

    if (size <= 0) {
        if (std::remove(path) != 0) {
            std::cerr << "Error: cannot remove file\n";
            return 1;
        }
        return 0;
    }
  
    std::ofstream out(path, std::ios::binary | std::ios::in);
    if (!out) {
        // пробуем открыть с trunc (если выше не получилось)
        out.open(path, std::ios::binary | std::ios::trunc);
        if (!out) {
            std::cerr << "Error: cannot open file for writing\n";
            return 1;
        }
    }

    const std::size_t BUF = 4096;
    std::vector<char> zeros(BUF, '\0');

    std::streamsize remaining = size;
    while (remaining > 0) {
        std::streamsize to_write = (remaining > (std::streamsize)BUF) ? BUF : remaining;
        out.write(zeros.data(), to_write);
        if (!out) {
            std::cerr << "Error: write failed\n";
            out.close();
            return 1;
        }
        remaining -= to_write;
    }

    out.flush();
    out.close();
  
    if (std::remove(path) != 0) {
        std::cerr << "Error: cannot remove file after overwrite\n";
        return 1;
    }

    return 0;
}
