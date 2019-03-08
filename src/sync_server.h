//**********************************************************
// File: sync_server.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

#include <braft/raft.h>

namespace photon {

class SyncServer : public braft::StateMachine {
public:
	SyncServer();

    virtual ~SyncServer();
    
	virtual void on_apply(::braft::Iterator& iter);
    
	virtual void on_shutdown();
    
	virtual void on_snapshot_save(::braft::SnapshotWriter* writer,
                                  ::braft::Closure* done);
    
	virtual int on_snapshot_load(::braft::SnapshotReader* reader);
    
	virtual void on_leader_start(int64_t term);
    
	virtual void on_leader_stop(const butil::Status& status);
    
	virtual void on_error(const ::braft::Error& e);
    
	virtual void on_configuration_committed(const ::braft::Configuration& conf);
    
	virtual void on_stop_following(const ::braft::LeaderChangeContext& ctx);
    
	virtual void on_start_following(const ::braft::LeaderChangeContext& ctx);
}; // class SyncServer

} // namespace photon
