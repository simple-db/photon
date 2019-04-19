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

static const char* MEMORY_STORAGE_PREFIX = "memory://";
static const char* LOCAL_STORAGE_PREFIX = "local://";

class SyncClosure : public ::braft::Closure {
public:
    void Run() {
        LOG(INFO) << "sync done";
        delete this;
    }
}; // class SyncClosure

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
    
    std::string memory_prefix = MEMORY_STORAGE_PREFIX + options.sync_data_path;
    std::string local_prefix = LOCAL_STORAGE_PREFIX + options.sync_data_path;
    
    node_options.log_uri = memory_prefix + "/log";
    node_options.raft_meta_uri = local_prefix + "/raft_meta";
    node_options.snapshot_uri = local_prefix + "/snapshot";
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
    
bool SyncStateMachine::add_peer(const ::butil::EndPoint& peer) {
    if (_node == nullptr) {
        return false;
    }

    SyncClosure* done = new SyncClosure();
    _node->add_peer(::braft::PeerId(peer), done);
    return true;
}

bool SyncStateMachine::remove_peer(const ::butil::EndPoint& peer) {
    if (_node == nullptr) {
        return false;
    }

    SyncClosure* done = new SyncClosure();
    _node->remove_peer(::braft::PeerId(peer), done);
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
    
void SyncStateMachine::on_leader_start(int64_t term) {
    _leader_term.store(term, butil::memory_order_release);
    LOG(INFO) << "node start working as leader";
}

void SyncStateMachine::on_leader_stop(const butil::Status& status) {
    _leader_term.store(-1, butil::memory_order_release);
    LOG(INFO) << "node stop working as leader";
}

void SyncStateMachine::on_start_following(const ::braft::LeaderChangeContext& ctx) {
    LOG(INFO) << "node start following " << ctx;
}
    
void SyncStateMachine::on_stop_following(const ::braft::LeaderChangeContext& ctx) {
    LOG(INFO) << "node stop following " << ctx;
}

} // namespace photon 
