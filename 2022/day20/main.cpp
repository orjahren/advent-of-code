#include <iostream>
#include <fstream>
#include <vector>

#define LOG(x) std::cout << x << std::endl;

class Point
{
public:
    Point(int x)
    {
        this->val = x;
        this->l = nullptr;
        this->r = nullptr;
    }
    int val;
    Point *l;
    Point *r;
};

int main()
{
    std::string line;
    std::vector<Point *> tuples;
    std::ifstream file("input");
    // std::ifstream file("small");

    Point *z = nullptr;

    while (getline(file, line))
    {
        int x = std::stoi(line);
        Point *pp = new Point(x);
        tuples.push_back(pp);
    }
    LOG("Har lest fil")
    std::cout << "Begynner simulering..\n";
    for (int i = 0; i < tuples.size(); i++)
    {
        Point *p = tuples.at(i);
        p->r = tuples.at((i + 1) % tuples.size());
        p->l = tuples.at((i - 1) % tuples.size());
    }

    const int m = tuples.size() - 1;

    for (int i = 0; i < tuples.size(); i++)
    {
        Point *xp = tuples.at(i);
        if (xp->val == 0)
        {
            z = tuples.at(i);
            continue;
        }
        Point *pp = xp;
        if (xp->val > 0)
        {
            for (int j = 0; j < (xp->val % m); j++)
            {
                pp = pp->r;
            }
            // if (xp->val == pp->val || (xp->l == pp->l && xp->r == pp->r))
            if (&*xp == &*pp)

            // if (*xp == *pp)
            {
                continue;
            }
            tuples.at(i)->r->l = xp->l;
            tuples.at(i)->l->r = xp->r;
            pp->r->l = tuples.at(i);
            xp->r = pp->r;
            pp->r = xp;
            xp->l = pp;
        }
        else
        {
            for (int j = 0; j < ((-(xp->val)) % m); j++)
            {
                pp = pp->l;
            }
            // if (xp == pp)
            // if (xp->val == pp->val)
            // if (xp->val == pp->val || (xp->l == pp->l && xp->r == pp->r))
            if (&*xp == &*pp)
            {
                continue;
            }
            tuples.at(i)->l->r = xp->r;
            tuples.at(i)->r->l = xp->l;
            pp->l->r = tuples.at(i);
            xp->l = pp->l;
            pp->l = xp;
            xp->r = pp;
        }
    }

    int part1res = 0;

    for (short i = 0; i < 3; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            z = z->r;
        }
        LOG(z)
        LOG("i:" << i << ", val: " << z->val)
        part1res += z->val;
    }
    LOG("...done")
    LOG("Part 1: " << part1res)
}