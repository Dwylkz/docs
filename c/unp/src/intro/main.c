#include <stdio.h>
#include <netinet/in.h>
#include <unp.h>
#include <dlib_comm.h>

static int basic(int argc, char** argv)
{
  struct in_addr addr;
  bzero(&addr, sizeof(addr));
  addr.s_addr = 10;
  printf("(%d)\n", addr.s_addr);

  struct sockaddr_in sockaddr;
  bzero(&sockaddr, sizeof(sockaddr));
  printf("(%hhu %hu %d %d)\n",
         sockaddr.sin_len,
         sockaddr.sin_port,
         sockaddr.sin_family,
         sockaddr.sin_addr.s_addr);
  return 0;
}

static int daytimetcpcli(int argc, char** argv)
{
  int sockfd, n;
  char recvline[MAXLINE+1];
  struct sockaddr_in servaddr;

  // Exercise 1.4
  int count;

  if (argc != 2)
    return -2;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  // Exercise 1.3
  // sockfd = socket(9999, SOCK_STREAM, 0);
  if (sockfd < 0) {
    err_sys("socket error");
  }

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  // servaddr.sin_port = htons(13);
  // Exercise 1.5
  servaddr.sin_port = htons(9999);
  if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
    err_quit("inet_pton error for %s", argv[1]);

  if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) < 0)
    err_sys("connect error");

  count = 0;
  while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
    recvline[n] = 0;
    if (fputs(recvline, stdout) == EOF)
      err_sys("fputs error");

    count++;
  }

  if (n < 0)
    err_sys("read error");

  printf("count = %d\n", count);

  return 0;

}

static int daytimetcpcliv6(int argc, char** argv)
{
  int sockfd, n;
  char recvline[MAXLINE+1];
  struct sockaddr_in6 servaddr;

  if (argc != 2)
    return -2;

  if ((sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0)
    err_sys("socket error");

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin6_family = AF_INET6;
  servaddr.sin6_port= htons(13);
  if (inet_pton(AF_INET6, argv[1], &servaddr.sin6_addr) <= 0)
    err_quit("inet_pton error for %s", argv[1]);

  if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) < 0)
    err_sys("connect error");

  while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
    recvline[n] = 0;
    if (fputs(recvline, stdout) == EOF)
      err_sys("fputs error");
  }
  if (n < 0)
    err_sys("read error");

  return 0;
}

static int daytimetcpsrv(int argc, char** argv)
{
  int listenfd = Socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in servaddr;
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(13);
  // Exercise 1.5
  servaddr.sin_port = htons(9999);
  Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));
  Listen(listenfd, LISTENQ);

  char buff[MAXLINE];
  for (;;) {
    int connfd = Accept(listenfd, (SA*)NULL, NULL);

    time_t ticks = time(NULL);
    snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
    // Write(connfd, buff, strlen(buff));
    // Exercise 1.5
    int buff_len = strlen(buff);
    int i;
    for (i = 0; i < buff_len; i++)
      Write(connfd, &buff[i], 1);

    Close(connfd);
  }

  return 0;
}

int main(int argc, char** argv)
{
  const dlib_cmd_t cmds[] = {
    DLIB_CMD_DEFINE(basic, ""),
    DLIB_CMD_DEFINE(daytimetcpcli, "<ip-address>"),
    DLIB_CMD_DEFINE(daytimetcpcliv6, "<ip-address>"),
    DLIB_CMD_DEFINE(daytimetcpsrv, ""),
    DLIB_CMD_NULL
  };
  return dlib_subcmd(argc, argv, cmds);
}
