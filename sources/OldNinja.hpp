#ifndef OLDNINJA_H
#define OLDNINJA_H

#include "Ninja.hpp"

namespace ariel {
    class OldNinja : public Ninja{
        public:
        OldNinja(std::string name, Point location);
        std::string getType() override;
    };
}

#endif 
