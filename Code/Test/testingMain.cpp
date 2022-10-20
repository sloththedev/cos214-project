#include "../Map/Map.h"
#include "../Map/Area.h"
using namespace std;

void testEuropeMap()
{
    Map *m = new Map("../Maps/europe.txt");

    m->printMap();
    cout << (m->getAreaByIndex(6)->toString()) << endl;
    cout << (m->getAreaByIndex(7)->toString()) << endl;
    cout << m->getAreaByIndex(7)->requestFactory(1) << endl;
    cout << (m->getAreaByIndex(7)->toString()) << endl;
    m->createTransportRoute(m->getAreaByIndex(6),m->getAreaByIndex(7));
    cout << m->getAreaByIndex(7)->requestFactory(0) << endl;
    cout << (m->getAreaByIndex(7)->toString()) << endl;

    delete m;
}

void testMap1()
{
    Map *m = new Map("../Maps/map1.txt");
    m->createTransportRoute(m->getAreaByIndex(1), m->getAreaByIndex(2));
    m->createTransportRoute(m->getAreaByIndex(0), m->getAreaByIndex(2));
    m->createTransportRoute(m->getAreaByIndex(1), m->getAreaByIndex(3));
    m->createTransportRoute(m->getAreaByIndex(5), m->getAreaByIndex(3));
    m->printMap();

    for (size_t i = 0; i < 6; i++)
    {
        m->listAdjacent(m->getAreaByIndex(i), false);
    }

    delete m;
}

int main()
{
    // testMap1();
    cout << endl
         << endl;
    testEuropeMap();
}
