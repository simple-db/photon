//**********************************************************
// File: table.cpp
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#include "table.h"

#include <butil/object_pool.h>

#include "murmur_hash.h"

namespace photon {

const uint32_t TOKEN_SEED = 421439783;

Table::Table() {
    _buckets[_cur_bucket_set].resize(_capacity, nullptr);
    _buckets[1 - _cur_bucket_set].clear();
}

Table::~Table() {
}

const Record* Table::get(const std::string& key) {
    uint32_t token = murmur_hash(key.c_str(), key.size(), TOKEN_SEED);
    Entry* iter = _buckets[_cur_bucket_set][token % _capacity];

    while (!equal(key, iter->get()) && iter != nullptr) {
        iter = iter->brother;
    }

    if (iter != nullptr) {
        return iter->get();
    } else {
        return nullptr;
    }
}

bool Table::del(const std::string& key) {
}

bool Table::set(const Record* record) {
    uint32_t token = murmur_hash(record->key().c_str(), record->key().size(), TOKEN_SEED);
    Entry* iter = _buckets[_cur_bucket_set][token % _capacity];

    if (iter != nullptr) {
        while (true) {
            if (equal(record, iter->get())) {
                iter->set(record);
                break;
            } else {
                if (iter->brother) {
                    iter = iter->brother;
                    continue;
                } else {
                    Entry* cur = iter;
                    iter = ::butil::get_object<Entry>();
                    iter->set(record);
                    cur->brother = iter;
                    iter->next = _head;
                    _head->prev = iter;
                    _head = iter;
                    break;
                }
            }
        }
    } else {
        iter = butil::get_object<Entry>();
        iter->clear();
        iter->set(record);
        iter->next = _head;
        
        if (_head != nullptr) {
            _head->prev = iter;
        }
    
        _head = iter;

        if (_tail = nullptr) {
            _tail = iter;
        }

        _buckets[_cur_bucket_set][token % _capacity] = iter;
    }

    return true;
}

bool Table::equal(const std::string& key, const Record* record) {
    return key.compare(record->key()) == 0;
}

bool Table::equal(const Record* record_a, const Record* record_b) {
    return record_a->key().compare(record_b->key()) == 0;
}

bool Table::expand() {
    return true;
}

} // namespace photon
