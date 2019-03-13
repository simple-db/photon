//**********************************************************
// File: meta.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

#include <vector>

#include "photon_service.pb.h"
#include "options.h"
#include "sign.h"

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

    /**
     * @brief cals segment id for this record
     */
    bool calc_seg_id(const Record* record, size_t* seg_id);

private:
    bool valid_segment(size_t seg_id);

private:
    int _num_segments {0};
    Signature* _sign {nullptr};
}; // class Meta

} // namespace photon
