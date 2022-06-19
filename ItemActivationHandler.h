#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <math.h>
#include <cstring>
#include <unistd.h>
#include "Item.h"
#include "Button.h"
#include "Character.h"

class ItemActivationHandler
{
    public:
    enum itemStatus {notEquipped, notActive, active};
    itemStatus fury = notEquipped;
    itemStatus projectileDisruptorField = notEquipped;
    itemStatus ghostBullets = notEquipped;
};