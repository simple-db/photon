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
    
    bool stop();

    bool add_peer(const ::butil::EndPoint& peer);
    
    bool remove_peer(const ::butil::EndPoint& peer);

	virtual void on_apply(::braft::Iterator& iter);

    virtual void on_leader_start(int64_t term);

    virtual void on_leader_stop(const butil::Status& status);

    virtual void on_start_following(const ::braft::LeaderChangeContext& ctx);
    
    virtual void on_stop_following(const ::braft::LeaderChangeContext& ctx);

private:
    braft::Node* _node {nullptr};
    butil::atomic<int64_t> _leader_term {-1};
}; // class SyncStateMachine

} // namespace photon
