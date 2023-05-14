#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Point.hpp"
#include <string>

namespace ariel{
    class Character {
        private:
        Point location;
        int hit_points;
        std::string name;

        public:
        Character(Point loc, int hit_p, std::string name);
        Character(Character &charac);
        Character(Character&& charac) noexcept;
        bool isAlive();
        void hit(int hit);
        int getHp();
        double distance(Character* othr);
        std::string getName();
        Point getLocation();
        void setLocation();
        std::string print();
        virtual std::string getType()=0;
        virtual ~Character();

        Character& operator=(const Character& charac);
        Character& operator=(Character&& charac) noexcept;
    };
}



#endif 
