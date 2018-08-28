//**********************************************************
// File: main.cpp                                         
// Author: wtzhuque@163.com                               
// Description: Main Entry of Photon
//**********************************************************

#include <gflags/gflags.h>
#include <glog/logging.h>

#include "service.h"

DEFINE_int32(port, 8080, "Service Port");

namespace photon {

int run(int argc, char** argv) {
    google::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging((const char *)argv[0]);

    LOG(INFO) << "photon start";

    Service service;

    service.start(FLAGS_port);

    while (1) {
        sleep(1);
    }

    google::ShutdownGoogleLogging();
    return 0;
}

} // namespace photon

int main(int argc, char** argv) {
    return ::photon::run(argc, argv);
}
