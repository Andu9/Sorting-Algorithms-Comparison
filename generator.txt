#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <random>
#include <string>

int randomGenerator(int Min = INT_MIN, int Max = INT_MAX) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(Min, Max);

    return dis(gen);
}

int main() {
    const int noFiles = 100;
    for (int k = 0; k < noFiles; k += 1) {
        std::ofstream fout("Teste n = 1000, Max = 1000/input" + std::to_string(k + 1) + ".in");

        const int testCases = 10000;

        fout << testCases;
        for (int j = 0; j < testCases; j += 1) {
            const int n = 1000;
            int Max = INT_MIN;
            std::vector<int> v(n);
            for (int i = 0; i < n; i += 1) {
                v[i] = randomGenerator(-1000, 1000);
                if (v[i] > Max) {
                    Max = v[i];
                }
            }

            fout << n << ' ' << Max << '\n';
            for (int i = 0; i < n; i += 1) {
                fout << v[i] << ' ';
            }
            fout << '\n';
        }

        std::cout << "Fisier " << k + 1 << '\n';

        fout.close();
    }
    return 0;
}
