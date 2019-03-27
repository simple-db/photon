//**********************************************************
// File: sync_server.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

#include <braft/raft.h>

namespace photon {

class SyncStateMachine : public braft::StateMachine {
public:
	SyncStateMachine();

    virtual ~SyncStateMachine();

    bool start();
    
	virtual void on_apply(::braft::Iterator& iter);

private:
    braft::Node* _node {nullptr};
}; // class SyncMachine

} // namespace photon
