#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>

template<typename T>
class vec3{

    public:
    T x,y,z;

    vec3() : x(T(0)), y(T(0)), z(T(0)){}
    vec3(T xx) : x(xx), z(xx), y(xx) {}
    vec3(T a, T b, T c) : x(a), y(b), z(c) {}

    vec3& normalize()
    {
        T nor2 = lenght2();
        if(nor2 > 0)
        {
            T invNor = 1/sqrt(nor2);
            x*=invNor;
            y*=invNor;
            z*=invNor;
        }
        return *this;
    }    

    T lenght2() const {return x*x + y*y + z*z;}
    T lenght() const { return sqrt(lenght2());}        
    vec3<T> operator * (const T& f) const { return vec3<T>(x*f, y*f, z*f);}
    vec3<T> operator * (const vec3& v) const { return vec3<T>(x*v.x, y*v.y, z*v.z);}
    vec3<T> operator + (const vec3& v) const { return vec3<T>(x+v.x, y+v.y, z+v.z);}
    vec3<T> operator - (const vec3<T> &v) const { return vec3<T>(x - v.x, y - v.y, z - v.z); }
    vec3<T>& operator += (const vec3<T> &v) { x += v.x, y += v.y, z += v.z; return *this; }
    vec3<T>& operator *= (const vec3<T> &v) { x *= v.x, y *= v.y, z *= v.z; return *this; }
    vec3<T> operator - () const { return vec3<T>(-x, -y, -z); }
    T dot(const vec3& v) const { return v.x*x + v.y*y + v.z*z;}
    friend std::ostream& operator << (std::ostream& os, const vec3& v )
    {
        os << "[ "<<v.x<<" "<<v.y<<" "<<v.z<<" ]";
        return os; 
    }
};
