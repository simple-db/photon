//**********************************************************
// File: memdb_test.cpp                                         
// Author: wtzhuque@163.com                               
// Description: unittest of memdb
//**********************************************************

#include <atomic>
#include <thread>
#include <vector>

#include <gtest/gtest.h>
#include <fmt/format.h>

#include "memdb.h"
#include "options.h"
#include "photon_service.pb.h"

using ::photon::Key;
using ::photon::Value;
using ::photon::Record;
using ::photon::Status;
using ::photon::MemDB;
using ::photon::Options;

class MemDBTest : public ::testing::Test {
}; // class MemDBTest

TEST_F(MemDBTest, init) {
    MemDB& db = MemDB::instance();

    Options options;
    options.num_channels = 4;
    options.num_segments = 16;
    ASSERT_EQ(db.init(options), 0);
}

TEST_F(MemDBTest, set) {
    MemDB& db = MemDB::instance();
    
    Record* record = new Record();
    Status* status = new Status();

    record->set_key("hello");
    record->set_value("world");

    std::atomic<bool> lock(true);
    
    int ret = db.set(record, status, [&lock](void){
        lock = false;
    });

    ASSERT_EQ(ret, 0);

    while (lock) {}

    delete record;
    delete status;
}

TEST_F(MemDBTest, get) {
    MemDB& db = MemDB::instance();

    Key* key = new Key();
    Status* status = new Status();
  
    key->set_key("hello");

    std::atomic<bool> lock(true);

    int ret = db.get(key, status, [&lock](void){
        lock = false;
    });

    ASSERT_EQ(ret, 0);

    while (lock) {}

    delete key;
    delete status;
}

TEST_F(MemDBTest, multithread) {
    std::vector<std::thread*> threads(10);

    for (int i = 0; i < 10; ++i) {
        threads[i] = new std::thread([](void){
            MemDB& db = MemDB::instance();
            Record* record = new Record();
            Status* status = new Status();

            for (int i = 0; i < 100; ++i) {
                record->set_key(fmt::format("hello{}", i));
                record->set_value("world");

                std::atomic<bool> lock(true);
    
                int ret = db.set(record, status, [&lock](void){
                    lock = false;
                });

                while (lock) {}
            }

            delete record;
            delete status;
        });
    }

    for (auto thread : threads) {
        thread->join();
    }
}

TEST_F(MemDBTest, destroy) {
    MemDB& db = MemDB::instance();
    ASSERT_EQ(db.destroy(), 0);
}
