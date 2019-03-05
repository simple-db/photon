//**********************************************************
// File: memdb.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

#include <vector>
#include <unordered_map>

#include "options.h"

namespace photon {

class Segment;
class Channel;

class MemDB {
public:
	static MemDB& instance();

public:
	~MemDB();

	int init(const Options& options);

	int destroy();

	int get();

	int set();

	int mget();

	int mset();

private:
	MemDB() {}
	MemDB(const MemDB&) {}

private:
	std::unordered_map<size_t, Segment*> _segments;
	std::unordered_map<size_t, size_t> _seg_chan_map;
	std::vector<Channel*> _channels;
}; // class MemDB

} // namespace photon

