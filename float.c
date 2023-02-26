#include <sys/types.h>
#include <stdio.h>
int main (int argc, char *argv[])
{
  char s[1024];
  FILE *fp;
  if((fp = fopen(argv[1], "r")) != (FILE*)0){
    while ((fgets(s,1024, fp)) != (char*) 0) {
      puts(s);
    }
  }else {
    fprintf(stderr, "file open error.\n");
    exit(1);
  }
  exit(0);
}
