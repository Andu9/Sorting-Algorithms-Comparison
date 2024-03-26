#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> v;



void ShellSort() {
    int n = v.size() - 1;
    for (int gap = (n >> 1); gap > 0; gap >>= 1) {
        for (int i = gap + 1; i <= n; i += 1) {
            int aux = v[i], j = i;
            while (j > gap && v[j - gap] > v[i]) {
                v[j] = v[j - gap], j = j - gap;
            }
            v[j] = aux;
        }
    }
}

int Partition(int low, int high)
{
    int i = low - 1;
    int pivot = v[high];
    for(int j = low; j < high; j++)
    {
        if(v[j] <= pivot)
        {
            i++;
            std::swap(v[i], v[j]);
        }
    }
    std::swap(v[i + 1], v[high]);
    return i + 1;
}

void QuickSort(int low, int high)
{
    if(low < high)
    {
        int pivot = Partition(low, high);
        QuickSort(low, pivot - 1);
        QuickSort(pivot + 1, high);

    }
}

void Merge(int left, int middle, int right) {
    std::vector<int> aux(right - left + 2);

    int i = left, j = middle + 1, k = 1;
    while (i <= middle && j <= right) {
        if (v[i] < v[j]) {
            aux[k] = v[i], k += 1, i += 1;
        } else {
            aux[k] = v[j], k += 1, j += 1;
        }
    }
    while (i <= middle) {
        aux[k] = v[i], k += 1, i += 1;
    }
    while (j <= right) {
        aux[k] = v[j], k += 1, j += 1;
    }

    for (int i = 1; i <= right - left + 1; i += 1) {
        v[left + i - 1] = aux[i];
    }
}

void MergeSort(int left, int right) {
    if (left < right) {
        int middle = (left + right) >> 1;
        MergeSort(left, middle);
        MergeSort(middle + 1, right);

        Merge(left, middle, right);
    }
}

void CountingSortRadix(int power, const int base) {
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

void RadixSort() {
    const int base = 10;

    int Max = v[1], n = v.size() - 1;
    for (int i = 2; i <= n; i += 1) {
        if (Max < v[i]) {
            Max = v[i];
        }
    }

    for (int i = 1; Max / i > 0; i *= base) {
        CountingSortRadix(i, base);
    }
}

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

    std::vector<int> SortedV(n + 1);
    for (int i = n; i >= 1; i -= 1) {
        SortedV[freq[v[i]]] = v[i];
        freq[v[i]] -= 1;
    }

    for (int i = 1; i <= n; i += 1) {
        v[i] = SortedV[i];
    }
}

bool CheckSorted() {
    int n = v.size() - 1;
    for (int i = 1; i < n; i += 1) {
        if (v[i] <= v[i + 1]) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}

int main() {
    std::ifstream fin("input.in");
    int testCases; fin >> testCases;
    for (int i = 1; i <= testCases; i += 1) {
        int n, Max;
        fin >> n >> Max, v.resize(n + 1);
        for (int i = 1; i <= n; i += 1) {
            fin >> v[i];
        }

        auto start = std::chrono::high_resolution_clock::now();

        /// Plasam sortarea aici

        auto finish = std::chrono::high_resolution_clock::now();
        auto interval = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);

        bool checked = CheckSorted();
        if (checked == true) {
            fout << "Test #" << i << ": " << interval.count() << '\n';
        } else {
            fout << "Test #" << i << " failed\n";
        }
    }
    return 0;
}
