//**********************************************************
// File: table_test.cpp                                         
// Author: wtzhuque@163.com                               
// Description: unittest of table
//**********************************************************

#include <gtest/gtest.h>
#include <fmt/format.h>

#include "table.h"
#include "photon_service.pb.h"

using ::photon::Table;
using ::photon::Record;
using ::photon::Key;
using ::photon::Entry;

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

    ASSERT_EQ(table->size(), 1);

    record = new Record();
    record->set_key("hello2");
    record->set_value("world2");
    
    ASSERT_TRUE(table->set(record));
    delete record;
    
    ASSERT_EQ(table->size(), 2);

    record = new Record();
    record->set_key("hello");
    record->set_value("world2");

    ASSERT_TRUE(table->set(record));
    delete record;
    
    ASSERT_EQ(table->size(), 2);

    for (int i = 0; i < 1024; ++i) {
        record = new Record();
        record->set_key(fmt::format("hello{}", i));
        record->set_value("world");
        ASSERT_TRUE(table->set(record));
        delete record;
    }
   
    // hello, hello0 ~ hello1023
    ASSERT_EQ(table->size(), 1025);

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
    ASSERT_TRUE(record->has_value());
    ASSERT_EQ(record->value().compare("world"), 0);

    delete new_record;
    new_record = nullptr;

    new_record = new Record();
    new_record->set_key("hello");
    new_record->set_value("world2");
    table->set(new_record);

    record = table->get("hello");
    ASSERT_NE(record, nullptr);
    ASSERT_TRUE(record->has_value());
    ASSERT_EQ(record->value().compare("world2"), 0);
    delete table;
}

TEST_F(TableTest, entry) {
    Table* table = new Table();

    ASSERT_EQ(table->head(), nullptr);
    ASSERT_EQ(table->tail(), nullptr);

    Record* new_record = new Record();
    new_record->set_key("hello");
    new_record->set_value("world");
    table->set(new_record);
    delete new_record;

    Entry* entry_head = table->head();
    Entry* entry_tail = table->tail();
    ASSERT_NE(entry_head, nullptr);
    ASSERT_NE(entry_tail, nullptr);

    Record* head_record = entry_head->get();
    Record* tail_record = entry_tail->get();
    ASSERT_EQ(head_record->key().compare("hello"), 0);
    ASSERT_EQ(head_record->value().compare("world"), 0);
    
    ASSERT_EQ(tail_record->key().compare("hello"), 0);
    ASSERT_EQ(tail_record->value().compare("world"), 0);
    
    new_record = new Record();
    new_record->set_key("hello");
    new_record->set_value("world2");
    table->set(new_record);
    delete new_record;
    
    entry_head = table->head();
    entry_tail = table->tail();
    head_record = entry_head->get();
    tail_record = entry_tail->get();
    ASSERT_EQ(head_record->key().compare("hello"), 0);
    ASSERT_EQ(head_record->value().compare("world2"), 0);
    
    ASSERT_EQ(tail_record->key().compare("hello"), 0);
    ASSERT_EQ(tail_record->value().compare("world2"), 0);
    
    new_record = new Record();
    new_record->set_key("hello2");
    new_record->set_value("world2");
    table->set(new_record);
    delete new_record;
    
    entry_head = table->head();
    entry_tail = table->tail();
    head_record = entry_head->get();
    tail_record = entry_tail->get();
    ASSERT_EQ(head_record->key().compare("hello2"), 0);
    ASSERT_EQ(head_record->value().compare("world2"), 0);
    
    ASSERT_EQ(tail_record->key().compare("hello"), 0);
    ASSERT_EQ(tail_record->value().compare("world2"), 0);

    delete table;
    table = nullptr;
}

TEST_F(TableTest, del) {
}


