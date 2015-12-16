#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int i;
  int p[2];
  printf(1, "benchpipe: calling uptime\n");
  int starttime = uptime();

  int sz = 1024 * 1024 * 32;
  char buf[512];
  printf(1, "benchpipe: parent clearing buf %p - %p of size %d\n", buf, &buf[sizeof(buf)], sizeof(buf));
  for(i = 0; i < 512; ++i) buf[i] = 0;

  printf(1, "benchpipe: calling pipe\n");
  pipe(p);
  printf(1, "benchpipe: calling fork\n");
  int child = fork();

  if (child == 0) {
    // child: read
    printf(1, "benchpipe: child reading into buf %p\n", buf);
    for(i = 0; i < sz; i += 128) {
      //printf(1, "reading %d\n", i);
      //int nread = read(p[0], &buf[0], 128);
      //printf(1, "           read %d\n", nread);
      read(p[0], &buf[0], 128);
    }
    close(p[1]);
    close(p[0]);
  } else {
    if (child == -1) {
      printf(1, "benchpipe: fork() failed\n");
      close(p[0]);
      close(p[1]);
    } else {
      // parent: write
      printf(1, "benchpipe: parent (child=%d) allocating buf\n", child);
      printf(1, "benchpipe: parent writing out buf\n");
      for(i = 0; i < sz; i += 128) {
        //printf(1, "writing %d\n", i);
        write(p[1], &buf[0], 128);
      }
      wait();
      close(p[0]);
      close(p[1]);

      int fintime = uptime();
      printf(1, "elapsed ticks: %d\n", fintime - starttime);
    }
  }

  exit();
}
