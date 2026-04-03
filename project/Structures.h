#pragma once
#include <cstdint>
struct CpuTrack{
    float usageHistory[60] = {0.0f};
    uint32_t cache[3];
    int freq;
};

struct RamTrack{
    int total;      
    int avaible; 
};

struct Monitoring{
    CpuTrack cpu;
    RamTrack ram;
};

