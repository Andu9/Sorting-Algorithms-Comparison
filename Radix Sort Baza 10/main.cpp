#include <iostream>
#include <vector>

const int base = 255;

std::vector<int> v;

void CountingSort(int power) {
    int n = v.size() - 1;
    std::vector<int> freq(base, 0);
    for (int i = 1; i <= n; i += 1) {
        freq[v[i] / power % base] += 1;
    }
    for (int i = 1; i < base; i += 1) {
        freq[i] += freq[i - 1];
    }

    std::vector<int> temporary(n + 1);
    for (int i = n; i >= 1; i -= 1) {
        temporary[freq[v[i] / power % base]] = v[i];
        freq[v[i] / power % base] -= 1;
    }

    for (int i = 1; i <= n; i += 1) {
        v[i] = temporary[i];
    }
}

int main() {
    int n; std::cin >> n;
    v.resize(n + 1);
    for (int i = 1; i <= n; i += 1) {
        std::cin >> v[i];
    }

    int Max = v[1];
    for (int i = 2; i <= n; i += 1) {
        if (Max < v[i]) {
            Max = v[i];
        }
    }

    for (int i = 1; Max / i > 0; i *= base) {
        CountingSort(i);
    }

    for (int i = 1; i <= n; i += 1)
        std::cout << v[i] << ' ';
    return 0;
}
