#pragma once

struct CpuTrack{
    float usage;
};

struct RamTrack{
    int total;      
    int avaible; 
};

struct Monitoring{
    CpuTrack cpu;
    RamTrack ram;
};

