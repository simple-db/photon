//**********************************************************
// File: meta.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

#include <vector>

#include "photon_service.pb.h"
#include "options.h"

namespace photon {

class Meta {
public:
    Meta();

    ~Meta();

    int init(const Options& options);

    int destroy();

    /**
     * @brief get segment list of this photon node
     */
    int get_segment_list(std::vector<size_t>* segments);

    /**
     * @brief calc segment id for this key
     */
    bool calc_seg_id(const Key* key, size_t* seg_id);

private:
    int _num_segments {0};
}; // class Meta

} // namespace photon
