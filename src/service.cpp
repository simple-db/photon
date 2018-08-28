//**********************************************************
// File: service.cpp
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#include "service.h"

#include "photon.pb.h"

namespace photon {

class DBServiceImpl : public PhotonDBService {
public:
    DBServiceImpl() {}

    ~DBServiceImpl() {}

    virtual void get(::google::protobuf::RpcController* controller,
                     const ::photon::Key* request,
                     ::photon::Status* response,
                     ::google::protobuf::Closure* done) {
    }

    virtual void mget(::google::protobuf::RpcController* controller,
                      const ::photon::KeySet* request,
                      ::photon::StatusSet* response,
                      ::google::protobuf::Closure* done) {
    }

    virtual void set(::google::protobuf::RpcController* controller,
                     const ::photon::Record* request,
                     ::photon::Status* response,
                     ::google::protobuf::Closure* done) {
    }

    virtual void mset(::google::protobuf::RpcController* controller,
                      const ::photon::RecordSet* request,
                      ::photon::StatusSet* response,
                      ::google::protobuf::Closure* done) {
    }
}; // class DBServiceImpl

class CMDServiceImpl : public PhotonCMDService {
public:
    CMDServiceImpl() {}

    ~CMDServiceImpl() {}
}; // class CMDServiceImpl

Service::Service() {
    _db_impl = new DBServiceImpl();
    _cmd_impl = new CMDServiceImpl();
}

Service::~Service() {
    delete _db_impl;
    delete _cmd_impl;
}

int Service::start(int port) {
    if (_server.AddService(_db_impl, brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
        // TODO: log
        return -1;
    }
   
    brpc::ServerOptions server_options;
    if (_server.Start(port, &server_options) != 0) {
        // TODO: log
        return -1;
    }

    return 0;
}

int Service::stop() {
    _server.Stop(0);
    return 0;
}

int Service::join() {
    return 0;
}

} // namespace photon
