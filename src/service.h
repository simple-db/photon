//**********************************************************
// File: service.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

#include <brpc/server.h>
#include "options.h"

namespace photon {

class DBServiceImpl;
//class CMDServiceImpl;

class Service {
public:
    Service(const Options& options);

    ~Service();

    /**
     * @brief Start Service on port $port
     * @return 0 for success, other for fail
     */
    int start(int port);

    /**
     * @brief Stop Service
     * @return 0 for success, other for fail
     */
    int stop();

    /**
     * @brief Wait for service to quit
     */
    int join();

private:
    DBServiceImpl* _db_impl {nullptr};
    //CMDServiceImpl* _cmd_impl {nullptr};
    ::brpc::Server _server;
}; // class Service

} // namespace photon
