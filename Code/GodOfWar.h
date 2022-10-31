#ifndef GODOFWAR_H
#define GODOFWAR_H
#include "Alliances.h"
#include "Area.h"
#include "CPU.h"
#include "User.h"
using namespace std;

class GodOfWar{
	private:
		Alliances *groupOne;
		Alliances *groupTwo;
		Player * player;
		Map * map;
		bool  turn;

	public:
		/**
		 * @brief Construct a new God Of War object using setup file
		 * 
		 * @param setupFile name of the textfile used to set up game
		 */
		GodOfWar(string setupFile);

		/**
		 * @brief allows alliance to take a turn
		 * 
		 * @details While there are action points remaining:
		 * 	- Pick a country:
		 * 	- Select action:
		 * 			- Destroy transport route
		 * 			- Choose area:
		 * 				- March into adjacent areas
		 * 				OR
		 * 				- Choose resource to clone factory of
		 * 	When no more action points remaining - resolveAllBattles
		 * 
		 * @param actions number of action points available
		 */
		void takeTurn(int actions);

		/**
		 * @brief one round of 
		 * 
		 */
		void round();

};

#endif
