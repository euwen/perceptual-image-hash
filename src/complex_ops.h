#define PI  3.1415926535897932

//complex number datatype with real and imaginary part
typedef struct complex_t {
    double r;
    double i;
} complex;

//complex number prototypes
complex from_polar(double r, double theta_rads);
double  magnitude(complex c);
complex add(complex left, complex right);
complex sub(complex left, complex right);
complex mult(complex left, complex right);

//complex number function from polar
complex from_polar(double r, double theta_rads) {
    complex result;
    result.r = r * cos(theta_rads);
    result.i = r * sin(theta_rads);
    return result;
}

double magnitude(complex c) {
    return sqrt(c.r*c.r + c.i*c.i);
}

complex add(complex left, complex right) {
    complex result;
    result.r = left.r + right.r;
    result.i = left.i + right.i;
    return result;
}

complex sub(complex left, complex right) {
    complex result;
    result.r = left.r - right.r;
    result.i = left.i - right.i;
    return result;
}

complex mult(complex left, complex right) {
    complex result;
    result.r = left.r*right.r - left.i*right.i;
    result.i = left.r*right.i + left.i*right.r;
    return result;
}
