#include <math.h>
#include "mag.h"

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062
#endif

void mag_incdec2xyz(double inclination, double declination, double* x, double* y, double* z) {
	const double deg2rad = M_PI / 180;
	inclination *= deg2rad;
	declination *= deg2rad;
	
	*x = cos(inclination) * sin(declination);
	*y = cos(inclination) * cos(declination);
	*z = -sin(inclination);
}
