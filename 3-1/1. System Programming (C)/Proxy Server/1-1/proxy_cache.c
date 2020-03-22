///////////////////////////////////////////////////////////////////
// File Name    : proxy_cache.c                                  //
// Date         : 2018/03/29                                     //
// Os           : Ubuntun 16.04.3 LTS 64bits                     //
// Author       : Jang Han Byeol                                 //
// Student ID   : 2012722028                                     //
// --------------------------------------------------------------//
// Title : System Programming Assignment #1-1 (proxy server)     //
// Description :                                                 //
// 1. Input url(web-site)                                        //
// 2. If Input "bye", then turn the program off                  //
// 3. Change inputed URL to Hashed URL by using sha1_hash func.  //
// 4. Create "cache" dir. in Home dir.                           //
// 5. Name of dir. would be 3 letters of hashed_url              // 
///////////////////////////////////////////////////////////////////

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>          // opendir(), readdir(), closedir()
#include <stdio.h>           // sprintf()
#include <string.h>          // strcpy()
#include <openssl/sha.h>     // SHA1()
#include <unistd.h>
#include <pwd.h>

char* sha1_hash(char* input_url, char* hashed_url);     // function declaration
char* getHomeDir(char* home);

///////////////////////////////////////////////////////////////////
// main                                                          //
// ============================================================= //
// Input: input : Input URL                                      //
// Output: create cache dir., hashed URL dir. hashed file        //
//                                                               //
// Purpose: create cache dir., hashed URL dir. hashed file       //
///////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
    char input[128];        // variable declaration
    char hashed[64];
    char temp_dir[64];      // to use name of dir
    char temp_file[64];     // name of file
    char home[64];          // to use to path
    FILE* fp;               // to use file open & close
   
    while(1)
    {
        printf("input URL> ");      // input URL
        scanf("%s", input);

        if(strcmp(input, "bye")==0) break;      // when bye Command, would be turned off
        
        sha1_hash(input, hashed);       // function call, change URL to hashed URL

        strncpy(temp_dir, hashed, 3);       // 3 letters in front of hashed URL would be the name of dir.
        strcpy(temp_file, hashed+3);        // the rest would be the name of file

        strcpy(home, getHomeDir(home));     // to get the path of Home dir.
        chdir(home);                        // change current working dir. to Home dir.
        strcat(home, "/cache");
        
        umask(000);                     // to change the permission

        if(opendir(home)==NULL)     // if cache dir. doesn't exist
            mkdir(home, 0777);      // make cache dir.
    
        chdir(home);                // change current working dir. to cache dir. 
        
        if(opendir(temp_dir)==NULL)     // if URL dir. doesn't exist
        {
            mkdir(temp_dir, 0777);      // make URL dir.
            strcat(home, "/");
            strcat(home, temp_dir);       // inputed URL dir.
            chdir(home);                  // cd URL dir.
            fp=fopen(temp_file,"w+");       // make URL file
        }
        else        // HIT : when URL already exist
        {
            break;      // Assignment#1-2
        }
        fclose(fp);
        // mkdir , make file, chdir  , fopen
    }
    
    struct dirent* pFile;
    DIR* pDir;
    
    if(argc<2) return 0;

    pDir=opendir(argv[1]);
    if(pDir==NULL)
    {
        printf("Dir read error\n");
        return 0; chdir(home);
    }
    //for(pFile=readdir(pDir);pFile;pFile=readdir(pDir))
    //    printf("%s\n", pFile->d_name);
    closedir(pDir);
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

    SHA1((unsigned char*) input_url, (unsigned long) strlen(input_url), hashed_160bits);
    
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
