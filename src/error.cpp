//**********************************************************
// File: error.cpp
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#include "error.h"

namespace photon {

const char* error_to_string(int code) {
    switch (code) {
        case Error::OK:
            return "ok";
        case Error::FAIL:
            return "fail";
    }
    return nullptr;
}

} // namespace photon
