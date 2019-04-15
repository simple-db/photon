//**********************************************************
// File: main.cpp                                         
// Author: wtzhuque@163.com                               
// Description: Main Entry of Photon
//**********************************************************

#include <gflags/gflags.h>
#include <butil/logging.h>

#include "service.h"
#include "sync.h"
#include "options.h"
#include "memdb.h"
#include "db_service.h"

DEFINE_int32(port, 8080, "service port");
DEFINE_int32(sync_port, 8081, "data sync port");
DEFINE_int32(channels, 4, "num of db channels");
DEFINE_int32(segments, 32, "num of db segments");

namespace photon {

int run(int argc, char** argv) {
    LOG(NOTICE) << "photon start running";
    google::ParseCommandLineFlags(&argc, &argv, true);

	Options options;
    options.num_channels = FLAGS_channels;
    options.num_segments = FLAGS_segments;
    options.port = FLAGS_port;

	MemDB& db = MemDB::instance();
	int ret = db.init(options);
	if (ret != 0) {
		LOG(FATAL) << "init photon mem db failed, error=" << ret;
		return ret;
    }
    LOG(NOTICE) << "photon mem db init success";
    
    ::brpc::Server server;
    
    DBServiceImpl db_svr_impl(options);
    
    // export db service
    if (server.AddService(&db_svr_impl, brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
        LOG(FATAL) << "fail to export db service";
        return -1;
    }
   
    // export raft service
    ::braft::add_service(&server, FLAGS_port);
   
    // start all service
    brpc::ServerOptions server_options;
    if (server.Start(FLAGS_port, &server_options) != 0) {
		LOG(FATAL) << "start server failed";
        return -1;
    }
   
    // start sync service
    Sync& sync = Sync::instance();
    ret = sync.init(options);
    if (ret != 0) {
        LOG(FATAL) << "init photon sync module failed, error=" << ret;
    }

    //Service service;
    //service.start(options, FLAGS_port, FLAGS_sync_port);

	//service.join();
    server.RunUntilAskedToQuit();
    LOG(NOTICE) << "photon service quit";

    db.destroy();
    LOG(NOTICE) << "bye";
    return 0;
}

} // namespace photon

#ifndef __UNITTEST__
int main(int argc, char** argv) {
    return ::photon::run(argc, argv);
}
#endif
