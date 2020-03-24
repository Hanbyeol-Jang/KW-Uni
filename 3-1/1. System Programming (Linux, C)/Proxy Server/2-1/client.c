///////////////////////////////////////////////////////////////////
// File Name    : client.c                                       //
// Date         : 2018/04/27                                     //
// Os           : Ubuntun 16.04.3 LTS 64bits                     //
// Author       : Jang Han Byeol                                 //
// Student ID   : 2012722028                                     //
// --------------------------------------------------------------//
// Title : System Programming Assignment #2-1 (proxy server)     //
// Description :                                                 //
// 1. connect to server                                          //
// 2. input url                                                  //
// 3. print MISS or HIT                                          //
// 4. disconnect from server                                     //
///////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>     // socket()
#include <netinet/in.h>     // inet_addr()
#include <arpa/inet.h>

#define BUFFSIZE 1024       // BUFFSIZE == 1024
#define PORTNO   40000      // PORTNO   == 40000

int main(void)
{
    int socket_fd, len;
    struct sockaddr_in server_addr;
    char haddr[] = "127.0.0.1";
    char buf[BUFFSIZE]={0, };
    
    if((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
        printf("can't create socket. \n");      // ERROR: when can't make it,
        return -1;
    }

    bzero(buf, sizeof(buf));                            // initialization buf
    bzero((char*)&server_addr, sizeof(server_addr));    // and server address
    server_addr.sin_family = AF_INET;                   // setting
    server_addr.sin_addr.s_addr = inet_addr(haddr);
    server_addr.sin_port = htons(PORTNO);

    if(connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("can't connect. \n");        // ERROR: when server NOT exist,
        return -1;
    }

    write(socket_fd, haddr, sizeof(haddr));         // for using 127.0.0.1 on server
    write(STDOUT_FILENO, "input url > ", 13);

    while((len = read(STDIN_FILENO, buf, sizeof(buf))) > 0)     // if inputed
    {
        if(write(socket_fd, buf, sizeof(buf)) > 0)      // if success
        { 
            if((len = read(socket_fd, buf, sizeof(buf))) > 0)
            {  
                if(strncmp(buf,"bye",3) == 0)           // if command "bye"
                {
                    close(socket_fd);               // terminate that process
                    return 0;
                }
                write(STDOUT_FILENO, buf, len);     // print MISS or HIT on client
                write(STDOUT_FILENO, "\n", 1);
                bzero(buf, sizeof(buf));
            }
        }
        write(STDOUT_FILENO, "input url > ", 13);
    }   // the end of while
}
