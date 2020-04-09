#include <iostream>
#include <queue>
#include <utility>

template <typename T>
class Array
{
private:
    T *arr;
    unsigned int m_size, max_size;
public:
    Array();
    Array(unsigned int n);
    ~Array();
    T& operator [](unsigned int index);
    unsigned int size();
    void push_back(T value);
};

template <typename T>
Array<T>::Array()
{
    arr = new T [4];
    max_size = 4;
    m_size = 0;
}

template <typename T>
Array<T>::Array(unsigned int n)
{
    arr = new T [n];
    max_size = n;
    m_size = 0;
}

template <typename T>
Array<T>::~Array()
{
    delete [] arr;
}

template <typename T>
unsigned int Array<T>::size()
{
    return m_size;
}

template <typename T>
void Array<T>::push_back(T value)
{
    arr[m_size++] = value;
}

template <typename T>
T& Array<T>::operator [](unsigned int index)
{
    return arr[index];
}

struct Neighbor
{
    char symbol;
    int id;
    Neighbor() {}
    Neighbor(char s, int i)
    {
        symbol = s;
        id = i;
    }
};

void bfs(int start, int end, Array<Neighbor> *neighbors, int n_size)
{
    std::pair<unsigned short,unsigned short> *visited = new std::pair<unsigned short,unsigned short> [n_size];
    for (int i = 0; i < n_size; ++i)
    {
        visited[i].first = 0;
        visited[i].second = 0;
    }
    std::queue<int> q;

    int curr;
    q.push(start);

    while (!q.empty())
    {
        curr = q.front();
        q.pop();

        if (curr == end)
        {
            std::cout << visited[curr].first << " " << visited[curr].second;
            break;
        }

        for (int i = 0; i < neighbors[curr].size(); i++)    // dla każdego sąsiada obecnego elementu curr
        {
            // neighbors[curr] - lista sąsiadów elementu o ID == curr
            if (visited[neighbors[curr][i].id].first == 0) // jeśli sąsiad nie został odwiedzony
            {
                // neighbors[curr][i].id - ID sąsiada elementu curr
                bool visit = true;
                int tmp;
                for (int j = 0; j < neighbors[neighbors[curr][i].id].size(); j++) // dla każdego sąsiada nieodwiedzonego elementu (sąsiada sąsiada curr)
                {
                    /*
                     * Sprawdzanie czy ten sąsiad jest w tej samej odległości od
                     * startu co obecny element curr) && czy jego
                     * liczba miejsc monitorowanych jest mniejsza niż liczba
                     * miejsc monitorowanych obecnego elementu curr
                     */
                    tmp = neighbors[neighbors[curr][i].id][j].id;   // ID sąsiadów sąsiada elementu curr
                    if (visited[tmp].first == visited[curr].first && visited[tmp].second < visited[curr].second)
                    {
                        // Jeśli tak, nie odwiedzaj.
                        visit = false;
                    }
                }
                if (visit)
                {
                    visited[neighbors[curr][i].id].first = visited[curr].first + 1;
                    if (neighbors[curr][i].symbol == 'M')
                    {
                        visited[neighbors[curr][i].id].second = visited[curr].second + 1;
                    }
                    else
                    {
                        visited[neighbors[curr][i].id].second = visited[curr].second;
                    }
                    q.push(neighbors[curr][i].id);
                }
            }
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int rows, cols;
    std::cin >> rows >> cols;

    // Utworzenie macierzy przechowującej dane wejściowe (posłuży jako wzór)
    Neighbor **input= new Neighbor *[rows];
    for (int i = 0; i < rows; ++i)
    {
        input[i] = new Neighbor [cols];
    }

    // Wczytanie danych do macierzy danych wejściowych
    int init_id = 0, hq_id, dst_id;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            std::cin >> input[i][j].symbol;
            if (input[i][j].symbol == '.')
            {
                input[i][j].id = init_id++;
            }
            else if (input[i][j].symbol == 'M')
            {
                input[i][j].id = init_id++;
            }
            else if (input[i][j].symbol == 'S')
            {
                input[i][j].id = init_id++;
                hq_id = input[i][j].id;
            }
            else if (input[i][j].symbol == 'X')
            {
                input[i][j].id = init_id++;
                dst_id = input[i][j].id;
            }
        }
    }

    // Utworzenie listy sąsiedztwa
    Array<Neighbor> *neighbors = new Array<Neighbor>[init_id];

    // Wypełnienie listy sąsiedztwa wartościami
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (input[i][j].symbol != '#')
            {
                if (j > 0 && input[i][j - 1].symbol != '#')
                {
                    neighbors[input[i][j].id].push_back(Neighbor(input[i][j - 1].symbol, input[i][j - 1].id));
                }
                if (i > 0 && input[i - 1][j].symbol != '#')
                {
                    neighbors[input[i][j].id].push_back(Neighbor(input[i - 1][j].symbol, input[i - 1][j].id));
                }
                if (i < rows - 1 && input[i + 1][j].symbol != '#')
                {
                    neighbors[input[i][j].id].push_back(Neighbor(input[i + 1][j].symbol, input[i + 1][j].id));
                }
                if (j < cols - 1 && input[i][j + 1].symbol != '#')
                {
                    neighbors[input[i][j].id].push_back(Neighbor(input[i][j + 1].symbol, input[i][j + 1].id));
                }
            }
        }
    }

    for (int i = 0; i < rows; ++i)
    {
        delete [] input[i];
    }
    delete [] input;

    bfs(hq_id, dst_id, neighbors, init_id);

    return 0;
}
