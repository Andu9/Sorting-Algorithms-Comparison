#include <iostream>
#include <fstream>

double v[100000001];
int n, maxim;

void shellSort(double v[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            double aux = v[i];
            int j = i;
            while (j >= gap && v[j - gap] > v[i]) {
                v[j] = v[j - gap];
                j = j - gap;
            }
            v[j] = aux;
        }
    }
}

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    fin >> n >> maxim;
    for (int i = 0; i < n; ++i) {
        fin >> v[i];
    }

    shellSort(v, n);

    for (int i = 0; i < n; ++i) {
        fout << v[i] << ' ';
    }

    return 0;
}
