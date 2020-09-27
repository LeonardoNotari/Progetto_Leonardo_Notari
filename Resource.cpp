//
// Created by leonardo on 17/08/20.
//

#include "Resource.h"

Resource* Resource::instance=nullptr;

Resource* Resource::getInstance() {
    if(instance == nullptr){
        instance = new Resource();
    }
    return instance;
}