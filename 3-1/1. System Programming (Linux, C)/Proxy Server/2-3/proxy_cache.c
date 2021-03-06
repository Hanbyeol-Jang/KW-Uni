///////////////////////////////////////////////////////////////////
// File Name    : proxy_cache.c                                  //
// Date         : 2018/05/18                                     //
// Os           : Ubuntun 16.04.3 LTS 64bits                     //
// Author       : Jang Han Byeol                                 //
// Student ID   : 2012722028                                     //
// --------------------------------------------------------------//
// Title : System Programming Assignment #2-3 (proxy server)     //
// Description :                                                 //
// 1. read cache file, if not exist                              //
// 2. communication with web server                              //
// 3. if exist, read the file and write on web browser           //
///////////////////////////////////////////////////////////////////

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>          // opendir(), readdir(), closedir()
#include <stdio.h>           // sprintf()
#include <string.h>          // strcpy()
#include <openssl/sha.h>     // SHA1()
#include <unistd.h>
#include <pwd.h>
#include <time.h>            // time()
#include <unistd.h>          // fork()
#include <sys/wait.h>        // wait()
#include <stdlib.h>          // exit()
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>          // open()

#define BUFFSIZE 1024
#define PORTNO   38077
#define h_addr h_addr_list[0]

char* sha1_hash(char* input_url, char* hashed_url);     // function declaration
char* getHomeDir(char* home);
char* getIPAddr(char* addr);
char* comweb(char* IPaddr, char* request, char* response);
static void handler();
void sig_int(int signo);
void my_alarm(int signo);
void server_term(void);
int client_fd = 0;      // global variable
int t_start = 0;        // for run time
int t_end = 0;         
int p_count = 0;        // count process
int child = 0;          // child flag

///////////////////////////////////////////////////////////////////
// main                                                          //
// ============================================================= //
// Input: input : Input URL                                      //
// Output: create cache dir, logfile dir, logfile.txt            //
//                                                               //
// Purpose: create cache, Hash, make dir, file                   //
//          measure tiem, file store, distinguish Miss & Hit     //
///////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
//// Variable Declaration //////////////////////////////////////////
    char input[256]={0, };
    char hashed[128]={0, };
    char temp_dir[128]={0, };      // to use name of dir
    char temp_file[128]={0, };     // name of file
    char home[128]={0, };          // to use to home path
    char log_path[128]={0, };      // logfile path
    char ca_path[128]={0, };       // cache path

    FILE* fp, *log_file;           // to use file open & close
    DIR* pDir;
    struct dirent* pFile;
    pid_t PID, PPID;
    int status;
    
    time_t now;                     // time
    struct tm* ltp;
    int flag = 0;                    // set flag
    
    struct sockaddr_in server_addr, client_addr;        // to use variable
    int socket_fd = 0;
    int len = 0, len_out = 0;
    int fd;                         // file descriptor
    int i = 0;
    pid_t pid;
//// Setting Path ////////////////////////////////////////////////
    umask(000);                     // to change the permission

    strcpy(home, getHomeDir(home));     // get home dir. path
    strcpy(log_path, home);
    strcat(log_path, "/logfile");         // logfile dir. path
    mkdir(log_path, 0777);              // make logfile dir.
    chdir(log_path);
    log_file = fopen("logfile.txt", "a");       // make logfile.txt
//// Socket ///////////////////////////////////////////////////////
    int opt =1;
    if((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
        printf("Server : Can't open stream socket.\n");      // ERROR: when can't open socket
        return 0;
    }
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    bzero((char*)&server_addr, sizeof(server_addr));        // initialization
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORTNO);

    if(bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        printf("Server : Can't bind local address. \n");
        close(socket_fd);   // ERROR: when Can't bind, please wait few minutes and try again
        return 0;
    }

    listen(socket_fd, 5);       // wait for connecting from client
///////////////////////////////////////////////////////////////////
    signal(SIGCHLD, (void *)handler);           // signal
    signal(SIGALRM, my_alarm);
    if(signal(SIGINT, sig_int) == SIG_ERR)
        fprintf(stderr, "signal error");
