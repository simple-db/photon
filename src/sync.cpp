//**********************************************************
// File: sync.cpp
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#include "sync.h"

namespace {
	static ::photon::Sync* g_instance = nullptr;
}

namespace photon {

Sync& Sync::instance() {
	if (g_instance == nullptr) {
		g_instance = new Sync();
	}

	return *g_instance;
}

int Sync::init(const Options& option) {
	return 0;
}

int Sync::destroy() {
	return 0;
}

} // namespace photon
