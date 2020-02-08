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


BigUnsigned& generate_prime(BigUnsigned&, const int);
BigUnsigned& new_random(BigUnsigned &, int);
void store_values(const BigUnsigned &, const BigUnsigned &, const char[]);
BigUnsigned& generate_e(const BigUnsigned &, BigUnsigned&);
void display_value(const BigUnsigned &, const char[]);



int main(){

	//seed random generator
	unsigned seed = time(0);
	srand(seed);
	int size_of_prime = 512;
	//generate p val
	BigUnsigned p_candidate = BigUnsigned(1);
	BigUnsigned p = generate_prime(p_candidate, size_of_prime);

	BigUnsigned q_candidate = BigUnsigned(1);
	BigUnsigned q =	generate_prime(q_candidate, size_of_prime);

	display_value(p, "p");
	display_value(q, "q");
	store_values(p, q, "p_q.txt");

	BigUnsigned n = p * q;
	display_value(n, "n");
	BigUnsigned phi_n = (p-1) * (q-1);
	display_value(phi_n, "phi of n");

	BigUnsigned e_candidate = 5;
	BigUnsigned e =	generate_e(phi_n, e_candidate);
	store_values(e, n, "e_n.txt");
	display_value(e, "e");
	BigUnsigned d = modinv(e, phi_n);
	display_value(d, "d");

	store_values(d, n, "d_n.txt");

	return 0;
}

BigUnsigned& generate_prime(BigUnsigned &candidate, const int size){
      std::cout << "Generating prime of size " << size << " bits...\n";
      BigUnsigned exponent;
      BigUnsigned base;
      BigUnsigned a = BigUnsigned(1);
      BigUnsigned result;
      bool isprime = false;
      // Iterate until a valid prime is generated
      while (!isprime)
      {
      	std::cout<< "Hello \n";
            do
            {
                  candidate = new_random(candidate, size);
                  std::cout << "new canidate found";
            } while (candidate % 2 == 0);
            // Conduct fermat test  with 3 different a values
            exponent = candidate - 1;
            for (int i = 0; i < 3; ++i)
            {
                  result = modexp(a, exponent, candidate);
                  // failed fermat, genereate new canidate
                  if (result != 1)
                  {
                  		i = i + 2;
                  }
                  if (i < 2)
                  {
                        // test with new a
                        a = new_random(a, (size-1));
                  }
                  // All 3 values of a passed
                  else
                  {
                        isprime = true;
                        return candidate;
                  }
            }
      }
}

BigUnsigned& new_random(BigUnsigned & candidate, int size)
{
      // constants for random number generation
      const int MIN_VAL = 1;
      const int MAX_VAL = 10;
      candidate = (rand() % (MAX_VAL - MIN_VAL + 1)) + MIN_VAL;
      for (int i = 1; i < size; i++)
      {
            candidate = candidate * 10 + ((rand() % (MAX_VAL - MIN_VAL + 1)) + MIN_VAL);
      }
      return candidate;

}
void store_values(const BigUnsigned &a, const BigUnsigned &b, const char file[])
	{
		std::ofstream output;
		output.open((file));
		output << a << "\n";
		output << b;
		output.close();
	}
BigUnsigned& generate_e(const BigUnsigned &phi_n, BigUnsigned &e)
{
	while((gcd(phi_n, e) !=1) && (e < phi_n))
	{
		e+=2;
	}
	return e;
}
void display_value(const BigUnsigned &a, const char var[])
{
	std::cout << "The value of " << var << "is:: \n"
			  << a << std::endl;
}