#include <iostream>
#include <vector>
    using namespace std;

    // Funkcija za generisanje varijacija sa ponavljanjem
    void variations_with_repetition(int n, int k) {
        // Kreiramo listu koja čuva varijacije
        int* list = new int[k];

        // Inicijalizujemo sve elemente niza na 1
        for (int i = 0; i < k; i++) {
            list[i] = 1;
        }

        // Glavna petlja za generisanje varijacija
        while (true) {
            // Ispis trenutne varijacije
            for (int i = 0; i < k; i++) {
                cout << list[i] << " ";
            }
            cout << "\n";

            // Pronađi poziciju gde treba da inkrementiraš
            int i;
            for (i = k - 1; i >= 0; i--) {
                if (list[i] < n) {
                    list[i] += 1;
                    break;
                }
                list[i] = 1; // resetuj trenutnu poziciju ako je dostigla maksimum
            }

            // Ako je cela lista resetovana, prekini
            if (i < 0) break;
        }

        // Oslobađanje memorije
        delete[] list;
    }

    int main() {
        // Unos brojeva n i k
        cout << "Unesi celobrojan broj n: " << endl;
        int n;
        cin >> n;

        cout << "Unesi celobrojan broj k: " << endl;
        int k;
        cin >> k;

        // Poziv funkcije za generisanje varijacija
        variations_with_repetition(n, k);

        return 0;
    }
