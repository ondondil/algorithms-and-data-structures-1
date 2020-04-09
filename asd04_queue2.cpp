#include <iostream>
#include <string>
#include <climits>

class Queue
{
private:
    struct Data
    {
        std::string m_name;
        int m_skill;
    };
    struct Node
    {
        Data data;
        int m_max, m_min;
    };
    int m_size, i1, i2;
    Node *s1;
    Node *s2;
public:
    Queue(int size);
    ~Queue();
    bool empty() const;
    void push(const std::string &name, int skill);
    void pop();
    Data& front();
    Data& back();
    int size() const;
    int max() const;
    int min() const;
};

Queue::Queue(int size)
{
    m_size = size;
    s1 = new Node[m_size];
    s2 = new Node[m_size];
    i1 = i2 = 0;
}

Queue::~Queue()
{
    delete [] s1;
    delete [] s2;
}

bool Queue::empty() const
{
    if (i1 == 0 && i2 == 0)
        return true;
    else
        return false;
}

void Queue::push(const std::string &name, int skill)
{
    if (i1 == m_size)
    {
        Node *tmp1 = new Node [m_size * 2];
        Node *tmp2 = new Node [m_size * 2];
        for (int i = 0; i < i1; ++i)
        {
            tmp1[i] = s1[i];
        }
        for (int i = 0; i < i2; ++i)
        {
            tmp2[i] = s2[i];
        }
        m_size *= 2;
        delete [] s1;
        delete [] s2;
        s1 = tmp1;
        s2 = tmp2;
    }
    s1[i1].data.m_name = name;
    s1[i1].data.m_skill = skill;
    if (i1 == 0)
    {
        s1[i1].m_max = skill;
        s1[i1].m_min = skill;
    }
    else
    {
        s1[i1].m_max = s1[i1 - 1].m_max > skill ? s1[i1 - 1].m_max : skill;
        s1[i1].m_min = s1[i1 - 1].m_min < skill ? s1[i1 - 1].m_min : skill;
    }
    ++i1;
}

void Queue::pop()
{
    if (i1 == 0 && i2 == 0)
        return;
    if (i2 > 0)
        --i2;
    else
    {
        for (int i = i1 - 1; i > 0; --i)
        {
            s2[i2].data.m_skill = s1[i].data.m_skill;
            s2[i2].data.m_name = s1[i].data.m_name;
            if (i2 == 0)
            {
                s2[i2].m_max = s2[i2].data.m_skill;
                s2[i2].m_min = s2[i2].data.m_skill;
            }
            else
            {
                s2[i2].m_max = s2[i2 - 1].m_max > s1[i].data.m_skill ? s2[i2 - 1].m_max : s1[i].data.m_skill;
                s2[i2].m_min = s2[i2 - 1].m_min < s1[i].data.m_skill ? s2[i2 - 1].m_min : s1[i].data.m_skill;
            }
            ++i2;
        }
        i1 = 0;
    }
}

Queue::Data &Queue::front()
{
    if (i2 != 0)
    {
        return s2[i2 - 1].data;
    }
    else if (i1 != 0)
    {
        return s1[0].data;
    }
}

Queue::Data &Queue::back()
{
    if (i1 != 0)
    {
        return s1[i1 - 1].data;
    }
    else if (i2 != 0)
    {
        return s2[0].data;
    }
}

int Queue::size() const
{
    return m_size;
}

int Queue::max() const
{
    if (i1 != 0 && i2 != 0)
    {
        return s1[i1 - 1].m_max > s2[i2 - 1].m_max ? s1[i1 - 1].m_max : s2[i2 - 1].m_max;
    }
    else if (i1 != 0 && i2 == 0)
    {
        return s1[i1 - 1].m_max;
    }
    else if (i1 == 0 && i2 != 0)
    {
        return s2[i2 - 1].m_max;
    }
}

int Queue::min() const
{
    if (i1 != 0 && i2 != 0)
    {
        return s1[i1 - 1].m_min < s2[i2 - 1].m_min ? s1[i1 - 1].m_min : s2[i2 - 1].m_min;
    }
    else if (i1 != 0 && i2 == 0)
    {
        return s1[i1 - 1].m_min;
    }
    else if (i1 == 0 && i2 != 0)
    {
        return s2[i2 - 1].m_min;
    }
}

int abs(int x)
{
    if (x >= 0)
        return x;
    else
        return -x;
}

int divide_roundtable(Queue *q1, Queue *q2, int max_skill_diff, int count, int sum1, int sum2)
{
    int tmp_result, best_result = INT_MAX, position = -1;

    std::string tmp_name1;
    int tmp_skill1;

    // Po połowie obrotu poznajemy wszystkie kombinacje
    for (int i = 0; i < count / 2; ++i)
    {
        if (q1->max() - q1->min() <= max_skill_diff && q2->max() - q2->min() <= max_skill_diff)
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

        tmp_name1 = q1->front().m_name;
        tmp_skill1 = q1->front().m_skill;
        sum1 -= tmp_skill1;
        q1->pop();

        sum1 += q2->front().m_skill;
        q1->push(q2->front().m_name, q2->front().m_skill);

        sum2 -= q2->front().m_skill;
        q2->pop();

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

    std::string name, surname;
    int skill, sum1, sum2;
    sum1 = sum2 = 0;

    // Wczytanie do pierwszej kolejki. Kolejka przechowuje połowę naukowców.
    Queue *q1 = new Queue(scientist_count / 2);
    for (int i = 0; i < scientist_count / 2; ++i)
    {
        std::cin >> name >> surname >> skill;
        name += " " + surname;
        sum1 += skill;
        q1->push(name, skill);
    }

    // Wczytanie do drugiej kolejki; jw
    Queue *q2 = new Queue(scientist_count / 2);
    for (int i = 0; i < scientist_count / 2; ++i)
    {
        std::cin >> name >> surname >> skill;
        name += " " + surname;
        sum2 += skill;
        q2->push(name, skill);
    }

    int x = divide_roundtable(q1, q2, max_skill_diff, scientist_count, sum1, sum2);

    print_results(q1, q2, x);

    return 0;
}
