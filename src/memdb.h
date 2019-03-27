//**********************************************************
// File: memdb.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

#include <vector>
#include <functional>
#include <unordered_map>

#include "photon_service.pb.h"
#include "options.h"
#include "meta.h"

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

    /**
     * @brief handle get request
     */
	int get(const Key* key, Status* status, std::function<void()> closure);

    /**
     * @brief handle set request
     */
	int set(const Record* record, Status* status, std::function<void()> closure);

    /**
	 * @brief multi-get
	 */
	int mget();

	/**
	 * @brief multi-set
	 */
	int mset();

private:
	MemDB() {}
	MemDB(const MemDB&) {}

private:
	std::unordered_map<size_t, Segment*> _segments;
	std::unordered_map<size_t, size_t> _seg_chan_map;
	std::vector<Channel*> _channels;
    Meta _meta;
}; // class MemDB

} // namespace photon

