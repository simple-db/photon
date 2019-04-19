//**********************************************************
// File: meta.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

#include <vector>
#include <unordered_map>

#include <butil/endpoint.h>

#include "photon_service.pb.h"
#include "options.h"
#include "sign.h"

namespace photon {

class Meta {
public:
    static Meta& instance();

public:
    ~Meta();

    int init(const Options& options);
int destroy(); 
    /**
     * @brief get segment list of this photon node
     */
    int get_segment_list(std::vector<size_t>* segments);

    /**
     * @brief calc segment id for this key
     */
    bool calc_seg_id(const Key* key, size_t* seg_id);

    /**
     * @brief cals segment id for this record
     */
    bool calc_seg_id(const Record* record, size_t* seg_id);

    /**
     * @brief get group id of this node
     */
    uint64_t group_id() const {
        return _group_id;
    }

    /**
     * @brief get all nodes addr in group
     */
    bool get_group_info(uint64_t group_id, std::vector<::butil::EndPoint>* group);
    
    /**
     * @brief get all nodes addr in current group
     */ 
    bool get_group_info(std::vector<::butil::EndPoint>* group);

private:
    Meta() {};
    Meta(const Meta&) {};
    
    bool valid_segment(size_t seg_id);

    bool load_local_meta(const std::string& meta);

private:
    struct GroupInfo {
        uint64_t group_id;
        std::vector<::butil::EndPoint> peers;
    }; // struct GroupInfo

    int _num_segments {0};
    uint64_t _group_id {0};
    std::unordered_map<uint64_t, GroupInfo*> _cluster_meta;
    Signature* _sign {nullptr};
}; // class Meta

} // namespace photon
