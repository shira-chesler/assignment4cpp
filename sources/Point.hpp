#ifndef POINT_HPP
#define POINT_HPP

namespace ariel {
    class Point {
        double x_cor;
        double y_cor;

        public:
        Point(double x_cor, double y_cor);
        double distance(Point &othr);
        void print();
        friend Point moveTowards(Point src, Point dst, double dist);

        bool operator==(Point& othr);
    };
}


#endif 
