#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Point.hpp"
#include <string>
#include <stdexcept>

namespace ariel{
    class Character {
        private:
        Point location;
        int hit_points;
        std::string name;
        bool in_team=false;

        public:
        Character(Point loc, int hit_p, std::string name);
        Character(Character &charac);
        Character(Character&& charac) noexcept;
        virtual ~Character();

        bool isAlive();
        void hit(int hit);
        double distance(Character* othr);

        int getHp();
        std::string getName();
        Point getLocation();
        void setLocation(Point pos);
        bool getInTeam();
        void SetInTeam();

        virtual std::string print()=0;
        virtual std::string getType()=0;

        Character& operator=(const Character& charac);
        Character& operator=(Character&& charac) noexcept;
    };
}



#endif 
