#include "main.hpp"

#include <math.h>

long fact(long x)
{
    if (x == 0) return 1;
    return x * fact(x - 1);
}

int main()
{
    const double coef = 2 * sqrt(2) / 9801;
    double sum = 0.0;
    long i = 0;
    do
    {
        double t1 = fact(4*i);
        long t2 = 1103 + 26390*i;
        double t3 = pow(fact(i), 4.0);
        double t4 = pow(396.0, 4.0*i);
        sum += (t1*t2)/(t3*t4);
        double pi_inv = coef * sum;
        volatile double pi = 1.0 / pi_inv;
        ++i;
        (void) pi;
    }
    while (1);
}
