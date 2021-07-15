#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  memmove(buf,p,strlen(p)+1);
  return buf;
}

char find_name[DIRSIZ+1];

void
dfs(char *path){

    char *p;
    int fd;
    struct dirent de;
    struct stat st;


    if((fd = open(path, 0)) < 0){
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    if(fstat(fd, &st) < 0){
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }
    
    switch(st.type){
        case T_FILE:
            if(strcmp(find_name,fmtname(path)) == 0) {
                fprintf(1,"%s\n",path);
            }
            break;

        case T_DIR:
            p = path+strlen(path);
            *p++ = '/';
            while(read(fd, &de, sizeof(de)) == sizeof(de)){
                if(de.inum == 0 || strcmp(de.name,".") == 0 || strcmp(de.name,"..") == 0 )
                    continue;
                memmove(p, de.name, DIRSIZ);
                dfs(path);
            }
            break;
      }
      close(fd);
}

int
main(int argc,char *argv[]){
    char path[512];
//    fprintf(1,"argc=%d\n",argc);
    if(argc < 2){
        exit(0);
    }
    if(argc <= 2){
        strcpy(find_name,argv[1]);
        strcpy(path,".");
    } else {
        strcpy(find_name,argv[2]);
        strcpy(path,argv[1]);
    }
    dfs(path);
    exit(0);
}

