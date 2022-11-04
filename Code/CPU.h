#ifndef CPU_H
#define CPU_H

#include "Player.h"
#include "User.h"
#include "Battle.h"

class CPU : public Player
{
public:
    /**
     * @brief Check whether the active player will retreat in this turn
     *
     * @param turn
     * @return true
     * @return false
     */
    virtual bool playerRetreat(Battle *battle);

    /**
     * @brief Check whether the active player wants to change strategy in this turn
     *
     * @param active, the unit's whose turn it is
     * @return true if unit wants to change strategy
     * @return false if unit does not want to change strategy
     */
    virtual bool checkChangeStrategy(Unit *active);

    /**
     * @brief Checks whether active side will request reinforcements in their turn
     *
     * @return true if reinforcements will be requested
     * @return false otherwise
     */
    virtual bool requestReinforcements(Battle *battle);

    /**
     * @brief Choses a country to take a turn with
     *
     * @param countries vector of countries of current alliance
     * @return int index of country chosen
     */
    virtual int chooseCountry(vector<Country *> countries, Map *map);

    /**
         * @brief choose which action player wants to take with country
         * 
         * @param area the area who will take the action
         * @param map the map in use
         * 
         * @return int:
         *  - 0 if march into area
         *  - 1 if attack transport route
         *  - 2 if requestResource
         *  - 3 if recruit
         *  - other end turn
         *  
         */
    virtual int chooseActionForCountry(Area * area, Map * map);

    /**
     * @brief choose which area to take action in
     *
     * @param areas list of all areas
     * @return int index of chosen
     */
    virtual int chooseAreaForAction(vector<Area *> areas);

    /**
     * @brief choose area from adjArea list
     *
     * @param adjAreas
     * @return int
     */
    virtual int chooseAdjacentArea(vector<Area *> adjAreas, Area * area);

    /**
     * @brief choose two areas to destroy transport routes between
     *
     * @param adjAreas of immediatly adjacent area
     * @return int array with index 0 containing the first array index and index 1 the second array index of chosen
     */
    virtual int* chooseAreasToDestroyTransportRoutes(vector<Area *> adjAreas, vector<vector<Area*>> otherAdj, Area * current);

    /**
     * @brief choose type of resource to request for area passed in
     *
     * @param area
     * @return int type of resource
     */
    virtual int chooseResource(Area *area);

    /**
     * @brief Check whether to change from CPU->User or User->CPU
     *
     * @return true if change should occur
     * @return false otherwise
     */
    virtual bool changePlayer();

    /**
     * @brief Change between player types
     *
     * @return Player* new player object
     */
    virtual Player *togglePlayer();

    /**
     * @brief randomly assignes a platoon either a land or air branch
     * 
     * @return int 
     */
    virtual int platoonType();

protected:
    /**
     * @brief Creates new Countries and add to map country vector
     *
     */
    virtual void createCountries(Map *map);

    /**
     * @brief Allows user to choose the number of countries to join the alliance
     *
     * @return int
     */
    virtual int numberOfCountriesInAlliance(Map *map);

    /**
     * @brief Choose a country to form part of alliance
     *
     * @return Country *  to chosen country
     */
    virtual Country *chooseCountryToJoinAlliance(Map *map);

    /**
     * @brief Adds a platoon to passed in country
     *
     * @param country the country to which platoon should be added
     *
     */
    virtual void addPlatoons(Country *country, Map *map);

    /**
     * @brief Adds selected factories to selected areas
     *
     */
    virtual void initialiseFactories(Map *map, Alliances *alliance);
};

#endif