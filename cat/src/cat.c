#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static void die(const char *message) {
  perror(message);
  exit(1);
}

#define BUFFER_SIZE 1024

static void do_cat(const int fd, const char* name) {
  int read_n, write_n;
  char buffer[BUFFER_SIZE];

  for (;;) {
    read_n = read(fd, buffer, BUFFER_SIZE);
    if (read_n < 0) {
      die(name);
    }
    if (read_n == 0)
      break;

    for (int write_total = 0; write_total < read_n;) {
      write_n = write(STDOUT_FILENO, &buffer[write_total], read_n - write_total);
      if (write_n < 0) {
        die(name);
      }
      if (write_n == 0) {
        printf("writing target is maybe full\n");
        break;
      }

      write_total += write_n;
    }
  }

  
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    do_cat(STDIN_FILENO, "stdio");
    exit(0);
  }

  if (strcmp(argv[1], "--help") == 0) {
    printf("Usage: cat <file1> <file2> ... \n");
    exit(1);
  }

  int fd;
  for (int i = 1; i < argc; ++i) {
    const char* file = argv[i];

    fd = open(file, O_RDONLY);
    if (fd < 0) {
      die(file);
    }
    do_cat(fd, file);
    if (close(fd) < 0) die(file);
  }
  exit(0);
}