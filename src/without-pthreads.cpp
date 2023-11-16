#include <iostream>
#include <unistd.h>

#include "some-shit.h"

void doSome(int taskID)
{
    sleep(2);

    std::cout << "ololo, inside the task #" << taskID << std::endl;

    doShit();
}

int main()
{
    std::cout << "A program WITHOUT threads" << std::endl << std::endl;

    for (int t = 0; t < numberOfTasks; t++)
    {
        doSome(t);
    }

    return EXIT_SUCCESS;
}
