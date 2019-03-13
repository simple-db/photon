//**********************************************************
// File: db_service.cpp
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#include "db_service.h"

#include <brpc/server.h>

#include "memdb.h"
#include "sync.h"

namespace photon {

void DBServiceImpl::get(::google::protobuf::RpcController* controller,
                        const ::photon::Key* key,
                        ::photon::Status* status,
                        ::google::protobuf::Closure* done) {
    brpc::ClosureGuard done_guard(done);
    MemDB& db = MemDB::instance();
    db.get(key, status, [done](void){done->Run();});
}

void DBServiceImpl::mget(::google::protobuf::RpcController* controller,
                         const ::photon::KeySet* key_set,
                         ::photon::StatusSet* status_set,
                         ::google::protobuf::Closure* done) {
    brpc::ClosureGuard done_guard(done);
    MemDB& db = MemDB::instance();
    db.mget();
}

void DBServiceImpl::set(::google::protobuf::RpcController* controller,
                        const ::photon::Record* record,
                        ::photon::Status* status,
                        ::google::protobuf::Closure* done) {
    if (_sync_mode == 1) {
        MemDB& db = MemDB::instance();
        db.set(record, status, [record, done](void){
		    Sync& sync = Sync::instance();
		    sync.sync(record, [](void){});
		    done->Run();
        });

    } else {
        // By default sync_mode = 0
        Sync& sync = Sync::instance();
        sync.sync(record, [record, status, done](void){
			MemDB& db = MemDB::instance();
			db.set(record, status, [done](void){done->Run();});
		});
    }
}

void DBServiceImpl::mset(::google::protobuf::RpcController* controller,
                         const ::photon::RecordSet* record_set,
                         ::photon::StatusSet* status_set,
                         ::google::protobuf::Closure* done) {
	if (_sync_mode == 1) {
        brpc::ClosureGuard done_guard(done);
        MemDB& db = MemDB::instance();
        db.mset();
	} else {
		Sync& sync = Sync::instance();
		sync.sync(record_set, [record_set, status_set, done](void) {
				MemDB& db = MemDB::instance();
			});
	}
}

} // namespace photon
