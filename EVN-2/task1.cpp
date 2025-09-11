#include <iostream>
#include <string>
using namespace std;

int myMax(int* arr, int n) {
    int max_el = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_el) {
            max_el = arr[i];
        }
    }
    return max_el;
}

int myMin(int* arr, int n) {
    int min_el = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min_el) {
            min_el = arr[i];
        }
    }
    return min_el;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Использование: " << argv[0] << " a b c\n";
        return 1;
    }

    int arr[3];
    for (int i = 0; i < 3; i++) {
        try {
            size_t pos;
            arr[i] = stoi(argv[i + 1], &pos);
            if (pos != string(argv[i + 1]).size()) {
                cerr << "Ошибка: '" << argv[i + 1] << "' не является числом\n";
                return 1;
            }
        } catch (...) {
            cerr << "Ошибка: '" << argv[i + 1] << "' не является числом\n";
            return 1;
        }
    }

    cout << "min-" << myMin(arr, 3) << ", max-" << myMax(arr, 3) << endl;
    return 0;
}

//решила вообще заново написать весь код))
