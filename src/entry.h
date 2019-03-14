//**********************************************************
// File: table.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

#include "photon_service.pb.h"

namespace photon {

class Entry {
public:
    Entry(const Record* record);

    ~Entry();

    Record* get() {
        return _record;
    }

private:
    Record* _record {nullptr};
    unsigned long _ts {0};
}; // class Entry

} // namespace photon
