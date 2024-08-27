#include "types.h"
#include "stat.h"
#include "user.h"

int 
main(int argc, char *argv[]){
    if(argc!=2){
        printf(2,"ERROR 404 : The program expects 2 arguments only. Received %d which is != 2 obviously\n",argc);
        exit();
    }
    for(int i=0;i<strlen(argv[1]);i++){
        if((argv[1][i]<'0')||(argv[1][i]>'9')){
            printf(2,"ERROR 405 : The argument passed is not a positive int. Received %s which is obviously not an pos int u dumbo\n",argv[1]);
            exit();
        }
    }
    int ticks=atoi(argv[1]);
    sleep(ticks);
    exit();


}