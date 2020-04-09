#include <iostream>
#include <string>

// ----- Lista z bazą szyfru -----
class List1
{
private:
    struct Node
    {
        int value;
        std::string word;
    };
    int size, capacity;
    Node **arr;
public:
    typedef int pos;
    List1();
    ~List1();
    bool empty() const;
    void insert(pos p, int val, const std::string &str);
    void erase(pos p);
    void push_back(int val, const std::string &str);
    Node& at(int n);
    int get_size() const;
};

List1::List1()
{
    capacity = 10;
    arr = new Node*[capacity];
    size = 0;
}

List1::~List1()
{
    for (int i = 0; i < size; ++i)
    {
        delete arr[i];
    }
    delete [] arr;
}

bool List1::empty() const
{
    if (size == 0) return true;
    else return false;
}

void List1::insert(pos p, int val, const std::string &str)
{
    if (size == capacity)
    {
        capacity *= 2;
        Node **tmp_arr = new Node* [capacity];
        for (int i = 0; i < p; ++i)
        {
            tmp_arr[i] = arr[i];
        }
        for (int i = p; i < size; ++i)
        {
            tmp_arr[i+1] = arr[i];
        }
        delete [] arr;
        arr = tmp_arr;
    }
    else
    {
        for (int i = size; i > p; --i)
        {
            arr[i] = arr[i - 1];
        }
    }
    arr[p] = new Node;
    arr[p]->value = val;
    arr[p]->word = str;
    ++size;
}

void List1::erase(pos p)
{
    delete arr[p];
    for (int i = p; i < size - 1; ++i)
    {
        arr[i] = arr[i + 1];
    }
    --size;
}

void List1::push_back(int val, const std::string &str)
{
    if (size == capacity)
    {
        capacity *= 2;
        Node **tmp_arr = new Node* [capacity];
        for (int i = 0; i < size; ++i)
        {
            tmp_arr[i] = arr[i];
        }
        delete [] arr;
        arr = tmp_arr;
    }
    arr[size] = new Node;
    arr[size]->value = val;
    arr[size]->word = str;
    ++size;
}

List1::Node& List1::at(int n)
{
    return *arr[n];
}

int List1::get_size() const
{
    return size;
}

// ----- Lista z dobieranymi słowami -----
class List2
{
private:
    unsigned int size;
    struct Data
    {
        int value1, value2;
        std::string word;
    };
    struct Node
    {
        Data data;
        Node *next;
    };
    Node* first;
    Node* last;
public:
    List2();
    ~List2();
    Data& front();
    Data& back();
    bool empty() const;
    void pop_front();
    void push_back(int val1, int val2, const std::string &str);
};

List2::List2()
{
    first = last = nullptr;
    size = 0;
}

List2::~List2()
{
    while(size > 0)
    {
        pop_front();
    }
}

List2::Data& List2::front()
{
    return first->data;
}

List2::Data& List2::back()
{
    return last->data;
}

bool List2::empty() const
{
    if (size == 0) return true;
    else return false;
}

void List2::pop_front()
{
    if (first == last && first != nullptr)
    {
        delete first;
        first = last = nullptr;
    }
    else if (size > 1)
    {
        Node* tmp = first;
        first = first->next;
        delete tmp;
    }
    --size;
}

void List2::push_back(int val1, int val2, const std::string &str)
{
    if (first == nullptr)
    {
        first = new Node;
        first->next = nullptr;
        first->data.value1 = val1;
        first->data.value2 = val2;
        first->data.word = str;
        last = first;
    }
    else
    {
        last->next = new Node;
        last = last->next;
        last->data.value1 = val1;
        last->data.value2 = val2;
        last->data.word = str;
    }
    ++size;
}

void decoder(List1 *l1, List2 *l2, int pos)
{
    int jump;
    while (!l1->empty())
    {
        if ((jump = l1->at(pos).value) != 0)
        {
            std::cout << l1->at(pos).word << " ";
            l1->erase(pos);
            if (l1->get_size() > 0 && jump > 0)
            {
                pos = (pos - 1 + jump) % l1->get_size();
            }
            else if (l1->get_size() > 0 && jump < 0)
            {
                pos = (pos + jump) % l1->get_size();
                if (pos < 0)
                {
                    pos = l1->get_size() + pos;
                }
            }
        }
        else
        {
            l1->at(pos).value = l2->front().value2;
            jump = l2->front().value2;
            l1->insert(pos, l2->front().value1, l2->front().word);
            l2->pop_front();
            pos = (pos + 1 + jump) % l1->get_size();
            if (pos < 0)
            {
                pos = l1->get_size() + pos;
            }
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    int list1_size, list2_size, start_word_num, value1, value2;
    std::string word_in;

    // Wczytanie liczby słów do wczytania w pierwszej liście i początkowego indeksu
    std::cin >> list1_size >> start_word_num;

    // Wczytywanie pierwszej listy słów
    List1 *l1 = new List1;
    for (int i = 0; i < list1_size; ++i)
    {
        std::cin >> word_in >> value1;
        l1->push_back(value1, word_in);
    }

    // Wczytywanie drugiej listy słów
    List2 *l2 = new List2;
    std::cin >> list2_size;
    for (int i = 0; i < list2_size; ++i)
    {
        std::cin >> word_in >> value1 >> value2;
        l2->push_back(value1, value2, word_in);
    }

    decoder(l1, l2, start_word_num);

    delete l1;
    delete l2;

    return 0;
}
