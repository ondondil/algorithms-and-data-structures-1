#include <iostream>
#include <string>

int main()
{
    std::ios_base::sync_with_stdio(false);

    // Przyjęcie liczby zestawów danych.
    int data_sets_no;
    std::cin >> data_sets_no;

    int name_no, name_print_no, *nums_arr = nullptr;
    std::string *names_arr = nullptr;

    // Przyjmowanie zestawu danych (nagłówek).
    for (int i = 0; i < data_sets_no; ++i)
    {
        std::cin >> name_no >> name_print_no;
        // Tablice imion i minut; dla tego samego indeksu jedna osoba.
        names_arr = new std::string [name_no];
        nums_arr  = new int [name_no];

        // Przyjmowanie nazwisk.
        for (int j = 0; j < name_no; ++j)
        {
            std::string tmp_name;
            int tmp_num;
            if (j > 0)
            {
                std::cin >> tmp_name >> tmp_num;
                names_arr[j] = tmp_name;
                nums_arr[j]  = tmp_num;
                // Sortowanie przez wstawianie w trakcie tworzenia tablicy.
                int k;
                if (nums_arr[j] > nums_arr[j - 1] || \
                        (nums_arr[j] == nums_arr[j - 1] && \
                         names_arr[j] < names_arr[j - 1]))
                {
                    for (k = j - 1; (k >= 0) && \
                         ((tmp_num > nums_arr[k]) || \
                          (tmp_num == nums_arr[k] && tmp_name < names_arr[k])); --k)
                    {
                        names_arr[k + 1] = names_arr[k];
                        nums_arr[k + 1]  = nums_arr[k];
                    }
                    names_arr[k + 1] = tmp_name;
                    nums_arr[k + 1]  = tmp_num;
                }
            }
            else
            {
                std::cin >> names_arr[j] >> nums_arr[j];
            }
        }

        // Wypisanie pierwszych nazwisk.
        for (int j = 0; j < name_print_no; ++j)
        {
            std::cout << names_arr[j] << " ";
        }

        // Obliczenia na podstawie posortowanej tablicy wskaźników do par imion i minut.
        long long time_sum = 1;
        // Obliczanie całkowitego czasu.
        for (int j = 1; j < name_no; ++j)
        {
            time_sum += 1 + nums_arr[j] * j;
        }
        std::cout << "\n" << (time_sum % 1000003) << "\n";
        delete [] names_arr;
        delete [] nums_arr;
    }

    return 0;
}
