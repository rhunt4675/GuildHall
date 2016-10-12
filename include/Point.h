#ifndef cordinate_header
#define cordinate_header

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

class Point {
    public:
        float getX();
        float getY();
        float getZ();
        float* getPos();
        void change_pos(float x, float y, float z);
        void move(float x, float y, float z);
        Point(float startX, float startY, float startZ);
        Point();

    protected:
        void updateCords();
        float posX, posY, posZ;
        float cords[3];

};

Point operator*( Point p, float f );
Point operator*( float f, Point p );
Point operator+( Point a, Point b );
Point operator-( Point a, Point b );
#endif
