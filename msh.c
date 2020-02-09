# define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE "\t\n"

#define MAX_COMMAND_SIZE 255

#define MAX_NUM_ARGUMENTS 10

int main()
{
  char *cmd_str = (char *)malloc(MAX_COMMAND_SIZE);

  while(1)
  {
    printf("msh>" );

    while(!fgets(cmd_str,MAX_COMMAND_SIZE,stdin));

    char *token[MAX_NUM_ARGUMENTS];

    int token_count=0;

    char *arg_ptr;

    char *working_str=strdup(cmd_str);

    char *working_root= working_str;

    while(((arg_ptr = strsep(&working_str,WHITESPACE))!NULL) && (token_count<MAX_NUM_ARGUMENTS))
    {
        token[token_count] = strndup(arg_ptr, MAX_COMMAND_SIZE);

        if(strlen(token[token_count])==0)
        {
          token[token_count]= NULL;

        }
          token_count++;

    }

    int token_index=0;
    for(token_index = 0; token_index<token_count; token_index++)
    {
      printf("token[%d] = %s\n", token_index, token[token_index] );
    }
    free(working_root);

}
