#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> v;

struct Nod {
    int val, h = 0, cnt;
    Nod *st, *dr;
};

int inaltime(Nod *x) {
    if (x != nullptr) {
        return x->h;
    }
    return 0;
}

void inordine(Nod* x) {
    if (x != nullptr) {
        inordine(x->st);
        while (x->cnt > 0) {
            v.emplace_back(x->val);
            x->cnt -= 1;
        }
        inordine(x->dr);
    }
}

Nod* nodNou(int valoare) {
    Nod* aux = new Nod;
    aux->val = valoare;
    aux->st = nullptr;
    aux->dr = nullptr;
    aux->h = 1;
    aux->cnt = 1;
    return aux;
}

Nod* rotatieStanga(Nod* x) {
    Nod *y = x->dr;
    Nod *stangaY = y->st;

    y->st = x;
    x->dr = stangaY;

    x->h = std::max(inaltime(x->st), inaltime(x->dr)) + 1;
    y->h = std::max(inaltime(y->st), inaltime(y->dr)) + 1;

    return y;
}

Nod* rotatieDreapta(Nod* x) {
    Nod *y = x->st;
    Nod *dreaptaY = y->dr;

    y->dr = x;
    x->st = dreaptaY;

    x->h = std::max(inaltime(x->st), inaltime(x->dr)) + 1;
    y->h = std::max(inaltime(y->st), inaltime(y->dr)) + 1;

    return y;
}

Nod* inserare(Nod *root, int nr) {
    if (root == nullptr)
        return nodNou(nr);

    if (nr < root->val) /// ramura stanga
        root->st = inserare(root->st, nr);
    else if (nr > root->val) /// ramura dreapta
        root->dr = inserare(root->dr, nr);
    else { /// element egal, marim contorul
        root->cnt++;
        return root;
    }

    root->h = std::max(inaltime(root->st), inaltime(root->dr)) + 1;
    int bf = inaltime(root->st) - inaltime(root->dr); /// Balance Factor

    if (bf > 1) { /// Balansat la stanga
        if (nr < root->st->val) /// Inserare la stanga
            return rotatieDreapta(root);
        else { /// Inserare la dreapta
            root->st = rotatieStanga(root->st);
            return rotatieDreapta(root);
        }
    }
    else if (bf < -1) { /// Balansat la dreapta
        if (nr > root->dr->val) /// Inserare la dreapta
            return rotatieStanga(root);
        else {
            root->dr = rotatieDreapta(root->dr);
            return rotatieStanga(root);
        }
    }
    return root;
}

void AVLSort() {
    Nod * root = nullptr;
    int n = v.size() - 1;
    for (int i = 1; i <= n; i += 1) {
        root = inserare(root, v[i]);
    }
    v.clear(), v.emplace_back(0);
    inordine(root);
}


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
