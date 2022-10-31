#include "GodOfWar.h"

GodOfWar::GodOfWar(string setupFile)
{

    int resp;
    cout << "Choose your mode:" << endl
         << "1. Real \n2. Design" << endl;
    cin >> resp;

    // clear buffer
    cin.ignore(30, '\n');

    if (resp == 1)
    {
        this->real = true;
    }
    else
    {
        this->real = false;
    }

    if (this->real)
    {
        this->player = new CPU();
    }
    else
    {
        this->player = new User();
    }

    cout << "Initialising map" << endl;

    ifstream inputFile(setupFile);
    vector<string> lines;
    string line;

    while (getline(inputFile, line) && line.at(0) != '#')
    {
        lines.push_back(line);
    }

    inputFile.close();

    string name = "";
    int colour = 0;
    string temp = "";
    for (int i = 0; i < lines.at(0).length(); i++)
    {
        if (lines.at(0).at(i) == ':')
        {
            name = temp;
            temp = "";
        }
        else
        {
            temp += (lines.at(0).at(i));
            if (i == lines.at(0).length() - 1)
            {
                colour = stoi(temp);
                temp = "";
            }
        }
    }
    groupOne = new Alliances(name, colour);
    name = "";
    colour = 0;

    for (int i = 0; i < lines.at(1).length(); i++)
    {
        if (lines.at(1).at(i) == ':')
        {
            name = temp;
            temp = "";
        }
        else
        {
            temp += (lines.at(1).at(i));
            if (i == lines.at(1).length() - 1)
            {
                colour = stoi(temp);
                temp = "";
            }
        }
    }
    groupTwo = new Alliances(name, colour);

    map = new Map(setupFile, player);

    this->turn = true;
}

void GodOfWar::takeTurn(int actions)
{
    this->map->printMap();
    Alliances *active = (turn) ? this->groupOne : this->groupTwo;
    while (actions > 0)
    {
        /*
        Inspect
        */
        this->player->inspect(this->map);

        /*
        Choose a country
        */
        vector<Country *> countries = this->map->getCountriesByColour(active->getColour());
        int countryIndex = 0;
        if (countries.size() == 0)
        {
            cout << "This alliance has no countries left" << endl;
            cout << "END OF WAR" << endl;
            return;
        }
        else if (countries.size() == 1)
        {
            countryIndex = 0;
        }
        else
        {
            countryIndex = this->player->chooseCountry(countries);
        }

        /*
        Get areas occupied by this country
        */
        vector<Area *> areas = this->map->getAreasByCountry(countries.at(countryIndex));

        /*
        Choose area to take action in
        */
        int areaIndex = -1;
        if (areas.size() == 0)
        {
            cout << "This country occupies no areas - lose turn" << endl;
            break;
        }
        else if (areas.size() == 1)
        {
            areaIndex = 0;
        }
        else
        {
            areaIndex = this->player->chooseAreaForAction(areas);
        }

        /*
        Select an action
        */
        int action = this->player->chooseActionForCountry();

        /*
        Chosen to attack transport route
        */
        if (action == 0)
        {
            /*
            List of adjacent areas to destroy transport routes between
            */
            vector<Area *> adjacentAreas = this->map->listAdjacent(areas.at(areaIndex), true);
            int adjAreaIndex = -1;
            if (adjacentAreas.size() == 0)
            {
                cout << "No adjacent transport routes to destroy" << endl;
                break;
            }
            else if (adjacentAreas.size() == 1)
            {
                adjAreaIndex = 0;
            }
            else
            {
                adjAreaIndex = this->player->chooseAdjacentArea(adjacentAreas);
            }

            cout << "Destroying route between:" << endl
                 << areas.at(areaIndex)->toString() << endl
                 << adjacentAreas.at(adjAreaIndex)->toString() << endl;

            this->map->destroyTransportRoute(areas.at(areaIndex), adjacentAreas.at(adjAreaIndex));
        }
        /*
        Request resources
        */
        else if (action == 1)
        {
            int resource = this->player->chooseResource(areas.at(areaIndex));
            if (areas.at(areaIndex)->requestFactory(resource))
            {
                cout << "Factory succesfully acquired" << endl;
                cout << areas.at(areaIndex)->toString();
            }
            else
            {
                cout << "Area could not acquire requested factory" << endl;
            }
        }
        /*
        March to adjacent area
        */
        else if (action == 2)
        {
            /*
            List of adjacent areas to march to
            */
            vector<Area *> adjacentAreas = this->map->listAdjacent(areas.at(areaIndex), false);
            int adjAreaIndex = -1;
            if (adjacentAreas.size() == 0)
            {
                cout << "No adjacent areas" << endl;
                break;
            }
            else if (adjacentAreas.size() == 1)
            {
                adjAreaIndex = 0;
            }
            else
            {
                adjAreaIndex = this->player->chooseAdjacentArea(adjacentAreas);
            }

            cout << "Marching from " << areas.at(areaIndex)->getName() << " to " << adjacentAreas.at(adjAreaIndex)->getName() << endl;
            areas.at(areaIndex)->marchOut(adjacentAreas.at(adjAreaIndex));
        }
        else
        {
            actions = 0;
        }
        actions--;
    }
}

void GodOfWar::warLoop()
{
    int resp = 0;
    do
    {
        round();
        if (this->map->checkIfEnd() != 94)
        {
            resp = 0;
        }else{
        cout << "Continue:" << endl
             << "1. Yes " << endl;
        cin >> resp;

        // clear buffer
        cin.ignore(30, '\n');
        }
    } while (resp == 1);

    int colour = this->map->checkIfEnd();
    cout<<"---------------------------------------------------------------"<<endl;
    cout<<"---------------------------------------------------------------"<<endl;
    if(colour == 94){
        cout<<"WAR ENDS WITH PEACE TREATY"<<endl;
    }else{
        if(colour == this->groupOne->getColour()){
            cout<<"WAR ENDS WITH "<<this->groupOne->getName()<<" AS THE GLOBAL SUPERPOWER"<<endl;
        }else{
            cout<<"WAR ENDS WITH "<<this->groupTwo->getName()<<" AS THE GLOBAL SUPERPOWER"<<endl;
        }
    }
}

void GodOfWar::round()
{

    /*
        First alliance turn
    */
    if (!this->real)
    {
        this->checkTogglePlayer();
    }

    this->turn = true;

    this->takeTurn(3);

    this->map->resolveBattles();

    if (this->map->checkIfEnd() != 94)
    {
        return;
    }

    /*
        Second alliance turn
    */
    this->turn = false;

    if (!this->real)
    {
        this->checkTogglePlayer();
    }

    this->takeTurn(3);

    this->map->resolveBattles();

    // this->map->toStringCount();
}

void GodOfWar::checkTogglePlayer()
{
    if (this->player->changePlayer())
    {
        Player *temp = this->player->togglePlayer();
        delete this->player;
        this->player = temp;
        this->map->setPlayer(this->player);
    }
}

void GodOfWar::initialiseSides()
{
    cout << "--------------------------------------------------------------" << endl;
    cout << "INITIALISING SIDES" << endl;
    cout << "--------------------------------------------------------------" << endl;
    this->player->initialise(this->groupOne, this->groupTwo, this->map);
}

void GodOfWar::printMap()
{
    this->map->printMap();
}

GodOfWar::~GodOfWar()
{
    /*
    Delete alliances
    */
    delete this->groupOne;
    delete this->groupTwo;

    /*
    Delete map
    */
    delete this->map;

    /*
    Delete player
    */
    delete this->player;
}