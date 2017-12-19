#include <iostream>

using namespace std;


class R3Vec
{
private:

public:
    double x;
    double y;
    double z;
    
    double length() const;
    R3Vec();
    R3Vec(double, double, double);
    ~R3Vec(); //деструктор
    R3Vec(const R3Vec& );
    R3Vec operator-() const;
    R3Vec operator+(const R3Vec& ) const;
    R3Vec operator-(const R3Vec& ) const;
    double operator*(const R3Vec& ) const;
    R3Vec& operator*=(double );
    double angle(const R3Vec& ) const;
    R3Vec operator^(const R3Vec& ) const;
    double distance(const R3Vec& ,const R3Vec& ,const R3Vec& ) const;

    friend ostream & operator<<(ostream & o, R3Vec v); //вывод
    friend istream & operator>>(istream & i, R3Vec& v); //ввод
    friend void dist(R3Vec A, R3Vec v, R3Vec B, R3Vec w );
};

