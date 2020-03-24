///////////////////////////////////////////////////////////////////
// File Name    : server.c                                       //
// Date         : 2018/04/27                                     //
// Os           : Ubuntun 16.04.3 LTS 64bits                     //
// Author       : Jang Han Byeol                                 //
// Student ID   : 2012722028                                     //
// --------------------------------------------------------------//
// Title : System Programming Assignment #2-1 (proxy server)     //
// Description :                                                 //
// 1. Multiple process                                           //
// 2. fork, exit                                                 //
// 3. waitpid, count sub process                                 //
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

#define BUFFSIZE 1024
#define PORTNO   40000  

static void handler(){
    pid_t pid;
    int status;
    while((pid = waitpid(-1, &status, WNOHANG)) > 0);
}

char* sha1_hash(char* input_url, char* hashed_url);     // function declaration
char* getHomeDir(char* home);

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
///////////////////////////////////////////////////////////////////
    char input[256]={0, };        // variable declaration
    char hashed[128]={0, };
    char temp_dir[128]={0, };      // to use name of dir
    char temp_file[128]={0, };     // name of file
    char home[128]={0, };          // to use to home path
    char log_path[128]={0, };      // logfile path
    char ca_path[128]={0, };       // cache path

    FILE* fp, *log_file;               // to use file open & close
    DIR* pDir;
    struct dirent* pFile;
    pid_t PID, PPID;
    int status;
    
    time_t now;                     // time
    struct tm* ltp;
    int h_count = 0, m_count = 0;       // count Hit, Miss
    int p_count = 0;                    // count process
    int t_start = 0, t_end = 0;         // for run time
    int flag = 0;                    // set flag
    
    struct sockaddr_in server_addr, client_addr;        // to use variable
    int socket_fd = 0, client_fd = 0;                   // about socket
    int len = 0, len_out = 0;
    int state = 0;
    char buf[BUFFSIZE] = {0, };
    char temp_buf[32] = {0, };
    pid_t pid;
    int i = 0;
///////////////////////////////////////////////////////////////////
    umask(000);                     // to change the permission

    strcpy(home, getHomeDir(home));     // get home dir. path
    strcpy(log_path, home);
    strcat(log_path, "/logfile");         // logfile dir. path
    mkdir(log_path, 0777);              // make logfile dir.
    chdir(log_path);
    log_file = fopen("logfile.txt", "a");       // make logfile.txt
