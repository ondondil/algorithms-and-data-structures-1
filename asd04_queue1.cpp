#include <iostream>
#include <string>
#include <climits>

class Pair
{
public:
    int val1, val2;
};

class Queue
{
private:
    struct Node
    {
        std::string m_name;
        int m_skill;
    };
    int m_size, first, last;
    Node *q;
public:
    Queue(int size);
    ~Queue();
    bool empty() const;
    void push(const std::string &name, int skill);
    void pop();
    Node& front();
    Node& back();
    int size() const;
    Pair max() const;
    Pair min() const;
};

Queue::Queue(int size)
{
    m_size = size + 1;  // Dodatkowe puste pole dla pozycji last
    q = new Node[m_size];
    first = last = 0;
}

Queue::~Queue()
{
    delete [] q;
}

bool Queue::empty() const
{
    if (first == last)
        return true;
    else
        return false;
}

void Queue::push(const std::string &name, int skill)
{
    q[last].m_name = name;
    q[last].m_skill = skill;
    last = (last + 1) % m_size;
    if (first == last)
    {
        Node *tmp = new Node [m_size * 2];
        for (int i = 0; i < m_size; ++i)
        {
            tmp[i].m_name = q[first].m_name;
            tmp[i].m_skill = q[first].m_skill;
            first = (first + 1) % m_size;
        }
        delete [] q;
        q = tmp;
        first = 0;
        last = m_size;
        m_size *= 2;
    }
}

void Queue::pop()
{
    first = (first + 1) % m_size;
}

Queue::Node &Queue::front()
{
    return q[first];
}

Queue::Node &Queue::back()
{
    if (last == 0 && !empty())
        return q[m_size - 1];
    else if (first == last)
        return q[last];
    else
        return q[last - 1];
}

int Queue::size() const
{
    return m_size;
}

Pair Queue::max() const
{
    int m_max = q[first].m_skill, count = 1;
    for (int i = first + 1; i != last; i = (i + 1) % m_size)
    {
        if (m_max < q[i].m_skill)
        {
            m_max = q[i].m_skill;
            count = 1;
        }
        else if (m_max == q[i].m_skill)
            ++count;
    }
    return Pair{m_max, count};
}

Pair Queue::min() const
{
    int m_min = q[first].m_skill, count = 1;
    for (int i = first + 1; i != last; i = (i + 1) % m_size)
    {
        if (m_min > q[i].m_skill)
        {
            m_min = q[i].m_skill;
            count = 1;
        }
        else if (m_min == q[i].m_skill)
            ++count;
    }
    return Pair{m_min, count};
}

int abs(int x)
{
    if (x >= 0)
        return x;
    else
        return -x;
}

int scientific_centipede(Queue *q1, Queue *q2, int max_skill_diff, int count,
                       int max1, int max2, int min1, int min2, int maxcount1,
                       int mincount1, int maxcount2, int mincount2, int sum1, int sum2)
{
    int tmp_result, best_result = INT_MAX, position = -1;

    std::string tmp_name1, tmp_name2;
    int tmp_skill1, tmp_skill2;

    // Po połowie obrotu poznajemy wszystkie kombinacje
    for (int i = 0; i < count / 2; ++i)
    {
        if (max1 - min1 <= max_skill_diff && max2 - min2 <= max_skill_diff)
        {
            // Śledzenie najlepszego ustawienia.
            if (position == -1)
            {
                best_result = abs(sum1 - sum2);
                position = i;
            }
            else if ((tmp_result = abs(sum1 - sum2)) < best_result)
            {
                best_result = tmp_result;
                position = i;
            }
        }

        /*
         * Proces przenoszenia pierwszego elementu kolejki do drugiej kolejki
         * dla obu kolejek. Podczas procesu sprawdzane jest czy nowy element
         * w kolejce nie jest nowym min/max i czy usuwany element nie był min/max.
         * Jeśli usuwany element jest jedynym elementem o wartości
         * min/max w danej kolejce, jest wykonywane wyszukiwanie nowego min/max.
         * Jeśli nie był jedynym min/max, zmieniany jest tylko przypisany do
         * danej wartości min/max licznik.
         */

        // Pierwszy element kolejki k1 przypisany do tymczasowych elementów
        tmp_name1 = q1->front().m_name;
        tmp_skill1 = q1->front().m_skill; 
        q1->pop();

        // Sprawdzanie max1 po popie
        if (tmp_skill1 == max1 && maxcount1 == 1)
        {
            Pair tmp_pair = q1->max();
            max1 = tmp_pair.val1;
            maxcount1 = tmp_pair.val2;
        }
        else if (tmp_skill1 == max1)
            --maxcount1;

        // Sprawdzanie min1 po popie
        if (tmp_skill1 == min1 && mincount1 == 1)
        {
            Pair tmp_pair = q1->min();
            min1 = tmp_pair.val1;
            mincount1 = tmp_pair.val2;
        }
        else if (tmp_skill1 == min1)
            --mincount1;

        // Obliczanie sumy k1 po popie
        sum1 -= tmp_skill1;


        // Sprawdzanie czy max1 zmieni się po pushu
        if (q2->front().m_skill > max1)
        {
            max1 = q2->front().m_skill;
            maxcount1 = 1;
        }
        else if (q2->front().m_skill == max1)
            ++maxcount1;

        // Sprawdzanie czy min1 zmieni się po pushu
        if (q2->front().m_skill < min1)
        {
            min1 = q2->front().m_skill;
            mincount1 = 1;
        }
        else if (q2->front().m_skill == min1)
            ++mincount1;

        // Obliczanie sumy k1 po pushu
        sum1 += q2->front().m_skill;
        q1->push(q2->front().m_name, q2->front().m_skill);


        // Sprawdzanie max2 po popie
        tmp_name2 = q2->front().m_name;
        tmp_skill2 = q2->front().m_skill;
        q2->pop();
        if (tmp_skill2 == max2 && maxcount2 == 1)
        {
            Pair tmp_pair = q2->max();
            max2 = tmp_pair.val1;
            maxcount2 = tmp_pair.val2;
        }
        else if (tmp_skill2 == max2)
            --maxcount2;

        // Sprawdzanie min2 po popie
        if (tmp_skill2 == min2 && mincount2 == 1)
        {
            Pair tmp_pair = q2->min();
            min2 = tmp_pair.val1;
            mincount2 = tmp_pair.val2;
        }
        else if (tmp_skill2 == min2)
            --mincount2;

        // Obliczanie sumy k2 po popie
        sum2 -= tmp_skill2;


        // Sprawdzanie czy max2 zmieni się po pushu
        if (tmp_skill1 > max2)
        {
            max2 = tmp_skill1;
            maxcount2 = 1;
        }
        else if (tmp_skill1 == max2)
            ++maxcount2;

        // Sprawdzanie czy min2 zmieni się po pushu
        if (tmp_skill1 < min2)
        {
            min2 = tmp_skill1;
            mincount2 = 1;
        }
        else if (tmp_skill1 == min2)
            ++mincount2;

        // Obliczanie sumy k2 po pushu
        sum2 += tmp_skill1;
        q2->push(tmp_name1, tmp_skill1);
    }

    return position;
}

