#include <stdio.h>
#include <string.h>

#include <signal.h>
#include <unistd.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <unp.h>
#include <dlib_comm.h>

// kernel to process: bind, connect, sendto, sendmsg
// process to kernel: accept, recvfrom, recvmsg, getpeername, getsockname
// network byteorder use big-endian, host-byteorder is cpu dependent
// while EINTR, we should read again

typedef union endian_t {
  short s;
  char c[sizeof(short)];
} endian_t;

static void sig_chld(int signo)
{
  pid_t pid;
  int stat;
  while ((pid = waitpid(-1, &stat, WNOHANG)) > 0) {
    printf("child terminated: pid=%d\n", pid);
  }
  return ;
}

static const char* system_endian()
{
  int ret = 0;

  static const char* msg[] = {"big-endian", "little-endian", "unknow"};
  if (sizeof(short) != 2)
    err_sys("sizeof(short)=%d\n", sizeof(short));

  endian_t s;
  s.s = 0x0102;
  if (s.c[0] == 1 && s.c[1] == 2)
    ret = 0;
  else if (s.c[0] == 2 && s.c[1] == 1)
    ret = 1;
  else
    ret = 2;
  return msg[ret];
}

static const char* endian_show(endian_t* s)
{
  static char foo[BUFSIZ];
  char* bar = foo;
  bar += sprintf(bar, "(endian_t");
  for (int i = 0, nmemb = sizeof(s->c); i < nmemb; i++)
    bar += sprintf(bar, " %hhu", s->c[i]);
  bar += sprintf(bar, ")");
  return foo;
}

static int inet_pton_loose(int af, const char* restrict src, void* restrict dst)
{
  if (inet_pton(af, src, dst) != 1)
    return inet_aton(src, dst);
  return 1;
}

static int multiplex(int argc, char** argv, int (*action)(int, char**))
{
  if (argc < 2)
    return -2;

  uint32_t times;
  if (sscanf(argv[1], "%u", &times) != 1)
    return -2;

  while (times--) {
    int pid = fork();
    if (pid == -1) {
      DLIB_ERR("fork failed: (%s)", dlib_syserr());
      return -1;
    }
    if (pid == 0) {
      exit(action(argc-1, argv+1));
    }
  }
  return 0;
}

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

  struct in6_addr addr6;
  bzero(&addr, sizeof(addr6));
  strcpy((char*)&addr6.s6_addr, "hhee");
  printf("(%s)\n", addr6.s6_addr);

#define SIN6_LEN

  struct sockaddr_in6 sockaddr6;
  bzero(&sockaddr6, sizeof(sockaddr6));
  printf("size=%ld\n", sizeof(sockaddr6));
  printf("%ld\n", (char*)&sockaddr6.sin6_family-(char*)&sockaddr6);
  printf("(%hhu %u %u %u (%s) %u)\n",
         sockaddr6.sin6_len,
         sockaddr6.sin6_family,
         sockaddr6.sin6_port,
         sockaddr6.sin6_flowinfo,
         sockaddr6.sin6_addr.s6_addr,
         sockaddr6.sin6_scope_id);

  struct sockaddr_storage ss;
  bzero(&ss, sizeof(ss));
  ss.ss_family = AF_INET6;
  printf("%ld\n", sizeof(ss));
  printf("(%u %u)\n", ss.ss_len, ss.ss_family);
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
  if (sockfd < 0)
    err_sys("socket error");

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  // servaddr.sin_port = htons(13);
  // Exercise 1.5
  servaddr.sin_port = htons(9999);
  if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
    err_quit("inet_pton error for %s", argv[1]);

  if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) < 0)
    err_sys("connect error");

  struct sockaddr_in si;
  socklen_t nsi = sizeof(si);
  if (getsockname(sockfd, (SA*)&si, &nsi) < 0)
    err_sys("getsockname failed");

  printf("cli: from %hu\n", ntohs(si.sin_port));
  printf("cli: to %s:%hu\n", inet_ntoa(servaddr.sin_addr), ntohs(servaddr.sin_port));

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
  // inet_pton(AF_INET, "192.168.1.103", &servaddr.sin_addr);
  servaddr.sin_port = htons(13);
  // Exercise 1.5
  servaddr.sin_port = htons(9999);
  Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));
  Listen(listenfd, LISTENQ);

  char buff[MAXLINE];
  for (;;) {
    struct sockaddr_in sockaddr;
    socklen_t len = sizeof(sockaddr);
    int connfd = Accept(listenfd, (SA*)&sockaddr, &len);
    printf("srv: %s:%hu\n", inet_ntoa(sockaddr.sin_addr), ntohs(sockaddr.sin_port));

    time_t ticks = time(NULL);
    snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
    // Write(connfd, buff, strlen(buff));
    // Exercise 1.5
    int buff_len = strlen(buff);
    int i;
    for (i = 0; i < buff_len; i++)
      Write(connfd, &buff[i], 1);

    struct sockaddr_in si;
    socklen_t nsi = sizeof(si);
    if (getsockname(listenfd, (SA*)&si, &nsi) == -1)
      err_sys("getsockname failed");
    printf("srv: %s:%hu\n", inet_ntoa(si.sin_addr), ntohs(si.sin_port));

    sleep(2);
    Close(connfd);
  }
  return 0;
}

