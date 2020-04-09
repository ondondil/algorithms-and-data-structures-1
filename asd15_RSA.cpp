#include <iostream>

using namespace std;

unsigned long long powMod(unsigned long long c, unsigned long long d, unsigned long long n)
{
    unsigned long long pew;
    if (d == 0)
        return 1;
    if (d == 1)
        return c;
    if (d % 2 == 1)
    {
        pew = powMod(c, d/2, n);
        return c * ((pew * pew) %n) % n;
    }
    else
    {
        pew = powMod(c, d/2, n);
        return  pew * pew % n;  // star wars reference
    }
}

void swap(long long &a, long long &b)
{
    long long c = a;
    a = b;
    b = c;
}

long long invModEuclid(long long a, long long b)
{
    long long x1, x2, y1, y2, aDIVb, aMODb, cpB;
    cpB = b;

    x1 = 1;
    y1 = 0;

    x2 = 0;
    y2 = 1;

    while (b != 0)
    {
        aDIVb = a / b;
        aMODb = a % b;
        a = b;
        b = aMODb;
        x1 = x1 - aDIVb * x2;
        y1 = y1 - aDIVb * y2;
        swap(x1, x2);
        swap(y1, y2);
    }
    if (x1 < 0)
        return x1 + cpB;
    return x1;
}

int main()
{
    ios_base::sync_with_stdio(false);

    long long t, p, q, e, c, n, eulerFun;
    unsigned long long d;
    cin >> t;
    for (long long i = 0; i < t; ++i)
    {
        cin >> p >> q >> e >> c;
        n = p * q;
        eulerFun = (p - 1) * (q - 1);
        d = invModEuclid(e, eulerFun);
        cout << powMod(c, d, n) << "\n";
    }
    return 0;
}
