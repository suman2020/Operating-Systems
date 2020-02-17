            /*
               Name:Suman Thapa Magar
               ID:100143016
            */

# define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE " \t\n"  //split command lines into tokens,here white space acts as a delimiter

#define MAX_COMMAND_SIZE 255  // the maximum command lin size

#define MAX_NUM_ARGUMENTS 10   // msh cell only supports 10 arguments


int main()
{
  //dynamically allocating memory with the use of malloc()
  char *cmd_str = (char *)malloc(MAX_COMMAND_SIZE);

  int i=0;  // keep track of the number of command lines enter

  int rotate= 1;

  char *hist[255]; // stores the command entered by the user

  int SHpid[15]={0}; // array of integers to store PIDs of child process

  int counter =0;  // keeps track of the command lines entered

  int Pidnum=0;    // keep track of the number of child process executed


  while(1)
  {
    //this conditional statement comes to operation
    //if the user wants to run a particular command from the history
     if(rotate==1)
     {
       //prints out the msh prompt
     	printf("msh>" );

      /* read commands from the command lines
         maximum number of commands that it can read is ten
         this while command waits until the user inputs something
         or else it returns NULL if there is no input
      */
      while(!fgets(cmd_str,MAX_COMMAND_SIZE,stdin));
     }

     //setting the rotate to its initial condition 1 so that
     //the msh prompt is printed each time there is new user input
     rotate= 1;
     //parse input
     char *token[MAX_NUM_ARGUMENTS];

     int token_count=0;
     //pointer that points the token
     //parsed by strsep
     char *arg_ptr;

     char *working_str=strdup(cmd_str);
     /*
      moving the working_str pointer
      so as to keep track of its originl value
      so that the actual data could be deallocated at the end
     */
     char *working_root = working_str;

     int j;
     //tokenize the input string with whitespace used as a delimiter
     while(((arg_ptr = strsep(&working_str,WHITESPACE))!=NULL) && (token_count<MAX_NUM_ARGUMENTS))
     {
       token[token_count] = strndup(arg_ptr, MAX_COMMAND_SIZE);

       if( strlen( token[token_count] ) == 0 )
       {
         token[token_count] = NULL;
       }

       token_count++;

     }

     //gives a new promt for user input if the user doesnot enter anything
     if(token[0]==NULL)
     {
     	continue;
     }
     //copyiny over the value in cmd_str for future command lines reference
     hist[i]=strdup(cmd_str);

     // terminates the msh cell if the user inputs exit or quit
     if(strcmp(token[0],"exit")==0 || strcmp(token[0],"quit")==0 )
     {

       return 0;
     }

     /*
      list the last 15 commands entered by the user with the history prompt
     */
     else if(strcmp(token[0],"history")==0)
     {
       if(counter>14)
       {
         for(j=0; j<15; j++)
         {
           hist[j]=hist[counter-14];
           printf("%d. %s",j, hist[j]);
           counter++;
         }

       }
       else
       {
         for(j = 0; j <=counter && j<15 ;j++)
         {
           printf("%d. %s", j,hist[j] );
         }
       }

      }

      // changes and handles directories cd:
      else if(strcmp(token[0], "cd")==0)
      {
        int value= chdir(token[1]);
        //if the user inputted directory is not present
        if(value==-1)
        {
          printf("-msh:cd: %s: No such file or directory \n", token[1]);
        }
      }

      // in case of !n : the nth command present is executed
      // runs the nth command entered by the user where n is from 1 to 15
      else if(token[0][0]=='!')
      {
        //string is converted to integer with the use of atoi()function
        int number = atoi(&cmd_str[1]);
        //if the nth command doesnot exist
        if(number> i|| number >15 || number ==0)
        {
          printf("\n%dth Command not found in history\n", number);

        }
        //if the nth command exist
        else
        {

          strcpy(cmd_str, hist[number-1]);

          rotate = 0;
          //skips this loop and execute from the top of the loop
          continue;
        }

      }
      //displays the process id of the child processes with the input of showpids command

      else if (strcmp(token[0], "showpids")==0)
      {
        int z;
        for(z = 0; z < Pidnum; z++ )
        {
          printf("%d:\t%d\n",z,SHpid[z]);
        }
      }

      // if the user enters invalid command line arguments
      else
      {
        //fork() used to create a child process
        pid_t pid = fork();

      //when fork() returns 0 we are in the child process
        if (pid==0)
        {
          fflush(NULL);
          //execvp() function replaces the currently running child process
          int ret= execvp(token[0], token);
          //user inputted invalid arguments
          if(ret==-1)
          {

            printf("%s: Command not found\n", *token);
          }

          exit(1);

        }
        //when fork() returns -1, it indicates that an error occured
        else if (pid == -1)
        {
          perror("fork failed \n");

          exit(0);
        }
        /* when fork() returns a postive number, it indicates that we are
          in the parent process  and the return value is the pid of the newly
          created child process
        */
        else
        {
          int status;
          fflush(NULL);
          // keeping track of process ids of the child process
          if(Pidnum>14) //if there is more than 15 child process to keep track of
          {
            int k;
            for(k=0; k<15; k++)
            {
              SHpid[k]=SHpid[k+1];

            }
                Pidnum--;

          }
          SHpid[Pidnum]=pid;
          Pidnum++;
          // wait for the child to exit;
          waitpid(pid, &status, 0);

        }

      }

      counter=i;
      //keep tracks of the number of command prompts entered by the user
      counter++;
      i++;
      //dynamically allocated memory is freed
      free(working_root);



    }
    return 0;

}
