//**********************************************************
// File: sync.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

#include <functional>

#include "photon_service.pb.h"
#include "state_machine.h"
#include "options.h"

namespace photon {

class Sync {
public:
    static Sync& instance();

public:
    ~Sync();
	
	int init(const Options& option);

    int destroy();

    bool sync(const RecordSet* records, std::function<void()> closure);

    bool sync(const Record* record, std::function<void()> closure);

private:
    Sync() {}
    Sync(const Sync&) {}

private:
	SyncStateMachine* _state_machine {nullptr};
}; // class Sync

} // namespace photon
