#ifndef COWBOY_HPP
#define COWBOY_HPP

#include "Character.hpp"

constexpr int INITIAL_BULLETS_NUM = 6;

namespace ariel {
    class Cowboy : public Character{
        int num_bullets = INITIAL_BULLETS_NUM;

        public:
        Cowboy(std::string name, Point loc);

        void shoot(Character* enemy);
        bool hasboolets() const;
        void reload();

        std::string getType() override;
        std::string print() override;
    };
}


#endif 
