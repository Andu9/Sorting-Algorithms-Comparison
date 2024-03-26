#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <random>
#include <string>

int main() {
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<int> dis(INT_MIN, INT_MAX);

    const int noFiles = 100;
    for (int k = 0; k < noFiles; k += 1) {
        std::ofstream fout("Teste n = 1000, Max = 1000000000/input" + std::to_string(k + 1) + ".in");


        std::cout << "Fisier " << k + 1 << '\n';
        const int testCases = 10000;

        fout << testCases << '\n';
        for (int j = 0; j < testCases; j += 1) {
            const int n = 1000;
            int Max = INT_MIN;
            std::vector<int> v(n);
            for (int i = 0; i < n; i += 1) {
                v[i] = dis(gen);
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

        fout.close();
    }
    return 0;
}
