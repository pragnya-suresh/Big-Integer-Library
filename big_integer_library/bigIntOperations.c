//  intal.c
//  Created by Pragnya Suresh on 14/03/18.

#include <stdio.h>
#include <stdlib.h>
#include "intal.h"
#include <string.h>
static int intal_size(void *intal);
static int difference(char*str1,char *str2);
static char* reverse(char *str);

void* intal_create(const char* str)
{
  //0000
    int i=0,j=0,flag=0;
    int l=strlen(str);
   
    int *A=(int*)malloc(sizeof(int)*l+1);
    if((str[0]=='0')&& (strlen(str)>1))
        flag=1;
    if(str[0]<'0'||str[0]>'9')
        flag=1;
    
    else{
        while(str[i]!='\0')
    {
        if(str[i]>='0' && str[i]<='9')
        {   if(flag==1)//to strip off leading zeroes
            {   if(str[i+1]=='\0')
                    break;
            if(str[i]=='0'&& str[i+1]!='0')
            {   i++;
                if(str[i]>='0' && str[i]<='9')
                {A[j++]=str[i]-'0';
                flag=0;
                i+=1;}
            }
                else
                    i+=1;}
            else{
              A[j++]=str[i]-'0';
                i+=1;
            }
        }
    else
    break;
        
        }
    }
    
    if(flag)//The string only consists of 0s
    {   A=realloc(A,sizeof(int)*2);
        j=0;
        A[j++]=0;
    }
    A[j]= -1;
    l=j;
    void *ptr = malloc(sizeof(int)*l+1);
    ptr=A;
    return ptr;
}

void intal_destroy(void* intal)
{
    free(intal);
}

char* intal2str(void* intal)
{
    if(intal==NULL){
        char *nan=(char *)malloc(4);
        nan[0]='N';nan[1]='a';nan[2]='N';nan[3]='\0';
    
        return nan;
    }
    
    char c;
    int size=intal_size(intal);
    int i;
    char *a=(char *)malloc(size);
    for( i=0;i< size;i++)
    {   c=((int*)intal)[i]+'0';
        a[i]= c;
    }
    a[i]='\0';
    return a;
}

void* intal_increment(void* intal)
{
    if(intal==NULL)
        return NULL;
   int num,c=1,i;
    int size=intal_size(intal);
    for(i=size-1;i>=0;i--)
    {   num=(((int*)intal)[i])+c;
        if(num>9)
        {   c=1;
            num=num%10;
            
            (((int*)intal)[i])=num;
            }
        
        else{
            (((int*)intal)[i])=num;
            c=0;
            }
    }
    if(c==1)
    {
        size+=1;
        intal=realloc(intal,(sizeof(int)*size+1));
       // printf("new size:%d\n",size);
        for(i=1;i<size;i++)
        {   ((int*)intal)[i]=((int*)intal)[i-1];
        }
        ((int*)intal)[0]=1;
        
    }
    ((int*)intal)[size]=-1;
   return intal;
}


void *intal_decrement(void* intal)
{
    if(intal==NULL)
        return NULL;
    int num,c=1,i;
    int size=intal_size(intal);
    if(size==1 && ((int*)intal)[0]==0)
    {//printf("Size after decrementing:%d\n",size);
        //for(i=0;i<size;i++)
           // printf("here%d",((int*)intal)[i]);
        
        return intal;
    }
    //printf("size after incrementing:%d\n",size);
    for(i=size-1;i>=0;i--)
    {
        num=(((int*)intal)[i])-c;
        if(num<0)
        {
            c=1;
            num=9;
            //printf("num :%d\n",num);
            ((int*)intal)[i]=num;
            
        }
        else{
            ((int*)intal)[i]=num;
            c=0;
        }
    }

    if(((int*)intal)[0]==0 && size!=1)
    {
        size-=1;
        intal=realloc(intal,(sizeof(int)*size+1));
        for(i=0;i<size-1;i++)
        {
            ((int*)intal)[i]=((int*)intal)[i+1];
            
        }
    }
    ((int*)intal)[size]=-1;
   // printf("Size after decrementing:%d\n",size);
    
    return intal;
}


