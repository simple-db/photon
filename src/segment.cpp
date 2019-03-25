//**********************************************************
// File: segment.cpp
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#include "segment.h"

namespace photon {

Segment::Segment() {
}

Segment::~Segment() {
}

bool Segment::set(const Record* record, Status* status) {
    if (_table.set(record)) {
        status->set_ret(0);
        return true;
    }
    return false;
}

bool Segment::get(const Key* key, Status* status) {
    const Record* record = _table.get(key->key());
    if (record) {
        status->set_ret(0);
        status->mutable_value()->set_value(record->value());
        return true;
    }
    
    status->set_ret(-1);
    return false;
}

} // namespace photon
