#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

int main()
{
    std::ios_base::sync_with_stdio(false);
    // Wczytywanie liczby t zestawów danych
    int dataset_no, tmp;
    std::cin >> dataset_no;
    for (int z = 0; z < dataset_no; ++z)
    {
        // Wczytywanie poszczególnych zestawów danych
        int name_no, name_pair_no;
        std::cin >> name_no >> name_pair_no;

        bool *visited = new bool[name_no];
        std::unordered_map<std::string, int> targets(name_no);
        std::vector<std::vector<int>> adjacency_list(name_no);
        std::string name1, name2;
        for (int i = 0; i < name_no; ++i)
        {
            std::cin >> name1;
            targets[name1] = i;
            visited[i] = false;
        }

        for (int i = 0; i < name_pair_no; ++i)
        {
            std::cin >> name1 >> name2;
            adjacency_list[targets[name2]].push_back(targets[name1]);
        }

        // Sprawdzanie listy od asystentki
        bool success = true;
        for (int i = 0; i < name_no; ++i)
        {
            std::cin >> name1;
            if (success)
            {
                tmp = targets[name1];
                visited[tmp] = true;
                for (int s: adjacency_list[tmp])
                {
                    if (!visited[s])
                    {
                        success = false;
                        break;
                    }
                }
            }
        }
        if (success)
        {
            std::cout << "TAK\n";
        }
        else
        {
            std::cout << "NIE\n";
        }

        delete [] visited;
    }
    return 0;
}
