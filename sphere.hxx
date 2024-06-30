#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include "vector.hxx"
#include <cassert>


typedef vec3<float> vec3f;
class sphere{
    public:

    vec3f center;                                   //position of the sphere
    float radius, radius2;                          //Radius of the sphere
    vec3f surface_color, emission_color;            //surface color and emission loght of the sphere
    float reflextion, transparency;                 // surface transparency and reflexivity

    sphere(
        const vec3f &c,
        const float &rad,
        const vec3f& s_color,    
        const float &refl=0,
        const float &trpcy=0,
        const vec3f& e_color=0
        
    ) : center(c), radius(rad),radius2(rad*rad), surface_color(s_color), emission_color(e_color), reflextion(refl), transparency(trpcy){}

    //Function to check whether incident ray intersecting the sphere or not.

    bool intersect(const vec3f & rayorig, const  vec3f& raydir, float& t0,float& t1)
    {
        vec3f l = center - rayorig;
        float tca = l.dot(raydir);
        if (tca < 0) return false;
        float d2 = l.dot(l) - tca * tca;
        if (d2 > radius2) return false;
        float thc = sqrt(radius2 - d2);
        t0 = tca - thc;
        t1 = tca + thc;      
        return true;
    }
};
