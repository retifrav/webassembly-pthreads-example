#include <iostream> // includes sin, tac, etc, how bizarre

#include "some-shit.h"

void doShit()
{
    double result = 0.0;
    for (int i = 0; i < 11111; i++)
    {
        result = result + sin(i) * tan(i);
    }

    //printf("result: %f\n", result);
    // using std::cout messes up the output
    //std::cout << "result: " << result << std::endl;
}
