#include <stdio.h>
#include <math.h>
#include <float.h>

int SolvSqr(float a, float b, float c,
            float* x1, float* x2);

const int ALLRTS = -1; // A state where any real x can be inserted as a root in the equation

int main()
{
    printf(
        "#YOUR_REQUEST: Quadratic equations solver\n"
        "================================================================================ \n"
        "Enter 3 numbers that correspond to a, b and c in the equation \n"
        "\t a*x^2 + b*x + c = 0 \n"
        ">"
    );

    float a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
    scanf("%f %f %f", &a, &b, &c);

    int Rts = SolvSqr(a, b, c, &x1, &x2);

    if(fabs(x1) < DBL_EPSILON) x1 = 0;

    if(fabs(x2) < DBL_EPSILON) x2 = 0;

    switch(Rts) {
        case(0) :
            printf("There are no roots in real numbers for the given equation\n");
            break;

        case(1) :
            printf("There is only one root %lg for the given equation\n", x1);
            break;

        case(2) :
            printf("The given equation possesses two roots in real numbers: %lg and %lg \n", x1, x2);
            break;

        case(ALLRTS) :
            printf("Any real number can be a root of the given equation\n");
    }

    printf(
        "================================================================================\n"
        "Request processed and result delivered.\n"
        "\tRestart application to process another quadratic equation."
    );

    return 0;
}

int SolvSqr(float a, float b, float c,
            float* x1, float* x2)
{

    if(fabs(a) > DBL_EPSILON) {
        float D = b * b - (4 * a * c);

        if(D < 0) return 0;
        else if(fabs(D) < DBL_EPSILON) {
            *x1 = (-b) / (2 * a);
            return 1;
        } else {
            D = sqrt(D);
            *x1 = (-b - D) / (2 * a);
            *x2 = (-b + D) / (2 * a);
            return 2;
        }
    } else if(fabs(b) > DBL_EPSILON) {
        *x1 = (-c) / b;
        return 1;
    } else if(fabs(c) > DBL_EPSILON) {
        return 0;
    } else
        return ALLRTS;

}
