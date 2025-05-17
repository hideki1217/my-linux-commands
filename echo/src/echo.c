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

int main(int argc, const char **argv) {
  int n, cur;
  int write_n;
  for (int i = 1; i < argc; ++i) {
    n = strlen(argv[i]);
    cur = 0;

    if (i > 1 && write(STDOUT_FILENO, " ", 1) < 0) {
        die(" ");
    }

    for (int cur = 0; cur < n;) {
      write_n = write(STDOUT_FILENO, &argv[i][cur], n - cur);
      if (write_n < 0) {
        die(argv[i]);
      }
      if (write_n == 0)
        break;

      cur += write_n;
    }
  }

  if (write(STDOUT_FILENO, "\n", 1) < 0) {
    die(" ");
  }
}