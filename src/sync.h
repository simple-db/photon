//**********************************************************
// File: sync.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

namespace photon {

class Sync {
public:
	static Sync& instance();

public:
	~Sync();

	int init(const Options& option);

	int destroy();

private:
	Sync() {}
	Sync(const Sync&) {}
}; // class Sync

} // namespace photon
