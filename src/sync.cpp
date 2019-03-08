//**********************************************************
// File: sync.cpp
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#include "sync.h"

#include <braft/raft.h>

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
    return 0;
}

int Sync::destroy() {
    return 0;
}

bool Sync::sync(const RecordSet* records, std::function<void()> closure) {
    return true;
}

bool Sync::sync(const Record* record, std::function<void()> closure) {
    return true;
}

} // namespace photon
