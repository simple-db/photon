//**********************************************************
// File: memdb.cpp
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#include "memdb.h"

#include <butil/logging.h>

#include "channel.h"
#include "segment.h"

namespace {
    static ::photon::MemDB* g_instance = nullptr;
}

namespace photon {

static const int MAX_CHANNEL_NUM = 255;
static const int MAX_SEGMENT_NUM = 255;

MemDB& MemDB::instance() {
	if (g_instance == nullptr) {
		g_instance = new MemDB();
	}

	return *g_instance;
}

MemDB::~MemDB() {
}

int MemDB::init(const Options& options) {
    if (options.num_channels < 0 || options.num_channels > MAX_CHANNEL_NUM) {
        LOG(FATAL) << "invalid channel num: " << options.num_channels;
        return -1;
    }

    if (options.num_segments < 0 || options.num_segments > MAX_SEGMENT_NUM) {
        LOG(FATAL) << "invalid channel num: " << options.num_channels;
        return -1;
    }

    int ret = _meta.init(options);
    if (ret != 0) {
        LOG(FATAL) << "init meta info failed";
        return ret;
    }

    _channels.resize(options.num_channels);
    for (int i = 0; i < options.num_channels; ++i) {
        _channels[i] = new Channel();
        _channels[i]->start();
    }

    std::vector<size_t> seg_list;
    ret = _meta.get_segment_list(&seg_list);
    if (ret != 0) {
        LOG(FATAL) << "get segment list failed";
        return ret;
    }

	return 0;
}

int MemDB::destroy() {
    for (auto channel : _channels) {
        channel->join();
        delete channel;
    }
	return 0;
}

int MemDB::get(const Key* key, Status* status) {
    size_t seg_id = 0;
    if (!_meta.calc_seg_id(key, &seg_id)) {
        LOG(WARNING) << "fail to calc segment id of key";
        return -1;
    }

    _channels[_seg_chan_map[seg_id]]->enqueue([key, status](void) {
                
            });
	return 0;
}

int MemDB::set(const Record* record, Status* status) {
	return 0;
}

int MemDB::mget() {
    // TODO
	return 0;
}

int MemDB::mset() {
    // TODO
	return 0;
}

} // namespace photon
