#include <iostream>
#include <limits>
#include <string>
#include <algorithm>
#include <stxxl/random>
#include <stxxl/sorter>
#include <stxxl.h>

using namespace std;

void encode(unsigned short* v, unsigned short* k)  {              
unsigned short n=32, y=v[0],z=v[1], sum=0, 
delta=0x9e37; 
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

struct cipher_entry {
    unsigned int ky;  // key
    unsigned int ct;  // cipher-text
	cipher_entry()
    { }
    cipher_entry(unsigned int _ky, unsigned int _ct)
        : ky(_ky), ct(_ct)
    { }
};  

struct plain_entry {
    unsigned int ky;  // key
    unsigned int pt;  // plain-text
	plain_entry()
    { }
    plain_entry(unsigned int _ky, unsigned int _pt)
        : ky(_ky), pt(_pt)
    { }
};  

struct Comparator
{
    bool operator () (const cipher_entry& a, const cipher_entry& b) const
    {
        return (a.ct < b.ct);
    }
    static cipher_entry min_value()
    {
		cipher_entry lowest;
		lowest.ky=std::numeric_limits<unsigned int>::min();
		lowest.ct=std::numeric_limits<unsigned int>::min();
        return lowest;
    }
    static cipher_entry max_value() 
    {
		cipher_entry highest;
		highest.ky=std::numeric_limits<unsigned int>::max();
		highest.ct=std::numeric_limits<unsigned int>::max();   
		return highest;
    }
};

struct Comparator1
{
    bool operator () (const plain_entry& a, const plain_entry& b) const
    {
        return (a.pt < b.pt);
    }
    static plain_entry min_value()
    {
		plain_entry lowest;
		lowest.ky=std::numeric_limits<unsigned short>::min();
		lowest.pt=std::numeric_limits<unsigned short>::min();
        return lowest;
    }
    static plain_entry max_value() 
    {
		plain_entry highest;
		highest.ky=std::numeric_limits<unsigned short>::max();
		highest.pt=std::numeric_limits<unsigned short>::max();   
		return highest;
    }
};

int main()
{

	typedef stxxl::vector<cipher_entry> vector;
	typedef stxxl::vector<plain_entry> vector1;
	vector vc1;
	vector1 vc2;
	cipher_entry my_vector;
	plain_entry my_vector1;
	unsigned short p[2];
	unsigned short c[2];
	unsigned short k1[2];
	unsigned short k2[2];

	FILE *fp;
	FILE *fp1;
	errno_t err = fopen_s(&fp,"D:/final2/cipher_key.txt","w+");
	errno_t err1 = fopen_s(&fp1,"D:/final2/plain_cipher.txt","w+");


   for (k1[1] = 0x2400; k1[1] <= 0x24ff; k1[1]++) 
	{
		for(k1[0] = 0x0000; k1[0] <= 0xffff; k1[0]++)
		{
			//printf("%d %d\n",k1[1],k1[0]);
			p[0]=0x0001;
			p[1]=0x0002;

			encode(p,k1);
			unsigned int complete2 = k1[0] | (k1[1] << 16);

			unsigned int complete1 = p[1] | ( p[0] << 16 ) ;
			my_vector.ky=complete2;
			my_vector.ct=complete1;

		 vc1.push_back(my_vector);
		 if (k1[0] == 0xffff)
		 {
			break;	 
		 }
		 
        }
		 if (k1[1] == 0x24ff)
		 {
			break;	 
		 }
	}
	for(k2[1] = 0x2700; k2[1] <= 0x27ff; k2[1]++) 
	{
		for(k2[0] = 0x0000; k2[0] <= 0xffff; k2[0]++)
		{
			c[0]=0x18b1;
			c[1]=0xb6ae;
			decode(c,k2);
			unsigned int complete2 = k2[0] | (k2[1] << 16);
			unsigned int complete1 = c[1] | (c[0] << 16);
			my_vector1.ky=complete2;
			my_vector1.pt=complete1;

		 vc2.push_back(my_vector1);
		 if (k2[0] == 0xffff)
		 {
			break;	 
		 }
		 
        }
		 if (k2[1] == 0x27ff)
		 {
			break;	 
		 }
	}
	
	//unsigned long M = 1024 * 1024 * 1024;
	stxxl::sort(vc1.begin(), vc1.end(), Comparator(), 1024 * 1024 * 1024);

	stxxl::sort(vc2.begin(), vc2.end(), Comparator1(), 1024 * 1024 * 1024);
	 	
	//unsigned int i=0;
	for (vector::iterator iter = vc1.begin(); iter != vc1.end(); ++iter){
			fprintf(fp,"%08x\t%08x\n",(*iter).ct,(*iter).ky);
			//std::cout << std::hex << showbase << (*iter).ct <<"\t" << std::hex << showbase << (*iter).ky << "\n";
	}	
	 

	//short int j=0;
	 for (vector1::iterator iter1 = vc2.begin(); iter1 != vc2.end(); ++iter1){
			fprintf(fp1,"%08x\t%08x\n",(*iter1).pt,(*iter1).ky);
			//std::cout << std::hex << showbase << (*iter).ct <<"\t" << std::hex << showbase << (*iter).ky << "\n";
		
	 }
	
}