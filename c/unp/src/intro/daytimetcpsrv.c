#include <time.h>

#include <unp.h>

int main(int argc, char** argv)
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
