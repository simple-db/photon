//**********************************************************
// File: pcli.cpp
// Author: wtzhuque@163.com
// Description: cli tool for photon
//**********************************************************

#include <gflags/gflags.h>

DEFINE_int32(port, 8080, "service port");
DEFINE_string(server, "120.0.0.1", "service address");

namespace photon {

int run(int argc, char** argv) {
    google::ParseCommandLineFlags(&argc, &argv, true);

    // TODO: connect to server

    // TODO: set/get  

    return 0;
}

} // namespace photon

int main(int argc, char** argv) {
    return ::photon::run(argc, argv);
}
