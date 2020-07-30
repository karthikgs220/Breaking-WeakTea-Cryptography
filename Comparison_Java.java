package test;

import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;

public class Comparison_Java {
	
	public static short[] p = new short[2];
	public static short[] c = new short[2];
	
	public static void encode(short[] v,  int[] k)
	{
		    short n=32, y=v[0],z=v[1], sum=0;
			short delta=(short) 0x9e37; 
			while (n-->0) 
			{                     
			  	sum += delta ;
			    y += ((z<<2)+k[0]) ^ (z+sum) ^ ((z>>3)+k[1]) ;
			    z += ((y<<2)+k[0]) ^ (y+sum) ^ ((y>>3)+k[1]) ; 
			} 
			v[0]=y ; v[1]=z ; 
	}

	public static void main(String[] args) throws IOException {

		System.out.println("Hello");

		
		Path path = Paths.get("D:\\xau");// ciphered text file path
		File file = new File("D:\\abc.txt");// deciphered text file path
		List<String> list = new ArrayList<String>();// list of string store  matching values
													
		Path file1 = Paths.get("D:\\res_test.txt");
		Path file2 = Paths.get("D:\\res_comtest.txt");// file for writing the result
		int lengthOfLine = 19;// length of each line including the tab
		RandomAccessFile randomAccessFile = new RandomAccessFile(file, "r");
	
		/**
		 * This uses lambda expression which takes each line of ciphered text
		 * and extracts the first column and performs binary search on the
		 * entire deciphered text file
		 */
		
		try (Stream<String> lines = Files.lines(path)) {
		
			lines.forEachOrdered(line -> {
				try {
					p[0]=(short) 0x0001;
				    p[1]=(short) 0x0002;
				    c[0]=(short) 0x18b1;
					c[1]=(short) 0xb6ae;
					long noOfLines = (randomAccessFile.length() / 19);
					long top = noOfLines;
					long middle;
					long bottom = 0;
					String search = line;
					String[] searchstring = search.split("\\t",2);
					while (bottom <= top) // binary search
					{
						middle = (bottom + top) / 2;
						randomAccessFile.seek(middle * lengthOfLine);
						String line1 = randomAccessFile.readLine();
						String col1[] = line1.split("\\t");// split by tab to  use the value of column 1
															
						int comparison = col1[0].compareTo(searchstring[0]);

						if (comparison == 0) {
							String output=searchstring[1]+"\t"+col1[1];
							list.add(output);
							Files.write(file2, list, StandardCharsets.UTF_8);
							System.out.println(searchstring[1]+"\n");

							String a=searchstring[1].substring(0,4);
							String b=searchstring[1].substring(4);
							System.out.println(a+"\t"+b+"\n");
							int[]k1= new int[2];
							k1[0]=(int)Long.parseUnsignedLong(b,16);
							k1[1]=(int)Long.parseUnsignedLong(a,16);
							
							System.out.println(col1[1]+"\n");

							String a1=col1[1].substring(0,4);
							String b1=col1[1].substring(4);
							System.out.println(a1+"\t"+b1+"\n");
							int[]k2= new int[2];
							k2[0]=(int)Long.parseUnsignedLong(b1,16);
							k2[1]=(int)Long.parseUnsignedLong(a1,16);
						
							encode(p,k1);
							encode(p,k2);
							System.out.println(p[0]+"\t"+p[1]+"\t"+String.format("0x%04x",p[0])+"\t"+String.format("0x%04x",p[1])+"\n");
							if (String.format("0x%04x",p[0]) == String.format("0x%04x",c[0]) && String.format("0x%04x",p[1]) == String.format("0x%04x",c[1]))
							{
								list.add(output);
								Files.write(file1, list, StandardCharsets.UTF_8);
							}
							break;
						} else if (comparison < 0) {
							bottom = middle + 1;
						} else {
							top = middle - 1;
						}

					}
					
				} catch (IOException e) {

				}

			});
			
			randomAccessFile.close();
			System.out.println("Finished");

		} 
		catch (IOException e) 
		{
			System.out.println("Exception");
		}

	}
}
