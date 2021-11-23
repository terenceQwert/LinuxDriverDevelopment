#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define DEVFILE "/dev/devnode"

int open_file(void)
{
  int fd;
  fd = open(DEVFILE, O_RDWR);
  if( fd == -1)
  {
    perror("open");
  }
  return (fd);
}


void close_file(int fd)
{
  if( close(fd)!=0)
  {
    perror("close");
  }
}

int main()
{
  int fd;
  printf("<1> process open file\n");
  fd = open_file();
  printf("<1> process sleep()\n");
  sleep(20);
  printf("<1> process close file\n");
  close_file(fd);
  return 0;
}





