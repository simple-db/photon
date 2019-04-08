//**********************************************************
// File: meta_test.cpp                                         
// Author: wtzhuque@163.com                               
// Description: unittest of meta
//**********************************************************

#include <vector>

#include <gtest/gtest.h>

#include "meta.h"
#include "options.h"

using ::photon::Meta;
using ::photon::Key;
using ::photon::Record;
using ::photon::Options;

class MetaTest : public ::testing::Test {
}; // class MetaTest

TEST_F(MetaTest, init) {
    Meta meta;

    Options options;
    options.num_channels = 4;
    options.num_segments = 4;

    ASSERT_EQ(meta.init(options), 0);
}

TEST_F(MetaTest, destroy) {
}

TEST_F(MetaTest, seg_list) {
    Meta meta;

    Options options;
    options.num_channels = 4;
    options.num_segments = 4;

    ASSERT_EQ(meta.init(options), 0);

    std::vector<size_t> seg_list;
    ASSERT_EQ(meta.get_segment_list(&seg_list), 0);

    for (size_t i = 0; i < options.num_segments; ++i) {
        ASSERT_EQ(i, seg_list[i]);
    }
}

TEST_F(MetaTest, calc_seg_id) {
    Meta meta;

    Options options;
    options.num_channels = 4;
    options.num_segments = 16;

    ASSERT_EQ(meta.init(options), 0);

    Key* key = new Key();
}


