#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

void FIFOpageReplacement(int pagetable[], int num, int frame[], int size)
{
  int i=0,j=0,k=0;
  int fagefault=0,cnt=0, count=0;
  for(i=0;i<num;i++)
  {
    cnt=0;
    for(j=0;j<size;j++ )
    {
      if(pagetable[i]==frame[j])
      {
        cnt=1;
        count++;
        break;

      }
    }

    if(cnt==0)
    {
      frame[k]=pagetable[i];
      k=(k+1)%3;


    }

  }


  printf("FICO:Page fault=%d\n",count);

}

int main(int argc, char *argv[])
{
  char *line=NULL;

  size_t line_length=MAX_LINE;
  char * filename;
  FILE * file;
  int c=0;


  if(argc<2)
  {
  printf("Error: You must provide a datafile as an argument.\n");
  printf("Example: ./fp datafile.txt\n");
  exit(EXIT_FAILURE);

  }

  filename= (char *) malloc(strlen(argv[1])+1);

  line = (char *) malloc(MAX_LINE);


  memset(filename, 0, strlen(argv[1])+1);

  strncpy(filename, argv[1], strlen(argv[1]));

  printf("Opening file %s\n", filename);
  file=fopen(filename,"r");
  int working_set_size=0;

  if(file)
  {
    while(fgets(line,line_length,file))
    {
      char *token;

      token= strtok(line," ");
      int working_set_size=atoi(token);
      printf("\nWorking set size:%d\n", working_set_size);
      while(token!=NULL)
      {
        token=strtok(NULL," ");
        if( token != NULL )
        {
           printf("Request: %d\n", atoi(token));
           c++;
        }
      }
    }
// free(line);
// fclose(file);
  }
 //  printf("%d",c);
 //  int pagetable[c];
 //  FILE *fp;
 //  int i=0;
 //  fp=fopen(filename,"r");
 //  while(fgets(line2, line_length, fp))
 //  {
 //    char *token2;
 //    token2=strtok(line2, " ");
 //    for(i=0;token2!=NULL&&i<c;i++)
 //    {
 //      token2=strtok(NULL," ");
 //
 //    pagetable[i]=atoi(token2);
 //
 //    }
 //
 // }
 // free(line2);
 // fclose(fp);

 printf("%d",c);
 int pagetable[c];
 fseek(file,0,SEEK_SET);
 int i=0;
  while(fgets(line, line_length, file))
  {
    char *token;
    token=strtok(line, " ");
    for(i=0;token!=NULL&&i<c;i++)
    {
      token=strtok(NULL," ");

    pagetable[i]=atoi(token);
    }

 }

 free(line);
 fclose(file);

 int frame[working_set_size];
 for(i=0;i<working_set_size;i++)
 {
   frame[i]=-1;
 }
 FIFOpageReplacement(pagetable,c,frame,working_set_size);




  return 0;
}
