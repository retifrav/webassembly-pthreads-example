#include <iostream>

#include "some-shit.h"

int main()
{
    std::cout << "A program WITHOUT threads" << std::endl << std::endl;

    for (int t = 0; t < numberOfTasks; t++)
    {
        doShit(t, false);
    }

    return EXIT_SUCCESS;
}
