//**********************************************************
// File: state_machine.cpp
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#include "state_machine.h"

#include <braft/raft.h>
#include <braft/storage.h>
#include <braft/util.h>
#include <fmt/format.h>

#include "options.h"

namespace photon {

SyncStateMachine::SyncStateMachine() {
}

SyncStateMachine::~SyncStateMachine() {
}

bool SyncStateMachine::start(const Options& options) {
    butil::EndPoint addr(butil::my_ip(), options.port);

    braft::NodeOptions node_options;
    if (node_options.initial_conf.parse_from(options.sync_conf_path) != 0) {
        LOG(FATAL) << "init sync node from config failed";
        return false;
    }
    node_options.election_timeout_ms = 5000;
    node_options.fsm = this;
    node_options.node_owns_fsm = false;
    node_options.snapshot_interval_s = 3600;
    std::string prefix = "local://{}" + options.sync_data_path;
    node_options.log_uri = prefix + "/log";
    node_options.raft_meta_uri = prefix + "/raft_meta";
    node_options.snapshot_uri = prefix + "/snapshot";
    node_options.disable_cli = false;

    braft::Node* node = new braft::Node("group", braft::PeerId(addr));
    if (node->init(node_options) != 0) {
        LOG(FATAL) << "fail to init raft node";
        delete node;
        return false;
    }

    _node = node;
    return true;
}
    
bool SyncStateMachine::stop() {
    return true;
}

void SyncStateMachine::on_apply(::braft::Iterator& iter) {
    /*
    while (iter.valid()) {
        if (iter.done()) {
            break;
        }
        iter.next();
    }
    */
}

} // namespace photon 
