#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void die(const char *message) {
  perror(message);
  exit(1);
}

void do_head(FILE *stream, int nrow) {
  int c;
  for (int i = 0; i < nrow; ++i) {
    for (;;) {
      c = fgetc(stream);

      if (c < 0) {
        goto loop_end;
      }

      fputc(c, stdout);
      if (c == '\n') {
        break;
      }
    }
  }
loop_end:
  exit(0);
}

void print_help() {
  printf("Usage: head <file=stdin> -n <nrow=5:int>\n");
  exit(1);
}

int main(int argc, const char **argv) {
  int nrow = 5;
  FILE *stream = stdin;

  int i;
  for (i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "-n") == 0) {
      if (i + 1 >= argc) {
        print_help();
      }

      i += 1;
      nrow = atoi(argv[i]);
      if (nrow == 0 && argv[i][0] != '0') {
        print_help();
      }

      continue;
    }

    stream = fopen(argv[i], "r");
    if (!stream) {
      die(argv[i]);
    }
  }

  do_head(stream, nrow);
}