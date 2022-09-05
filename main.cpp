#include <SFML/Graphics.hpp>

#include "Geodesic.hpp"
#include "Particle.hpp"
#include "Spacetime.hpp"

#include "SkyMap.hpp"

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

int main()
{
    // ############### SPACETIME ###############
    // Flat st;
    
    const double M = 0.25;
    Schwarzschild st(M);

    // double M = 0.25;
    // double a = 0.;
    // Kerr st(M, a);

    // ############### AGENT ###############

    // spherical coords
    VecD position({10., M_PI / 2., 0.});
    // light speed proportional
    VecD velocity({0., 0.0, 0.0});

    // view inclination angle in radians
    const double alpha = 180. / 180. * M_PI;
    // view azimuth angle in radians
    const double beta = 0. / 180. * M_PI;

    //Spacetime, position, velocity, view_alpha, view_beta, velocity squared
    Particle par(st, position, velocity, alpha, beta, -1.);
    
    // set the vertical and horizontal field of view
    const field_of_view = 45. / 180. * M_PI;
    par.setAngleViews(field_of_view, field_of_view);
    
    const int dim = 200;
    // create a matrix with the positional information of the pixel in the 
    // original sky for each pixel inside the view
    // matrix of size  dim x dim, if the horizontal and vertical angles 
    // of the FOV are the same
    auto mat = par.view(dim);

    // ############### SKY ###############
    
    const bool do_elliptic_parametrization = false;
    // load an image to fill the sky
    ImageSkyMap sky(st, "res/images/stars_3.jpg", do_elliptic_parametrization);
    
    // color the sky with 8 colors
    // bool grid_agle =  M_PI / 18.;
    // bool thickness = M_PI / 180. / 5.;
    //ColorSkyMap sky(st, do_elliptic_parametrization, grid_agle, thickness);

    // ############### RESULTS ###############
    
    sf::Image view = sky.getSkyView(mat);
    view.saveToFile("tmp/screenshot" + std::to_string(time(NULL)) + ".png");

    return 0;
}
