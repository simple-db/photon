//**********************************************************
// File: memdb.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

namespace photon {

class MemDB {
public:
	MemDB();

	~MemDB();

	int init();

	int destroy();
}; // class MemDB

} // namespace photon

