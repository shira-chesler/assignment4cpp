#ifndef YOUNGNINJA_H
#define YOUNGNINJA_H

#include "Ninja.hpp"

namespace ariel {
    class YoungNinja : public Ninja{
        public:
        YoungNinja(std::string name, Point location);
        std::string getType() override;
    };
}

#endif 
