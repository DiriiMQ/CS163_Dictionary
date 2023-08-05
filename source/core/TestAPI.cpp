//
// Created by dirii on 5/8/23.
//

#include "TestAPI.h"

TestAPI::TestAPI() {
    // construct here
    this->dicts = Dicts();
    this->api = new Api(this->dicts);
}

void TestAPI::run() {

}
