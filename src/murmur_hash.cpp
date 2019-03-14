//**********************************************************
// File: murmur_hash.cpp
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#include "murmur_hash.h"

#include <butil/third_party/murmurhash3/murmurhash3.h>

namespace photon {

uint32_t murmur_hash(const char* buff,
                     uint32_t len,
                     uint32_t seed) {
    uint32_t hash = 0;
    butil::MurmurHash3_x86_32((void*)buff, len, seed, &hash);
    return hash;
}

} // namespace photon
