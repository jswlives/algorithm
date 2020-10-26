
// /* For sockaddr_in */
// #include <netinet/in.h>
// /* For socket functions */
// #include <sys/socket.h>
// /* For gethostbyname */
// #include <netdb.h>

// #include <unistd.h>
// #include <string.h>
// #include <stdio.h>
// #include <event.h>
// #include "demo1.h"


// void debug(char *msg){
//     printf("[DEBUG]%s\n", msg);
// }

// int demo1(){
    
//     const char query[] =
//         "GET / HTTP/1.0\r\n"
//         "Host: www.hao123.com\r\n"
//         "\r\n";

//     const char hostname[] = "www.hao123.com";
//     struct sockaddr_in sin;
//     struct hostent *h;
//     const char *cp;
//     int fd;
//     ssize_t n_written, remaining;
//     char buf[802400];

//     /* Look up the IP address for the hostname.   Watch out; this isn't
//        threadsafe on most platforms. */
//     h = gethostbyname(hostname);
//     if (!h) {
//         fprintf(stderr, "Couldn't lookup %s: %s", hostname, hstrerror(h_errno));
//         return 1;
//     }
//     if (h->h_addrtype != AF_INET) {
//         fprintf(stderr, "No ipv6 support, sorry.");
//         return 1;
//     }

//     /* Allocate a new socket */
//     fd = socket(AF_INET, SOCK_STREAM, 0);
//     if (fd < 0) {
//         perror("socket");
//         return 1;
//     }

//     /* Connect to the remote host. */
//     sin.sin_family = AF_INET;
//     sin.sin_port = htons(80);
//     sin.sin_addr = *(struct in_addr*)h->h_addr;
//     if (connect(fd, (struct sockaddr*) &sin, sizeof(sin))) {
//         perror("connect");
//         close(fd);
//         return 1;
//     }

//     /* Write the query. */
//     /* XXX Can send succeed partially? */
//     cp = query;
//     remaining = strlen(query);
//     while (remaining) {
//       n_written = send(fd, cp, remaining, 0);
//       if (n_written <= 0) {
//         perror("send");
//         return 1;
//       }
//       remaining -= n_written;
//       cp += n_written;
//     //   printf("11111111111\n");
//     }

//     /* Get an answer back. */
//     int count = 0;
//     while (1) {
//         ssize_t result = recv(fd, buf, sizeof(buf), 0);
//         if (result == 0) {
//             break;
//         } else if (result < 0) {
//             perror("recv");
//             close(fd);
//             return 1;
//         }
//         ++count;
//         printf("receive byte:%d\n", result);
//         // printf("hello");
//         // fwrite(buf, 1, result, stdout);
//     }
//     printf("read count:%d\n", count);
//     close(fd);
//     return 0;
// }

// int demo2()
// {
//     fd_set rd;
//     struct timeval tv;
//     int err;
    

//     FD_ZERO(&rd);
//     FD_SET(0,&rd);
    
//     tv.tv_sec = 5;
//     tv.tv_usec = 0;
//     err = select(1, &rd,NULL,NULL,&tv);
    
//     if(err == 0) //超时
//     {
//         printf("select time out!\n");
//     }
//     else if(err == -1)  //失败
//     {
//         printf("fail to select!\n");
//     }
//     else  //成功
//     {
//         printf("data is available!\n");
//     }

    
//     return 0;
// }

// /////////////////////////
// #include <fcntl.h>
// /* for select */
// #include <sys/select.h>
// #include <assert.h>
// #include <string.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <errno.h>
// #define MAX_LINE 16384

// static char rot13_char(char c)
// {
//     /* We don't want to use isalpha here; setting the locale would change
//      * which characters are considered alphabetical. */
//     if ((c >= 'a' && c <= 'm') || (c >= 'A' && c <= 'M'))
//         return c + 13;
//     else if ((c >= 'n' && c <= 'z') || (c >= 'N' && c <= 'Z'))
//         return c - 13;
//     else
//         return c;
// }

// struct fd_state {
//     char buffer[MAX_LINE];
//     size_t buffer_used;

//     int writing;
//     size_t n_written;
//     size_t write_upto;
// };

// static struct fd_state *
// alloc_fd_state(void)
// {
//     struct fd_state *state = malloc(sizeof(struct fd_state));
//     if (!state)
//         return NULL;
//     state->buffer_used = state->n_written = state->writing =
//         state->write_upto = 0;
//     return state;
// }

