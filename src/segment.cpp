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
    return true;
}

bool Segment::get(const Key* key, Status* status) {
    return true;
}

} // namespace photon
