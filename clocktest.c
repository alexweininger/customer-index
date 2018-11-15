#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
int main(int argc, char* argv[]){
    struct timeval start, end;
    unsigned long long total;
    gettimeofday(&start, NULL);
       sleep(3.75);
    gettimeofday(&end,NULL);
    total = ((unsigned long long)end.tv_sec*1000000ULL -
             (unsigned long long)start.tv_sec*1000000ULL) +
            ((unsigned long long)end.tv_usec -
             (unsigned long long)start.tv_usec);
    printf("Elapsed time: %ld uS\n", total);
}
