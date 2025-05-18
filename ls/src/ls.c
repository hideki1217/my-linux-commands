#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void die(const char *message) {
  perror(message);
  exit(1);
}

#define TAIL_DEFAULT_BUFFER_SIZE 1024

#define SET_TEXT_BLUE "\x1b[34m"
#define SET_TEXT_YELLOW "\x1b[33m"
#define RESET_TEXTURE "\x1b[39m"

void do_ls(const char *path) {
  DIR *dirp;
  struct dirent *diren;
  int status;

  dirp = opendir(path);
  if (!dirp) {
    die(path);
  }

  for (int is_not_first = 0;;) {
    diren = readdir(dirp);
    if (!diren) {
      break;
    }

    if (diren->d_name[0] == '.')
      continue;

    if (is_not_first++) {
      fputs("  ", stdout);
    }

    if (diren->d_type == DT_DIR) {
      fputs(SET_TEXT_BLUE, stdout);
    } else if (diren->d_type & DT_CHR) {
      fputs(SET_TEXT_YELLOW, stdout);
    } else {
    }
    fputs(diren->d_name, stdout);
    fputs(RESET_TEXTURE, stdout);
  }
  fputc('\n', stdout);

  status = closedir(dirp);
  if (status < 0) {
    die(path);
  }

  exit(0);
}

int main(int argc, const char **argv) {
  const char *path;
  if (argc < 2) {
    path = ".";
  } else {
    path = argv[1];
  }

  do_ls(path);
}