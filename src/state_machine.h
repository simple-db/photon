//**********************************************************
// File: state_machine.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

#include <braft/raft.h>

#include "options.h"

namespace photon {

class SyncStateMachine : public braft::StateMachine {
public:
	SyncStateMachine();

    virtual ~SyncStateMachine();

    bool start(const Options& options);
    
	virtual void on_apply(::braft::Iterator& iter);

    bool stop();

private:
    braft::Node* _node {nullptr};
}; // class SyncStateMachine

} // namespace photon
