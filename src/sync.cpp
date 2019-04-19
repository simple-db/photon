//**********************************************************
// File: sync.cpp
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#include "sync.h"

#include <braft/raft.h>

#include "meta.h"

namespace {
    static ::photon::Sync* g_instance = nullptr;
}

namespace photon {

/**
 * @brief callback of braft
 */
class SyncClosure : public braft::Closure {
public:
    void Run() {
        // TODO
    }
}; // class DBClosure

Sync& Sync::instance() {
    if (g_instance == nullptr) {
        g_instance = new Sync();
    }

    return *g_instance;
}

int Sync::init(const Options& option) {
    _state_machine = new SyncStateMachine();
    if (!_state_machine->start(option)) {
        LOG(FATAL) << "fail to start sync state machine";
        return -1;
    }

    Meta& meta = Meta::instance();
    std::vector<::butil::EndPoint> sync_group;
    if (!meta.get_group_info(&sync_group)) {
        LOG(WARNING) << "fail to get group info";
        return -1;
    }

    for (auto node : sync_group) {
        _state_machine->add_peer(node);
    }

    return 0;
}

int Sync::destroy() {
    if (_state_machine != nullptr) {
        if (_state_machine->stop()) {
            delete _state_machine;
            _state_machine = nullptr;
        } else {
            LOG(WARNING) << "fail to stop sync state machine, leak ALARM"; return -1;
        }
    }
    return 0;
}

bool Sync::sync(const RecordSet* records, std::function<void()> closure) {
    return true;
}

bool Sync::sync(const Record* record, std::function<void()> closure) {
    return true;
}

} // namespace photon
