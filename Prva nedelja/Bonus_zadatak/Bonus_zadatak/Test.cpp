#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>  // Za merenje vremena


using namespace std;

// Funkcija za pronalaženje minimalnog vremena
int transferPeople(vector<int>& times, int N, int M) {
    sort(times.begin(), times.end());  // Sortiramo vremena u rastućem redosledu
    int total_time = 0; //Ukupno najkrace vreme
    int cnt = 0; //Broj iteracija
    vector <int> currentGroup;
    vector <int> arrivalTimes;
    int notEmpty = 1;
    int flag = 0;

    while (N >= M || notEmpty) {
        cnt++;
        
        if (M >= N) { //Ukoliko mogu svi da predju!
            cout << "Otisli su: ";
            for (size_t i = 0; i < times.size(); i++) {
                cout << times[i]; // Ispisujemo element
                if (i < times.size() - 1) {
                    cout << ", "; // Dodajemo zarez ako nije poslednji element
                }
            }
            cout << std::endl; // Novi red nakon ispisa
            total_time += times.back();
            N = 0;
            notEmpty = 0;
        }

        else if (flag == 1) { // Ovo je za slucaj kad imamo 4 osoba sa 3 moguca prelaska da isprazni ostatak koji je preostao u times
            //Tehnicki samo ce proci sve ove ostale i izbaciti vremena i put
            currentGroup.assign(times.begin(), times.end());
            cout << "Otisli su: ";
            for (size_t i = 0; i < currentGroup.size(); i++) {
                cout << currentGroup[i]; // Ispisujemo element
                if (i < currentGroup.size() - 1) {
                    cout << ", "; // Dodajemo zarez ako nije poslednji element
                }
            }
            cout << std::endl; // Novi red nakon ispisa
            total_time += currentGroup.back();
            break;
        }
        


        else if (N - M < M && cnt == 1) { //Ovo je ubaceno za slucaj isto kad imamo 4 coveka sa 3 moguca prelaza da bi uzeli najbrzeg
            //... iz times-a i poslednjih M-1 clanova, odnosno da najbrzi preveze najsporije i da se vrati po ostatak koji ce zavrsiti u narednoj
            // iteraciji sa if flag == 1.
            currentGroup.push_back(times[0]);
            currentGroup.insert(currentGroup.end(), times.end() - M + 1, times.end());
            cout << "Otisli su: ";
            for (size_t i = 0; i < currentGroup.size(); i++) {
                cout << currentGroup[i]; // Ispisujemo element
                if (i < currentGroup.size() - 1) {
                    cout << ", "; // Dodajemo zarez ako nije poslednji element
                }
            }
            cout << std::endl; // Novi red nakon ispisa

            // Izbriši prvu osobu i poslednje M osobe iz times
            times.erase(times.begin(), times.begin() + 1); // Briše prvu osobu
            times.erase(times.end() - M + 1, times.end()); // Briše poslednje M osobe
            arrivalTimes.assign(currentGroup.begin(), currentGroup.end());
            total_time += arrivalTimes.back();
            cout << "Vratio se: " << arrivalTimes.front() << endl;
            if (!arrivalTimes.empty()) {
                times.insert(times.begin(), arrivalTimes.front()); // Umetnuti najbržeg na početak
            }
            arrivalTimes.erase(arrivalTimes.begin());
            if (!times.empty()) {
                total_time += times[0]; // Dodajemo vreme najbržeg iz times
            }
        
        }

        else if (cnt == 1) { //Ovo je standardno ukoliko ima normalan odnos N i M npr 4 i 2 da prevezemo najbrze prvo i da vratimo najbrzeg
            // Prva iteracija uvek šaljemo najbrže.
             
            currentGroup.assign(times.begin(), times.begin() + M);
            cout << "Otisli su: ";
            for (size_t i = 0; i < currentGroup.size(); i++) {
                cout << currentGroup[i]; // Ispisujemo element
                if (i < currentGroup.size() - 1) {
                    cout << ", "; // Dodajemo zarez ako nije poslednji element
                }
            }
            cout << std::endl; // Novi red nakon ispisa

            times.erase(times.begin(), times.begin() + M);
            arrivalTimes.assign(currentGroup.begin(), currentGroup.end());
            total_time += arrivalTimes.back();
            cout << "Vratio se: " << arrivalTimes.front() << endl;
            if (!arrivalTimes.empty()) {
                times.insert(times.begin(), arrivalTimes.front()); // Umetnuti najbržeg na početak
            }
            arrivalTimes.erase(arrivalTimes.begin());
            if (!times.empty()) {
                total_time += times[0]; // Dodajemo vreme najbržeg iz times
            }
        }

        else if (cnt % 2 == 0) { //Ovo je kada smo prevezli najbrze da sada prevezemo najsporije i vratimo jednog brzog
            currentGroup.assign(times.end() - M, times.end());
            
            cout << "Otisli su: ";
            for (size_t i = 0; i < currentGroup.size(); i++) {
                cout << currentGroup[i]; // Ispisujemo element
                if (i < currentGroup.size() - 1) {
                    cout << ", "; // Dodajemo zarez ako nije poslednji element
                }
            }
            cout << std::endl; // Novi red nakon ispisa
            
            times.erase(times.end() - M, times.end());
            arrivalTimes.insert(arrivalTimes.end(), currentGroup.begin(), currentGroup.end());
            total_time += arrivalTimes.back();

            if (!arrivalTimes.empty() && !times.empty()) {
                times.insert(times.begin(), arrivalTimes.front());
            }
            if (!times.empty()) {
                total_time += times[0];
                cout << "Vratio se: " << times[0] << endl;
            }

            sort(times.begin(), times.end());
            arrivalTimes.erase(arrivalTimes.begin());

            
        }
         
        else { //A ovo je da stalno u neparnim iteracijama saljemo najbrze 1,2 npr da bi imao ko da vraca ove najsporije....
            currentGroup.assign(times.begin(), times.begin() + M);
            cout << "Otisli su: ";
            for (size_t i = 0; i < currentGroup.size(); i++) {
                cout << currentGroup[i]; // Ispisujemo element
                if (i < currentGroup.size() - 1) {
                    cout << ", "; // Dodajemo zarez ako nije poslednji element
                }
            }
            cout << std::endl; // Novi red nakon ispisa

            times.erase(times.begin(), times.begin() + M);
            arrivalTimes.insert(arrivalTimes.begin(), currentGroup.begin(), currentGroup.end());
            total_time += currentGroup.back();
            if (!arrivalTimes.empty() && !times.empty()) {
                times.insert(times.begin(), arrivalTimes[0]); // Umetnuti najbržeg na početak
            }
            if (!times.empty() ) {
                total_time += times[0]; // Dodajemo vreme najbržeg iz times
                cout << "Vratio se: " << times[0] << endl;
            }
            arrivalTimes.erase(arrivalTimes.begin());
            sort(times.begin(), times.end());
            
        
        }

        if (times.empty()) { // Ovo da setuje kada je times prazna flag da bi while se prekinuo
            notEmpty = 0;
        }
        N -= (M -1); //Smanjujemo N konstantno za M - 1 prevezenih putnika.

        if (N < M && cnt == 1) { //Ovo se setuje fleg za onaj slucaj kad je M veliko i ostalo je samo nekolicina da predje put.
            flag = 1;
        }
    
        if (times.empty()) { //Da potvrdimo ukoliko je times prazno da totalno izadjemo iz while
            N = 0;
            notEmpty = 0;
        }
    }

    return total_time;
}

int main() {
    int N, M;
    cout << "Unesite broj ljudi N: ";
    cin >> N;
    cout << "Unesite maksimalan broj ljudi koji moze preci odjednom M: ";
    cin >> M;

    vector<int> times(N);
    cout << "Unesite vremena prelaska za svaku osobu:\n";
    for (int i = 0; i < N; i++) {
        cout << "Vreme " << i + 1 << " osobe: ";
        cin >> times[i];
        cout << endl;
    }
    auto start = std::chrono::high_resolution_clock::now();
    int min_time = transferPeople(times, N, M);
    auto end = std::chrono::high_resolution_clock::now();

    // Izračunaj trajanje u milisekundama
    std::chrono::duration<double, std::milli> duration = end - start;
    cout << "Minimalno vreme potrebno da svi predju most je: " << min_time << " minuta.\n";

    // Ispiši vreme izvršavanja
    std::cout << "Vreme izvršavanja: " << duration.count() << " milisekundi" << std::endl;

    return 0;
}
