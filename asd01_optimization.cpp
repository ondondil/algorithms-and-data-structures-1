#include <iostream>

// Określenie liczby faz badań.
int num_of_test_phases(int max_diff, int max_clue, int clue_no)
{
    int temp_diff, test_phases_no;
    if (max_diff <= 0 && max_clue < clue_no)
    {
        return -1;  // Brak metod.
    }
    else if (max_clue >= clue_no)
    {
        return 1;
    }
    else
    {
        test_phases_no = ((temp_diff = (clue_no - max_clue)) / max_diff) + 1;
        if (temp_diff % max_diff != 0) return test_phases_no + 1;
        else return test_phases_no;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    unsigned int data_set_no;
    int clue_no, method_no, x, y, max_diff, temp, max_clue;

    std::cin >> data_set_no;    // Wczytaj liczbę zestawów danych (t).

    /*
     * Wczytaj liczbę tropów clue_no (n) i metod method_no (m)
     * dla każdego zestawu danych data_set_no (t).
     */
    for (unsigned int i = 0; i < data_set_no; ++i)
    {
        std::cin >> clue_no >> method_no;
        max_diff = max_clue = temp = 0;


        // Wczytanie method_no (m) par liczb x (tropów zbadanych) i y (tropów nowych)
        for (int j = 0; j < method_no; ++j)
        {
            std::cin >> x >> y;
            // Znalezienie największej różnicy.
            if ((temp = x - y) > max_diff) max_diff = temp;
            // Znalezienie największego jednorazowego reduktora tropów.
            if (x > max_clue) max_clue = x;
        }
        if ((temp = num_of_test_phases(max_diff, max_clue, clue_no)) > 0)
            std::cout << temp << "\n";
        else
            std::cout << "BRAK METOD\n";
    }

    return 0;
}
