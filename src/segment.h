//**********************************************************
// File: segment.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

#include "photon_service.pb.h"

#include "table.h"

namespace photon {

class Segment {
public:
    Segment();

    ~Segment();

    bool set(const Record* record, Status* status);
	
    bool get(const Key* key, Status* status);

private:
    Table _table;
}; // class Segment

} // namespace photon
