#pragma once
#include <cstring>
#include "Structures.h"

class TuiComp{
public:
    virtual ftxue::Element getBox() = 0;
    virtual ~TuiComp() = default;
};
