//**********************************************************
// File: channel.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

#include <functional>
#include <bthread/execution_queue.h>

namespace photon {

class Channel {
public:
	Channel();

	~Channel();

    /**
     * @brief start channel
     */
    int start();

    /**
     * @brief push an async task in queue
     */
    bool enqueue(std::function<void()> task);

    /**
     * @brief Wait all tasks in channel finished
     */
    int join();

private:
    static int channel_loop(void *meta,
            ::bthread::TaskIterator<std::function<void()>>& iter);

private:
    ::bthread::ExecutionQueueId<std::function<void()>> _exec_queue;
}; // class Channel

} // namespace photon