void* intal_add(void* intal1, void* intal2)
{
    if(intal1==NULL ||intal2==NULL)
        return NULL;
    int i,j,k=0, d1,d2; int sum=0, carry=0; void *intal;
    
    char *str1=intal2str(intal1);
    char *str2=intal2str(intal2);
    int size1=strlen(str1);
    int size2=strlen(str2);
    int max=(size1>=size2)?size1:size2;
    char *str=(char*)malloc(max+1);
    for(i=size1-1,j=size2-1;i>=0 || j>=0;i--,j--)
    {
        d1=(str1[i]-'0');
        d2=(str2[j]-'0');
        if(i<0)
            d1=0;
        else if(j<0)
            d2=0;
        sum=d1+d2+carry;
        str[k++]=(sum%10)+'0';
        carry=sum/10;
    }
    if(carry)
        str[k]=carry+'0';
    
    char *rev=reverse(str);
    intal=intal_create(rev);
    return intal;
}

   void* intal_diff(void* intal1, void* intal2)
{//return non negative difference.
    //if diff is 0 then handle.
    if(intal1==NULL ||intal2==NULL)
        return NULL;
    int i,j,k=0; int diff=0, carry=0; int d1,d2; void *intal;
    char *str1=intal2str(intal1);
    char *str2=str2=intal2str(intal2);
    int size1=strlen(str1);
    int size2=strlen(str2);
    int max=(size1>=size2)?size1:size2;
    char*l; char*s;
    if(intal_compare(intal1,intal2)==1){
        l=intal2str(intal1);s=intal2str(intal2);
    }
    else if(intal_compare(intal1,intal2)==-1){
        l=intal2str(intal2);s=intal2str(intal1);
    }
    
    if(intal_compare(intal1,intal2)==0)
    {
        intal=intal_create("0");
        return intal;
    }
    char *str=(char*)malloc(max+1);
   
   for(i=strlen(l)-1,j=strlen(s)-1;i>=0 || j>=0;i--,j--)
    {
        d1=(l[i]-'0');
        d2=(s[j]-'0');
        if(i<0)
            d1=0;
        else if(j<0)
            d2=0;
        diff=d1-d2-carry;
        if(diff<0)
        {
            diff+= 10;
            carry = 1;
        }
        else
            carry = 0;
        
        str[k++]=diff+'0';
    }
    str[k]='\0';
    char *rev=reverse(str);
    intal=intal_create(rev);
    return intal;
}



    void* intal_multiply(void* intal1, void* intal2){
        if(intal1==NULL ||intal2==NULL)
            return NULL;
        char *str1=intal2str(intal1);
        char *str2=intal2str(intal2);
        
        int size1 = strlen(str1);
        int size2 = strlen(str2);
        char *str=(char *)malloc(size1+size2+1);
        if (str1[0] == '0'||str2[0] == '0'){
            char str[2];
            str[0]='0';str[1]='\0';
            return intal_create(str);
        }
        int* A=(int*)malloc((size1 + size2)*sizeof(int));
        int x =0;
        int y =0;
        int i,j,carry;
        for(i=0;i<size1+size2;i++)
            A[i]=0;
        for(i=size1-1;i>=0;i--){
            carry = 0;
            int x1 = str1[i]-'0';
            y=0;
            for(j=size2-1;j>=0;j--){
                int y1=str2[j]-'0';
                int sum = x1*y1 + A[x+y] + carry;
                carry = sum/10;
                A[x+y] = sum % 10;
                y++;
            }
            if (carry)
                A[x+y]+= carry;
            x++;
        }
        for(i=0;i<(size1+size2);i++)
            str[i]=A[i]+'0';
        str[i]='\0';
        char * rev=reverse(str);
        return intal_create(rev);
    }


