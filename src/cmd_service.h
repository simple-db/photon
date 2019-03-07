//**********************************************************
// File: cmd_service.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

#include "photon_service.pb.h"

namespace photon {

class CMDServiceImpl : public PhotonCMDService {
public:
    CMDServiceImpl() {}

    ~CMDServiceImpl() {}
}; // class CMDServiceImpl

} // namespace photon
