//
// Created by leonardo on 17/08/20.
//

#ifndef PROGETTO_LEONARDO_NOTARI__RESOURCE_H
#define PROGETTO_LEONARDO_NOTARI__RESOURCE_H

#include <SFML/Graphics.hpp>
#include <list>

class Resource {
public:
    static Resource * getInstance();
    ~Resource()=default;
private:
    static Resource* instance;
    std::list<std::string> textures;
    Resource();
};


#endif //PROGETTO_LEONARDO_NOTARI__RESOURCE_H
