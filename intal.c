//C library for the integers of arbitrary length (intal).

//Report by:
// Name : Ankitha P
// SRN  : PES1201801491
// Class: Sem 4, section D

#include "intal.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



int intal_compare(const char* intal1, const char* intal2)
{
	int n1=strlen(intal1);
	int n2=strlen(intal2);
	if(n1>n2){return 1;}
	else if(n2>n1){return -1;}
	else {
        int x= memcmp(intal1, intal2, n1);
        if(x>0){return 1;}
        else if(x<0){return -1;}
        else return 0;
    	}
}


static char* int_to_string(unsigned int n)
{
	char* str=(char*)malloc(sizeof(char)*1001);
	sprintf(str,"%d",n);
	return str;

}

char* intal_add(const char* intal1, const char* intal2)
{
	const char* l1;
	const char* l2;
	char* res;
	char* res2;
	int n,a,b;
	int n1 = strlen(intal1);
	int n2 = strlen(intal2);
	int carry,sum;
	if(n2>n1)
	{
		l1=intal2;
		l2=intal1;
		n=n2;
	}
	else
	{
		l1=intal1;
		l2=intal2;
		n=n1;
	}
	res=(char*)malloc(sizeof(char)*(n+1));
	res2=(char*)malloc(sizeof(char)*(n+2));
	if(strcmp(intal2,"0") == 0)
	{
		strcpy(res2,intal1);
		free(res);
	}
	else if(strcmp(intal1,"0") == 0)
	{
		strcpy(res2,intal2);
		free(res);
	}	
	else
	{
		a = strlen(l1);
		b = strlen(l2);
		carry = 0;
		for(int i=b-1;i>=0;i--)
		{
			sum=(l1[a-b+i] - '0') + (l2[i] - '0') + carry;
			res[a-b+i] = (sum %10) + '0';
			carry = sum/10;
		}
		for(int i=a-b-1;i>=0;i--)
		{
			sum=(l1[i] - '0' )+ carry;
			res[i] = (sum)%10 + '0';
			carry = sum/10;
		}
		res[a] = '\0';
		if(carry)
		{
			res2[0] = carry + '0';
			res2[1] = '\0';
			strcat(res2,res);
			free(res);
		}
		else
		{
			strcpy(res2,res);
			free(res);
		}
	}
	return res2;
}	


char* intal_diff(const char* intal1, const char* intal2){
	const char* l1;
	const char* l2;
	int a,b,k;
	char* res;
	char* res2;
	int n1 = strlen(intal1);
	int n2 = strlen(intal2);
	int carry,diff;
	int compare=intal_compare(intal1,intal2);
	if(compare==0)
	{
		res=(char*)malloc(sizeof(char)*2);
		res[0]='0';
		res[1]='\0';
		return res;
	}
	else if(compare==1)
	{
		l1 = intal1;
		l2 = intal2;
	}
	else if(compare==-1)
	{
		l1 = intal2;
		l2 = intal1;
	}
	int n=n1>n2?n1:n2;
	res = (char*)malloc(sizeof(char)*(n+1));
	a = strlen(l1);
	b = strlen(l2);
	
	carry = 0;
	for(int i=b-1;i>=0;i--)
	{
		diff=(l1[a-b+i] - '0') - (l2[i] - '0') - carry;

		if(diff<0){
			res[a-b+i]=(diff+10)+'0';
			carry=1;
		}
		else
		{
			res[a-b+i]=diff+'0';
			carry=0;
		}
	}
	for(int i=a-b-1;i>=0;i--)
	{
		diff=l1[i] - '0' -carry;
		if(diff<0){
			res[i]=(diff+10)+'0';
			carry=1;
		}
		else
		{
			res[i]=diff+'0';
			carry=0;
		}
		res[i]=diff+'0';
	}
	res[a]='\0';
	for(k=0;k<a;k++)
	{
		if(res[k]!='0'){break;}
	}
	if(k==0){return res;}
	res2=(char*)malloc(sizeof(char)*(a-k+1));
	strcpy(res2,res+k);
	free(res);
	return res2;
}


