#ifndef JOINEDSTATE_H
#define JOINEDSTATE_H
#include "CountryState.h"
using namespace std;

class JoinedState : public CountryState {
    public:
        void handleCountry();
        CountryState* changeCountryState();
};

#endif
