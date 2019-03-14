//**********************************************************
// File: table.cpp
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#include "table.h"

namespace photon {

Table::Table() {
    _buckets[0].resize(_capacity);
    _buckets[1].clear();
}

Table::~Table() {
}

Record* Table::get(const std::string& key) {
}

bool Table::set(const Record* record) {
    return true;
}

bool Table::expand() {
    return true;
}

} // namespace photon
