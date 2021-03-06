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
    
    bool del(const std::string& key);

    bool set(const Record* record);

    uint32_t capacity() const {
        return _capacity;
    }

    uint32_t size() const {
        return _size;
    }

    Entry* head() const {
        return _head;
    }

    Entry* tail() const {
        return _tail;
    }

private:
    bool equal(const std::string& key, const Record* record);
    
    bool equal(const Record* record_a, const Record* record_b);

    bool expand();

private:
    uint32_t _capacity {197};
    uint32_t _size {0};
    uint8_t _cur_bucket_set {0};

    typedef std::vector<Entry*> EntryArray;

    EntryArray _buckets[2];
    Entry* _head {nullptr};
    Entry* _tail {nullptr};
}; // class Table

} // namespace photon
