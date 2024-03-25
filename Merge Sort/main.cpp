#include <iostream>
#include <fstream>
/// Merge Sort

int n;
long long maxim;
double array[100000001];

void merge(double v[], int st, int mij, int dr) {
    double aux[n];
    int i = st;
    int j = mij + 1;
    int k = 0; /// indexul vectorului auxiliar

    while (i <= mij && j <= dr) {
        if (v[i] < v[j])
            aux[k++] = v[i++];
        else
            aux[k++] = v[j++];
    }
    while (i <= mij)
        aux[k++] = v[i++];
    while (j <= dr)
        aux[k++] = v[j++];

    for (int p = 0; p < k; ++p)
        v[st + p] = aux[p];
}

void mergeSort(double v[], int st, int dr) {
    if (st < dr) {
        int mij = st + (dr - st) / 2;
        mergeSort(v, st, mij);
        mergeSort(v, mij + 1, dr);

        merge(v, st, mij, dr);
    }
}

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    fin >> n >> maxim;
    for (int i = 0; i < n; ++i) {
        fin >> array[i];
    }

    mergeSort(array, 0, n - 1);

    for (int i = 0; i < n; ++i)
        fout << array[i] << ' ';

    fin.close();
    fout.close();
    return 0;
}
