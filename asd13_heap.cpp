#include <iostream>

using namespace std;

struct Node
{
    int id;
    int priority;
    Node() {}
    Node(int id, int priority)
    {
        this->id = id;
        this->priority = priority;
    }
};

class Heap
{
    Node *arr;
    int size;
    int *countries;
    int findVertex(int id) const;
public:
    Heap(Node *arr, int size, int *countries)
    {
        this->arr = arr;
        this->size = size;
        this->countries = countries;
    }
    unsigned int hops(int newId, int newPriority);
};

int Heap::findVertex(int id) const
{
    return countries[id];
}

unsigned int Heap::hops(int newId, int newPriority)
{
    unsigned int steps = 0;
    int v = findVertex(newId);
    Node tmp;
    bool max = false;
    int oldPriority = arr[v].priority;
    arr[v].priority = newPriority;
    if (newPriority > oldPriority)
    {
        // Spróbuj przesiać w górę
        while (!max && v != 0)
        {
            if (arr[v].priority > arr[(v - 1) / 2].priority)
            {
                countries[arr[v].id] = (v - 1) / 2;
                countries[arr[(v - 1) / 2].id] = v;
                tmp = arr[(v - 1) / 2];
                arr[(v - 1) / 2] = arr[v];
                arr[v] = tmp;
                v = (v - 1) / 2;
                ++steps;
            }
            else
            {
                max = true;
            }
        }
    }
    else if (newPriority < oldPriority)
    {
        // Spróbuj przesiać w dół
        max = false;
        while (!max)
        {
            if (2*v+2 < size)
            {
                if (arr[2*v+1].priority > arr[2*v+2].priority || arr[2*v+1].priority == arr[2*v+2].priority)
                {
                    if (arr[v].priority < arr[2*v+1].priority)
                    {
                        countries[arr[v].id] = 2*v+1;
                        countries[arr[2*v+1].id] = v;
                        tmp = arr[2*v+1];
                        arr[2*v+1] = arr[v];
                        arr[v] = tmp;
                        v = 2*v+1;
                        ++steps;
                    }
                    else
                    {
                        max = true;
                    }
                }
                else if (arr[2*v+1].priority < arr[2*v+2].priority)
                {
                    if (arr[v].priority < arr[2*v+2].priority)
                    {
                        countries[arr[v].id] = 2*v+2;
                        countries[arr[2*v+2].id] = v;
                        tmp = arr[2*v+2];
                        arr[2*v+2] = arr[v];
                        arr[v] = tmp;
                        v = 2*v+2;
                        ++steps;
                    }
                    else
                    {
                        max = true;
                    }
                }
            }
            else if (2*v+1 < size)  // ostatni element w lewej gałęzi
            {
                if (arr[v].priority < arr[2*v+1].priority)
                {
                    countries[arr[v].id] = 2*v+1;
                    countries[arr[2*v+1].id] = v;
                    tmp = arr[2*v+1];
                    arr[2*v+1] = arr[v];
                    arr[v] = tmp;
                    v = 2*v+1;
                    ++steps;
                }
                else
                {
                    max = true;
                }
            }
            else
            {
                max = true;
            }
        }
    }
    return steps;
}

int main()
{
    ios_base::sync_with_stdio(false);
    int vertices, id, priority;
    // Tablica: indeks to id państwa, wartość to indeks państwa w tablicy arr
    int *countryId = new int [1001];
    cin >> vertices;
    Node *arr = new Node [vertices];
    for (int i = 0; i < vertices; ++i)
    {
        cin >> id >> priority;
        countryId[id] = i;
        arr[i].id = id;
        arr[i].priority = priority;
    }

    Heap h(arr, vertices, countryId);

    cin >> vertices;

    int sum = 0;

    for (int i = 0; i < vertices; ++i)
    {
        cin >> id >> priority;
        sum += h.hops(id, priority);
    }

    cout << sum << "\n";

    return 0;
}