static int byteorder(int argc, char** argv)
{
  endian_t hs;
  hs.s = 0x0102;
  printf("%s: %s\n", CPU_VENDOR_OS, system_endian());

  endian_t ns;
  ns.s = htons(hs.s);
  printf("host byteorder: %s\n", endian_show(&hs));
  printf("network byteorder: %s\n", endian_show(&ns));

  return 0;
}

static int bytemanipulation(int argc, char** argv)
{
  // memcmp regard every byte as unsigned char
  char a[] = {-5};
  char b[] = {0};
  printf("memcmp = %d\n", memcmp(a, b, sizeof(a)));
  printf("strncmp = %d\n", strncmp(a, b, sizeof(a)));
  printf("bcmp = %d\n", bcmp(a, b, sizeof(a)));
  return 0;
}

static int inet_conv(int argc, char** argv)
{
  int ret = 0;

  const char* addr = "10.192.28.22";
  struct in_addr ia;
  if ((ret = inet_aton(addr, &ia)) != 1) {
    DLIB_ERR("%d: inet_aton failed: cp=%s\n", ret, addr);
    goto err_0;
  }
  printf("ia=%s\n", inet_ntoa(ia));

  // inet_addr can't handle broadcast
  // const char* bc = "255.255.255.255";
  // if ((ret = inet_addr(bc)) == INADDR_NONE) {
  //   DLIB_ERR("%d: inet_addr failed: cp=%s\n", ret, bc);
  //   goto err_0;
  // }
  
  const char* bc = "255.255.255.254";
  if ((ret = inet_addr(bc)) == INADDR_NONE) {
    DLIB_ERR("%d: inet_addr failed: cp=%s\n", ret, bc);
    goto err_0;
  }
  ia.s_addr = ret;
  printf("ia=%s\n", inet_ntoa(ia));
  printf("%s\n", endian_show((endian_t*)&ia));

  if ((ret = inet_pton(AF_INET, addr, &ia)) != 1) {
    DLIB_ERR("%d: inet_pton failed: cp=%s,errmsg=%s", ret, addr, dlib_syserr());
    goto err_0;
  }

  char foo[BUFSIZ];
  printf("%d,ia=%s\n", INET_ADDRSTRLEN, inet_ntop(AF_INET, &ia, foo, INET_ADDRSTRLEN));

  const char* addr6 = "ff:ff:ff:ff:ff:ff:ff:f1";
  struct in6_addr i6a;
  if ((ret = inet_pton(AF_INET6, addr6, &i6a)) != 1) {
    DLIB_ERR("%d: inet_pton failed: cp=%s,errmsg=%s", ret, addr6, dlib_syserr());
    goto err_0;
  }
  printf("%d,ia=%s\n", INET6_ADDRSTRLEN, inet_ntop(AF_INET6, &i6a, foo, INET6_ADDRSTRLEN));
  printf("%d\n", (errno==ENOSPC));

  printf("%d\n", inet_pton_loose(AF_INET, "127.0.0.0x1", &ia));
  printf("%s\n", inet_ntop(AF_INET, &ia, foo, INET_ADDRSTRLEN));

  printf("%d\n", inet_pton_loose(AF_INET6, "::ffff:127.0.0.1", &i6a));
  printf("%s\n", inet_ntop(AF_INET6, &i6a, foo, INET6_ADDRSTRLEN));
  return 0;
err_0:
  return -1;
}

static int multireq(int argc, char** argv)
{
  return multiplex(argc, argv, daytimetcpcli);
}

