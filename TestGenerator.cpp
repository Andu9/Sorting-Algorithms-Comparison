#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <chrono>
#include <algorithm>

std::vector<int> v, Aux;

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
            int aux = v[i], j;
            for (j = i - gap; j > 0 && v[j] > aux; j -= gap)
                v[j + gap] = v[j];

            v[j + gap] = aux;
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

void resetVector(int n) {
    for (int i = 1; i <= n; ++i) {
        v[i] = Aux[i];
    }
}

int ok = 3;

int main() {
    std::string ceva = "Pentru AVL";
    std::string intrare = "Speciale";
    std::string iesire1 = "Sortari/AVL Sort Results";
    std::string iesire2 = "Sortari/Counting Sort Results";
    std::string iesire3 = "Sortari/Merge Sort Results";
    std::string iesire4 = "Sortari/Quick Sort Results";
    std::string iesire5 = "Sortari/Radix Sort Results";
    std::string iesire6 = "Sortari/Shell Sort Results";
    std::string iesire7 = "Sortari/STL Sort Results";

    std::string fail = "FAIL ------------------------------------------\n";
    for (int k = 1; k <= 1; ++k) {

        std::ifstream fin(intrare + "Pentru AVL");
        std::ofstream fout1(iesire1 + "/" + intrare + "/" + ceva + "/timp.out");
        std::ofstream fout2(iesire2 + "/" + intrare + "/" + ceva + "/timp.out");
        std::ofstream fout3(iesire3 + "/" + intrare + "/" + ceva + "/timp.out");
        std::ofstream fout4(iesire4 + "/" + intrare + "/" + ceva + "/timp.out");
        std::ofstream fout5(iesire5 + "/" + intrare + "/" + ceva + "/timp.out");
        std::ofstream fout6(iesire6 + "/" + intrare + "/" + ceva + "/timp.out");
        std::ofstream fout7(iesire7 + "/" + intrare + "/" + ceva + "/timp.out");


        int testCases; fin >> testCases;
        //std::cout << "Fisierul " << k << '\n';
        for (int i = 1; i <= 10; i += 1) {
            std::cout << "Testul " << i << '\n';
            int n, Max;
            fin >> n >> Max, v.resize(n + 1);
            Aux.resize(n + 1);
            std::cout << "Depunere in vector...\n";
            for (int i = 1; i <= n; i += 1) {
                fin >> Aux[i];
            }

            /// 1 AVL
            resetVector(n);
            std::cout << "AVL SORT start\n";
            auto start = std::chrono::steady_clock::now();
            AVLSort();
            auto finish = std::chrono::steady_clock::now();

            auto interval = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);

            bool checked = CheckSorted();
            if (checked == true) {
                fout1 << interval.count() << '\n';
                std::cout << "AVL SORT end\n";
            } else {
                fout1 << "Test #" << i << " failed\n";
                std::cout << fail;
            }

            /// 2 Counting Sort
            resetVector(n);
            std::cout << "COUNTING SORT start\n";
            start = std::chrono::steady_clock::now();
            CountingSort();
            finish = std::chrono::steady_clock::now();

            interval = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);

            checked = CheckSorted();
            if (checked == true) {
                fout2 << interval.count() << '\n';
                std::cout << "COUNGING SORT end\n";
            } else {
                fout2 << "Test #" << i << " failed\n";
                std::cout << fail;
            }

            /// 3 MERGE sort
            resetVector(n);
            std::cout << "MERGE SORT start\n";
            start = std::chrono::steady_clock::now();
            MergeSort(1, n);
            finish = std::chrono::steady_clock::now();

            interval = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);

            checked = CheckSorted();
            if (checked == true) {
                fout3 << interval.count() << '\n';
                std::cout << "MERGE SORT end\n";
            } else {
                fout3 << "Test #" << i << " failed\n";
                std::cout << fail;
            }


            // 4 Quick
            resetVector(n);
            std::cout << "QUICK SORT start\n";
            start = std::chrono::steady_clock::now();
            QuickSort(1, n);
            finish = std::chrono::steady_clock::now();

            interval = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);

            checked = CheckSorted();
            if (checked == true) {
                fout4 << interval.count() << '\n';
                std::cout << "QUICK SORT end\n";
            } else {
                fout4 << "Test #" << i << " failed\n";
                std::cout << fail;
            }


            ///5 Radix Sort
            resetVector(n);
            std::cout << "RADIX SORT start\n";
            start = std::chrono::steady_clock::now();
            RadixSort();
            finish = std::chrono::steady_clock::now();

            interval = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);

            checked = CheckSorted();
            if (checked == true) {
                fout5 << interval.count() << '\n';
                std::cout << "RADIX SORT end\n";
            } else {
                fout5 << "Test #" << i << " failed\n";
                std::cout << fail;
            }

            /// 6 SHELL
            resetVector(n);
            std::cout << "SHELL SORT start\n";
            start = std::chrono::steady_clock::now();
            ShellSort();
            finish = std::chrono::steady_clock::now();

            interval = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);

            checked = CheckSorted();
            if (checked == true) {
                fout6 << interval.count() << '\n';
                std::cout << "SHELL SORT end\n";
            } else {
                fout6 << "Test #" << i << " failed\n";
                std::cout << fail;
            }

            /// STD SORT
            resetVector(n);
            std::cout << "STD SORT start\n";
            start = std::chrono::steady_clock::now();
            std::sort(v.begin() + 1, v.end());
            finish = std::chrono::steady_clock::now();

            interval = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);

            checked = CheckSorted();
            if (checked == true) {
                fout7 << interval.count() << '\n';
                std::cout << "STL SORT end\n";
            } else {
                fout7 << "Test #" << i << " failed\n";
                std::cout << fail;
            }
            std::cout << '\n';
        }
        fin.close();
        fout1.close();
        fout2.close();
        fout3.close();
        fout4.close();
        fout5.close();
        fout6.close();
    }
    return 0;
}
