#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits> // Za korišćenje std::numeric_limits

using namespace std;


double calculateMinDistance(const vector<vector<double>>& holes, int n) {
    double sum = 0.0;
    double distance = 0.0;

    for (int i = 0; i < (n - 1); i++) {
        distance = sqrt((holes[i][0] - holes[i + 1][0]) * (holes[i][0] - holes[i + 1][0]) +
            (holes[i][1] - holes[i + 1][1]) * (holes[i][1] - holes[i + 1][1]));
        sum += distance;
    }
    return sum;
}

int main() {
    cout << "Unesi broj rupica: " << endl;
    int n;
    cin >> n;

    vector<vector<double>> holes;  // Vektor vektora za pakovanje koordinata
    vector<vector<double>> original_holes; // Čuvanje permutacije sa minimalnom sumom
    vector<int> holeIndices(n);    // Vektor za čuvanje redosleda rupa
    double x, y = 0.0;
    double minSum = numeric_limits<double>::max(); // Postavljanje na maksimalnu vrednost
    vector<vector<double>> minPermutation; // Čuvanje permutacije sa minimalnom sumom
    vector<int> minIndexPermutation;       // Čuvanje indeksa sa minimalnom sumom
    int k = 1;
    int permutation = 0;

    // Inicijalizacija indeksa rupa (1, 2, 3, ..., n)
    for (int i = 0; i < n; i++) {
        holeIndices[i] = i + 1; // Početni redosled rupa
        cout << "Unesi x koordinatu za rupicu " << i + 1 << ": ";
        cin >> x;
        cout << "Unesi y koordinatu za rupicu " << i + 1 << ": ";
        cin >> y;
        holes.push_back({ x, y }); // Dodavanje para [x, y] u vektor
    }

    original_holes = holes;

    // Generisanje permutacija i pronalaženje minimalne sume
    do {
        double sum = calculateMinDistance(holes, n);
        k++;
        if (sum < minSum) {
            minSum = sum;  // Ažuriranje minimalne sume
            minPermutation = holes; // Čuvanje permutacije sa minimalnom sumom
            permutation = k;
        }
    } while (next_permutation(holes.begin(), holes.end()));

    

    // Ispis rezultata
    cout << "Minimalna suma udaljenosti: " << minSum << endl;
    cout << "Permutacija sa minimalnom sumom: " << endl;
    for (const auto& hole : minPermutation) {
        cout << "[" << hole[0] << ", " << hole[1] << "] ";
    }
    cout << endl;

    // Ispis redosleda rupa (kombinacija)
    cout << "Kombinacija rupa sa minimalnom sumom: ";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(minPermutation[i] == original_holes[j])
                if (i != n-1) {
                    cout << j + 1 << "-";
                }
                else {
                    cout << j + 1;
                }
                
        }
    }
    cout << endl;

    return 0;
}
