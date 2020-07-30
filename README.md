# Breaking-WeakTea-Cryptography

Convinced that block ciphers are made unnecessarily strong, Dr. Dimwit has designed his own block cipher WeakTea. 
It is an unashamed rip-off of the Tea cipher, with a 32-bit key and a 32-bit block size.

The key is supplied as two 16-bit numbers. The plaintext also comes as two 16-bit numbers, as does the ciphertext. 

However, concerned that the key may in fact be too small, he decides to use it in Double-WeakTea mode, doubly encrypting the plaintext with two different keys k1 and k2. In this way he hopes to get an effective key size of 64-bits.

Find the program weaktea.cpp.

When run with the correct key it produces this output

Plaintext (   1,   2)  Encoded= (18b1,b6ae)  Decoded= (   1,   2)
Plaintext (1234,5678)  Encoded= (4ad4,423d)  Decoded= (1234,5678)
Plaintext (6789,dabc)  Encoded= (de10,1250)  Decoded= (6789,dabc)
Plaintext (9abc,deff)  Encoded= (0b4e,111d)  Decoded= (9abc,deff)

However the key in the program has been removed…

    	k1[0]=0xXXXX;  // Find XXXX!
    	k1[1]=0x24XX;

    	k2[0]=0xXXXX;
    	k2[1]=0x27XX;

The mission is to recover both 32-bit keys, k1 and k2.


1.The approach would be to encrypt one of the plain texts using all the possible 32-bit key combinations possible. 
Hence the range of the keys would be from 00000000 to ffffffff. 
Once we are done, we would have the list of every cipher-key combination possible.

2.Then the corresponding cipher texted obtained after successfully encrypting twice needs to be considered. 
We then, decipher the final cipher text with every possible 32-bit key, in order to get the list of all the cipher-key combinations.

3.These two files need to be compared for the first column, i.e. the cipher. Then the corresponding keys are considered as the prospective candidates for the k1 and k2 keys.

4.These keys need to be picked and each of the plain texts provided in the initial document need to be encrypted twice, to check if they encrypt to give the final corresponding cipher text provided in the document.

5.If they match , those are the right k1 and k2 values.
For generation of the two files, i.e. the encrypt file and the decrypt file we make the use of a custom C++ library called as STXXL, which extends the usage of STL in C++. 
The program takes 10mins & 304mb each to generate sorted files with the hint applied. (Reference: www.stxxl.org)
The generation code is available in the Generation.cpp file.

Once both the files are generated, both the files need to be compared to get the prospective key pairs. 
This was achieved by using Apache Hadoop. I used pig and hive, to upload the large files into two tables and ran the following query to unload the file onto a file. 
The steps for which are available in the Hadoop.txt file

Now, once we have the prospective keys, they need to be used to encrypt all the available plain text in the document and check which one equals up to the corresponding cipher text for all the plain text – cipher text pairs.  
The code in final_comp.cpp or Comparion_java.java can be used to compare either in java or C++. 
The cpp code takes less than a min to obtain the final key combination and is faster than the java comparison.

Once the code completed execution, I got the following keys.

2408beef	2707dead

Once done, I cross verified my result by plugging in the keys onto the weaktea.cpp file to get the same output as specified in the document.

Plaintext ( 1, 2) Encoded= (18b1,b6ae) Decoded= ( 1, 2)

Plaintext (1234,5678) Encoded= (4ad4,423d) Decoded= (1234,5678)

Plaintext (6789,dabc) Encoded= (de10,1250) Decoded= (6789,dabc)

Plaintext (9abc,deff) Encoded= (0b4e,111d) Decoded= (9abc,deff)
