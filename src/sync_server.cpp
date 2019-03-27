//**********************************************************
// File: sync_server.cpp
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#include "sync_server.h"

namespace photon {

SyncStateMachine::SyncStateMachine() {
}

SyncStateMachine::~SyncStateMachine() {
}

bool SyncStateMachine::start() {
    return false;
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