char* intal_multiply(const char* intal1, const char* intal2){
	char* prod;char*result;
	int a=strlen(intal1);
	int b=strlen(intal2);
	if(intal1[0]=='0'||intal2[0]=='0')
	{
	prod=(char*)malloc(sizeof(char)*2);
	prod[0]='0';
	prod[1]='\0';
	return prod;
	}
	prod=(char*)malloc(sizeof(char)*(a+b+1));
	prod[a+b]='\0';
	for(int i=0;i<(a+b);i++)
		prod[i]='0';
	int p1=0;int p2=0;int n=a+b-1;
	for(int i=a-1;i>=0;i--)
	{
	int carry=0;
	int n1=intal1[i]-'0';
	p2=0;
		for(int j=b-1;j>=0;j--)
		{
		int n2=intal2[j]-'0';
		int sum=(n1*n2)+carry+(prod[n-(p1+p2)]-'0');
		carry=sum/10;
		prod[n-(p1+p2)]=sum%10+'0';
		p2++;
		}
	if(carry>0){prod[n-(p1+p2)]+=carry;}
	p1++;
	}
	int p=0;
	while(prod[p]=='0'){p++;}
	if(p==0)
		return prod;
	result=(char*)malloc(sizeof(char)*(a+b+1-p));
	memcpy(result,prod+(p*sizeof(char)),(a+b+1-p)*sizeof(char));
	free(prod);
	return result;
}




static char* shift(const char* intal)
{
	int a=strlen(intal);
	char* res=(char*)malloc(sizeof(char)*(a+1));
	char* res2;
	int carry=0;
	for(int i=0;i<a;i++)
	{
	res[i]=((intal[i]-'0'+carry)/2)+'0';
	carry=((intal[i]-'0'+carry)%2)*10;
	}
	res[a]='\0';
	int k;
	for(k=0;k<a;k++)
	{
	if(res[k]!='0')
		break;
	}
	if(k==0) return res;
	res2=(char*)malloc(sizeof(char)*(a-k+1));
	strcpy(res2,res+k);
	free(res);
	return res2;
}


char* intal_mod(const char* intal1, const char* intal2)
{
	char* temp1;char* temp2;
	int a=strlen(intal1);
	char* l=(char*)malloc(sizeof(char)*(a+1));
	char* m=(char*)malloc(sizeof(char)*(a+1));
	char* h=(char*)malloc(sizeof(char)*(a+1));
	strcpy(l,"0");
	strcpy(h,intal1);
	while(intal_compare(l,h)==-1)
	{
	temp1=intal_add(l,h);
	temp2=shift(temp1);
	strcpy(m,temp2);
	free(temp1);
	free(temp2);
	temp1=intal_multiply(m,intal2);
	if(intal_compare(intal1,temp1)>=0)
	{
	temp2=intal_diff(intal1,temp1);
	free(temp1);
	if(intal_compare(temp2,intal2)>=0)
	{
	temp1=intal_add(m,"1");
	strcpy(l,temp1);
	free(temp1);
	}
	else
	{strcpy(h,m);}
	free(temp2);
	}
	else{strcpy(h,m);free(temp1);}
	}
	temp1=intal_multiply(l,intal2);
	temp2=intal_diff(intal1,temp1);
	free(temp1);free(l);free(m);free(h);
	return temp2;
}



char* intal_pow(const char* intal1, unsigned int n)
{	
	char* pow;
	if(n==0)
	{
		pow=(char*)malloc(sizeof(char)*2);
		strcpy(pow,"1");
		return pow;
	}
	if(strcmp(intal1,"0")==0)
	{
		pow=(char*)malloc(sizeof(char)*2);
		strcpy(pow,"0");
		return pow;
	}
	pow=(char*)malloc(sizeof(char)*1001);
	if(n==1)
	{strcpy(pow,intal1); return pow;}
	char* t1=intal_pow(intal1,n/2);
	char* t2=intal_multiply(t1,t1);
	free(t1);
	if(n%2==0)
	{
	strcpy(pow,t2);
	free(t2);
	}
	else
	{
	t1=intal_multiply(t2,intal1);
	strcpy(pow,t1);
	free(t1);
	free(t2);
	}
	return pow;
}


char* intal_gcd(const char* intal1, const char* intal2){
	char* gcd=(char*)malloc(sizeof(char)*1001);
	strcpy(gcd,"0");
	if(strcmp(intal1,"0")==0 && strcmp(intal2,"0")==0){return gcd;}
	strcpy(gcd,intal1);
	char* x=(char*)malloc(sizeof(char)*1001);
	strcpy(x,intal2);
	int cmp=0;
	while((cmp=intal_compare(x,"0"))!=0)
	{
		char *temp =intal_mod(gcd,x);
        	free(gcd);
        	gcd=x;
        	x=temp;
	}
    	free(x);
	return gcd;
}


