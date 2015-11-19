#include <apue.h>

#include <errno.h>
#include <assert.h>
#include <dirent.h>

#include <dlib_comm.h>

static int ls(int argc, char** argv)
{
  char* dir = ".";
  if (argc == 2) dir = argv[1];

  DIR* dp = opendir(dir);
  assert(dp != NULL);

  struct dirent* ent;
  while ((ent = readdir(dp)) != NULL)
    printf("%s\n", ent->d_name);

  assert(closedir(dp) == 0);
  return 0;
}

/* unbuffered io */
static int ubio(int argc, char** argv)
{
  char buf[BUFSIZ];
  int nread;
  while ((nread = read(STDIN_FILENO, buf, BUFSIZ)) > 0)
    assert(write(STDOUT_FILENO, buf, nread) >= 0);
  return 0;
}

static void sig_int(int signo)
{
  printf("interupt\n>> ");
  fflush(stdout);
}

static int runcmd(int argc, char** argv)
{
  if (signal(SIGINT, sig_int) == SIG_ERR) {
    perror("set signal failed");
    return -1;
  }
  char buf[BUFSIZ];
  printf(">> ");
  fflush(stdout);
  while (fgets(buf, BUFSIZ, stdin)) {
    int nbuf = strlen(buf);
    if (buf[nbuf-1] == '\n') buf[nbuf-1] = '\0';
    int pid = fork();
    if (pid == -1) {
      perror(buf);
      continue;
    }
    if (pid == 0) {
      /* child */
      execlp(buf, (char*)NULL);
      perror(buf);
      return -1;
    }
    /* parent */
    waitpid(pid, NULL, 0);
    printf(">> ");
    fflush(stdout);
  }
  return 0;
}

static int ugid(int argc, char** argv)
{
  printf("uid=%d gid=%d\n", getuid(), getgid());
  return 0;
}

int main(int argc, char** argv)
{
  const dlib_cmd_t cmds[] = {
    DLIB_CMD_DEFINE(ls, "[<dir>]"),
    DLIB_CMD_DEFINE(ubio, ""),
    DLIB_CMD_DEFINE(runcmd, ""),
    DLIB_CMD_DEFINE(ugid, ""),
    DLIB_CMD_NULL
  };
  return dlib_subcmd(argc, argv, cmds);
}
