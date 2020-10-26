
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


// int demo2(){
    
//     const char query[] ="ABCDEFGHIJK1241234QWERQW\n";

//     struct sockaddr_in sin;
//     struct hostent *h;
//     const char *cp;
//     int fd;
//     ssize_t n_written, remaining;
//     char buf[802400];

//     /* Allocate a new socket */
//     fd = socket(AF_INET, SOCK_STREAM, 0);
//     if (fd < 0) {
//         perror("socket");
//         return 1;
//     }

//     /* Connect to the remote host. */
//     sin.sin_family = AF_INET;
//     sin.sin_port = htons(40713);
//     sin.sin_addr.s_addr = inet_addr("127.0.0.1");
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
//     int loop = 1;
//     while (loop) {
//         printf("while\n");
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
//         fwrite(buf, 1, result, stdout);
//         int i;
//         for(i = 0; i < result; ++i){
//             // printf("=========%d\n",i);
//             if(buf[i] == '\n'){
//                 loop = 0;
//             }
//         }

//     }
//     printf("read count:%d\n", count);
//     close(fd);
//     return 0;
// }


// int main(int argc, char const *argv[])
// {
//     demo2();
//     return 0;
// }
