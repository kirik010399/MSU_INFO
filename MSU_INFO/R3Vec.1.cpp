#include "R3Vec.1.h"
#include <math.h>
#include <iostream>
#include <iomanip>

R3Vec::R3Vec():x(0.),y(0.),z(0.) {}

double R3Vec::length() const
{
    return sqrt(x*x + y*y + z*z);
}

R3Vec::R3Vec(double x1, double y1, double z1): x(x1), y(y1), z(z1) {}
R3Vec::R3Vec(const R3Vec& v): x(v.x), y(v.y), z(v.z) {}
R3Vec::~R3Vec() {}

R3Vec R3Vec::operator-() const
    {
        R3Vec v;
        v.x = -x;
        v.y = -y;
        v.z = -z;
        return v;
    }
R3Vec R3Vec::operator+(const R3Vec& v) const
    {
        R3Vec w;
        w.x = x + v.x;
        w.y = y + v.y;
        w.z = z + v.z;
        return w;
    }
R3Vec R3Vec::operator-(const R3Vec& v) const
    {
        R3Vec w;
        w.x = x - v.x;
        w.y = y - v.y;
        w.z = z - v.z;
        return w;
    }

double R3Vec::operator*(const R3Vec& v) const  //scalar product
{
    return x*(v.x) + y*(v.y) + z*(v.z);
}
R3Vec& R3Vec::operator*=(double c)
{
    x *= c;
    y *= c;
    z *= c;
    return *this;
}
R3Vec R3Vec::operator^(const R3Vec& v) const //vector product
{
    R3Vec w;
    w.x = y*v.z - z*v.y;
    w.y = z*v.x - x*v.z;
    w.z = x*v.y - y*v.x;
    return w;
}
double R3Vec::angle(const R3Vec& v) const
{
    return acos((x*v.x + y*v.y + z*v.z)/(sqrt(x*x + y*y + z*z)*sqrt(v.x*v.x + v.y*v.y + v.z*v.z)));
}


ostream & operator<<(ostream & o, R3Vec v)
{
    o << setprecision(2) << v.x << " " << v.y << " " << v.z << " ";
    return o;
}

istream & operator>>(istream & i, R3Vec &v)
{
    i >> v.x >> v.y>> v.z;
    return i;
}

void dist(R3Vec A, R3Vec v, R3Vec B, R3Vec w );
void dist(R3Vec A, R3Vec v, R3Vec B, R3Vec w )
{
    double m = B.x-A.x;
    double n = B.y-A.y;
    double k = B.z-A.z;
    double c = v.y*w.z-v.z*w.y;
    double d = v.x*w.z-v.z*w.x;
    double e = v.x*w.y-v.y*w.x;
    double p = sqrt(c*c + d*d + e*e);
    double q = v.x*w.y*k + v.y*w.z*m + v.z*w.x*n - v.z*w.y*m - v.x*w.z*n - v.y*w.x*k;
    cout << setprecision(3) << fabs(q)/p << ' ' ;

}

double R3Vec::distance(const R3Vec& E, const R3Vec& G, const R3Vec& H) const
{
    double A = G.y*H.z-G.y*E.z-E.y*H.z+H.y*E.z-H.y*G.z+E.y*G.z;
    double B = H.x*G.z-H.x*E.z-E.x*G.z-G.x*H.z+G.x*E.z+E.x*H.z;
    double C = G.x*H.y-G.x*E.y-E.x*H.y-H.x*G.y+H.x*E.y+E.x*G.y;
    double D = E.x*(H.y*G.z-G.y*H.z)+G.x*(E.y*H.z-E.z*H.y)+H.x*(G.y*E.z-E.y*G.z);
    return (fabs(A*x + B*y + C*z + D)/sqrt(A*A + B*B + C*C));
}

