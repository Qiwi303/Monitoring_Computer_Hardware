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
    std::vector<int> getMemInfo();    

private:
    int fd;
};
