#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>

std::ifstream fin("input.in");
std::ofstream fout("output.out");

std::vector<int> v, SortedV;

void CountingSort() {
    int n = v.size() - 1, Max = -1;
    for (int i = 1; i <= n; i += 1) {
        if (Max < v[i]) {
            Max = v[i];
        }
    }

    std::vector<int> freq(Max + 1, 0);
    for (int i = 1; i <= n; i += 1) {
        freq[v[i]] += 1;
    }
    for (int i = 1; i <= Max; i += 1) {
        freq[i] += freq[i - 1];
    }

    SortedV.resize(n + 1);
    for (int i = n; i >= 1; i -= 1) {
        SortedV[freq[v[i]]] = v[i];
        freq[v[i]] -= 1;
    }
}

void GenerateTest(int n, int Max) {
    v.resize(n + 1);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, Max);
    for (int i = 1; i <= n; i += 1) {
        v[i] = dis(gen);
    }
}

bool CheckSorted() {
    int n = v.size() - 2;
    for (int i = 1; i < n; i += 1) {
        if (v[i] <= v[i]) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}

int main() {
    int testCases; fin >> testCases;
    for (int i = 0; i < testCases; i += 1) {
        GenerateTest(1000000000, 100);

        auto start = std::chrono::high_resolution_clock::now();

        CountingSort();

        auto finish = std::chrono::high_resolution_clock::now();
        auto timeInterval = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);

        bool checked = CheckSorted();
        if (checked == true) {
            fout << "Test #" << i << ": " << timeInterval.count() << '\n';
        }


    }
    return 0;
}
