//**********************************************************
// File: sync.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

#include "options.h"

namespace photon {

class Sync {
public:
	static Sync& instance();

public:
	~Sync();

	int init(const Options& option);

	int destroy();

    bool sync(const RecordSet* records);

    bool sync(const Record* record);

private:
	Sync() {}
	Sync(const Sync&) {}
}; // class Sync

} // namespace photon
