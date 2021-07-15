#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int
main(int argc,char *argv[]){
    char buf[512];
    read(0,buf,512);
    char* p[MAXARG+10];
    for(int i=0;i<argc;i++){
        p[i]=argv[i];
    }
    int len = strlen(buf);
    short fst = 1;
    int pcur = argc;
    for(int i=0;i<len;i++){
        if(fst && buf[i]!=' ' && buf[i]!='\n'){
            p[pcur++] = &buf[i];
            fst = 0;
        } else {
            if(buf[i] == ' '){
                buf[i] = '\0';
                fst = 1;
            } else if(buf[i] == '\n'){
                buf[i] = '\0';
                p[pcur++] = 0;
                if(fork() == 0){
                    exec(p[1],(char**)(&p[1]));
                }
                wait((int*)0);
                pcur = argc;
                fst = 1; 
            }
        }
    }
    exit(0);
}
