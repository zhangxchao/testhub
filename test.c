#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    char *path = NULL;
    int fd = 0;	
    printf("argc=%d\n",argc);
    if (argc == 2) {
        path = argv[1];
    } else
        path = "carveout_heap";
    printf("path=%s\n",path);
    if((fd = open(path, O_RDONLY, 0x800)) < 0) {
        printf("open file failed, errno=%d\n",errno);
    } else {
        int n = lseek(fd, 0, SEEK_END);
        lseek(fd, 0, 0);
        unsigned char * tmp = (unsigned char *)malloc(n);
        unsigned char *p = tmp; 
        unsigned char *p1=tmp;

        if (read(fd, tmp, n) > 0) {
            for(;;) {
                p1 = strchr(p,'\n');
                if (p1 == NULL) {
                    printf("%s\n",p);
                    break;
                }
                *p1 = '\0';
                printf("%s\n",p);
                p = p1+1;
            }
        }
        free(tmp);
        tmp = NULL;
        close(fd);

    }
    return 0;
}
