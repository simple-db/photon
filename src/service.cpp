//**********************************************************
// File: service.cpp
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#include "service.h"

#include <butil/logging.h>

#include "photon.pb.h"
#include "memdb.h"

namespace photon {

class DBServiceImpl : public PhotonDBService {
public:
    DBServiceImpl() {}

    ~DBServiceImpl() {}

    virtual void get(::google::protobuf::RpcController* controller,
                     const ::photon::Key* request,
                     ::photon::Status* response,
                     ::google::protobuf::Closure* done) {
		MemDB& db = MemDB::instance();
		db.get();
    }

    virtual void mget(::google::protobuf::RpcController* controller,
                      const ::photon::KeySet* request,
                      ::photon::StatusSet* response,
                      ::google::protobuf::Closure* done) {
		MemDB& db = MemDB::instance();
		db.mget();
    }

    virtual void set(::google::protobuf::RpcController* controller,
                     const ::photon::Record* request,
                     ::photon::Status* response,
                     ::google::protobuf::Closure* done) {	
		MemDB& db = MemDB::instance();
		db.set();
    }

    virtual void mset(::google::protobuf::RpcController* controller,
                      const ::photon::RecordSet* request,
                      ::photon::StatusSet* response,
                      ::google::protobuf::Closure* done) {
		MemDB& db = MemDB::instance();
		db.mset();
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
		LOG(FATAL) << "export memdb service failed";
        return -1;
    }

	if (_server.AddService(_cmd_impl, brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
		LOG(FATAL) << "export cmd service failed";
		return -1;
	}
   
    brpc::ServerOptions server_options;
    if (_server.Start(port, &server_options) != 0) {
		LOG(FATAL) << "start server failed";
        return -1;
    }

    return 0;
}

int Service::stop() {
    _server.Stop(0);
    return 0;
}

int Service::join() {
    _server.RunUntilAskedToQuit();
    return 0;
}

} // namespace photon
