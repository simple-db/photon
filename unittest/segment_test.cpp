//**********************************************************
// File: segment_test.cpp                                         
// Author: wtzhuque@163.com                               
// Description: unittest of segment
//**********************************************************

#include <gtest/gtest.h>

#include "segment.h"
#include "photon_service.pb.h"

using ::photon::Segment;
using ::photon::Record;
using ::photon::Key;
using ::photon::Value;
using ::photon::Status;

class SegmentTest : public ::testing::Test {
}; // SegmentTest

TEST_F(SegmentTest, init) {
    Segment* seg = new Segment();
    delete seg;
    seg = nullptr;
}

TEST_F(SegmentTest, set) {
    Segment* seg = new Segment();
    
    Record* record = new Record();
    Status* status = new Status();
    
    record->set_key("hello");
    record->set_value("world");

    ASSERT_TRUE(seg->set(record, status));
    ASSERT_EQ(status->ret(), 0);
    ASSERT_FALSE(status->has_value());

    delete record;
    delete status;

    record = new Record();
    status = new Status();

    ASSERT_FALSE(seg->set(record, status));

    delete seg;
    seg = nullptr;

    delete record;
    record = nullptr;
    delete status;
    status = nullptr;
}

TEST_F(SegmentTest, get) {
    Segment* seg = new Segment();
    
    Record* record = new Record();
    Status* status = new Status();
    
    record->set_key("hello");
    record->set_value("world");
    
    ASSERT_TRUE(seg->set(record, status));
    delete record;
    record = nullptr;
    delete status;
    status = nullptr;

    Key* key = new Key();
    key->set_key("hello");
    status = new Status();

    ASSERT_TRUE(seg->get(key, status));
    ASSERT_EQ(status->ret(), 0);
    ASSERT_TRUE(status->has_value());

    const Value& val = status->value();
    ASSERT_EQ(val.value().compare("world"), 0);

    key->Clear();
    status->Clear();

    key->set_key("hello2");
    ASSERT_FALSE(seg->get(key, status));

    ASSERT_NE(status->ret(), 0);
    ASSERT_FALSE(status->has_value());

    delete key;
    delete status;
    delete seg;
}
