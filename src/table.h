//**********************************************************
// File: table.h
// Author: wtzhuque@163.com
// Description:
//**********************************************************

#pragma once

namespace photon {

class Table {
public:
    Table();

    ~Table();

    int get();

    int mget();

    int set();

    int mset();
}; // class Table

} // namespace photon
