///////////////////////////////////////////////////////////////////
// File Name    : proxy_cache.c                                  //
// Date         : 2018/04/05                                     //
// Os           : Ubuntun 16.04.3 LTS 64bits                     //
// Author       : Jang Han Byeol                                 //
// Student ID   : 2012722028                                     //
// --------------------------------------------------------------//
// Title : System Programming Assignment #1-2 (proxy server)     //
// Description :                                                 //
// 1. Measure run time                                           //
// 2. Logfile.txt open, store the format                         //
// 3. Distinguish between Miss and Hit clearly                   //
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
    
    time_t now;                     // time
    struct tm* ltp;
    int h_count = 0, m_count = 0;       // count Hit, Miss
    int t_start = 0, t_end = 0;         // for run time
    int flag = 0;                    // set flag
    
    t_start = time(NULL);           // measure time
    
    umask(000);                     // to change the permission

    strcpy(home, getHomeDir(home));     // get home dir. path
    
    strcpy(log_path, home);
    strcat(log_path, "/logfile");         // logfile dir. path
    mkdir(log_path, 0777);              // make logfile dir.
    chdir(log_path);
    log_file = fopen("logfile.txt", "a");       // make logfile.txt
    
    while(1)
    {
        flag = 0;
        time(&now);                     // present time
        ltp = localtime(&now);
       
        printf("input URL> ");      // input URL
        scanf("%s", input);
        
        if(strcmp(input, "bye") == 0)       // when bye,
        {
            t_end = time(NULL);             // stop measuring time
            fprintf(log_file, "[Terminated] run time: %d sec. #request hit: %d, miss: %d\n",
                    t_end - t_start, h_count, m_count);
            return 0;      // when bye Command, would be turned off
        }
        sha1_hash(input, hashed);           // function call, change URL to hashed URL

        strncpy(temp_dir, hashed, 3);       // 3 letters in front of hashed URL would be the name of dir.
        strcpy(temp_file, hashed+3);        // the rest would be the name of file

        strcpy(ca_path, home);           // cache path
        strcat(ca_path, "/cache");  
        mkdir(ca_path, 0777);            // make cache dir.
        chdir(ca_path);                  // change current working dir. to cache dir.
        
        pDir = opendir(temp_dir);
        
        if(pDir == NULL)     // MISS : if same dir. doesn't exist
        {
            mkdir(temp_dir, 0777);      // make URL dir.
            strcat(ca_path, "/");
            strcat(ca_path, temp_dir);       // inputed URL dir.
            chdir(ca_path);                  // cd URL dir.
            fp = fopen(temp_file,"a");       // make URL file

            fprintf(log_file, "[Miss]%s-[%d/%d/%d, %02d:%02d:%02d]\n",
                    input, ltp->tm_year+1900, ltp->tm_mon+1, ltp->tm_mday,
                    ltp->tm_hour, ltp->tm_min, ltp->tm_sec);
            m_count++;                  // count Miss
            continue;
        }
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
            
            if(flag == 0)       // MISS : same dir. different file
            {
                fp = fopen(temp_file,"a");       // make URL file

                fprintf(log_file, "[Miss]%s-[%d/%d/%d, %02d:%02d:%02d]\n",
                        input, ltp->tm_year+1900, ltp->tm_mon+1, ltp->tm_mday,
                        ltp->tm_hour, ltp->tm_min, ltp->tm_sec);
                m_count++;                  // count Miss
                continue;
            }
            else                // HIT : same dir. different file
            {
                fprintf(log_file, "[Hit]%s/%s-[%d/%d/%d, %02d:%02d:%02d]\n",
                        temp_dir, temp_file, ltp->tm_year+1900, ltp->tm_mon+1, ltp->tm_mday,
                        ltp->tm_hour, ltp->tm_min, ltp->tm_sec);
                fprintf(log_file, "[Hit]%s\n", input);
                h_count++;                  // count Hit
                continue;
            }
        }
        fclose(fp);
        fclose(log_file);
    }
    /*
    if(argc<2) return 0;

    pDir=opendir(argv[1]);
    if(pDir==NULL)
    {
        printf("Dir read error\n");
        return 0; chdir(home);
    }
    for(pFile=readdir(pDir);pFile;pFile=readdir(pDir))
        printf("%s\n", pFile->d_name);
    closedir(pDir);
    */
    return 1;
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
