#pragma once
#include "Gasolinera.h"

class GasolineraFacade
{

public:

    void venderGasolina() {
        gas.vender();   
    }

private:
    Gasolinera gas;

};
