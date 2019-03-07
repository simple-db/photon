//**********************************************************
// File: db_service.cpp
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#include "db_service.h"

#include "memdb.h"
#include "sync.h"

namespace photon {

void DBServiceImpl::get(::google::protobuf::RpcController* controller,
                        const ::photon::Key* key,
                        ::photon::Status* status,
                        ::google::protobuf::Closure* done) {
    MemDB& db = MemDB::instance();
    db.get(key, status);
}

void DBServiceImpl::mget(::google::protobuf::RpcController* controller,
                         const ::photon::KeySet* key_set,
                         ::photon::StatusSet* status_set,
                         ::google::protobuf::Closure* done) {
    MemDB& db = MemDB::instance();
    db.mget();
}

void DBServiceImpl::set(::google::protobuf::RpcController* controller,
                        const ::photon::Record* record,
                        ::photon::Status* status,
                        ::google::protobuf::Closure* done) {
	//MemDB& db = MemDB::instance();
	//db.set(record, status);
    if (_sync_mode == 1) {
    } else {
        // By default sync_mode = 0
        Sync& sync = Sync::instance();
        sync.sync(record);
    }
}

void DBServiceImpl::mset(::google::protobuf::RpcController* controller,
                         const ::photon::RecordSet* record_set,
                         ::photon::StatusSet* status_set,
                         ::google::protobuf::Closure* done) {
	MemDB& db = MemDB::instance();
	db.mset();
}

} // namespace photon
