//**********************************************************
// File: murmur_sign.cpp
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#include "murmur_sign.h"

#include "murmur_hash.h"

namespace photon {

const unsigned int seed_h1 = 3371518343;
const unsigned int seed_h2 = 1685759167;

size_t MurmurSign::sign(const std::string& key) {
    size_t h = murmur_hash(key.c_str(), key.size(), seed_h1);
    return (h << 32) | murmur_hash(key.c_str(), key.size(), seed_h2);
}

} // namespace photon
