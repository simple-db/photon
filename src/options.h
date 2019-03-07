//**********************************************************
// File: options.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

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
     */
	int num_segments {32};
}; // class Options

} // namespace photon
