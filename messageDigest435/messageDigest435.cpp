/***
   Jaron Smith 4203199
**/

#include <string.h>
#include <iostream>
#include <fstream>
#include "sha256.h"
#include "BigIntegerLibrary.hh"

 
int main(int argc, char *argv[])
{
   //Second part of your project starts here
   if (argc != 3 || (argv[1][0]!='s' && argv[1][0]!='v')) 
      std::cout << "wrong format! should be \"a.exe s filename\"";
   else {
      std::string filename = argv[2];
      
            
      //read the file
      std::streampos begin,end;
      std::ifstream myfile (filename.c_str(), std::ios::binary);
      begin = myfile.tellg();
      myfile.seekg (0, std::ios::end);
      end = myfile.tellg();
      std::streampos size = end-begin;
      std::cout << "size of the file: " << size << " bytes.\n"; //size of the file
      
      myfile.seekg (0, std::ios::beg);
      char * memblock = new char[size];
      myfile.read (memblock, size); //read file; it's saved in the char array memblock
      myfile.close();
      
      std::string copyOFfile = filename+".Copy"; 
      std::ofstream myfile2 (copyOFfile.c_str(), std::ios::binary);
      myfile2.write (memblock, size); //write to a file
      myfile2.close();
      
      std::cout<<memblock;
        
      if (argv[1][0]=='s') {
         std::cout << "\n"<<"Need to sign the doc.\n";
         std::string content_hash = sha256(memblock);
         BigUnsignedInABase hash(content_hash, 16);
         BigUnsigned hash_convert = hash;
         std::ifstream dn_file;
         dn_file.open(d_n.txt);
         std::string d_string, n_string;
         dn_file >> d_string;
         dn_file >> n_string;
         dn_file.close();

         BigUnsigned d = stringToBigUnsigned(d_string);
         BigUnsigned n = stringToBigUnsigned(n_string);

         BigUnsigned signature = modexp(hash_convert, d, n);

         std::ofstream sign;
         sign.open(filename+".signature");
         sign << signature << std::endl;
         sign.close();
         
      }
      else {
         std::cout << "\n"<<"Need to verify the doc.\n";
         std::string sign_file = argv[3];
         std::string content_hash = sha256(memblock);
         BigUnsignedInABase hash(content_hash, 16);
         BigUnsigned hash_convert = hash;
         std::ifstream sign;
         sign.open(sign_file);
         std::string signature;
         sign >> signature;
         sign.close();

         BigUnsigned sign_convert = stringToBigUnsigned(signature);

         std::ifstream en_file;
         en_file.open("e_n.txt");
         std::e_string;
         std::n_string;
         en_file >> e_string;
         en_file >> n_string;
         en_file.close();

         BigUnsigned e = stringToBigUnsigned(e_string);
         BigUnsigned n = stringToBigUnsigned(n_string);


         BigUnsigned encrypt = modexp(sign_convert, e, n);
         if(encrypt == hash_convert)
         {
         	std::cout << "Document is authentic." << std::endl;
         }

         else
         {
         	std::cout << "Document has been altered." << std::endl; 
         }
  
      }
      delete[] memblock;
    }
    return 0;
}