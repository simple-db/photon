//**********************************************************
// File: sign.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

#include <string>

namespace photon {

class Signature {
public:
    Signature() {}

    virtual ~Signature() {}

    virtual size_t sign(const std::string& key) = 0;
}; // class Signature

} // namespace photon
