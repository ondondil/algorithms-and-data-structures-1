#include <iostream>
#include <vector>
#include <climits>

using namespace std;

long sum = 0;

struct Node
{
    long prio, rand, k1, k2, k3, k4;
    Node()
    {
        k1 = k2 = k3 = k4 = -1;
    }
    long operator[](long n)
    {
        if (n == 0)
            return prio;
        if (n == 1)
            return rand;
        if (n == 2)
            return k1;
        if (n == 3)
            return k2;
        if (n == 4)
            return k3;
        if (n == 5)
            return k4;
    }
};

void countSort(Node *arr, long size, long ind, long min, long max, bool isLast)
{
    Node *arr2 = new Node [size];
    long *ocArr = new long[max - min + 1];
    for (long i = 0; i < (max - min + 1); ++i)
    {
        ocArr[i] = 0;
    }

    for (long i = 0; i < size; ++i)
    {
        ocArr[arr[i][ind] - min]++;
    }

    ocArr[0]--;
    for (long i = 1; i < (max - min + 1); ++i)
    {
        ocArr[i] += ocArr[i - 1];
    }

    for (long i = size - 1; i >= 0; i--)
    {
        arr2[ ocArr[arr[i][ind] - min] ] = arr[i];
        ocArr[arr[i][ind] - min]--;
    }

    for (long i = 0; i < size; ++i)
    {
        arr[i] = arr2[i];
        if (isLast)
            sum += arr[i].rand * i % 100000007;
    }

    delete [] arr2;
    delete [] ocArr;
}

void insertSort(vector<Node> &vec, long ind)
{
    Node tmp;
    long j;
    for (unsigned long i = 1; i < vec.size(); ++i)
    {
        if (vec[i][ind] < vec[i - 1][ind])
        {
            tmp = vec[i];
            for (j = i - 1; (j >= 0) && (vec[j][ind] > tmp[ind]); --j)
            {
                vec[j + 1] = vec[j];
            }
            vec[j + 1] = tmp;
        }
    }
}

void bucketSort(Node *arr, long ind, long size, long min, long max, bool isLast)
{
    long bucIn;
    long bucNum = size;
    vector<Node> *buckets = new vector<Node> [bucNum + 1];
    for (long i = 0; i < size; ++i)
    {
        // Obliczanie indeksu kubełka.
        if (max - min == 0)
            bucIn = 0;
        else
            bucIn = bucNum * (arr[i][ind] - min) / (max - min);
        buckets[bucIn].push_back(arr[i]);
    }

    // Sortowanie poszczególnych kubełków.
    long k = 0;
    for (long i = 0; i <= bucNum; ++i)
    {
        insertSort(buckets[i], ind);
        for (unsigned long j = 0; j < buckets[i].size(); ++j)
        {
            arr[k] = buckets[i][j];
            if (isLast)
                sum += arr[k].rand * k % 100000007;
            ++k;
        }
    }
    delete [] buckets;
}

void radixSort(Node *arr, long size, bool isLast)
{
    bool innerIsLast = false;
    for (long i = 5; i > 1; --i)
    {
        if (isLast && i == 2)
            innerIsLast = true;
        countSort(arr, size, i, -1, 255, innerIsLast);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    long size, randIdMin, randIdMax, uniq, symbNo;
    randIdMin = INT_MAX;
    randIdMax = -1;
    long sortOrder [4];

    // Wczytywanie danych
    cin >> size;
    Node *arr = new Node [size];
    for (long i = 0; i < size; ++i)
    {
        cin >> uniq;            // unikatowy numer
        uniq = uniq - 1;
        cin >> arr[uniq].prio   // priorytet
            >> arr[uniq].rand   // losowy kod
            >> symbNo;          // liczba symboli

        if (arr[uniq].rand > randIdMax)
            randIdMax = arr[uniq].rand;
        if (arr[uniq].rand < randIdMin)
            randIdMin = arr[uniq].rand;
        // Wczytywanie symboli kodów
        if (symbNo == 1)
            cin >> arr[uniq].k1;
        else if (symbNo == 2)
            cin >> arr[uniq].k1 >> arr[uniq].k2;
        else if (symbNo == 3)
            cin >> arr[uniq].k1 >> arr[uniq].k2 >> arr[uniq].k3;
        else if (symbNo == 4)
            cin >> arr[uniq].k1 >> arr[uniq].k2 >> arr[uniq].k3 >> arr[uniq].k4;
        sum += arr[uniq].rand * uniq % 100000007;
    }

    // Wczytanie priorytetów
    cin >> sortOrder[0] >> sortOrder[1] >> sortOrder[2] >> sortOrder[3];

    // Jakiekolwiek sortowanie poprzedzające sortowanie po unikalnym ID jest bezcelowe
    if (sortOrder[0] == 1)
    {
        cout << sum % 100000007 << "\n";
        return 0;
    }
    else
    {
        sum = 0;
    }

    // Pomijanie sortowań po 1. kolumnie (posortowano na wejściu)
    bool keepSorting = false;
    bool isLast = false;
    for (long i = 3; i >= 0; --i)
    {
        if (sortOrder[i] == 1)
        {
            keepSorting = true;
        }
        else
        {
            if (i == 0)
            {
                isLast = true;
            }
            if (keepSorting)
            {
                switch (sortOrder[i])
                {
                case 2:
                    countSort(arr, size, 0, 0, 10, isLast);
                    break;
                case 3:
                    bucketSort(arr, 1, size, randIdMin, randIdMax, isLast);
                    break;
                case 4:
                    radixSort(arr, size, isLast);
                    break;
                }
            }
        }
    }

    cout << sum % 100000007 << "\n";
    return 0;
}
