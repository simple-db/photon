//**********************************************************
// File: pcli.cpp
// Author: wtzhuque@163.com
// Description: cli tool for photon
//**********************************************************

#include <gflags/gflags.h>
#include <brpc/channel.h>
#include "photon_service.pb.h"

DEFINE_string(server, "127.0.0.1:8080", "service address");

namespace photon {

int run(int argc, char** argv) {
    google::ParseCommandLineFlags(&argc, &argv, true);

    // TODO: connect to server
    ::brpc::Channel chan;
    
    brpc::ChannelOptions options;
    options.protocol = "baidu_std";
    options.connection_type = "single";
    options.timeout_ms = 100;
    options.max_retry = 2;
    if (chan.Init(FLAGS_server.c_str(), "", &options) != 0) {
        LOG(ERROR) << "Fail to initialize channel";
        return -1;
    }

    int logid = 0;
    PhotonDBService_Stub stub(&chan);
    while (!::brpc::IsAskedToQuit()) {
        Key key;
        Status status;

        key.set_key("hello");

        brpc::Controller cntl;
        cntl.set_log_id(logid++);

        stub.get(&cntl, &key, &status, nullptr);
        if (!cntl.Failed()) {
            LOG(NOTICE) << "key=" << key.key();
        } else {
            LOG(WARNING) << cntl.ErrorText();
        }
    }

    return 0;
}

} // namespace photon

int main(int argc, char** argv) {
    return ::photon::run(argc, argv);
}
