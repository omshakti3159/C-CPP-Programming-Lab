#include <math.h>

int distance(double lat1, double lon1, double lat2, double lon2) {
    double phi1 = (90 - lat1) * M_PI / 180;
    double phi2 = (90 - lat2) * M_PI / 180;
    double theta1 = lon1 * M_PI / 180;
    double theta2 = lon2 * M_PI / 180;
    double c;
    int    d;
    c = sin(phi1)*sin(phi2)*cos(theta1-theta2) + cos(phi1)*cos(phi2);
    d = (int)6371*acos(c);
    return d;
}
