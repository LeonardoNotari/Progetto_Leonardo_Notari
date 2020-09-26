//
// Created by leonardo on 23/09/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI__OBSERVER_H
#define PROGETTO_LEONARDO_NOTARI__OBSERVER_H

class Observer{
public:
    virtual~Observer();
    virtual void update()=0;
    /*virtual void attach()=0;
    virtual void detach()=0;*/
};

#endif //PROGETTO_LEONARDO_NOTARI__OBSERVER_H
