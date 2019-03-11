//**********************************************************
// File: meta.cpp
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#include "meta.h"

namespace photon {

Meta::Meta() {
}

Meta::~Meta() {
}

int Meta::init(const Options& options) {
    _num_segments = options.num_segments;
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
    return 0;
}

} // namespace photon
