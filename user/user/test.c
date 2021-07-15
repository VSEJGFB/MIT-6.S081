#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int
main(int argc,char *argv[]){
    char *ca[6];
    ca[0]="xargs";
    ca[1]="echo";
    ca[2]="bye";
    ca[3]="hello";
    ca[4]="too";
    ca[5]=0;
   exec(ca[1],(char**)(&ca[1]));
   exit(0);
}
