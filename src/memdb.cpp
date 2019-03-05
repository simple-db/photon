//**********************************************************
// File: memdb.cpp
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#include "memdb.h"

#include "channel.h"
#include "segment.h"

namespace {
    static ::photon::MemDB* g_instance = nullptr;
}

namespace photon {

MemDB& MemDB::instance() {
	if (g_instance == nullptr) {
		g_instance = new MemDB();
	}

	return *g_instance;
}

MemDB::~MemDB() {
}

int MemDB::init(const Options& options) {
	return 0;
}

int MemDB::destroy() {
	return 0;
}

int MemDB::get() {
	return 0;
}

int MemDB::set() {
	return 0;
}

int MemDB::mget() {
	return 0;
}

int MemDB::mset() {
	return 0;
}

} // namespace photon
