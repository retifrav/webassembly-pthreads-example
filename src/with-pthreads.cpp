#include <iostream>
#include <pthread.h>

#include "some-shit.h"

void *threadCallback(void *arg)
{
    doShit(*(int *)arg, true);

    return NULL;
}

int main(int argc, char* argv[])
{
    std::cout << "A program WITH threads" << std::endl << std::endl;

    pthread_t thread_ids[numberOfTasks];

    int batchID = 1;
    for (int i = 0; i < numberOfTasks; i++)
    {
        // using `i` instead of `batchID` will result in all the threads getting 10 (the last value)
        int rez = pthread_create(&thread_ids[i], NULL, threadCallback, &batchID);
        if (rez)
        {
            std::cerr << "[ERROR] return code from pthread_create() is " << rez
                      << " | " << strerror(rez)
                      << std::endl;
            return EXIT_FAILURE;
        }
        pthread_detach(thread_ids[i]);

        std::cout << "Spawned thread #" << i << std::endl;
    }

    std::cout << std::endl;

    // pthread_join() is blocking, so if you have 9000 threads running for a long time each,
    // then threads 1-8999 will not be joined until thread 0 completes, while some of these
    // may end a lot earlier, so pthread_detach() would be more preferred
    // for (int i = 0; i < numberOfTasks; i++)
    // {
    //     pthread_join(thread_ids[i], NULL);
    // }

    // if using pthread_detach()
    pthread_exit(0);

    return EXIT_SUCCESS;
}
