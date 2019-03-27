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

	MemDB& db = MemDB::instance();
	int ret = db.init(options);
	if (ret != 0) {
		LOG(FATAL) << "init photon mem db failed, error=" << ret;
		return ret;
    }
    LOG(NOTICE) << "photon mem db init success";

    Sync& sync = Sync::instance();
    ret = sync.init(options);
    if (ret != 0) {
        LOG(FATAL) << "init photon sync module failed, error=" << ret;
    }

    Service service;
    service.start(options, FLAGS_port, FLAGS_sync_port);

	service.join();
    LOG(NOTICE) << "photon service quit";

    sync.destroy();
    LOG(NOTICE) << "photon stoped sync";

    db.destroy();
    LOG(NOTICE) << "bye";
    return 0;
}

} // namespace photon

int main(int argc, char** argv) {
    return ::photon::run(argc, argv);
}
