//**********************************************************
// File: table.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

#include <vector>

#include "entry.h"

namespace photon {

class Table {
public:
    Table();

    ~Table();

    const Record* get(const std::string& key);

    bool set(const Record* record);

private:
    bool expand();

private:
    uint32_t _capacity {197}
    std::vector<Entry*> _buckets[2];
    Entry* _head {nullptr};
    Entry* _tail {nullptr};
}; // class Table

} // namespace photon
