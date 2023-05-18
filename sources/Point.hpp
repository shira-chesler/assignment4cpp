#ifndef POINT_HPP
#define POINT_HPP

#include <string>

namespace ariel {
    class Point {
        double x_cor;
        double y_cor;

        public:
        Point(double x_cor, double y_cor);
        double distance(Point othr) const;
        std::string print();
        double getX();
        double getY();
        static Point moveTowards(Point src, Point dst, double dist);

        bool operator==(Point& othr);
    };
}


#endif 