///////////////////////////////////////////////////////////////////
    while(1)
    {
        struct in_addr inet_client_address;         // Variable Declaration
        
        char buf[BUFFSIZE] = {0, };
        char request[BUFFSIZE] = {0, };
        char response[BUFFSIZE*BUFFSIZE*4] = {0, };

        char response_header[BUFFSIZE] = {0, };
        char response_message[BUFFSIZE] = {0, };
        char tmp[BUFFSIZE] = {0, };
        char method[20] = {0, };
        char url[BUFFSIZE] = {0, };
        char tok[BUFFSIZE] = {0, };
        char host[BUFFSIZE] = {0, };
        char IPaddress[BUFFSIZE] ={0, };
        char temp[BUFFSIZE] = {0, };
    
        len = sizeof(client_addr);
        client_fd = accept(socket_fd, (struct sockaddr*)&client_addr, &len);    //for accept client
        
        if(client_fd < 0){
            printf("Server : accept failed.\n");        // ERROR
            return 0;
        }

        inet_client_address.s_addr = client_addr.sin_addr.s_addr;   // web browser connection
       
        printf("[%s : %d] client was connected. \n",
                 inet_ntoa(inet_client_address),              // convert IP addr to dot
                 client_addr.sin_port);

        read(client_fd, buf, sizeof(buf));     // read the information of web browser
        strcpy(tmp, buf);

        if(buf[0]=='\0')            // when buf is NULL
            continue;
        
        puts("============================================================");       // on terminal
        printf("Request from [%s : %d]\n", inet_ntoa(inet_client_address), client_addr.sin_port);
        puts(buf);
        puts("============================================================\n");
        strcpy(request, buf);

        strcpy(tok, strtok(tmp, " "));         // to get 'GET'
        strcpy(method, tok);

        if(strcmp(method, "GET") == 0){
            strcpy(tok, strtok(NULL, " "));
            strcpy(url, tok);            // for using only url
        }

        if(url[0]=='\0')            // when url is NULL
            continue;

        strcpy(url, url+7);         // to detach 'http://'
        i = 0;
        while(1){
            if(url[i] == '\0')      // to detach '/' at the end
                break;
            i++;
        }
 
        if(url[i-1] == '/')         // only the end is '/'
            url[i-1] = '\0';

        printf("url:===%s===\n", url);
        strcpy(temp, url);
        strcpy(host, strtok(temp, "/"));        // to get host
        printf("host:===%s===\n", host);
        strcpy(IPaddress, getIPAddr(host));    // convert host to IP address
        printf("IPaddr:===%s===\n", IPaddress);
    ///////////////////////////////////////////////////////////////////
        pid = fork();       // create new process
        if(pid == -1){
            close(client_fd);close(socket_fd);  // ERROR: about creating process
            continue;
        }
    ///////////////////////////////////////////////////////////////////
        else if(pid == 0)        // if PID = 0, Child process
        {   
            child = 1;                      // child flag
            flag = 0;
            time(&now);                     // present time
            ltp = localtime(&now);
            t_start = time(NULL);           // start time
        ///////////////////////////////////////////////////////////////////
            sha1_hash(url, hashed);           // function call, change URL to hashed URL

            printf("hash url:===%s===\n", url);
            printf("hashed:===%s===\n\n", hashed);
            strncpy(temp_dir, hashed, 3);       // 3 letters in front of hashed URL would be the name of dir.
            strcpy(temp_file, hashed+3);        // the rest would be the name of file
                
            strcpy(ca_path, home);           // cache path
            strcat(ca_path, "/cache");  
            mkdir(ca_path, 0777);            // make cache dir.
            chdir(ca_path);                  // change current working dir. to cache dir.
            
            int sl = 0;             // string length
            char st[4] = {0, };     // string temp
            char stemp = '\0';      // string temp

            sl = strlen(url);               // to detach url that don't input  
            st[0] = url[sl-2];
            st[1] = url[sl-1];
        ///////////////////////////////////////////////////////////////////
            pDir = opendir(temp_dir);
            if(pDir == NULL)     // MISS : if same dir. doesn't exist
            {  
                strcpy(response, (comweb(IPaddress, request, response)));
                //==============================================================
                mkdir(temp_dir, 0777);      // make URL dir.
                strcat(ca_path, "/");
                strcat(ca_path, temp_dir);       // inputed URL dir.
                chdir(ca_path);                  // cd URL dir.

                fp = fopen(temp_file, "a");       // make URL file
                fprintf(fp, "%s", response);        // write response on that
                fclose(fp);

                if(strcmp(st, "69") !=0 &&strcmp(st, "53") !=0 &&strcmp(st, "64") !=0 &&strcmp(st, "58") !=0 &&strcmp(st, "32") !=0 &&strcmp(st, "24") !=0 &&strcmp(st, "=1") !=0 &&strcmp(st, "40") !=0 &&strcmp(st, "19") !=0 &&strcmp(st, "35") !=0 &&strcmp(st, "pg") !=0 &&strcmp(st, "11") !=0 &&strcmp(st, "co") !=0 &&strcmp(st, "ss") != 0 &&strcmp(st, "js") != 0 &&strcmp(st, "xt") != 0 &&strcmp(st, "ng") != 0)
                {
                    chdir(log_path);        // change directory
                
                    fprintf(log_file, "[Miss]%s-[%d/%d/%d, %02d:%02d:%02d]\n",
                            url, ltp->tm_year+1900, ltp->tm_mon+1, ltp->tm_mday,
                            ltp->tm_hour, ltp->tm_min, ltp->tm_sec);
                    fclose(log_file);
                }
            }
            ///////////////////////////////////////////////////////////////////
            else     // if same dir. exist
            {
                strcat(ca_path, "/");
                strcat(ca_path, temp_dir);       // inputed URL dir.
                chdir(ca_path);                  // cd URL dir.

                pFile = readdir(pDir);           // to distinguish 
                while(pFile)                     // find same file till the end
                {
                    if(!strcmp(pFile->d_name, temp_file))     // if same file
                    {
                        flag++;                 // increase flag
                        break;
                    }
                    pFile = readdir(pDir);
                }
                ///////////////////////////////////////////////////////////////////
                if(flag == 0)       // MISS : same dir. but different file
                {
                    strcpy(response, (comweb(IPaddress, request, response)));
                    //==============================================================
                    fp = fopen(temp_file,"a");       // make URL file
                    fprintf(fp, "%s", response);
                    fclose(fp);

                    if(strcmp(st, "69") !=0 &&strcmp(st, "53") !=0 &&strcmp(st, "64") !=0 &&strcmp(st, "58") !=0 &&strcmp(st, "32") !=0 &&strcmp(st, "24") !=0 &&strcmp(st, "=1") !=0 &&strcmp(st, "40") !=0 &&strcmp(st, "19") !=0 &&strcmp(st, "35") !=0 &&strcmp(st, "pg") !=0 &&strcmp(st, "11") !=0 &&strcmp(st, "co") !=0 &&strcmp(st, "ss") != 0 &&strcmp(st, "js") != 0 &&strcmp(st, "xt") != 0 &&strcmp(st, "ng") != 0)
                    {
                        chdir(log_path);
                
                        fprintf(log_file, "[Miss]%s-[%d/%d/%d, %02d:%02d:%02d]\n",
                                url, ltp->tm_year+1900, ltp->tm_mon+1, ltp->tm_mday,
                                ltp->tm_hour, ltp->tm_min, ltp->tm_sec);
                        fclose(log_file);
                    }
                }
                ///////////////////////////////////////////////////////////////////
                else                // HIT : same dir. different file
                {
                    fd = open(temp_file, O_RDONLY);             // open cache file
                    read(fd, response, sizeof(response));         // read it
                    write(client_fd, response, strlen(response));   // write it on web browser
                    //==============================================================
                    if(strcmp(st, "69") !=0 &&strcmp(st, "53") !=0 &&strcmp(st, "64") !=0 &&strcmp(st, "58") !=0 &&strcmp(st, "32") !=0 &&strcmp(st, "24") !=0 &&strcmp(st, "=1") !=0 &&strcmp(st, "40") !=0 &&strcmp(st, "19") !=0 &&strcmp(st, "35") !=0 &&strcmp(st, "pg") !=0 &&strcmp(st, "11") !=0 &&strcmp(st, "co") !=0 &&strcmp(st, "ss") != 0 &&strcmp(st, "js") != 0 &&strcmp(st, "xt") != 0 &&strcmp(st, "ng") != 0)
                    {
                        chdir(log_path);
                        fprintf(log_file, "[Hit]%s/%s-[%d/%d/%d, %02d:%02d:%02d]\n",
                                temp_dir, temp_file, ltp->tm_year+1900, ltp->tm_mon+1, ltp->tm_mday,
                                ltp->tm_hour, ltp->tm_min, ltp->tm_sec);
                        fprintf(log_file, "[Hit]%s\n", url);
                        fclose(log_file);
                    }
                }
                ///////////////////////////////////////////////////////////////////
            } // the end of if same dir
            printf("[%s : %d] client was disconnectd. \n",
                     inet_ntoa(inet_client_address), client_addr.sin_port);   // address convert
            close(client_fd);
            fclose(fp);
            exit(0);      // when bye Command, would be turned off
        } // the end of PID = 0
    ///////////////////////////////////////////////////////////////////
        else        // PID > 0, Parent process
        {
            PPID = waitpid(PID, &status, 0);      // wait for exiting child process
            p_count++;
        }
        close(client_fd);
    }
