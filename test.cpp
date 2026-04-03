#include <iostream>
#include <cstdint>
#include <cpuid.h> 

struct CacheInfo {
    uint32_t l2;
    uint32_t l3;
};

CacheInfo get_static_cache() {
    static CacheInfo cached_data = {0, 0}; 
    static bool initialized = false;

    if (!initialized) {
        unsigned int eax, ebx, ecx, edx;

        if (__get_cpuid(0x80000006, &eax, &ebx, &ecx, &edx)) {
            cached_data.l2 = (ecx >> 16);
            
            cached_data.l3 = (edx >> 18) * 512;
        }
        initialized = true;
    }
    return cached_data;
}

int main() {
    CacheInfo info = get_static_cache();
    
    if (info.l2 == 0 && info.l3 == 0) {
        std::cout << "Кэш не определен " << std::endl;
    } else {
        std::cout << "L2 Cache: " << info.l2 << " KB" << std::endl;
        std::cout << "L3 Cache: " << info.l3 << " KB" << std::endl;
    }

    return 0;

