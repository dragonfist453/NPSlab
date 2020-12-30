#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

long int gcd(long int a, long int b)
{
if(a == 0)
return b;
if(b == 0)
return a;
return gcd(b, a%b);
}

long int isprime(long int a)
{
int i;
for(i = 2; i< a; i++){
if((a % i) == 0)
return 0;
    }
return 1;
}

long int encrypt(char ch, long int n, long int e)
{
int i;
long int temp = ch;
for(i = 1; i< e; i++)
temp = (temp * ch) % n;
return temp;
}

char decrypt(long int ch, long int n, long int d)
{
int i;
long int temp = ch;
for(i = 1; i< d; i++)
ch =(temp * ch) % n;
return ch;
}

int main()
{
long int i, len;
long int p, q, n, phi, e, d, cipher[50];
char text[50];
srand(time(0));

//cout<< "Enter the text to be encrypted: ";
printf("Enter the text to be encrypted: ");
//cin.getline(text, sizeof(text));
gets(text);
len = strlen(text);
do {
        p = rand() % 1000;
    } while (!isprime(p));
do {
        q = rand() % 1000;
    } while (!isprime(q));
    n = p * q;
phi = (p - 1) * (q - 1);
do {
        e = rand() % phi;
    } while (gcd(phi, e) != 1);
do {
        d = rand() % phi;
    } while (((d * e) % phi) != 1);
//cout<< "Two prime numbers (p and q) are: " << p << " and " << q <<endl;
//cout<< "n(p * q) = " << p << " * " << q << " = " << p*q <<endl;
//cout<< "(p - 1) * (q - 1) = "<< phi <<endl;
//cout<< "Public key (n,  e): (" << n << ", " << e << ")\n";
//cout<< "Private key (n, d): (" << n << ", " << d << ")\n";
printf("Two prime numbers (p and q) are: %ld and %ld\n",p,q);
printf("n(p * q) = %ld\n",p*q);
printf("(p - 1) * (q - 1) = %ld\n",phi);
printf("Public key (n,  e): (%ld,%ld)\n",n,e);
printf("Private key (n, d): (%ld,%ld)\n",n,d);
for (i = 0; i<len; i++)
cipher[i] = encrypt(text[i], n, e);
printf("Encrypted message: ");
for (i = 0; i<len; i++)
printf("%ld",cipher[i]);
for (i = 0; i<len; i++)
text[i] = decrypt(cipher[i], n, d);
printf("\n");
printf("Decrypted message: ");
for (i = 0; i<len; i++)
printf("%c",text[i]);
printf("\n");
return 0;
}