#include <iostream>
#include <string>

std::string test(unsigned &x, unsigned &y, unsigned &id)
{
    unsigned xTest, yTest;
    std::string direction = "";
    switch (id)
    {
    case 0:
        xTest = 5;
        yTest = 5;
        break;
    case 1:
        xTest = 14;
        yTest = 16;
        break;
    default:
        xTest = 0;
        yTest = 0;
        break;
    }
    if(yTest < y)
        direction = "S";
    else if(yTest > y)
        direction = "N";
    if(xTest < x)
        direction += "W";
    else if(xTest > x)
        direction += "E";
    return direction;
}

void find_bugs(unsigned int x, unsigned int y, unsigned int t)
{
    unsigned int xs, xe, xi, ys, ye, yi;

    std::string result;
    for (unsigned int i = 0; i < t; ++i)
    {
        xs = ys = 0;
        xe = x;
        ye = y;
        xi = (xe - xs) / 2;
        yi = (ye - ys) / 2;

        while ((result = test(xi, yi, i)) != "")
        {
            if (result == "N")
            {
                ys = yi;
                yi += (ye - ys) / 2;
            }
            else if (result == "NE")
            {
                ys = yi;
                yi += (ye - ys) / 2;
                xs = xi;
                xi += (xe - xs) / 2;
            }
            else if (result == "E")
            {
                xs = xi;
                xi += (xe - xs) / 2;
            }
            else if (result == "SE")
            {
                ye = yi;
                yi -= (ye - ys) / 2;
                xs = xi;
                xi += (xe - xs) / 2;
            }
            else if (result == "S")
            {
                ye = yi;
                yi -= (ye - ys) / 2;
            }
            else if (result == "SW")
            {
                ye = yi;
                yi -= (ye - ys) / 2;
                xe = xi;
                xi -= (xe - xs) / 2;
            }
            else if (result == "W")
            {
                xe = xi;
                xi -= (xe - xs) / 2;
            }
            else if (result == "NW")
            {
                ys = yi;
                yi += (ye - ys) / 2;
                xe = xi;
                xi -= (xe - xs) / 2;
            }
        }
        if (result == "")
        {
            std::cout << xi << " " << yi << "\n";
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    unsigned int x, y, t;

    // Wczytanie danych wejściowych
    std::cin >> x >> y >> t;

    find_bugs(x, y, t);

    return 0;
}
