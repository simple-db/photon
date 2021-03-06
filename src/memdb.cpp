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

    std::vector<size_t> seg_list;
    int ret = Meta::instance().get_segment_list(&seg_list);
    if (ret != 0) {
        LOG(FATAL) << "get segment list failed";
        return ret;
    }
    
    for (auto seg_id : seg_list) {
        Segment* segment = new Segment();
        _segments[seg_id] = segment;
    }
    
    _channels.resize(options.num_channels);
    for (int i = 0; i < options.num_channels; ++i) {
        _channels[i] = new Channel();
        _channels[i]->start();
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

int MemDB::get(const Key* key,
               Status* status,
               std::function<void()> closure) {
    size_t seg_id = 0;
    if (!Meta::instance().calc_seg_id(key, &seg_id)) {
        LOG(WARNING) << "fail to calc segment id of key";
        return -1;
    }

    Segment* seg = _segments[seg_id];
    if (!seg) {
        LOG(WARNING) << "no such segment seg_id=" << seg_id;
    }
    _channels[seg_id % _channels.size()]->enqueue([seg, key, status, closure](void) {
                seg->get(key, status);
                closure();
            });
	return 0;
}

int MemDB::set(const Record* record,
               Status* status,
               std::function<void()> closure) {
    size_t seg_id = 0;
    if (!Meta::instance().calc_seg_id(record, &seg_id)) {
        LOG(WARNING) << "fail to calc segment id of record";
        return -1;
    }

    Segment* seg = _segments[seg_id];
    if (!seg) {
        LOG(WARNING) << "no such segment seg_id=" << seg_id;
    }
    _channels[seg_id % _channels.size()]->enqueue([seg, record, status, closure](void) {
            seg->set(record, status);
            closure();
        });
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
