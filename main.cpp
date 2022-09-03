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
    // Flat st;
    
    double M = 0.25;
    Schwarzschild st(M);

    // double M = 0.25;
    // double a = 0.;
    // Kerr st(M, a);

    VecD position({10., M_PI / 2., 0.});
    VecD velocity({0., 0.0, 0.0});
    double alpha = 180. / 180. * M_PI;
    double beta = 0. / 180. * M_PI;

    Particle par(st, position, velocity, alpha, beta, -1.);
    par.setAngleViews(45. / 180. * M_PI, 45. / 180. * M_PI);
    int dim = 200;
    auto mat = par.view(dim);

    ImageSkyMap sky(st, "res/images/stars_3.jpg", false);
    //ColorSkyMap sky(st, false, M_PI / 18., M_PI / 180. / 5.);

    sf::Image view = sky.getSkyView(mat);

    view.saveToFile("tmp/screenshot" + std::to_string(time(NULL)) + ".png");

    return 0;
}
