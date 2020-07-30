#include <iostream>
#include <fstream>
#include <string>

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

int main()
{
	ifstream fin; 
	string line;
	unsigned short k1[2],k2[2];
    unsigned short p[2],c[2];

	FILE *fp1;
 	errno_t err1 = fopen_s(&fp1,"D:/final1/final_result.txt","w+");

    fin.open("D:/result.txt"); 
  

    while (getline(fin, line)) { 

		p[0]=0x0001;
		p[1]=0x0002;
		c[0]=0x18b1;
		c[1]=0xb6ae;
        unsigned int line1=std::stoi (line.substr(0,8),nullptr,16);
		unsigned int line2=std::stoi (line.substr(9,8),nullptr,16);

		k2[0]=(short)line1;
		k2[1]=(short)(line1 >> 16);
		k1[1]=(short)(line2 >> 16);
		k1[0]=(short)line2;

		encode(p,k1);

		encode(p,k2);

		if (p[0] == c[0])
		{
			if (p[1] == c[1])
			{
				p[0]=0x1234;
				p[1]=0x5678;
				c[0]=0x4ad4;
				c[1]=0x423d;
				encode(p,k1);
				encode(p,k2);
				if (p[0] == c[0])
				{
					if (p[1] == c[1])
					{
						p[0]=0x6789;
						p[1]=0xdabc;
						c[0]=0xde10;
						c[1]=0x1250;
						encode(p,k1);
						encode(p,k2);
						if (p[0] == c[0])
						{
							if (p[1] == c[1])
							{
								p[0]=0x9abc;
								p[1]=0xdeff;
								c[0]=0x0b4e;
								c[1]=0x111d;
								encode(p,k1);
								encode(p,k2);
								if (p[0] == c[0])
								{
									if (p[1] == c[1])
									{
											fprintf(fp1,"%04x\t%04x\t%04x\t%04x\n",k1[1],k1[0],k2[1],k2[0]);
									}
								}
							}
						}
					}
				}
			}
		
		}
	}
    fin.close(); 
	return 0;
}