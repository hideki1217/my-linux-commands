#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

void die(const char *message) {
  perror(message);
  exit(1);
}

void die_with_help() {
  printf("Usage: time <cmd> <arg1> ...\n");
  exit(1);
}

int main(int argc, const char *argv[]) {
  int pid;

  if (argc < 2) {
    die_with_help();
  }

  pid = fork();
  if (pid < 0) {
    die("fork");
  }

  char **arguments = malloc(sizeof(char *) * argc);
  if (!arguments) {
    die("malloc");
  }
  for (int i = 0; i < argc - 1; ++i) {
    arguments[i] = malloc(sizeof(char) * (strlen(argv[1 + i]) + 1));
    if (!arguments[i]) {
      die("malloc");
    }

    strcpy(arguments[i], argv[1 + i]);
  }
  arguments[argc - 1] = NULL;

  // Worker
  if (pid == 0) {
    execvp(argv[1], arguments);
    die("execv");
  } else {
    struct timeval t1, t2;
    struct timezone dummy;
    int wstatus;
    float elapse;

    gettimeofday(&t1, &dummy);
    waitpid(pid, &wstatus, 0);
    gettimeofday(&t2, &dummy);

    elapse =
        (t2.tv_sec - t1.tv_sec) + (float)(t2.tv_usec - t1.tv_usec) / 1000000;
    printf("\n\n-----\ntime\n\nos: %f (s) \n", elapse);

    for (int i = 0; i < argc - 1; ++i) {
      free(arguments[i]);
    }
    free(arguments);
  }

  exit(0);
}