#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024


void FIFOpageReplacement(int pagetable[], int num, int frame[], int size)
{
  int i=0,j=0,k=0;
  int fagefault=0,cnt=0, count=0;

  // for(i=0;i<size;i++)
  // {
  //   printf("%d\t",frame[i]);
  // }
  printf("\n");
  for(i=0;i<num;i++)
  {

    cnt=0;
    for(j=0;j<size;j++ )
    {
      if(pagetable[i]==frame[j])
      {
        cnt=1;
        break;

      }
    }
    if(cnt==0)
      {

        frame[k]=pagetable[i];
        k++;
        if(k==size)
        {
          k=0;
        }
        count++;
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


  int pagetable[MAX_LINE];
  int number_pages=0;
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
      working_set_size=atoi(token);
      printf("\nWorking set size:%d\n", working_set_size);
      while(token!=NULL)
      {
        token=strtok(NULL," ");
        if( token != NULL )
        {
          pagetable[number_pages]=atoi(token);
           printf("Request: %d\n", pagetable[number_pages]);
           number_pages++;
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

 printf("%d\n",number_pages);
 printf("%d\n", working_set_size);

 free(line);
 fclose(file);
 int i;

 int frame[working_set_size];
 for(i=0;i<working_set_size;i++)
 {
   frame[i]=-1;
   printf("%d\t\t", frame[i]);
 }

 FIFOpageReplacement(pagetable,number_pages,frame,working_set_size);




  return 0;
}
