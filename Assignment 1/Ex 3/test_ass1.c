#include "types.h"
#include "stat.h"
#include "user.h"

int main(void)
{
    int retime, rutime, stime;
    int pid = fork();
    
    if(pid == 0) {
        for (volatile int i = 0; i < 100000000; i++) {} 
        char buf[100];
        read(0, buf, 100);
        sleep(69); 
        for (volatile int j = 0; j < 10000; j++) {} 
        exit();
    } else {
        // Parent process
        if (wait2((void*)&retime, (void*)&rutime, (void*)&stime) >= 0) {
            printf(1,"retime: %d, rutime: %d, stime: %d\n", retime, rutime, stime);
        } 
        else {
            printf(1,"wait2 failed \n ");
        }
    }
    
    exit();
}
