//**********************************************************
// File: table_test.cpp                                         
// Author: wtzhuque@163.com                               
// Description: unittest of table
//**********************************************************

#include <gtest/gtest.h>
#include <fmt/format.h>

#include "table.h"
#include "photon_service.pb.h"

namespace photon {
} // namespace photon

using ::photon::Table;
using ::photon::Record;
using ::photon::Key;

class TableTest : public ::testing::Test {
}; // class TableTest


TEST_F(TableTest, init) {
    Table* table = new Table();
    delete table;
}

TEST_F(TableTest, set) {
    Table* table = new Table();
    Record* record = new Record();

    ASSERT_FALSE(table->set(record));

    record->set_key("hello");
    record->set_value("world");

    ASSERT_TRUE(table->set(record));
    delete record;

    record = new Record();
    record->set_key("hello2");
    record->set_value("world2");
    
    ASSERT_TRUE(table->set(record));
    delete record;

    record = new Record();
    record->set_key("hello");
    record->set_value("world2");

    ASSERT_TRUE(table->set(record));
    delete record;

    for (int i = 0; i < 1024; ++i) {
        record = new Record();
        record->set_key(fmt::format("hello{}", i));
        record->set_value("world");
        ASSERT_TRUE(table->set(record));
        delete record;
    }

    delete table;
}

TEST_F(TableTest, get) {
    Table* table = new Table();

    const Record* record = table->get("hello");
    ASSERT_EQ(record, nullptr);

    Record* new_record = new Record();
    new_record->set_key("hello");
    new_record->set_value("world");
    table->set(new_record);

    record = table->get("hello");
    ASSERT_NE(record, nullptr);

    delete new_record;
    delete table;
}

TEST_F(TableTest, del) {
}


