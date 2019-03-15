//**********************************************************
// File: Entry.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

#include "photon_service.pb.h"

#include <butil/object_pool.h>

namespace photon {

class Entry {
public:
    Entry() {}

    ~Entry() {}

    inline Record* get() {
        return _record;
    }

    void set(const Record* record) {
        if (_record) {
            _record->Clear();
        } else {
            _record = ::butil::get_object<Record>();
            _record->Clear();
        }
        _record->CopyFrom(*record);
    }

    uint32_t ref(uint32_t n) {
        return (_ref += n);
    }

    uint32_t unref() {
        return --_ref;
    }

    uint32_t ref_count() const {
        return _ref;
    }

    void clear() {
        _ts = 0;
        _ref = 0;
        _record = nullptr;

        next = nullptr;
        prev = nullptr;
        brother = nullptr;
    }

private:
    uint32_t _ts {0};
    uint32_t _ref {0};

    Record* _record {nullptr};

public:
    Entry* next {nullptr};
    Entry* prev {nullptr};
    Entry* brother {nullptr};
}; // class Entry

} // namespace photon
