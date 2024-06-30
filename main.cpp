#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>
#include "render.hxx"

int main(int argc, char **argv)
{
    srand48(13);
    std::vector<sphere> spheres;
    // position, radius, surface color, reflectivity, transparency, emission color
    spheres.push_back(sphere(vec3f( 0.0, -10004, -20), 10000, vec3f(0.20, 0.20, 0.20), 0, 0.0));
    spheres.push_back(sphere(vec3f( 0.0,      0, -20),     4, vec3f(1.00, 0.32, 0.36), 1, 0.5));
    spheres.push_back(sphere(vec3f( 5.0,     -1, -15),     2, vec3f(0.90, 0.76, 0.46), 1, 0.0));
    spheres.push_back(sphere(vec3f( 5.0,      0, -25),     8, vec3f(0.65, 0.77, 0.97), 1, 0.0));
    spheres.push_back(sphere(vec3f(-5.5,      0, -15),     4, vec3f(0.90, 0.90, 0.90), 1, 0.0));
    spheres.push_back(sphere(vec3f( 6.0,      1, -25),     4, vec3f(0.65, 0.77, 0.97), 1, 0.0));
    spheres.push_back(sphere(vec3f(-6.5,      2, -15),     1, vec3f(0.90, 0.90, 0.90), 1, 0.0));
    // light
    spheres.push_back(sphere(vec3f( 0.0,     20, -30),     3, vec3f(0.00, 0.00, 0.00), 0, 0.0, vec3f(3)));
    render(spheres);
    
    return 0;
}