/////////////////////////////////////////////////////////////////// 
    close(socket_fd);
    return 0;
}

///////////////////////////////////////////////////////////////////
// sha1_hash                                                     //
// ============================================================= //
// Input: input URL                                              //
// Output: hashed url                                            //
//                                                               //
// Purpose: to change inputed URL to hashed URL                  //
///////////////////////////////////////////////////////////////////

char* sha1_hash(char* input_url, char* hashed_url)
{
    unsigned char hashed_160bits[20];
    char hashed_hex[41];
    int i;
    SHA1(input_url, strlen(input_url), hashed_160bits);

    for(i=0;i<sizeof(hashed_160bits);i++)
        sprintf(hashed_hex + i*2, "%02x", hashed_160bits[i]);

    strcpy(hashed_url, hashed_hex);

    return hashed_url;
}

///////////////////////////////////////////////////////////////////
// getHomeDir                                                    //
// ============================================================= //
// Input: home that have nothing                                 //
// Output: home that have the path of Home dir.                  //
//                                                               //
// Purpose: to get the path of Home dir.                         //
///////////////////////////////////////////////////////////////////

char* getHomeDir(char* home)
{
    struct passwd* usr_info = getpwuid(getuid());
    strcpy(home, usr_info->pw_dir);
    return home;
}

