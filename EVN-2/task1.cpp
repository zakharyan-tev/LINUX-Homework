#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Использование: " << argv[0] << " a b c\n";
        return 1;
    }

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int c = atoi(argv[3]);

    int minVal = a;
    if (b < minVal) minVal = b;
    if (c < minVal) minVal = c;

    int maxVal = a;
    if (b > maxVal) maxVal = b;
    if (c > maxVal) maxVal = c;

    cout << "min-" << minVal << ", max-" << maxVal << endl;

    return 0;
}
