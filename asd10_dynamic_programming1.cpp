#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    long n, start, day, limit, m;
    cin >> n >> start >> day >> limit >> m;

    // Tablica przechowująca numery gazet, które cytują kogoś danego dnia (indeks = dzień; wartość = nr gazety).
    unordered_set<long> *quoting_newspapers = new unordered_set<long> [7];
    // Tablica dwuwymiarowa śledząca wartości wyników podproblemów.
    long **results = new long *[n];
    /*
     * Tablica dwuwymiarowa przechowująca listy sąsiedztwa dla pól które cytują.
     * Listy sąsiedztwa zawierają współrzędne cytowanech pól.
     */
    vector<pair<long, long>> **adjacency_table = new vector<pair<long, long>> *[n];

    // Wypełnianie tablicy wynikowej zerami.
    for (long i = 0; i < n; ++i)
    {
        results[i] = new long [7];
        adjacency_table[i] = new vector<pair<long, long>> [7];
        for (long j = 0; j < 7; ++j)
        {
            results[i][j] = 0;
        }
    }

    long a, b, c, d;
    // Wczytywanie zależności do list sąsiedztwa i gazet cytujących do tablicy cytujących.
    for (long i = 0; i < m; ++i)
    {
        cin >> a >> b >> c >> d;
        adjacency_table[a][b].push_back(make_pair(c, d));
        quoting_newspapers[b].insert(a);
    }

    // Oznaczenie punktu startowego (oryginalne źródło).
    results[start][day] = 1;
    /*
     * Jeśli punkt początkowy nikogo nie cytuje, to jego wartość nie jest
     * zliczana w pętli głównej progamu, stąd różne wartości startowe.
     */
    long res;
    if (adjacency_table[start][day].empty())
        res = 1;
    else
        res = 0;
    long curr_day;

    // Główna pętla programu
    for (long i = 0; i < limit; ++i)
    {
        curr_day = (i + day) % 7;
        // Kasowanie początkowej wartości po pierwszym tygodniu.
        if (i == 7 && quoting_newspapers[curr_day].find(start) == quoting_newspapers[curr_day].end())
            results[start][day] = 0;
        for (long newspaper: quoting_newspapers[curr_day])
        {
            // Pominięcie zerowania punktu startowego w pierwszym przejściu, jeśli ten kogoś cytuje.
            if (i == 0 && newspaper == start && curr_day == day) {}
            else
                results[newspaper][curr_day] = 0;

            // Do każdego cytującego pola dodaj wartości z jego sąsiadów.
            for (auto neighbor: adjacency_table[newspaper][curr_day])
            {
                results[newspaper][curr_day] += results[neighbor.first][neighbor.second] % 100000007;
            }
            res += results[newspaper][curr_day] % 100000007;
        }
    }

    cout << res % 100000007;
    return 0;
}
