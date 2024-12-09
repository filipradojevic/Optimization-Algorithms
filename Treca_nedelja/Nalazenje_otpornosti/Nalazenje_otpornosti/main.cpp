#include <iostream>
#include <time.h>
#include <math.h>

using namespace std;

#define R_UKUPNO 50
#define R_OHM 75

bool next_partition(int* p, int n)
{
    int k = 0, i;
    int q = 0;

    if (p[0] == 0)
    {
        p[0] = n;
        return true;
    }
    else
    {
        for (i = 0; i < n; i++)
        {
            if (p[i] != 0)
                k = i;
            else
                break;
        }
    }

    while (k >= 0 && p[k] == 1)
    {
        q++;
        k--;
    }

    if (k < 0)
        return false;

    p[k]--;
    q++;

    while (q > p[k])
    {
        p[k + 1] = p[k];
        q = q - p[k];
        k++;
    }

    p[k + 1] = q;
    k++;

    for (i = k + 1; i < n; i++)
        p[i] = 0;

    return true;
}

void calculate_optimal_resistance(int R_REF)
{
    time_t start, stop;
    int p[R_UKUPNO], temp_p[R_UKUPNO];
    double R, Rmin = R_REF, Ropt = 0;
    int Rser = 0, RUsed = 0;

    time(&start);

    if (R_REF > R_OHM)
        Rser = R_REF / R_OHM;

    for (int j = 0; j < R_UKUPNO; j++)
        temp_p[j] = 0;

    for (int i = 1; i < R_UKUPNO - Rser + 1; i++)
    {
        for (int j = 0; j < R_UKUPNO; j++)
            p[j] = 0;

        while (next_partition(p, i))
        {
            R = 0;

            for (int k = 0; k < R_UKUPNO && p[k] > 0; k++)
                R += (double)R_OHM / p[k];

            if (abs(R_REF - Rser * R_OHM - R) < Rmin)
            {
                Rmin = abs(R_REF - Rser * R_OHM - R);
                Ropt = R;

                if (Rmin == 0)
                {
                    cout << "Optimal resistance for R_REF = " << R_REF << " Ohm: " << (double)Ropt + Rser * R_OHM << " Ohm" << endl;

                    for (int k = 0; k < Rser; k++)
                        cout << "Group " << k + 1 << ": 1 resistor" << endl;

                    for (int k = 0; k < R_UKUPNO && p[k] > 0; k++)
                    {
                        RUsed += p[k];
                        cout << "Group " << k + Rser + 1 << ": " << p[k] << " resistors" << endl;
                    }

                    cout << "Total used resistors: " << Rser + RUsed << endl;

                    RUsed = 0;
                }
                else
                {
                    for (int j = 0; j < R_UKUPNO; j++)
                        temp_p[j] = p[j];
                }
            }
        }
    }

    time(&stop);

    if (Rmin != 0)
    {
        cout << "Optimal resistance for R_REF = " << R_REF << " Ohm: " << (double)Ropt + Rser * R_OHM << " Ohm" << endl;

        for (int j = 0; j < Rser; j++)
            cout << "Group " << j + 1 << ": 1 resistor" << endl;

        for (int j = 0; j < R_UKUPNO && temp_p[j] > 0; j++)
        {
            RUsed += temp_p[j];
            cout << "Group " << j + Rser + 1 << ": " << temp_p[j] << " resistors" << endl;
        }

        cout << "Total used resistors: " << Rser + RUsed << endl;
    }

    cout << "Execution time: " << stop - start << " seconds" << endl;
}

int main()
{
    // Define the R_REF values
    int R_REF_values[] = { 58, 483, 717 };

    // Calculate for each R_REF value
    for (int i = 0; i < sizeof(R_REF_values) / sizeof(R_REF_values[0]); i++)
    {
        cout << "Calculating for R_REF = " << R_REF_values[i] << " Ohm:" << endl;
        calculate_optimal_resistance(R_REF_values[i]);
        cout << endl;
    }

    return 0;
}
