//**********************************************************
// File: channel.cpp
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#include "channel.h"

namespace photon {

using ::bthread::execution_queue_start;
using ::bthread::execution_queue_stop;
using ::bthread::execution_queue_join;

Channel::Channel() {
}

Channel::~Channel() {
}

int Channel::start() {
    int ret = execution_queue_start(&_exec_queue,
                                    nullptr,
                                    &Channel::channel_loop,
                                    nullptr);
    if (ret != 0) {
        LOG(FATAL) << "channel start exec queue failed";
    }

    return ret;
}

int Channel::join() {
    int ret = execution_queue_stop(_exec_queue);
    if (ret != 0) {
        LOG(WARNING) << "channel stop exec queue failed";
        return ret;
    }

    ret = execution_queue_join(_exec_queue);
    if (ret != 0) {
        LOG(WARNING) << "channel join exec queue failed";
        return ret;
    }

    return ret;
}

bool Channel::enqueue(std::function<void()> task) {
    return true;
}

int Channel::channel_loop(void* /*meta*/, 
        ::bthread::TaskIterator<std::function<void()>>& iter) {
    if (iter.is_queue_stopped()) {
        return 0;
    }

    while (iter) {
        (*iter)();
        ++iter;
    }

    return 0;
}

} // namespace photon
