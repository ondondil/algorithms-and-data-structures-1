#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

int main()
{
    std::ios_base::sync_with_stdio(false);
    int dataset_no, passenger_no, join, leave, leave_station, lookup_counter = 0;

    // Przyjęcie liczby zestawów danych
    std::cin >> dataset_no;

    // Przyjmowanie zestawów danych
    for (int i = 0; i < dataset_no; ++i)
    {
        std::cin >> passenger_no;
        std::vector<std::pair<int, int>> passenger_list;
        for (int j = 0; j < passenger_no; ++j)
        {
            std::cin >> join >> leave;
            passenger_list.push_back({join, leave});
        }

        // Sortowanie względem stacji, na której pasażer wysiada
        std::sort(passenger_list.begin(), passenger_list.end(),
                  [](const std::pair<int, int> &x, const std::pair<int, int> &y)
                    {
                        return x.second < y.second;
                    });

        /*
         * Znajdowanie najkrótszych niekolidujących ze sobą kursów.
         * Liczba tych kursów jest równa liczbie oczekiwanej jako wynik
         */
        if (passenger_list.size() != 0)
        {
            ++lookup_counter;
            leave_station = passenger_list[0].second;
            for (std::vector<std::pair<int, int>>::size_type j = 1; j < passenger_list.size(); ++j)
            {
                if (passenger_list[j].first >= leave_station)
                {
                    ++lookup_counter;
                    leave_station = passenger_list[j].second;
                }
            }
            std::cout << lookup_counter << "\n";
        }
        else
        {
            std::cout << 0 << "\n";
        }
        lookup_counter = 0;
    }
    return 0;
}
