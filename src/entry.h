//**********************************************************
// File: Entry.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

#include "photon_service.pb.h"

namespace photon {

class Entry {
public:
    Entry();

    ~Entry();

    Record* get() {
        return _record;
    }

private:
    Record* _record {nullptr};
    uint32_t _ts {0};
    uint32_t _ref {0};

    Entry* _next {nullptr};
    Entry* _prev {nullptr};
    Entry* _brother {nullptr};
}; // class Entry

} // namespace photon
