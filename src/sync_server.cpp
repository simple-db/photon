//**********************************************************
// File: sync_server.cpp
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#include "sync_server.h"

namespace photon {

SyncServer::SyncServer() {
}

SyncServer::~SyncServer() {
}

bool SyncServer::start() {
}

void SyncServer::on_apply(::braft::Iterator& iter) {
}
    
void SyncServer::on_shutdown() {
}
    
void SyncServer::on_snapshot_save(::braft::SnapshotWriter* writer,
                                  ::braft::Closure* done) {
}
    
int SyncServer::on_snapshot_load(::braft::SnapshotReader* reader) {
}
    
void SyncServer::on_leader_start(int64_t term) {
}
    
void SyncServer::on_leader_stop(const butil::Status& status) {
}
    
void SyncServer::on_error(const ::braft::Error& e) {
}
    
void SyncServer::on_configuration_committed(const ::braft::Configuration& conf) {
}
    
void SyncServer::on_stop_following(const ::braft::LeaderChangeContext& ctx) {
}
    
void SyncServer::on_start_following(const ::braft::LeaderChangeContext& ctx) {
}

} // namespace photon

