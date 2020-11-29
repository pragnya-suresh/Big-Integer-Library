
#include <stdio.h>

#include <stdlib.h>
#include <time.h>
int main()
{
int m,i,n=50000;
 FILE * fp=fopen("ip.txt","w");
srand(time(0));
    
    for(i=0;i<10000;i++)
   { m= random();
       fprintf(fp,"%s",m);
 
    }
    fclose(fp);
    return 0;
    }