static int tcpserv01(int argc, char** argv)
{
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    DLIB_ERR("socket failed: %s", dlib_syserr());
    return -1;
  }

  struct sockaddr_in serveraddr;
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(SERV_PORT);

  if (bind(sockfd, (SA*)&serveraddr, sizeof(serveraddr)) < 0) {
    DLIB_ERR("bind failed: %s", dlib_syserr());
    return -1;
  }

  if (listen(sockfd, LISTENQ) < 0) {
    DLIB_ERR("listen failed: %s", dlib_syserr());
    return -1;
  }

  Signal(SIGCHLD, sig_chld);

  while (1) {
    struct sockaddr_in clientaddr;
    socklen_t clientaddr_len = sizeof(clientaddr);
    int clifd = accept(sockfd, (SA*)&clientaddr, &clientaddr_len);
    if (clifd < -1) {
      if (errno == EINTR) {
        continue;
      }
      DLIB_ERR("accept failed: %s", dlib_syserr());
      return -1;
    }

    char foo[INET_ADDRSTRLEN];

    socklen_t serveraddr_len = sizeof(serveraddr);
    if (getsockname(sockfd, (SA*)&serveraddr, &serveraddr_len) < 0) {
      DLIB_ERR("getsockname failed: (%s)", dlib_syserr());
      return -1;
    }

    printf("server addr: ip=(%s),port=(%u)\n", 
           inet_ntop(AF_INET, (SA*)&serveraddr, foo, INET_ADDRSTRLEN),
           ntohs(serveraddr.sin_port));

    printf("accept addr: ip=(%s),port=(%hu)\n",
           inet_ntop(AF_INET, (SA*)&clientaddr, foo, INET_ADDRSTRLEN),
           ntohs(clientaddr.sin_port));

    if (getpeername(clifd, (SA*)&serveraddr, &serveraddr_len) < 0) {
      DLIB_ERR("getpeername failed: (%s)", dlib_syserr());
      return -1;
    }

    printf("perr addr: ip=(%s),port=(%hu)\n",
           inet_ntop(AF_INET, (SA*)&clientaddr, foo, INET_ADDRSTRLEN),
           ntohs(clientaddr.sin_port));

    int pid = fork();
    if (pid == -1) {
      DLIB_ERR("fork failed: %s", dlib_syserr());
      return -1;
    }
    else if (pid == 0) {
      close(sockfd);
      sleep(2);
      str_echo(clifd);
      close(clifd);
      return 0;
    }
    else {
      close(clifd);
    }
  }
  return 0;
}

static int tcpcli01(int argc, char** argv)
{
  if (argc != 3)
    return -2;

  const char* server_addr_str = argv[1];
  int need_redirect = argv[2][0]-'0';

  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  if (inet_pton(AF_INET, server_addr_str, &server_addr.sin_addr) != 1) {
    DLIB_ERR("inet_pton failed: (%s)", dlib_syserr());
    return -1;
  }
  server_addr.sin_port = htons(SERV_PORT);

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (connect(sockfd, (SA*)&server_addr, sizeof(server_addr)) < 0) {
    DLIB_ERR("connect failed: (%s)", dlib_syserr());
    return -1;
  }

  if (need_redirect)
    freopen("in", "r", stdin);

  str_cli(stdin, sockfd);
  close(sockfd);
  return 0;
}

static int tcpcli01test(int argc, char** argv)
{
  return multiplex(argc, argv, tcpcli01);
}

int main(int argc, char** argv)
{
  const dlib_cmd_t cmds[] = {
    DLIB_CMD_DEFINE(basic, ""),
    DLIB_CMD_DEFINE(daytimetcpcli, "<ip-address>"),
    DLIB_CMD_DEFINE(daytimetcpcliv6, "<ip-address>"),
    DLIB_CMD_DEFINE(daytimetcpsrv, ""),
    DLIB_CMD_DEFINE(byteorder, ""),
    DLIB_CMD_DEFINE(bytemanipulation, ""),
    DLIB_CMD_DEFINE(inet_conv, ""),
    DLIB_CMD_DEFINE(multireq, "<times> <ip-address>"),
    DLIB_CMD_DEFINE(tcpserv01, ""),
    DLIB_CMD_DEFINE(tcpcli01, "<ip-address>"),
    DLIB_CMD_DEFINE(tcpcli01test, "<times> <ip-address>"),
    DLIB_CMD_NULL
  };
  return dlib_subcmd(argc, argv, cmds);
}
