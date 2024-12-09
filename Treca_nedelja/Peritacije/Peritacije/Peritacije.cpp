#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

const int MAX_OTPORNIKA = 50; // Maksimalan broj otpornika
const double OTPORNOST = 75.0; // Otpornost pojedinačnog otpornika

// Funkcija koja računa otpornost za n paralelnih otpornika
double izracunajParalelnuOtpornost(int brojParalelnih) {
    return OTPORNOST / brojParalelnih; // Otpornost paralelne veze
}

// Rekurzivna funkcija za generisanje svih kombinacija
void generisiKombinacije(int preostaliOtpornici, vector<vector<int>>& sveKombinacije, vector<int>& trenutnaGrupa) {
    // Ako su svi otpornici korišćeni, dodaj trenutnu grupu u sve kombinacije
    if (preostaliOtpornici == 0) {
        sveKombinacije.push_back(trenutnaGrupa);
        return;
    }

    // Istraži sve mogućnosti dodavanja novih grupa
    for (int i = 1; i <= preostaliOtpornici; ++i) {
        trenutnaGrupa.push_back(i); // Dodaj grupu sa i otpornika
        generisiKombinacije(preostaliOtpornici - i, sveKombinacije, trenutnaGrupa); // Rekurzivni poziv
        trenutnaGrupa.pop_back(); // Ukloni poslednju grupu (backtrack)
    }
}

// Funkcija za računanje ukupne otpornosti
double izracunajUkupnuOtpornost(const vector<int>& grupa) {
    double ukupnaOtpornost = 0.0;

    // Računaj otpornost za svaku grupu
    for (int otpornik : grupa) {
        ukupnaOtpornost += izracunajParalelnuOtpornost(otpornik);
    }

    return ukupnaOtpornost + (grupa.size() - 1) * OTPORNOST; // Ukupna otpornost sa serijskim vezama
}

// Prikazivanje kombinacija i njihovih otpornosti
void prikaziKombinacije(const vector<vector<int>>& sveKombinacije) {
    cout << fixed << setprecision(2);
    for (const auto& kombinacija : sveKombinacije) {
        double ukupnaOtpornost = izracunajUkupnuOtpornost(kombinacija);

        // Prikaz kombinacije i ukupne otpornosti
        cout << "Grupa: ";
        for (int otpornik : kombinacija) {
            cout << otpornik << " ";
        }
        cout << "=> Ukupna otpornost: " << ukupnaOtpornost << " Ohm" << endl;
    }
}

int main() {
    vector<vector<int>> sveKombinacije; // Vektor za čuvanje svih kombinacija
    vector<int> trenutnaGrupa; // Vektor za trenutnu grupu otpornika

    // Generiši kombinacije otpornika
    generisiKombinacije(MAX_OTPORNIKA, sveKombinacije, trenutnaGrupa);

    // Prikaz svih kombinacija
    cout << "Sve kombinacije rednih i paralelnih veza za " << MAX_OTPORNIKA << " otpornika:\n";
    prikaziKombinacije(sveKombinacije);

    return 0;
}