char* intal_fibonacci(unsigned int n){
	char* res;
	if(n==0)
	{
	res=malloc(sizeof(char)*2);
	res[0]='0';
	res[1]='\0';
	return res;
	}
	else if(n==1)
	{
	res=malloc(sizeof(char)*2);
	res[0]='1';
	res[1]='\0';
	return res;
	}
	char* b=(char*)malloc(sizeof(char)*1001);
	char* c=(char*)malloc(sizeof(char)*1001);
	res=(char*)malloc(sizeof(char)*1001);
	strcpy(b,"0");
	strcpy(c,"1");
	for(int i=2;i<=n;i++)
	{
	char* temp=intal_add(b,c);
	strcpy(res,temp);
	free(temp);
	strcpy(b,c);
	strcpy(c,res);
	}
	free(b);free(c);
	return res;
}


char* intal_factorial(unsigned int n)
{
	char* fact ;
	if(n==0||n==1)
	{
	fact=malloc(sizeof(char)*2);
	fact[0]='1';
	fact[1]='\0';
	return fact;
	}
	char* n1=int_to_string(n);
	fact=malloc(sizeof(char)*1001);
	char* temp1=intal_factorial(n-1);
	char* temp2=intal_multiply(n1,temp1);
	free(n1);
	free(temp1);
	strcpy(fact,temp2);
	free(temp2);
	return fact;
}


char* intal_bincoeff(unsigned int n, unsigned int k)
{	char** table=(char**)malloc(sizeof(char*)*(k+1));
	int i;
	for(i=0;i<k+1;i++)
	{
	table[i]=(char*)malloc(sizeof(char*)*1001);
	strcpy(table[i],"0");
	}
	table[0][0]='1';
	for(i=1;i<=n;i++)
	{
		for(int j=i<k?i:k;j>0;j--)
		{
		char* temp=intal_add(table[j],table[j-1]);
		strcpy(table[j],temp);
		free(temp);
		}
	}
	char* result=table[k];
	for(i=0;i<k;i++){free(table[i]);}
	free(table);
	return result;
}

int intal_max(char **arr, int n)
{
	char* a=arr[0];
	int index;
	index=0;
	for(int i=1;i<n;i++){
	if(intal_compare(arr[i],a)==1){
    	index=i;
    	a=arr[i];}
    	}
    	return index;
}



int intal_min(char **arr, int n)
{
	char* a=arr[0];
	int index;
	index=0;
	for(int i=1;i<n;i++){
	if(intal_compare(arr[i],a)==-1){
    	index=i;
    	a=arr[i];}
    	}
    	return index;
}



int intal_search(char **arr, int n, const char* key)
{
	int index;
	index=-1;
	for(int i=0;i<n;i++)
	{
	if(intal_compare(arr[i],key)==0){index=i;break;}
	}
	return index;
}

int intal_binsearch(char **arr, int n, const char* key)
{
	int l=0;
	int h=n-1;
	int m,a;
	while(l<=h)
	{
	m=(l+h)/2;
	a=intal_compare(arr[m],key);
	if(a==-1){l=m+1;}
	else if(m>0 && (intal_compare(arr[m-1],key))>=0) { h=m-1;}
	else {return m;}
	}
	return -1;
}



static void merge(char** arr, int l, int m, int r) 
{ 
     	int n=r-l+ 1;
	char* temp[n];
	
	int i=l;
	int j=m + 1;
	int k=0;
	
	while((i<=m)&&(j<=r))
	{
	int cmp=intal_compare(arr[i],arr[j]);
	if(cmp==-1)
	{
		temp[k]=arr[i];
		++i;
	}
	else
	{
		temp[k]=arr[j];
		++j;
	}
	++k;
	}
	
	while(i<=m){temp[k++]=arr[i++];}
	while(j<=r){temp[k++]=arr[j++];}
	memcpy(&arr[l],temp,n* sizeof(char*));
}

static void mergeSort(char** arr, int l, int r) 
{ 
	if (l<r) 
	{ 
	int m=(l+r)/2; 
	mergeSort(arr,l,m); 
	mergeSort(arr,m+1,r); 
	merge(arr,l,m,r); 
	} 
}

void intal_sort(char **arr, int n){mergeSort(arr,0,n-1);}


char* coin_row_problem(char **arr, int n)
{
	char* curr=(char*)malloc(sizeof(char)*1001);
	if(n==0)
	{
	strcpy(curr,"0");
	return curr;}
	char* prev=(char*)malloc(sizeof(char)*1001);
	char* next=(char*)malloc(sizeof(char)*1001);
	int x;
	char* temp;
	strcpy(prev,"0");
	strcpy(curr,arr[0]);
	for(int i=1;i<n;i++)
	{
	temp=intal_add(prev,arr[i]);
	x=intal_compare(temp,curr);
	if(x==1) strcpy(next,temp);
	else strcpy(next,curr);
	free(temp);
	strcpy(prev,curr);
	strcpy(curr,next);
	}
	free(prev);
	free(next);
	return curr;
}





