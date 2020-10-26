
/* For sockaddr_in */
#include <netinet/in.h>
/* For socket functions */
#include <sys/socket.h>
/* For gethostbyname */
#include <netdb.h>

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <event.h>
#include "demo1.h"


#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int demo112()
{
  char buf[5];
  FILE *myfile =stdin;
  printf("before reading\n");
  printf("read buffer base %p\n", myfile->_IO_read_base);
  printf("read buffer length %d\n", myfile->_IO_read_end - myfile->_IO_read_base);
  printf("write buffer base %p\n", myfile->_IO_write_base);
  printf("write buffer length %d\n", myfile->_IO_write_end - myfile->_IO_write_base);
  printf("buf buffer base %p\n", myfile->_IO_buf_base);
  printf("buf buffer length %d\n", myfile->_IO_buf_end - myfile->_IO_buf_base);
  printf("---------------\n");
  fgets(buf, 5, myfile);
  fputs(buf, myfile);
  printf("---------------\n");
  printf("after reading\n");
  printf("read buffer base %p\n", myfile->_IO_read_base);
  printf("read buffer length %d\n", myfile->_IO_read_end - myfile->_IO_read_base);
  printf("write buffer base %p\n", myfile->_IO_write_base);
  printf("write buffer length %d\n", myfile->_IO_write_end - myfile->_IO_write_base);
  printf("buf buffer base %p\n", myfile->_IO_buf_base);
  printf("buf buffer length %d\n", myfile->_IO_buf_end - myfile->_IO_buf_base);

  return 0;
}

int demo113()
{
    char buf[5];
    char *cur;
    FILE *myfile;
    myfile = fopen("bbb.txt", "r");
    printf("before reading, myfile->_IO_read_ptr: %d\n", myfile->_IO_read_ptr - myfile->_IO_read_base);
    fgets(buf, 5, myfile); //仅仅读4个字符
    cur = myfile->_IO_read_base;

    printf("fgets buff:%s\n", buf);

    // while (cur < myfile->_IO_read_end) //实际上读满了这个缓冲区
    // {
    //     printf("%c",*cur);
    //     cur++;
    // }
    puts(myfile->_IO_read_ptr);
    puts(myfile->_IO_read_base);
    printf("\nafter reading, myfile->_IO_read_ptr: %d\n", myfile->_IO_read_ptr - myfile->_IO_read_base);

    return 0;
}

int demo114()
{
    char buf[10]="abcdefg\n";
    int i;
    FILE *myfile;
    myfile = fopen("aaa.txt", "w+");
    i= 0;
    while (i < 1)
    {
        fwrite(buf, 1, 1, myfile);
        i +=1;
        //注释掉这句则可以写入aaa.txt
        // myfile->_IO_write_ptr = myfile->_IO_write_base;
        printf("%p write buffer base\n", myfile->_IO_write_base);
        printf("%p buf buffer base \n", myfile->_IO_buf_base);
        printf("%p read buffer base \n", myfile->_IO_read_base);
        printf("%p write buffer ptr \n", myfile->_IO_write_ptr);
        printf("\n");
    }
    return 0;
}

int demo115()
{
    char buf[5];
    char buf2[2048];
    char buf3[2048];
    
    


                                            //而非仅仅上面需要的个字符
    // stdin->_IO_read_ptr = stdin->_IO_read_end; //标准I/O会认为缓冲区已空,再次调用read
                                                //注释掉,再看看效果
    printf("-----------0\n");
    fgets(buf, 5, stdin); //第一次输入时,超过5个字符
    printf("-----------0\n");
    puts(buf);
    puts(stdin->_IO_read_ptr);//本句说明整行会被一次全部读入缓冲区,

    printf("-----------1\n");
    fgets(buf2, 2048, stdin);
    printf("-----------1\n");
    puts(buf2);
    puts(stdin->_IO_read_ptr);//本句说明整行会被一次全部读入缓冲区,

    printf("-----------2\n");
    fgets(buf3, 2048, stdin);
    printf("-----------2\n");
    puts(buf3);

    return 0;    
}

char demo6buf[5]={'1','2', '3', '4', '5'}; //最后一个不要是\n,是\n的话,标准I/O会自动flush的
                                                    //这是行缓冲跟全缓冲的重要区别
void writeLog(FILE *ftmp)
{
    fprintf(ftmp, "%p write buffer base\n", stdout->_IO_write_base);
    fprintf(ftmp, "%p buf buffer base \n", stdout->_IO_buf_base);
    fprintf(ftmp, "%p read buffer base \n", stdout->_IO_read_base);
    fprintf(ftmp, "%p write buffer ptr \n", stdout->_IO_write_ptr);
    fprintf(ftmp, "\n");
}

int demo116()
{
    int i;
    FILE *ftmp;
    ftmp = fopen("ccc.txt", "w");
    i= 0;
    while (i < 4)
    {
        fwrite(demo6buf, 1, 5, stdout);
        i++;
        *stdout->_IO_write_ptr++ = '\n';//可以单独把这句打开,看看效果
        getchar();//getchar()会标准I/O将缓冲区输出
        //打开下面的注释,你就会发现屏幕上什么输出也没有
        //stdout->_IO_write_ptr = stdout->_IO_write_base;
        writeLog(ftmp); //这个只是为了查看缓冲区指针的变化  
    }
    return 0;    
}

int demo117()
{
    printf("hello world:% 10.2f xxxx\n", 12.1212);
    printf("hello world:% 10.2f xxxx\n", 123.23);

}

void print_va(int num, ...)
{
    va_list vl;
    va_start(vl, num);
    while(num > 0)
    {
        int var = va_arg(vl, int);
        printf("va:%d\n", var);
        --num;
    }
    va_end(vl);
}

void logss(const char * format, ...)
{
    va_list vl;
    va_start(vl, format);
    vprintf(format, vl);
}

int demo118()
{
    // print_va(8, 1, 2, 3, 4, 5, 6, 7, 8);
    logss("hello world:%d\n", 100);
}