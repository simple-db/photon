//**********************************************************
// File: error.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

namespace photon {

struct Error {
    enum ErrorCode {
        OK = 0,
        FAIL,
    }; // enum ErrorCode
}; // struct Error

const char* error_to_string(int code);

} // namespace photon
