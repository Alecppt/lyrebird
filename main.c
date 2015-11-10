/*
(1) student's name:     Alec Chen
(2) student ID:         301187669
(3) SFU user name:      cca169
(4) lecture section:    CMPT 300 D1 (Fall 2015)
(5) instructor's name:  Brian Booth
(6) TA's name:          Scott Kristjansonnclude <stdio.h>
*/
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "decrypt.h"
#include "memwatch.h"
#define NUM_CONFIG 1024
char* getCurrentTime(time_t* nowTime);

int main(int argc, char const *argv[])
{
  FILE *config;
  time_t nowTime;
  int read, status = 0;
  pid_t child_pid, wpid;
  if(argc != 2 )
  {
    printf("%s\n", "Usage: ./lyrebird [config file name]");
    exit(EXIT_FAILURE);
  }

  char inputFile[NUM_CONFIG], outputFile[NUM_CONFIG];

  /*open file error check*/
  config = fopen (argv[1], "r");
  if(config == NULL){
    printf("[%s] Parent process ID #%d fails to open config file", getCurrentTime(&nowTime), getpid());
    /*fprintf(stderr, "failed to open \"%s\"\n",argv[2]);*/
  }
  /*loop through config files*/
  read = fscanf(config,"%s %s\n",inputFile, outputFile);
  while(read != EOF){
    child_pid = fork();
    if (child_pid == 0){
      printf("[%s] Child process ID #%d created to decrypt %s.\n",getCurrentTime(&nowTime), getpid(), inputFile);
      int checkDecrpt = decrypt(inputFile, outputFile);
      if (checkDecrpt == 0 ){
      /*printf("[%s] Decryption of %s compeltes.\nProcess ID #%d Exiting with code[%d].\n",getCurrentTime(&nowTime), inputFile,getpid(), checkDecrpt);*/
      exit(checkDecrpt);
      }
      else{
        if(checkDecrpt == 1){
        /* printf("[%s] Fails to open \"%s\"\nChild process ID#%d Exiting with code[%d]\n",getCurrentTime(&nowTime), inputFile,getpid(), checkDecrpt);*/
        }
        exit(1);
      }
    }
    else if (child_pid < 0){
    printf("[%s] fork error.\n", getCurrentTime(&nowTime));
    }
    else{
    read = fscanf(config, "%s %s\n", inputFile, outputFile);
    }
  }/*end of while loop*/
  while ((wpid = waitpid(-1,&status,0)) > 0){
    if(status==0){
      printf("[%s] Decryption compeltes. Child process ID #%d.\n",getCurrentTime(&nowTime), getpid());
    }
      else{
      printf("[%s] Child process ID #%d did not terminate successfully.\n",getCurrentTime(&nowTime), getpid());

      }
    }
  return 0;
}

char* getCurrentTime(time_t* nowTime){

  time (nowTime);
  char* now =ctime(nowTime);
  removeTrailingNewLine(now);
  return now;

}