//**********************************************************
// File: meta.cpp
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#include "meta.h"

#include <butil/logging.h>

#include "murmur_sign.h"

namespace {
    ::photon::Meta* g_instance = nullptr;
}

namespace photon {

Meta& Meta::instance() {
    if (g_instance == nullptr) {
        g_instance = new Meta();
    }

    return *g_instance;
}

Meta::~Meta() {
}

int Meta::init(const Options& options) {
    _num_segments = options.num_segments;

    if (options.hash_func.compare("murmur") == 0) {
        _sign = new MurmurSign();
    } else {
        LOG(FATAL) << "Unknown hash func " << options.hash_func;
        return -1;
    }
    return 0;
}

int Meta::destroy() {
    return 0;
}

int Meta::get_segment_list(std::vector<size_t>* segments) {
    // Temp code, designed to load meta info from etcd
    for (int i = 0; i < _num_segments; ++i) {
        segments->push_back((size_t)i);
    }
    return 0;
}

bool Meta::calc_seg_id(const Key* key, size_t* seg_id) {
    size_t id = _sign->sign(key->key()) % _num_segments;
    if (valid_segment(id)) {
        *seg_id = id;
        return true;
    } else {
        return false;
    }
}

bool Meta::calc_seg_id(const Record* record, size_t* seg_id) {
    size_t id = _sign->sign(record->key()) % _num_segments;
    if (valid_segment(id)) {
        *seg_id = id;
        return true;
    } else {
        return false;
    }
}

bool Meta::valid_segment(size_t seg_id) {
    return true;
}
    
bool Meta::load_local_meta(const std::string& meta) {  
    return true;
}

bool Meta::get_group_info(uint64_t group_id,
                          std::vector<::butil::EndPoint>* group) {
    return true;
}

bool Meta::get_group_info(std::vector<::butil::EndPoint>* group) {
    return true;
}

} // namespace photon
