#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int i,p,n,pp[2],pp2[2];
    short flag = 0;
    pipe(pp);
    for(i = 2;i<=36;i++)
        write(pp[1],&i,4);
    if(fork() == 0){
        close(pp[1]);
        while(1){
            read(pp[0],&p,4);
            fprintf(0,"prime %d\n",p);
            while(1){
                if(read(pp[0],&n,4) == 0 || n == 36){
                    close(pp2[1]);
                    wait((int*)0);
                    exit(0);
                }
                if(n % p != 0){
                    if(!flag){
                        pipe(pp2);
                        if(fork() != 0){
                            write(pp2[1],&n,4);
                            flag = 1;
                        }else{
                            close(pp[0]);
                            pp[0] = pp2[0];
                            close(pp2[1]);
                            flag = 0;
                            break;
                        }
                    }else{ 
                        write(pp2[1],&n,4);
                    }
                }
            }
        }
    } else {
        close(pp[0]);
        wait((int*)0);
        close(pp[1]);
        exit(0);
    }
    exit(1);
}
