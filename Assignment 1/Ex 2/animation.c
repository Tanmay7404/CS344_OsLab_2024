#include "types.h"
#include "stat.h"
#include "user.h"

void clearScreen() {
    printf(1, "\033[2J\033[H");
}

void print(int frameNumber){
    for(int i=0;i<frameNumber;i++){
        printf(1," ");
    }
    printf(1,"-----\n");
    for(int j=0;j<2;j++){
        for(int i=0;i<frameNumber;i++){
            printf(1," ");
        }
        printf(1,"|   |\n");
    }
    for(int i=0;i<frameNumber;i++){
        printf(1," ");
    }
    printf(1,"-----\n");

    for(int j=0;j<2;j++){
        for(int i=0;i<frameNumber+2;i++){
            printf(1," ");
        }
        printf(1,"|\n");
    }
    for(int i=0;i<frameNumber;i++){
        printf(1," ");
    }
    printf(1,"--|--\n");
    for(int j=0;j<2;j++){
        for(int i=0;i<frameNumber+2;i++){
            printf(1," ");
        }
        printf(1,"|\n");
    }
    for(int i=0;i<frameNumber+2;i++){
        printf(1," ");
    }
    printf(1,"^\n");
    for(int i=0;i<frameNumber+1;i++){
        printf(1," ");
    }
    printf(1,"/ \\\n");
    for(int i=0;i<frameNumber;i++){
        printf(1," ");
    }
    printf(1,"/   \\\n");
    for(int i=0;i<105;i++){
        printf(1,"-");
    }

}

void printFrame(int frameNumber) {
    clearScreen();
    
    
    print(frameNumber);
}

int main(int argc, char *argv[]) {
    int i;
    while(1){
        for (i = 0; i <=100; i++) {
            printFrame(i);     
            sleep(6);         
        }
        for(int i=100;i>=0;i--){
            printFrame(i);
            sleep(6);
        }
    }
    
    exit();
}