// static void
// free_fd_state(struct fd_state *state)
// {
//     free(state);
// }

// static void
// make_nonblocking(int fd)
// {
//     fcntl(fd, F_SETFL, O_NONBLOCK);
// }

// static int
// do_read(int fd, struct fd_state *state)
// {
//     debug("do_read!");
//     char buf[1024];
//     int i;
//     ssize_t result;
//     while (1) {
//         result = recv(fd, buf, sizeof(buf), 0);
//         debug("recv");
//         if (result <= 0)
//             break;

//         for (i=0; i < result; ++i)  {
//             if (state->buffer_used < sizeof(state->buffer))
//                 state->buffer[state->buffer_used++] = rot13_char(buf[i]);
//             if (buf[i] == '\n') {
//                 state->writing = 1;
//                 state->write_upto = state->buffer_used;
//                 debug("read finish, return later");
//             }
//         }
//     }

//     if (result == 0) {
//         debug("client close connect");
//         return 1;
//     } else if (result < 0) {
//         if (errno == EAGAIN){
//             debug("EAGAIN");
//             return 0;
//         }
//         debug("recv error!");
//         return -1;
//     }
//     return 0;
// }

// static int
// do_write(int fd, struct fd_state *state)
// {
//     debug("do_write");
//     while (state->n_written < state->write_upto) {
//         ssize_t result = send(fd, state->buffer + state->n_written,
//                               state->write_upto - state->n_written, 0);
//         if (result < 0) {
//             if (errno == EAGAIN)
//                 return 0;
//             return -1;
//         }
//         assert(result != 0);

//         state->n_written += result;
//     }

//     if (state->n_written == state->buffer_used)
//         state->n_written = state->write_upto = state->buffer_used = 0;

//     state->writing = 0;

//     return 0;
// }

// static void
// run(void)
// {
//     int listener;
//     struct fd_state *state[FD_SETSIZE];
//     struct sockaddr_in sin;
//     int i, maxfd;
//     fd_set readset, writeset, exset;

//     sin.sin_family = AF_INET;
//     sin.sin_addr.s_addr = 0;
//     sin.sin_port = htons(40713);

//     for (i = 0; i < FD_SETSIZE; ++i)
//         state[i] = NULL;

//     listener = socket(AF_INET, SOCK_STREAM, 0);
//     make_nonblocking(listener);


//     if (bind(listener, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
//         perror("bind");
//         return;
//     }

//     if (listen(listener, 16)<0) {
//         perror("listen");
//         return;
//     }

//     FD_ZERO(&readset);
//     FD_ZERO(&writeset);
//     FD_ZERO(&exset);

//     while (1) {
//         debug("======while=====");
//         maxfd = listener;

//         FD_ZERO(&readset);
//         FD_ZERO(&writeset);
//         FD_ZERO(&exset);

//         FD_SET(listener, &readset);

//         for (i=0; i < FD_SETSIZE; ++i) {
//             if (state[i]) {
//                 if (i > maxfd)
//                     maxfd = i;
//                 FD_SET(i, &readset);
//                 if (state[i]->writing) {
//                     FD_SET(i, &writeset);
//                     debug("fd_set writting");
//                 }
//             }
//         }

//         if (select(maxfd+1, &readset, &writeset, &exset, NULL) < 0) {
//             perror("select");
//             return;
//         }

//         if (FD_ISSET(listener, &readset)) {
//             struct sockaddr_storage ss;
//             socklen_t slen = sizeof(ss);
//             int fd = accept(listener, (struct sockaddr*)&ss, &slen);
//             if (fd < 0) {
//                 perror("accept");
//             } else if (fd > FD_SETSIZE) {
//                 close(fd);
//             } else {
//                 make_nonblocking(fd);
//                 state[fd] = alloc_fd_state();
//                 assert(state[fd]);/*XXX*/
//             }
//             debug("accept a connect!");
//         }

//         for (i=0; i < maxfd+1; ++i) {
//             int r = 0;
//             if (i == listener)
//                 continue;

//             if (FD_ISSET(i, &readset)) {
//                 r = do_read(i, state[i]);
//             }
//             if (r == 0 && FD_ISSET(i, &writeset)) {
//                 r = do_write(i, state[i]);
//             }
//             if (r) {
//                 free_fd_state(state[i]);
//                 state[i] = NULL;
//                 close(i);
//             }
//         }
//     }
// }



// int demo3(){
//     run();
// }