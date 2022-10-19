#ifndef VEHICLEBUILDER_H
#define VEHICLEBUILDER_H

#include "BobTheBuilder.h"

using namespace std;

class VehicleBuilder : public BobTheBuilder {
    public:
        Unit* buildPart();
        Unit* getResult();
};

#endif
