//**********************************************************
// File: service.h
// Author: wtzhuque@163.com
// Description: Main Entry of Photon
//**********************************************************

#pragma once

namespace photon {

class Service {
public:
    Service();

    ~Service();

    int start();

    int stop();

    int join();
}; // class Service

} // namespace photon
