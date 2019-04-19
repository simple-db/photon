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
#include "meta.h"
#include "options.h"
#include "photon_service.pb.h"

using ::photon::Key;
using ::photon::Value;
using ::photon::Record;
using ::photon::Status;
using ::photon::MemDB;
using ::photon::Options;
using ::photon::Meta;

class MemDBTest : public ::testing::Test {
}; // class MemDBTest

TEST_F(MemDBTest, init) {


    Options options;
    options.num_channels = 4;
    options.num_segments = 16;
    Meta& meta = Meta::instance();
    meta.init(options);
    
    MemDB& db = MemDB::instance();
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

    int ret = db.get(key, status, [&lock](void){lock = false;});

    ASSERT_EQ(ret, 0);

    while (lock) {}

    delete key;
    delete status;
}

TEST_F(MemDBTest, multithread) {
    std::vector<std::thread*> w_threads(10);
    std::vector<std::thread*> r_threads(10);

    for (int i = 0; i < 10; ++i) {
        r_threads[i] = new std::thread([](void){
            MemDB& db = MemDB::instance();
            Key* key = new Key();
            Status* status = new Status();

            for (int i = 0; i < 100; ++i) {
                key->set_key(fmt::format("hello{}", i));

                std::atomic<bool> lock(true);
                
                int ret = db.get(key, status, [&lock](void){
                    lock = false;
                });

                while (lock) {}
        
                ASSERT_EQ(ret, 0);
            }

            delete key;
            delete status;
        });
    }

    for (int i = 0; i < 10; ++i) {
        w_threads[i] = new std::thread([](void){
            MemDB& db = MemDB::instance();
            Record* record = new Record();
            Status* status = new Status();

            for (int i = 0; i < 100; ++i) {
                record->set_key(fmt::format("hello{}", i));
                record->set_value(fmt::format("world{}", i));

                std::atomic<bool> lock(true);
    
                int ret = db.set(record, status, [&lock](void){
                    lock = false;
                });

                while (lock) {}
        
                ASSERT_EQ(ret, 0);
            }

            delete record;
            delete status;
        });
    }

    for (auto thread : w_threads) {
        thread->join();
    }

    for (auto thread : r_threads) {
        thread->join();
    }

    MemDB& db = MemDB::instance();
    Key* key = new Key();
    Status* status = new Status();

    for (int i = 0; i < 100; ++i) {
        key->set_key(fmt::format("hello{}", i));

        std::atomic<bool> lock(true);
                
        int ret = db.get(key, status, [&lock](void){
            lock = false;
        });

        while (lock) {}

        ASSERT_EQ(ret, 0);
        ASSERT_EQ(status->ret(), 0);
        ASSERT_EQ(status->value().value().compare(fmt::format("world{}", i)), 0);
    }

    delete key;
    delete status;
}

TEST_F(MemDBTest, destroy) {
    MemDB& db = MemDB::instance();
    ASSERT_EQ(db.destroy(), 0);
}
