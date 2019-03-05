//**********************************************************
// File: main.cpp                                         
// Author: wtzhuque@163.com                               
// Description: Main Entry of Photon
//**********************************************************

#include <gflags/gflags.h>
#include <butil/logging.h>

#include "service.h"
#include "options.h"
#include "memdb.h"

DEFINE_int32(port, 8080, "service port");
DEFINE_int32(channels, 4, "num of db channels");
DEFINE_int32(segments, 32, "num of db blocks");

namespace photon {

int run(int argc, char** argv) {
    google::ParseCommandLineFlags(&argc, &argv, true);

	Options db_options;
	db_options.num_channels = FLAGS_channels;
	db_options.num_segments = FLAGS_segments;

	MemDB& db = MemDB::instance();
	int ret = db.init(db_options);
	if (ret != 0) {
		LOG(FATAL) << "init photon mem db failed error=" << ret;
		return ret;
	}

    Service service;
    service.start(FLAGS_port);

	service.join();
    return 0;
}

} // namespace photon

int main(int argc, char** argv) {
    return ::photon::run(argc, argv);
}
