#ifndef TRAINEDNINJA_H
#define TRAINEDNINJA_H

#include "Ninja.hpp"

namespace ariel {
    class TrainedNinja : public Ninja{
        public:
        TrainedNinja(std::string name, Point location);
        std::string getType() override;
    };
}

#endif 
