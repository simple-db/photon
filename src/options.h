//**********************************************************
// File: options.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

#include <string>

namespace photon {

class Options {
public:
    /**
     * Sync Mode:
     *   0: return after sync
     *   1: return before sync
     */
    int sync_mode {0};

    /**
     * Num of op channels
     */
	int num_channels {8};

    /**
     * Total num of segments
     */
	int num_segments {32};

    /**
     * Hash func of key
     */
    std::string hash_func {"murmur"};

    /**
     * Cache Strategy
     * 0: FIFO
     * 1: LRU
     * 2: Overflow
     */
    int cache_strategy {0};
}; // class Options

} // namespace photon
