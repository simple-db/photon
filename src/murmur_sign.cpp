//**********************************************************
// File: murmur_sign.cpp
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#include "murmur_sign.h"

namespace photon {

const unsigned int SEED = 0xee6b27eb;

size_t MurmurSign::sign(const std::string& key) {
    const unsigned int m = 0x5bd1e995;
    const int r = 24;

    unsigned int h1 = SEED ^ key.size();
    unsigned int h2 = 0;

    const unsigned int* data = (const unsigned int *)(key.c_str());
    size_t len = key.size();

    while(len >= 8) {
        unsigned int k1 = *data++;
        k1 *= m; k1 ^= k1 >> r; k1 *= m;
        h1 *= m; h1 ^= k1;
        len -= 4;

        unsigned int k2 = *data++;
        k2 *= m; k2 ^= k2 >> r; k2 *= m;
        h2 *= m; h2 ^= k2;
        len -= 4;
    }

    if (len >= 4) {
        unsigned int k1 = *data++;
        k1 *= m; k1 ^= k1 >> r; k1 *= m;
        h1 *= m; h1 ^= k1;
        len -= 4;
    }

    switch (len) {
        case 3: h2 ^= ((unsigned char*)data)[2] << 16;
        case 2: h2 ^= ((unsigned char*)data)[1] << 8;
        case 1: h2 ^= ((unsigned char*)data)[0];
        h2 *= m;
    }

    h1 ^= h2 >> 18; h1 *= m;
    h2 ^= h1 >> 22; h2 *= m;
    h1 ^= h2 >> 17; h1 *= m;
    h2 ^= h1 >> 19; h2 *= m;

    size_t h = h1;
    h = (h << 32) | h2;

    return h;
}

} // namespace photon
