#pragma once

#include <iostream>
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include "Parser.h"

class Ram{
public:
    Ram();
    ~Ram();
    std::vector<float> getMemInfo();    

private:
    int fd;
};
