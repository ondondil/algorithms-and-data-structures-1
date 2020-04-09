#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    long n, start, day, limit, m;
    cin >> n >> start >> day >> limit >> m;

    /*
     * Struktura mająca postać dwuwymiarowej tablicy przechowującej pary
     * wektor (lista sąsiedztwa dla danego pola) - liczba (liczba cytowań
     * dla danego pola).
     */
    pair<vector<pair<long, long>>, long> **arr = new pair<vector<pair<long, long>>, long> *[n];
    for (long i = 0; i < n; ++i)
    {
        arr[i] = new pair<vector<pair<long, long>>, long> [7];
        for (long j = 0; j < 7; ++j)
        {
            arr[i][j].second = 0;
        }
    }

    long a, b, c, d;
    // Wczytywanie zależności
    for (long i = 0; i < m; ++i)
    {
        cin >> a >> b >> c >> d;
        arr[a][b].first.push_back(make_pair(c, d));
    }

    // Oznaczenie punktu startowego
    arr[start][day].second = 1;
    bool first_run = true;
    long res = 0;
    long curr_day;

    // Główna pętla programu
    for (long i = 0; i < limit; ++i)
    {
        curr_day = (i + day) % 7;
        /*
         * Przechodzenie po wszystkich gazetach danego dnia. Dla każdego
         * rozważanego dnia pole gazety jest zerowane, następnie dodawane są
         * do niego liczby cytowań z dni zawartych w jego liście sąsiedztwa.
         */
        for (long j = 0; j < n; ++j)
        {
            // W pierwszym przejściu nie zerować punktu startowego
            if (first_run && curr_day == day && j == start)
                first_run = false;
            else
                arr[j][curr_day].second = 0;
            if (!arr[j][curr_day].first.empty())
            {
                for (auto &e: arr[j][curr_day].first)
                {
                    arr[j][curr_day].second += arr[e.first][e.second].second % 100000007;
                }
            }
            res += arr[j][curr_day].second % 100000007;
        }
    }

    cout << res % 100000007;
    return 0;
}
