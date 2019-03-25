//**********************************************************
// File: db_service.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

#include "photon_service.pb.h"

#include "options.h"

namespace photon {

class DBServiceImpl : public PhotonDBService {
public:
    DBServiceImpl(const Options& options)
        : _sync_mode(options.sync_mode) {
    }

    ~DBServiceImpl() {}

    virtual void get(::google::protobuf::RpcController* controller,
                     const ::photon::Key* key,
                     ::photon::Status* status,
                     ::google::protobuf::Closure* done);

    virtual void mget(::google::protobuf::RpcController* controller,
                      const ::photon::KeySet* key_set,
                      ::photon::StatusSet* status_set,
                      ::google::protobuf::Closure* done);

    virtual void set(::google::protobuf::RpcController* controller,
                     const ::photon::Record* record,
                     ::photon::Status* status,
                     ::google::protobuf::Closure* done);

    virtual void mset(::google::protobuf::RpcController* controller,
                      const ::photon::RecordSet* record_set,
                      ::photon::StatusSet* status_set,
                      ::google::protobuf::Closure* done);

private:
    int _sync_mode {0};
}; // class DBServiceImpl

} // namespace photon