///////////////////////////////////////////////////////////////////
// getIPAddr                                                     //
// ============================================================= //
// Input: addr                                                   //
// Output: haddr                                                 //
//                                                               //
// Purpose: address conversion.                                  //
///////////////////////////////////////////////////////////////////

char* getIPAddr(char* addr)
{
    struct hostent* hent;
    char* haddr;
    int len = strlen(addr);

    if((hent = (struct hostent*)gethostbyname(addr)) != NULL)
        haddr = inet_ntoa(*((struct in_addr*)hent->h_addr_list[0]));

    return haddr;
}

///////////////////////////////////////////////////////////////////
// comweb                                                        //
// ============================================================= //
// Input: IPaddr                                                 //
// Output: haddr                                                 //
//                                                               //
// Purpose: communication with web server                        //
///////////////////////////////////////////////////////////////////

char* comweb(char* IPaddr, char* request, char* response)
{
    int web_fd = 0, len = 0, len_out = 0;
    struct sockaddr_in server_addr;
    char buf[BUFFSIZE*BUFFSIZE*2] = {0, };
    
    if((web_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0){     // create socket
        printf("can't create socket. \n");
        exit(-1);
    }
    
    bzero(buf, sizeof(buf));                                // initialization
    bzero((char*)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(IPaddr);
    server_addr.sin_port = htons(80);
    
    if(connect(web_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        printf("can't connect. \n");
        exit(-1);                                   // to connect with proxy server
    }       

    write(web_fd, request, strlen(request));        // resquest to web server
    alarm(10);          // alarm setting

    while((len = read(web_fd, buf, sizeof(buf))) > 0)     // read every line
    {
        write(client_fd, buf, len);             // write it on web browser
        
        strcat(response, buf);              // memory corruption
        bzero(buf, sizeof(buf));
        alarm(0);       // clear alarm
    }

    close(web_fd);
    return response;     // have to return response
}

///////////////////////////////////////////////////////////////////
// signal                                                        //
// ============================================================= //
// Input: signo                                                  //
//                                                               //
// Purpose: process about that siganl                            //
///////////////////////////////////////////////////////////////////

static void handler(){
    pid_t pid;
    int status;
    while((pid = waitpid(-1, &status, WNOHANG)) > 0);
}

void sig_int(int signo){
    server_term();          // call function to store logfile
    exit(0);
}

void my_alarm(int signo){
    printf("No Response\n");     // print 'no response'
    exit(0);
}

///////////////////////////////////////////////////////////////////
// server_term                                                   //
// ============================================================= //                                                               //
// Purpose: when process terminate, store message on log file    //
///////////////////////////////////////////////////////////////////

void server_term(void)
{
    t_end = time(NULL);             // time end
    char log_path[128] ={0, };
    FILE* log_file;
        
    strcpy(log_path, getHomeDir(log_path));     // get home dir. path
    strcat(log_path, "/logfile");         // logfile dir. path
    chdir(log_path);
    log_file = fopen("logfile.txt", "a");       // make logfile.txt
    if(child == 1)
    {
        fprintf(log_file, "**SERVER** [Terminated] run time: %d sec. #sub process: %d\n",
            t_end - t_start, p_count);
    }
    fclose(log_file);
    exit(0);
}