///////////////////////////////////////////////////////////////////
    if((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
        printf("Server: Can't open stream socket.\n");      // ERROR: when can't open socket
        return 0;
    }

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
    signal(SIGCHLD,(void *)handler);
///////////////////////////////////////////////////////////////////
    while(1)
    {
        bzero((char*)&client_addr, sizeof(client_addr));        // initialization
        len = sizeof(client_addr);
        client_fd = accept(socket_fd, (struct sockaddr*)&client_addr, &len);    //for accept client
        
        if(client_fd < 0){
            printf("Server : accept failed.  %d\n", getpid());      // ERROR: server can't accept client
            close(socket_fd);
            return 0;
        }

        read(client_fd, buf, sizeof(buf));     // haddr
        strcpy(temp_buf, buf);
        printf("[%s : %d] client was connected. \n", temp_buf, client_addr.sin_port);
    ///////////////////////////////////////////////////////////////////
        pid = fork();       // create new process
        if(pid == -1){
            close(client_fd);close(socket_fd);  // ERROR: about creating process
            continue;
        }
    ///////////////////////////////////////////////////////////////////
        else if(pid == 0)        // if PID = 0, Child process
        {
            flag = 0;
            time(&now);                     // present time
            ltp = localtime(&now);
            t_start = time(NULL);

            while((len_out = read(client_fd, buf, sizeof(buf))) > 0)
            {
            ///////////////////////////////////////////////////////////////////
                i = 0;
                while(1){
                    if(buf[i] == '\n'){     // to change \n(the end of buf)
                        buf[i] = '\0';      // to  \0(NULL)
                        break;
                    }
                    i++;
                }
            ///////////////////////////////////////////////////////////////////
                if(strncmp(buf,"bye",3) == 0)       // when command "bye"
                {
                    t_end = time(NULL);             // stop measuring time
                    write(client_fd, buf, sizeof(buf));     // write on client
                    fprintf(log_file, "[Terminated] ServerPID: %d | run time: %d sec. #request hit: %d, miss: %d\n",
                            getpid(), t_end - t_start, h_count, m_count);
                    break;
                }
            ///////////////////////////////////////////////////////////////////
                sha1_hash(buf, hashed);           // function call, change URL to hashed URL

                strncpy(temp_dir, hashed, 3);       // 3 letters in front of hashed URL would be the name of dir.
                strcpy(temp_file, hashed+3);        // the rest would be the name of file
                
                strcpy(ca_path, home);           // cache path
                strcat(ca_path, "/cache");  
                mkdir(ca_path, 0777);            // make cache dir.
                chdir(ca_path);                  // change current working dir. to cache dir.
            ///////////////////////////////////////////////////////////////////
                pDir = opendir(temp_dir);

                if(pDir == NULL)     // MISS : if same dir. doesn't exist
                {
                    mkdir(temp_dir, 0777);      // make URL dir.
                    strcat(ca_path, "/");
                    strcat(ca_path, temp_dir);       // inputed URL dir.
                    chdir(ca_path);                  // cd URL dir.
                    fp = fopen(temp_file,"a");       // make URL file
                    chdir(log_path);
                    
                    fprintf(log_file, "[Miss] ServerPID : %d | %s-[%d/%d/%d, %02d:%02d:%02d]\n",
                            getpid(), buf, ltp->tm_year+1900, ltp->tm_mon+1, ltp->tm_mday,
                            ltp->tm_hour, ltp->tm_min, ltp->tm_sec);
                    m_count++;                  // count Miss
                    bzero(buf, sizeof(buf));
                    write(client_fd, "MISS", 5);
                    continue;
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
                            flag++; 
                            break;
                        }
                        pFile = readdir(pDir);
                    }
                    ///////////////////////////////////////////////////////////////////
                    if(flag == 0)       // MISS : same dir. different file
                    {
                        fp = fopen(temp_file,"a");       // make URL file
                        chdir(log_path);
                        
                        fprintf(log_file, "[Miss] ServerPID : %d | %s-[%d/%d/%d, %02d:%02d:%02d]\n",
                                getpid(), buf, ltp->tm_year+1900, ltp->tm_mon+1, ltp->tm_mday,
                                ltp->tm_hour, ltp->tm_min, ltp->tm_sec);
                        m_count++;                  // count Miss
                        bzero(buf, sizeof(buf));
                        write(client_fd, "MISS", 5);
                        continue;
                    }
                    ///////////////////////////////////////////////////////////////////
                    else                // HIT : same dir. different file
                    {
                        chdir(log_path);
                        
                        fprintf(log_file, "[Hit] ServerPID : %d | %s/%s-[%d/%d/%d, %02d:%02d:%02d]\n",
                                getpid(), temp_dir, temp_file, ltp->tm_year+1900, ltp->tm_mon+1, ltp->tm_mday,
                                ltp->tm_hour, ltp->tm_min, ltp->tm_sec);
                        fprintf(log_file, "[Hit]%s\n", buf);
                        h_count++;                  // count Hit
                        bzero(buf, sizeof(buf));
                        write(client_fd, "HIT", 4);
                        continue;
                    }
                ///////////////////////////////////////////////////////////////////
                } // the end of if same dir
            }
            printf("[%s : %d] client was disconnectd. \n",
                     temp_buf, client_addr.sin_port);   
            close(client_fd);
            fclose(fp);
            fclose(log_file);
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
