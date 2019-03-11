//**********************************************************
// File: meta.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

#include "options.h"

namespace photon {

class Meta {
public:
    Meta();

    ~Meta();

    int init(const Options& options);

    int destroy();

    int get_segment_list();

    int calc_seg_id();
}; // class Meta

} // namespace photon
