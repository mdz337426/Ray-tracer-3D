#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>
#include "sphere.hxx"
#define MAX_RAY_DEPTH 5


float mix(const float &a, const float &b, const float &mix)
{
    return b * mix + a * (1 - mix);
}

// This is the main trace function. It takes a ray as argument (defined by its origin
// and direction). We test if this ray intersects any of the geometry in the scene.
// If the ray intersects an object, we compute the intersection point, the normal
// at the intersection point, and shade this point using this information.
// Shading depends on the surface property (is it transparent, reflective, diffuse).
// The function returns a color for the ray. If the ray intersects an object that
// is the color of the object at the intersection point, otherwise it returns
// the background color.

vec3f trace(
    const vec3f& rayOrig,
    const vec3f& rayDir,
    std::vector<sphere>&spheres,
    const int& depth
    )
{
    //if(rayDir.lenght()!=1) std::cerr<<"Error "<<rayDir<<'\n';

    const sphere * Sphere = NULL;
    float tnear = INFINITY;

    for(long long i =0; i<spheres.size(); i++)
    {
        float t0 = INFINITY, t1 = INFINITY;
        if(spheres[i].intersect(rayOrig, rayDir, t0, t1))
        {
            if(t0<0) t0=t1;
            if(t0<tnear){
            Sphere = &spheres[i];
            tnear = t0;
            }
        }
    }

    if(!Sphere) return vec3f(2);
    vec3f surfaceColor = 0; // color of the ray/surfaceof the object intersected by the ray
    vec3f phit = rayOrig + rayDir * tnear; // point of intersection
    vec3f nhit = phit - Sphere->center; // normal at the intersection point
    nhit.normalize(); // normalize normal direction
    float bias = 1e-4;
    bool is_inside = false;
    if(nhit.dot(rayDir) >0) nhit=-nhit, is_inside=true;

     if ((Sphere->transparency > 0 || Sphere->reflextion > 0) && (depth < MAX_RAY_DEPTH)) {
        float facingratio = -rayDir.dot(nhit);
        // change the mix value to tweak the effect
        float fresneleffect = mix(pow(1 - facingratio, 3), 1, 0.1);
        // compute reflection direction (not need to normalize because all vectors
        // are already normalized)
        vec3f refldir = rayDir - nhit * 2 * rayDir.dot(nhit);
        refldir.normalize();
        vec3f reflection = trace(phit + nhit * bias, refldir, spheres, depth + 1);
        vec3f refraction = 0;
        // if the sphere is also transparent compute refraction ray (transmission)
        if (Sphere->transparency) {
            float ior = 1.1, eta = (is_inside) ? ior : 1 / ior; // are we inside or outside the surface?
            float cosi = -nhit.dot(rayDir);
            float k = 1 - eta * eta * (1 - cosi * cosi);
            vec3f refrdir = rayDir * eta + nhit * (eta *  cosi - sqrt(k));
            refrdir.normalize();
            refraction = trace(phit - nhit * bias, refrdir, spheres, depth + 1);
        }
        // the result is a mix of reflection and refraction (if the sphere is transparent)
        surfaceColor = (
            reflection * fresneleffect +
            refraction * (1 - fresneleffect) * Sphere->transparency) * Sphere->surface_color;
    }
    else {
        // it's a diffuse object, no need to raytrace any further
        for (unsigned i = 0; i < spheres.size(); ++i) {
            if (spheres[i].emission_color.x > 0) {
                // this is a light
                vec3f transmission = 1;
                vec3f lightDirection = spheres[i].center - phit;
                lightDirection.normalize();
                for (unsigned j = 0; j < spheres.size(); ++j) {
                    if (i != j) {
                        float t0, t1;
                        if (spheres[j].intersect(phit + nhit * bias, lightDirection, t0, t1)) {
                            transmission = 0;
                            break;
                        }
                    }
                }
                surfaceColor += Sphere->surface_color * transmission *
                std::max(float(0), nhit.dot(lightDirection)) * spheres[i].emission_color;
            }
        }
    }
    
    return surfaceColor + Sphere->emission_color;
}