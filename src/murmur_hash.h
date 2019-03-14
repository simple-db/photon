//**********************************************************
// File: murmur_hash.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

#include <stdint.h>

namespace photon {

//uint64_t murmur_hash(const char* data, uint64_t len, uint64_t seed);
uint32_t murmur_hash(const char* data, uint32_t len, uint32_t seed);

} // namespace photon