void print_results(Queue *q1, Queue *q2, int position)
{
    if (position == -1)
    {
        std::cout << "NIE\n";
        return;
    }

    // Ustawianie kolejek do pozycji wypisywania ich zawartości na stdout.
    std::string tmp_name;
    int tmp_skill;
    for (int i = 0; i < position; ++i)
    {
        tmp_name = q1->front().m_name;
        tmp_skill = q1->front().m_skill;
        q1->pop();
        q1->push(q2->front().m_name, q2->front().m_skill);
        q2->pop();
        q2->push(tmp_name, tmp_skill);
    }

    /*
     * Kolejność kolejek do wypisywania jest zamieniona, ponieważ w trakcie
     * wyszykiwania rozwiązań, wykonano tylko pół "obrotu stołem", co sprawiło,
     * że elementy k1 znalazły się w k2 i na odwrót.
     */
    while (!q2->empty())
    {
        std::cout << q2->front().m_name << "\n";
        q2->pop();
    }

    std::cout << "\n";

    while (!q1->empty())
    {
        std::cout << q1->front().m_name << "\n";
        q1->pop();
    }

}

int main()
{
    std::ios_base::sync_with_stdio(false);

    // Wczytanie liczby naukowców i maksymalnej różnicy umiejętności
    int scientist_count, max_skill_diff;
    std::cin >> scientist_count >> max_skill_diff;

    // Wczytanie do pierwszej kolejki
    std::string name, surname;
    int skill, max1, max2, min1, min2, mincount1, mincount2, maxcount1,
            maxcount2, sum1, sum2;
    max1 = max2 = sum1 = sum2 = 0;
    min1 = min2 = 1001;
    mincount1 = mincount2 = maxcount1 = maxcount2 = 0;

    // Kolejka przechowuje połowę naukowców. Obliczenia min, max, sum przy wczytywaniu.
    Queue *q1 = new Queue(scientist_count / 2);
    for (int i = 0; i < scientist_count / 2; ++i)
    {
        std::cin >> name >> surname >> skill;
        name += " " + surname;
        if (skill > max1)
        {
            max1 = skill;
            maxcount1 = 1;
        }
        else if (skill == max1)
            ++maxcount1;

        if (skill < min1)
        {
            min1 = skill;
            mincount1 = 1;
        }
        else if (skill == min1)
            ++mincount1;

        sum1 += skill;
        q1->push(name, skill);
    }

    // Wczytanie do drugiej kolejki; jw
    Queue *q2 = new Queue(scientist_count / 2);
    for (int i = 0; i < scientist_count / 2; ++i)
    {
        std::cin >> name >> surname >> skill;
        name += " " + surname;
        if (skill > max2)
        {
            max2 = skill;
            maxcount2 = 1;
        }
        else if (skill == max2)
            ++maxcount2;

        if (skill < min2)
        {
            min2 = skill;
            mincount2 = 1;
        }
        else if (skill == min2)
            ++mincount2;

        sum2 += skill;
        q2->push(name, skill);
    }

    int x = scientific_centipede(q1, q2, max_skill_diff, scientist_count,
                                 max1, max2, min1, min2, maxcount1, mincount1,
                                 maxcount2, mincount2, sum1, sum2);

    print_results(q1, q2, x);

    return 0;
}
