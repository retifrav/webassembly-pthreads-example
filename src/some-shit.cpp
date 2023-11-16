#include <iostream> // also includes sin, tac, etc, how bizarre
#include <unistd.h>

#include "some-shit.h"

void doShit(int someID, bool isAThread)
{
    sleep(2);

    if(isAThread)
    {
        // using std::cout messes up the output
        //std::cout << "ololo, inside a thread, batch ID:" << *(int *)arg << std::endl;
        printf("ololo, inside a thread, batch ID: %d\n", someID);
    }
    else
    {
        std::cout << "ololo, inside the task #" << someID << std::endl;
    }

    double result = 0.0;
    for (int i = 0; i < 11111; i++)
    {
        result = result + sin(i) * tan(i);
    }

    //printf("result: %f\n", result);
    // using std::cout messes up the output
    //std::cout << "result: " << result << std::endl;
}
