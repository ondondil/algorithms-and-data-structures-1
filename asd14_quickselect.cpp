#include <iostream>
#include <utility>
#include <vector>
#include <climits>

using namespace std;

int quickSelect(vector<pair<int, int>> &countries, int elem)
{
    bool firstRun = true;
    vector<pair<int, int>> *source = &countries;
    vector<pair<int, int>> *less = nullptr;
    vector<pair<int, int>> *equal = nullptr;
    vector<pair<int, int>> *more = nullptr;
    int pivot;
    int result = 0;

    while (true)
    {
        less = new vector<pair<int, int>>;
        equal = new vector<pair<int, int>>;
        more = new vector<pair<int, int>>;
        pivot = (*source)[source->size() / 2].second;
        for (auto i: *source)
        {
            if (i.second < pivot)
                less->push_back(i);
            else if (i.second > pivot)
                more->push_back(i);
            else if (i.second == pivot)
                equal->push_back(i);
        }
        if (elem <= less->size() + result)
        {
            // zwróć i-ty element listy less
            delete equal;
            delete more;
            if (!firstRun)
                delete source;
            else
                firstRun = false;
            source = less;
        }
        else if (elem <= less->size() + equal->size() + result)
        {
            result += less->size();
            delete less;
            delete more;
            if (!firstRun)
                delete source;
            else
                firstRun = false;
            source = equal;
            // zwróć elem (wyszukaj wśród równych second tego o najmniejszej wartości first)
            int min = INT_MAX;
            int m;
            for (m = 0; m < source->size(); ++m)
            {
                if ((*source)[m].first < min)
                {
                    min = (*source)[m].first;
                }
            }
            delete equal;
            return min;
        }
        else
        {
            // zwróć (i - (less->size() + equal->size())-ty element listy more
            result += less->size() + equal->size();
            delete less;
            delete equal;
            if (!firstRun)
                delete source;
            else
                firstRun = false;
            source = more;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    int countryNo, reqNo, req;
    cin >> countryNo;
    vector<pair<int, int>> countries(countryNo);

    // Wczytywanie danych o państwach
    for (int i = 0; i < countryNo; ++i)
    {
        cin >> countries[i].first >> countries[i].second;
    }

    cin >> reqNo;

    for (int i = 0; i < reqNo; ++i)
    {
        cin >> req;
        // Wyszukiwanie elementu
        cout << quickSelect(countries, req) << "\n";
    }

    return 0;
}
