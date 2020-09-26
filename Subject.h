//
// Created by leonardo on 23/09/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI__SUBJECT_H
#define PROGETTO_LEONARDO_NOTARI__SUBJECT_H
#include "Observer.h"
class Subject {
public:
    virtual ~Subject();
    virtual void subscribe(Observer* o)=0;
    virtual void unsubscribe(Observer* o)=0;
    virtual void notify()=0;

};


#endif //PROGETTO_LEONARDO_NOTARI__SUBJECT_H
