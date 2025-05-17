#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void die(const char *message) {
  perror(message);
  exit(1);
}

#define TAIL_DEFAULT_BUFFER_SIZE 1024

void do_tail(FILE *stream, int nrow) {
  long **table;
  int *table_size;
  int *table_capacity;
  int table_start = 0;
  int c;
  int cur;

  table = malloc(sizeof(long *) * (nrow + 1));
  table_size = malloc(sizeof(int) * (nrow + 1));
  table_capacity = malloc(sizeof(int) * (nrow + 1));
  for (int i = 0; i < (nrow + 1); ++i) {
    table_size[i] = 0;
    table_capacity[i] = TAIL_DEFAULT_BUFFER_SIZE;
    table[i] = malloc(sizeof(char) * table_capacity[i]);
  }

  cur = 0;
  for (;;) {
    c = fgetc(stream);
    if (c < 0) {
      break;
    }

    if (table_size[cur] == table_capacity[cur]) {
      long *tmp = table[cur];
      table[cur] = malloc(table_capacity[cur]);
      memcpy(table[cur], tmp, table_capacity[cur]);
      table_capacity[cur] *= 2;
      free(tmp);
    }
    table[cur][table_size[cur]++] = c;


    if (c == '\n') {
      cur = (cur + 1) % (nrow + 1);
      table_size[cur] = 0;
    }
  }

  cur = (cur + 2) % (nrow + 1);
  for (int _=0;_<nrow; ++_) {
    for (int j=0; j<table_size[cur]; ++j) {
      fputc(table[cur][j], stdout);
    }
    cur = (cur + 1) % (nrow + 1);
  }

  for (int i = 0; i < (nrow + 1); ++i) {
    free(table[i]);
  }
  free(table);
  free(table_size);
  free(table_capacity);
  exit(0);
}

void print_help() {
  printf("Usage: tail <file=stdin> -n <nrow=5:int>\n");
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

  do_tail(stream, nrow);
}