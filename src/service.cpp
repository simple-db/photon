//**********************************************************
// File: service.cpp
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#include "service.h"

#include <butil/logging.h>
#include <braft/raft.h>

#include "db_service.h"
//#include "cmd_service.h"

namespace photon {

Service::Service() {
}

Service::~Service() {
}

int Service::start(const Options& options, int port, int sync_port) {
    _db_impl = new DBServiceImpl(options);
    
    _server = new ::brpc::Server;

    // braft state machine should reuse this brpc server
    ::braft::add_service(_server, sync_port);

    if (_server->AddService(_db_impl, brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
		LOG(FATAL) << "export memdb service failed";
        return -1;
    }

    /*
	if (_server->AddService(_cmd_impl, brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
		LOG(FATAL) << "export cmd service failed";
		return -1;
	}
    */

    brpc::ServerOptions server_options;
    if (_server->Start(port, &server_options) != 0) {
		LOG(FATAL) << "start server failed";
        return -1;
    }

    return 0;
}

int Service::stop() {
    _server->Stop(0);
    return 0;
}

int Service::join() {
    _server->RunUntilAskedToQuit();
    return 0;
}

} // namespace photon
