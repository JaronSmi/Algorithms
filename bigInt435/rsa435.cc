/*  
	Jaron Smith, Spring 2020, Algorithms
	4203199
*/


// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <fstream>
#include <ctime>
// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"


void generate_prime(BigUnsigned &, const int);
void new_random(BigUnsigned &, int);
void store_values(const BigUnsigned &, const BigUnsigned &, const char[]);
void generate_e(const BigUnsigned &, BigUnsigned &);
void display_value(const BigUnsigned &, const char[]);



int main(){

	//seed random generator
	unsigned seed = time(0);
	srand(seed);
	size_of_prime = 512;
	//generate p val
	BigUnsigned p = BigUnsigned(1);
	generate_prime(p, size_of_prime);

	BigUnsigned q = BigUnsigned(1);
	generate_prime(q, size_of_prime);

	display_value(p, "p");
	display_value(q, "q");
	store_values(p, q, "p_q.txt");

	BigUnsigned n = p * q;
	display_value(n, 'n');
	BigUnsigned phi_n = (p-1) * (q-1);
	display_value(phi_n, "phi of n");

	BigUnsigned e = 13;
	generate_e(phi_n, e);
	store_values(e, n, "e_n.txt");
	display_value(e, "e");
	BigUnsigned d = modinv(e, phi_n);
	display_value(d, "d");

	store_values(d, n, "d_n.txt");



	/*try {
		      
      std::cout << "a couple of test cases for 3460:435/535 Algorithms!!!\n";
      BigUnsigned big1 = BigUnsigned(1);
      for (int i=0;i<400;i++) {
         big1 = big1*10 +rand();
      }
      std::cout << "my big1 !!!\n";
      std::cout << big1;
      BigUnsigned big2 = BigUnsigned(1);
      for (int i=0;i<400;i++) {
         big2 = big2*10 +rand();
      }
      std::cout << "my big2 !!!\n";
      std::cout << big2;
      std::cout << "my big3 = big1*big2 !!!\n";
      BigUnsigned big3 = big1*big2;
      std::cout <<big3;
      std::cout << "my big3/big2 !!!\n";
      std::cout <<big3/big2;
      
	} catch(char const* err) {
		std::cout << "The library threw an exception:\n"
			<< err << std::endl;
	}*/

	return 0;
}

void generate_prime(BigUnsigned &, const int);
void new_random(BigUnsigned &, int);
void store_values(const BigUnsigned &a, const BigUnsigned &b, const char file[])
{
	std::ofstream output;
	output.open((file);
	output << a << "\n";
	output << b;
	output.close();
}
void generate_e(const BigUnsigned &phi_n, BigUnsigned &e)
{
	while((gcd(phi_n, e) !=1) && (e < phi_n))
	{
		++e;
	}
}
void display_value(const BigUnsigned &a, const char var[])
{
	std::cout << "The value of " << var << "is:: \n"<<
			  << value << std::endl;
}