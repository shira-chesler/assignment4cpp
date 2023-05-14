#ifndef NINJA_HPP
#define NINJA_HPP

#include "Character.hpp"

namespace ariel {
    class Ninja : public Character{
        private:
        int speed;
        
        public:
        Ninja(std::string name, Point loc, int hit_p, int speed);
        Ninja(Ninja &nin);
        Ninja(Ninja&& nin) noexcept;
        void move(Character* enemy);
        void slash(Character* enemy);
        std::string getType() override=0;
        ~Ninja() override;

        Ninja& operator=(const Ninja& nin);
        Ninja& operator=(Ninja&& nin) noexcept;
    };
}

#endif
