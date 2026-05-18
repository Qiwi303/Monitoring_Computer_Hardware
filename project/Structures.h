#pragma once
#include <cstdint>

namespace Network{
    inline constexpr int PORT = 9099;
    std::string name = "MONI";
} 

struct CpuTrack{
    float usageHistory[60] = {0.0f};
    uint32_t cache[3];
    int freq;
};

struct RamTrack{
    float total;      
    float avaible;
    float usageHistory[60] = {0.0f};
};

struct Monitoring{
    CpuTrack cpu;
    RamTrack ram;
};

