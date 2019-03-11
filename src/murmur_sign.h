//**********************************************************
// File: murmur_sign.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

#include "sign.h"

namespace photon {

class MurmurSign {
public:
    MurmurSign() {}

    virtual ~MurmurSign() {}
    
    virtual size_t sign(const std::string& key);
}; // class MurmurSign

} // namespace photon
