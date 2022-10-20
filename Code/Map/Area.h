#ifndef AREA_H
#define AREA_H
#include "MapComponent.h"
#include "../Platoon/Platoon.h"
#include "Iterator.h"
#include "Coordinate.h"
#include "TheatreOfWar.h"
#include "../TransportFactory/TransportFactory.h"
#include "../TransportFactory/PTFactory.h"
#include "../TransportFactory/ATFactory.h"
#include "../TransportFactory/GTFactory.h"
#include <string>

class Battle;

class Area : public MapComponent
{

private:
	vector<Coordinate*> areasCoordinates;
	string name;
	int index;
	int colour;
	TheatreOfWar* land;
	TheatreOfWar* air;
	TransportFactory* allFactories[3];

	

public:
	/**
	 * @brief Construct a new Area object with the given index
	 *
	 * @name name the name of the country
	 * @param index the index of the area (used in the map's adjacency matrix)
	 * @param colour the colour of the area on the map
	 * @param factories indicates whether or not the area starts with factories
	 */
	Area(string name,int index,int colour,bool factories);

	/**
	 * @brief Gets the index of the area for the adjacency matrix
	 *
	 * @return int
	 */
	int getIndex();

	/**
	 * @brief Get the Colour object
	 * 
	 * @return int 
	 */
	int getColour();
	/**
	 * @brief Not a clue right now
	 *
	 * @param type
	 * @param platoonName
	 */


	/**
	 * @brief Get the Name of the area
	 * 
	 * @return string 
	 */
	string getName();
	
	void updatePlatoons(int type, string platoonName);

	/**
	 * @brief Create a Iterator object that can loop through the area (under review)
	 *
	 * @return Iterator*
	 */
	Iterator *createIterator();

	/**
	 * @brief Called when a platoon marches into this area, determines whether or not a battle takes place and returns a Battle pointer if it does, otherwise returns NULL
	 * @details When a platoon marches into an area a few things could happen depending on the state of the area.
	 * 	
	 * 1) The area is unoccupied:
	 * 		The platoon claims the area for their country/alliance.
	 * 		A Transport route is set up between this area and the area the platoon came from.
	 * 		No battle occurs so NULL is returned.
	 *
	 *  2) The area is occupied by allies:
	 * 		The platoon joins with the platoon already in the area.
	 * 		No battle occurs so NULL is returned.
	 *
	 * 	3) The area is occupied by enemies:
	 * 		The platoon that "marched in" is set as the attacker whilst the troop that preexisted is the defender.
	 * 		The attacking platoon fights the defending platoon in a battle.
	 * 		A pointer to the battle object is returned for resoltion.
	 *
	 *
	 * @param platoon The platoon marching into this area.
	 * 
	 */
	void marchIn(Unit *unit);

	/**
	 * @brief Orders the platoon to leave the area and go to another area
	 *
	 * @param whereTo The area to marchTo
	 * 
	 * @return true if the destination area is valid
	 * @return false if the destination area is invalid
	 */
	void marchOut(Area* whereTo);

	/**
	 * @brief This function can be called by the defending platoon during a battle, to get aid from adjecent friendly areas which are connected by active transport routes
	 *
	 * @return true if there were friendly platoons in adjecent areas which are connected by active transport routes
	 * @return false if there were no friendly platoons in adjecent areas which are connected by active transport routes
	 */
	bool requestReinforcements();

	/**
	 * @brief Request a specific type of resource from adjacent connected areas
	 * 
	 * @param type the type of resource
	 * @return true on success
	 * @return false on failure
	 */
	bool requestResources(int type);
	/**
	 * @brief Adds a cell to the area to be printed
	 * 
	 * @param coord the coordinate of the a cell to be added in the format "x,y"
	 */
	void addCell(string coord);

	/**
	 * @brief Get the vector of Coordinates that this area takes up on the map grid
	 * 
	 * @return vector<Coordinate*> 
	 */
	vector<Coordinate*> getAreaCoordinates();

	/**
	 * @brief Checks if a battle would happen if it does return a Battle object to resolve else return null.
	 * 
	 * A battle occurs if there is an attacker and a defender in either land, air or both
	 * 
	 * @return the battle holding combatants if it occurs 
	 */
	Battle* returnBattle();

	/**
	 * @brief Get the a specific type of factory if it exists here.
	 * Used when another area is requeting a factory.
	 * 
	 * Types:
	 * 0) Person
	 * 1) Ammo
	 * 2) Goods
	 * 
	 * @param type 
	 * @return TransportFactory* 
	 */
	TransportFactory* getFactory(int type);

	
	/**
	 * @brief requests a specific type of factory if it exists in an adjacent area.
	 * 
	 * @param type the type of factory to request.
	 * @return true if an factory of the specified type exists, false otherwise
	 * @return false 
	 */
	bool requestFactory(int type);
	
	string toString(){
		string out= "Name: " + name +"\tID: " + to_string(index) +"\tColour: " + to_string(colour);
		out+="\n \tFactories: Person["+to_string(allFactories[0]!=NULL)+"]\t Ammo["+to_string(allFactories[1]!=NULL)+"]\t Goods["+to_string(allFactories[2]!=NULL)+"]";
		return out;
	}
	/**
	 * @brief Attempts to retreat from Area 
	 * 
	 * @param type will be "attack" or "defense"
	 * 
	 */
	bool retreat(string type);

	/**
	 * @brief Destroy the Area object
	 * 
	 */
	~Area();

};

#endif