void* intal_divide(void* intal1, void* intal2){//long division
    if(intal1==NULL || intal2==NULL)
        return NULL;
    char *str1=intal2str(intal1);
    char *str2=intal2str(intal2);
    void *intal_zero =intal_create("0");
    
    if(str1[0]=='0')
        return intal_zero;
    if(str2[0]=='0')
        return NULL; //division by 0 returns NaN.
    
   if(intal_compare(intal1,intal2)==-1)//if 2nd number is larger, quotient will be 0
        return intal_create("0");
    int i,j,k,cmp;
    char *quotient;
    char *z,*tmp; char ch[2];
    void *n,*mul,*m,*diff;
   
    int l1=strlen(str1);
    int l2=strlen(str2);
    z=(char*)malloc(l2+2);
    quotient=(char*)malloc(l1-l2+2);
    ch[1]='\0';
    j=l2;
    for(i=0;i<l2;i++)
        z[i]=str1[i];
    z[i]='\0';
    i=0;
    while(j<=l1){
        n=intal_create(z);
        mul=intal_create(str2);
        cmp=intal_compare(n,mul);
        if(cmp==-1){
            z[strlen(z)+1]='\0';
            if(j==l1){
                quotient[i++]='0';
                break;
            }
            z[strlen(z)]=str1[j];
            n=intal_create(z);
            j++;
            quotient[i++]='0';
        }
        k=0;
        while(intal_compare(n,mul)>-1){
            ++k;
            if(k<10){
                ch[0]=k+'0';
                m=intal_create(ch);
            }
            else
                m=intal_create("10");
            //printf("m=%d\n",*(int*)m);
            mul=intal_multiply(intal2,m);
            
        }
    
        if(j==l1){
            if(k>0)
                quotient[i++]=(k-1)+'0';
            else
                quotient[i++]='0';
            break;
        }
        if(k==0)
            quotient[i++]='0';
        else
            quotient[i++]=(k-1)+'0';
        mul=intal_diff(mul,intal2);
        diff=intal_diff(n,mul);
        tmp=intal2str(diff);
        for(k=0;k<strlen(tmp);k++)
            z[k]=tmp[k];
        z[k++]=str1[j++];
        z[k]='\0';
        }
    quotient[i]='\0';
    return intal_create(quotient);
}





int intal_compare(void* intal1, void* intal2)
{//0-equal ,-1 intal2  is larger 1-1st is larger
    int i=0; int flag=1, r;
    char *str1=intal2str(intal1);
    char *str2=intal2str(intal2);
    int size1=strlen(str1);
    int size2=strlen(str2);
   if((intal1==NULL)||(intal2==NULL))
        return 0;
   if(size1==size2)
 {
    for(i=0;i<size1;i++)
    {
        if(str1[i]!=str2[i])
        {  flag=0;
        break;}
    }
     if(flag==1)
         return 0;
        r=difference(str1,str2);
        if(r==0)//2nd is bigger
            return -1;
            else
                return 1;}
    else if(size1<size2)
       return -1;
        else
            return 1;
   }


void* intal_pow(void* intal1, void* intal2){
  //decrease by constant factor
    if(intal1==NULL ||intal2==NULL)
        return NULL;
    void*intal;
    
    char *str1=intal2str(intal1);
    char *str2=intal2str(intal2);
    void *intal_zero =intal_create("0");
    
    if(str1[0]=='0')
        return intal_zero;
   
   
    if(str2[0]=='0')//base condition
        return intal_create("1");
    void *intal_2=intal_create("2");
    intal=intal_pow(intal1,(intal_divide(intal2,intal_2)));
    // printf("%s /%s=%s \n",intal2str(intal2),intal2str(intal_2), intal2str(intal_divide(intal2,intal_2)));
   
    if((str2[strlen(str2)-1]-'0')%2==0)//even
        return intal_multiply(intal,intal);
    else
        return intal_multiply(intal1,(intal_multiply(intal,intal)));
    }
    


static int intal_size(void *intal)
{
    int j=0;

while(((int*)intal)[j]!=-1)
    j++;
    return j;
}


static int difference(char*str1,char *str2)
{
   char* str=(char*)malloc(strlen(str1)+1);
int i,k=0,d1,d2,j,diff=0,carry=0;
    for(i=strlen(str1)-1,j=strlen(str2)-1;i>=0 || j>=0;i--,j--)
    {
        d1=(str1[i]-'0');
        d2=(str2[j]-'0');
        if(i<0)
            d1=0;
        else if(j<0)
            d2=0;
        diff=d2-d1-carry;//assuming str2 is bigger
        if(diff<0)
        {
            diff+= 10;
            carry = 1;
        }
        else
            carry = 0;
        
        str[k++]=diff+'0';
    }
    str[k]='\0';
    if(carry)//if carry is set, diff is negative.Hence str1 is bigger.
        return 1;
    else
        return 0;

}
static char* reverse(char *str)
{   char *rev=(char*)malloc(strlen(str)+1);
    int j=0,i;
    for(i=strlen(str)-1;i>=0;i--)
        rev[j++]=str[i];
    rev[j]='\0';
    return rev;
}

