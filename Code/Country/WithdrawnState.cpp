#include "WithdrawnState.h"

using namespace std;

void WithdrawnState::handleCountry() {

}

CountryState* WithdrawnState::changeCountryState() {
    return new WithdrawnState();
}