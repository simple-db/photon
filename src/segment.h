//**********************************************************
// File: segment.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

#include "photon_service.pb.h"

namespace photon {

class Segment {
public:
    Segment();

    ~Segment();

    bool set();
	
    bool get(const Key* key, Status* status);
private:
}; // class Segment

} // namespace photon
