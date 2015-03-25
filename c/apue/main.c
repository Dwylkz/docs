#include <apue.h>

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

// unbuffered io
static int ubio(int argc, char** argv)
{
  char buf[BUFSIZ];
  int nread;
  while ((nread = read(STDIN_FILENO, buf, BUFSIZ)) > 0)
    assert(write(STDOUT_FILENO, buf, nread) >= 0);
  return 0;
}

int main(int argc, char** argv)
{
  const dlib_cmd_t cmds[] = {
    DLIB_CMD_DEFINE(ls, "[<dir>]"),
    DLIB_CMD_DEFINE(ubio, ""),
    DLIB_CMD_NULL
  };
  return dlib_subcmd(argc, argv, cmds);
}
