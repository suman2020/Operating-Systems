            /*
               Name:Suman thapa magar
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

#define WHITESPACE " \t\n"

#define MAX_COMMAND_SIZE 255

#define MAX_NUM_ARGUMENTS 10


int main()
{
  char *cmd_str = (char *)malloc(MAX_COMMAND_SIZE);

  int i=0;
   int rotate= 1;

  int status;
    char *hist[255];
    char *history[255];
     int counter =0;

    while(1)

    {

      if(rotate=1)
      {
        printf("msh>" );

        while(!fgets(cmd_str,MAX_COMMAND_SIZE,stdin));
     }
     rotate= 1;
      char *token[MAX_NUM_ARGUMENTS];

      int token_count=0;

        char *arg_ptr;

        char *working_str=strdup(cmd_str);

        char *working_root = working_str;

        char *separate;

        int j;
        while(((arg_ptr = strsep(&working_str,WHITESPACE))!=NULL) && (token_count<MAX_NUM_ARGUMENTS))
        {
            token[token_count] = strndup(arg_ptr, MAX_COMMAND_SIZE);

            if( strlen( token[token_count] ) == 0 )
            {
              token[token_count] = NULL;
            }

            token_count++;
        }

              if(token[0]==NULL)
              {
                continue;
              }
              hist[i]=strdup(cmd_str);

                  if(strcmp(token[0],"exit")==0 || strcmp(token[0],"quit")==0 )
                  {

                    return 0;
                  }

                  else if(strcmp(token[0],"history")==0)
                  {
                    if(counter>14)
                    {
                      for(j=0; j<15; j++)
                      {
                      history[j]=hist[counter-14];
                      printf("%d. %s",j, history[j]);
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
                  else if(strcmp(token[0], "cd")==0)
                  {
                    int value= chdir(token[1]);
                    if(value==-1)
                    {
                      printf("-msh:cd: %s: No such file or directory ", token[1]);
                    }
                  }
                  else if(token[0][0]=='!')
                  {

                    int number = atoi(&cmd_str[1]);

                    printf("%d", number);
// atoi[&cmd_str[1]
                    if(number> i|| number >15 || number ==0)
                    {
                      printf("\n%dth Command not in history\n", number);

                    }
                    else
                    {
                    strcpy(cmd_str, hist[number-1]);

                    rotate = 0;
                      continue;
                    }
                  }


                  else
                  {
                    pid_t pid = fork();
                    if (pid==0)
                    {
                      int ret= execvp(token[0], &token[0]);
                      if(ret==-1)
                      {

                        printf("%s: Command not found\n", working_root);
                      }

                      fflush(NULL);
                      exit(0);
                    }
                    else if (pid == -1)
                    {
                      perror("fork failed \n");

                      exit(0);
                    }
                    else
                    {
                      int status;
                      fflush(NULL);
                      waitpid(pid, &status, 0);

                    }



                  }

                counter=i;




      counter++;
      i++;
          free(working_root);
    }


  return 0;
}
