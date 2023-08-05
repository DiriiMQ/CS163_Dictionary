//
// Created by dirii on 5/8/23.
//

#ifndef CS163_GROUP9_TESTAPI_H
#define CS163_GROUP9_TESTAPI_H

#include "Api.h"

class TestAPI {
public:
    Api* api;
    Dicts dicts;

    TestAPI();

    void run();
};


#endif //CS163_GROUP9_TESTAPI_H
