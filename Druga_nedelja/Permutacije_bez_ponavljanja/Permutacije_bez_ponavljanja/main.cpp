#include <iostream>
#include <vector>
#include <algorithm> // Za std::reverse
using namespace std;

int nextPermutation(int n, vector<int>* list) {
    int k = -1;
    int l = -1;

    // 1. Pronađi najveći indeks k
    for (int i = 0; i < n - 1; i++) {
        if ((*list)[i] < (*list)[i + 1]) {
            k = i;
        }
    }

    // Ako k nije pronađen, niz je u opadajućem redosledu
    if (k == -1) {
        return 0; // Nema sledeće permutacije
    }

    // 2. Pronađi najveći indeks l veći od k
    for (int i = 0; i < n; i++) {
        if ((*list)[k] < (*list)[i]) {
            l = i;
        }
    }

    // 3. Zamenite list[k] i list[l]
    swap((*list)[k], (*list)[l]);

    // 4. Obrni deo niza od k + 1 do kraja
    reverse((*list).begin() + k + 1, (*list).end());

    return 1; // Uspešna permutacija
}

int main() {
    cout << "Unesi broj elemenata n: " << endl;
    int n;
    cin >> n;

    vector<int> list(n);

    // Popunjavanje vektora od 1 do n
    for (int i = 0; i < n; i++) {
        list[i] = i + 1; // Pravilna inicijalizacija
    }

    // Ispis svih permutacija
    do {
        for (int i = 0; i < n; i++) {
            cout << list[i] << " ";
        }
        cout << "\n";

    } while (nextPermutation(n, &list)); // Poziv sledeće permutacije

    return 0;
}
