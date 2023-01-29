#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <deque>
struct point
{
    int i;
    int j;
    char letter;
};
void printPlayMatrix(std::vector<std::vector<char>> &v)
{
    for (auto &element : v)
    {
        for (auto &el : element)
        {
            std::cout << el;
        }
        std::cout << std::endl;
    }
}
point findS(std::vector<std::vector<char>> &v,point &endpoint)
{
    point p;
    for (int i = 0; i != v.size(); i++)
    {
        for (int j = 0; j != v[0].size(); j++)
        {
            if (v[i][j] == 'S')
            {
                p.i = i;
                p.j = j;
                v[i][j] = 'a';
            }
            if (v[i][j] == 'E')
            {
                v[i][j] = 'z';
                endpoint.i=i;
                endpoint.j=j;
                endpoint.letter='E';
            }
        }
    }
    return p;
}

class element
{
public:
    element(std::vector<std::vector<char>> &v, int i, int j, int value)
    {
        p.i = i;
        p.j = j;
        p.letter = v[i][j];
        v[i][j] = '~';
        score = value;
        // std::cout << "value:" << p.i <<" " << p.j << " score:" << score << std::endl;
    }
    point get_elementPoint()
    {
        return p;
    }
    int get_score()
    {
        return score;
    }
    void get_adjacent(std::vector<std::vector<char>> &v, std::deque<element> &vec_elements)
    {
        // printPlayMatrix(v);
        // std::cin.get();
        if (p.i < v.size() - 1 && v[p.i + 1][p.j] - p.letter < 2)
        {
            element el1 = element(v, p.i + 1, p.j, score + 1);
            vec_elements.push_front(el1);
        }
        if (p.i > 0 && v[p.i - 1][p.j] - p.letter < 2)
        {
            element el1 = element(v, p.i - 1, p.j, score + 1);
            vec_elements.push_front(el1);
        }
        if (p.j < v[0].size() - 1 && v[p.i][p.j + 1] - p.letter < 2)
        {
            element el1 = element(v, p.i, p.j + 1, score + 1);
            vec_elements.push_front(el1);
        }
        if (p.j > 0 && v[p.i][p.j - 1] - p.letter < 2)
        {
            element el1 = element(v, p.i, p.j - 1, score + 1);
            vec_elements.push_front(el1);
        }
    }

private:
    point p;
    int score;
};
void addElementoSet(std::vector<std::vector<char>> &v, std::deque<element> &el_vec)
{
        for (int i = 0; i != v.size(); i++)
    {
        for (int j = 0; j != v[0].size(); j++)
        {
            if (v[i][j] == 'a')
            {
                element el = element(v, i, j, 0);
                el_vec.push_front(el);
            }
        }
    }
}

int main(int argc, char *argv[])
{

    std::ifstream infile(argv[1]);
    std::string line;
    std::vector<std::vector<char>> vv;
    while (std::getline(infile, line))
    {
        std::vector<char> v;
        std::copy(line.begin(), line.end(), std::back_inserter(v));
        vv.push_back(v);
    }
    point endpoint;
    point start_point = findS(vv, endpoint);
    element el(vv, start_point.i, start_point.j, 0);
    std::deque<element> el_vec;
    el_vec.push_back(el);
    //addElementoSet(vv, el_vec);
    do
    {
        element el1 = el_vec.back();
        el_vec.pop_back();
        if (el1.get_elementPoint().i == endpoint.i && el1.get_elementPoint().j==endpoint.j)
        {
            std::cout << "result is : " << el1.get_score() << std::endl;
            break;
        }
        el1.get_adjacent(vv, el_vec);

    } while (!el_vec.empty());

    return 0;
}