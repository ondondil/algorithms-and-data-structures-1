#include <iostream>

using namespace std;

// Główny algorytm
bool isEnough(bool *stationsArr, int **connectionsArr, int conSize, int k, int count, int maxVolunteers)
{
    // Jeśli przekroczono maksymalną liczbę wolontariuszy, wróć.
    if (count > maxVolunteers)
    {
        return false;
    }
    // Jeśli osiągnięto ostatni indeks tablicy + 1, sprawdź poprawność uzupełnienia.
    if (k == conSize)
    {
        return true;
    }
    /*
     * Jeśli odcinek jest już w zasięgu wolontariusza (z uwagi na obsadzenie,
     * w którymś z poprzednich kroków rekurencji), omiń go przekazując wartość
     * z kolejnego wywołania funkcji na poziom wyżej.
     */
    if (stationsArr[connectionsArr[k][0]] || stationsArr[connectionsArr[k][1]])
    {
        return isEnough(stationsArr, connectionsArr, conSize, k + 1, count, maxVolunteers);
    }
    else
    {
        /*
         * Jeśli odcinek nie jest w zasięgu wolontariusza, obsadź wolontariusza
         * w jednej ze stacji będących końcem odcinka i wywołaj kolejny poziom rekurencji.
         */
        stationsArr[connectionsArr[k][0]] = true;
        if (isEnough(stationsArr, connectionsArr, conSize, k + 1, count + 1, maxVolunteers))
        {
            return true;
        }
        stationsArr[connectionsArr[k][0]] = false;
        stationsArr[connectionsArr[k][1]] = true;
        if (isEnough(stationsArr, connectionsArr, conSize, k + 1, count + 1, maxVolunteers))
        {
            return true;
        }
        stationsArr[connectionsArr[k][1]] = false;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    int datasetsNo, stations, connections, volunteers, statA, statB;
    cin >> datasetsNo;
    // Wczytywanie poszczególnych zestawów danych
    for (int i = 0; i < datasetsNo; ++i)
    {
        cin >> stations >> connections >> volunteers;

        // Konstrukcja tablicy stacji
        bool *stationsArr = new bool [stations];
        for (int j = 0; j < stations; ++j)
        {
            stationsArr[j] = false;
        }
        int **connectionsArr = new int *[connections];

        // Konstrukcja tablicy wyników.
        for (int j = 0; j < connections; ++j)
        {
            connectionsArr[j] = new int [2];
            cin >> statA >> statB;
            /*
             * Numery stacji zaczynają się od 1 i mogą być równe wielkości
             * tablicy je przechowującej, stąd pomniejszenie o 1 danych wejściowych.
             */
            connectionsArr[j][0] = statA - 1;
            connectionsArr[j][1] = statB - 1;
        }

        // Wywołanie algorytmu
        if (isEnough(stationsArr, connectionsArr, connections, 0, 0, volunteers))
        {
            cout << "TAK\n";
        }
        else
        {
            cout << "NIE\n";
        }

        // Zwalnianie pamięci
        delete [] stationsArr;
        for (int j = 0; j < connections; ++j)
        {
            delete [] connectionsArr[j];
        }
        delete [] connectionsArr;
    }
    return 0;
}
