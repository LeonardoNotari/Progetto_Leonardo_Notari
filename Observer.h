//
// Created by leonardo on 23/09/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI__OBSERVER_H
#define PROGETTO_LEONARDO_NOTARI__OBSERVER_H

#include <iostream>

class Observer {
public:
    virtual~Observer();

    virtual void update(const std::string &goalReach) = 0;
};

#endif //PROGETTO_LEONARDO_NOTARI__OBSERVER_H
