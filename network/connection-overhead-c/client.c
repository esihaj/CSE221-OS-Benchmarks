/*
 * https://www.cs.cmu.edu/afs/cs/academic/class/15213-f00/www/class24code/echoclient.c
 * echoclient.c - A simple connection-based client
 * usage: echoclient <host> <port>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>

#define BUFSIZE 1024
const int MAX_MEASUREMENTS = 256;

/*
 * error - wrapper for perror
 */
void error(char *msg)
{
  perror(msg);
  exit(0);
}

int main(int argc, char **argv)
{
  int portno, n;
  struct sockaddr_in serveraddr;
  struct hostent *server;
  char *hostname;
  char buf[BUFSIZE];
  struct timespec start, end;
  double SETUP_MEASUREMENTS[MAX_MEASUREMENTS];
  double TEARDOWN_MEASUREMENTS[MAX_MEASUREMENTS];

  /* check command line arguments */
  if (argc != 3)
  {
    fprintf(stderr, "usage: %s <hostname> <port>\n", argv[0]);
    exit(0);
  }
  hostname = argv[1];
  portno = atoi(argv[2]);

  /* gethostbyname: get the server's DNS entry */
  server = gethostbyname(hostname);
  if (server == NULL)
  {
    fprintf(stderr, "ERROR, no such host as %s\n", hostname);
    exit(0);
  }

  /* build the server's Internet address */
  bzero((char *)&serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  bcopy((char *)server->h_addr,
        (char *)&serveraddr.sin_addr.s_addr, server->h_length);
  serveraddr.sin_port = htons(portno);

  clockid_t clock_source = CLOCK_REALTIME;
  // Structure to hold the start and end times
  // Start measuring time

  for (int i = 0; i < MAX_MEASUREMENTS; i++)
  {
    /* socket: create the socket */
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
      error("ERROR opening socket");
    clock_gettime(clock_source, &start);
    /* connect: create a connection with the server */
    if (connect(sockfd, &serveraddr, sizeof(serveraddr)) < 0)
      error("ERROR connecting");
    clock_gettime(clock_source, &end);
    // Calculate the elapsed time in microseconds
    SETUP_MEASUREMENTS[i] = (end.tv_nsec - start.tv_nsec) / 1000.0;

    clock_gettime(clock_source, &start);
    close(sockfd);
    clock_gettime(clock_source, &end);
    TEARDOWN_MEASUREMENTS[i] = (end.tv_nsec - start.tv_nsec) / 1000.0;
  }
  printf("times are in microseconds:\n");
  printf("setup:\n");
  for (int i = 0; i < MAX_MEASUREMENTS; i++)
  {
    printf("%.0f, ", SETUP_MEASUREMENTS[i]);
  }
  printf("\ntear down:\n");
  for (int i = 0; i < MAX_MEASUREMENTS; i++)
  {
    printf("%.0f, ", TEARDOWN_MEASUREMENTS[i]);
  }
  printf("\n");

  return 0;
}