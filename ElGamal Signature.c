#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
long long int gcd(long long int a, long long int b){
    if (a==0)
        return b;
    return gcd(b%a, a);
}
long long int modPow(long long int base,long long int exp,long long int modulus){
  base %= modulus;
  long long int result = 1;
  while (exp > 0) {
    if(exp & 1)
        result=(result*base)%modulus;
    base=(base*base)%modulus;
    exp>>=1;
  }
  return result;
}
long long int gcdExtended(long long int a, long long int b, long long int *x, long long int *y){
    if (a == 0){
        *x = 0;
        *y = 1;
        return b;
    }
    long long int x1, y1;
    long long int gcd = gcdExtended(b%a,a,&x1,&y1);
    *x = y1-(b/a)*x1;
    *y = x1;
    return gcd;
}
void verify(long long int alpha,long long int beta,long long int signature,long long int p,long long int g){

	long long int temp=modPow(alpha,beta,p);
	long long int temp1=modPow(beta,signature,p);
	temp=temp*temp1;
	temp%=(p);
	printf("Enter message at receiver\n");
	long long int m;
	scanf("%lld",&m);
	long long int g_m= modPow(g,m,p);
		if(temp==g_m){
			printf("Signature Verified correctly!!!\n");
		}
		else{
			printf("Wrong Signature!!!\n");
		}
}
int main(){
long long int p,g,x,m,alpha,beta,s,x1,y1,i,k;
long long int flag=0;
srand(time(NULL));
while(flag==0){
    p=rand();
    for(i=2;i<=sqrt(p);i++){
        if(p%i==0){
                flag=1;
            break;
        }
    }
    if(flag==0){
        g=rand();
        if(g<p){
        int ghg=0;
        long long int *size=(long long int*)malloc(sizeof(long long int)*p);
        for(i=1;i<p;i++){
            size[modPow(g,i,p)]=1;
        }
        for(i=1;i<p;i++){
            if(size[i]!=1){
                    ghg=1;
                break;
            }
        }
        if(ghg==1)
            flag=0;
        else
            flag=1;
        }
    }
    else
        flag=0;
}
int xxxx;
printf("Enter 1 to randomly generate p and g\nEnter 2 to enter manually\n");
scanf("%d",&xxxx);
switch(xxxx){
    case 1: printf("Randomly Generated Prime is %lld\n",p);
            printf("Randomly Generated Generator g is %lld\n",g);
            break;
    case 2: printf("Enter Prime p\n");
            scanf("%lld",&p);
            printf("Enter Generator g\n");
            scanf("%lld",&g);
            break;

}
//printf("Randomly Generated Prime is %lld\n",p);
//printf("Randomly Generated Generator g is %lld\n",g);
flag=0;
while(flag==0){
k=rand();
if(k<p){
flag=gcd(k,p-1);
if(flag!=1)
    flag=0;
}
}
printf("Randomly Generated k is %lld\n",k);
printf("Enter the private key x for sender : \n");
scanf("%lld",&x);
printf("Enter the message m for sender which is less than p: \n");
scanf("%lld",&m);
while(m>p){
    printf("Previously entered value is greater than p \n Please,Enter the message m again for sender which is less than p: \n");
    scanf("%lld",&m);
}
alpha=modPow(g,x,p);
beta=modPow(g,k,p);
printf("Public key alpha(g^x mod p) is %lld\n",alpha);
printf("Public key beta(g^k mod p) is %lld\n",beta);
gcdExtended(k,p-1,&x1,&y1);
s=m-(beta*x);
s=s%(p-1);
s=s*x1;
s=s%(p-1);
if(s<0)
    s=s+(p-1);
printf("Signature is : %lld\n",s);
verify(alpha,beta,s,p,g);
return 0;
}
