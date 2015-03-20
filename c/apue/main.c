#include <assert.h>
#include <stdio.h>
#include <dirent.h>

#include <dlib_comm.h>

int ls(int argc, char** argv)
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

int main(int argc, char** argv)
{
  const dlib_cmd_t cmds[] = {
    DLIB_CMD_DEFINE(ls, "[<dir>]"),
    DLIB_CMD_NULL
  };
  return dlib_subcmd(argc, argv, cmds);
}
