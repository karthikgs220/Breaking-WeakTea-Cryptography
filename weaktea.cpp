// WeakTea Block Cipher
// Compile as
// g++ -O2 weaktea.cpp -o weaktea
// or
// cl /O2 weaktea.cpp
//
// (c) Dr. Dimwit 2010
//

#include <stdio.h>

using namespace std;

void encode(unsigned short* v, unsigned short* k)  {              
unsigned short n=32, y=v[0],z=v[1], sum=0, 
delta=0x9e37; /* a key schedule constant */
while (n-->0) 
{                     
  	sum += delta ;
    y += ((z<<2)+k[0]) ^ (z+sum) ^ ((z>>3)+k[1]) ;
    z += ((y<<2)+k[0]) ^ (y+sum) ^ ((y>>3)+k[1]) ; 
} 
v[0]=y ; v[1]=z ; }


void decode(unsigned short* v,unsigned short* k)  {
unsigned short n=32, sum, y=v[0], z=v[1],
delta=0x9e37 ;
sum=delta<<5;
while (n-->0) 
{
    z-= ((y<<2)+k[0]) ^ (y+sum) ^ ((y>>3)+k[1]) ; 
    y-= ((z<<2)+k[0]) ^ (z+sum) ^ ((z>>3)+k[1]) ;
   	sum-=delta ;  
}
v[0]=y ; v[1]=z ;  }

int main(int argc, char *argv[])
{
    unsigned short k1[2],k2[2];
    unsigned short p[2],c[2];

    k1[0]=0xXXXX;
    k1[1]=0xXXXX;

    k2[0]=0xXXXX;
    k2[1]=0xXXXX;

    p[0]=0x0001;
    p[1]=0x0002;

    printf("Plaintext (%04x,%04x)",p[0],p[1]);

/* double encrypt */

    encode(p,k1);
    encode(p,k2);
    
    printf("  Encoded= ");
    printf("(%04x,%04x)",p[0],p[1]);

/* double decrypt */

    decode(p,k2);
    decode(p,k1);

    printf("  Decoded= ");
    printf("(%04x,%04x)\n",p[0],p[1]);

    
    p[0]=0x1234;
    p[1]=0x5678;

    printf("Plaintext (%04x,%04x)",p[0],p[1]);

    encode(p,k1);
    encode(p,k2);

    printf("  Encoded= ");
    printf("(%04x,%04x)",p[0],p[1]);

    decode(p,k2);
    decode(p,k1);

    printf("  Decoded= ");
    printf("(%04x,%04x)\n",p[0],p[1]);

    p[0]=0x6789;
    p[1]=0xDABC;

    printf("Plaintext (%04x,%04x)",p[0],p[1]);

    encode(p,k1);
    encode(p,k2);
    
    printf("  Encoded= ");
    printf("(%04x,%04x)",p[0],p[1]);

    decode(p,k2);
    decode(p,k1);

    printf("  Decoded= ");
    printf("(%04x,%04x)\n",p[0],p[1]);

    p[0]=0x9ABC;
    p[1]=0xDEFF;

    printf("Plaintext (%04x,%04x)",p[0],p[1]);

    encode(p,k1);
    encode(p,k2);

    printf("  Encoded= ");
    printf("(%04x,%04x)",p[0],p[1]);

    decode(p,k2);
    decode(p,k1);

    printf("  Decoded= ");
    printf("(%04x,%04x)\n",p[0],p[1]);

    return 0;
}
