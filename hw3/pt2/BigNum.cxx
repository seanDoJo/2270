// FILENAME: BigNum.cxx
// This is the implementation file of the BigNum class


#ifndef HW3_BIGNUM_CXX
#define HW3_BIGNUM_CXX
#include <algorithm>   // Provides copy function
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include "BigNum.h"
using namespace std;

namespace HW3
{
	BigNum::BigNum()
	{
		capacity = DEFAULT_CAPACITY;
		positive = true;
		digits = new unsigned int[capacity];
		digits[0] = 0;
		used = 1;
	}    

	BigNum::BigNum(int num)
	{
		if (num < 0)
		{
			positive = false;
			num = num / -1;
		}
		else
		{
			positive = true;
		}
		
		int i = 0;
		int numcop = num;
		bool raw = true;
		bool remainingnum = true;
		int num1 = 0;
		unsigned int num2 = 0;
		
		if (num == 0)
		{
			raw = false;
			remainingnum = false;
		}
			
		
		while (raw == true)
		{
			if (numcop == 0)
			{
				raw = false;
			}
			else
			{
				numcop = numcop / 10;
				i++;
			}
		}
		
		if (num == 0)
		{
			capacity = DEFAULT_CAPACITY;
			digits = new unsigned int[capacity];
			digits[0] = 0;
			used = 1;
		}
		else
		{
			used = 0;
			capacity = (unsigned int)i;
			digits = new unsigned int[capacity];
		}
		unsigned int counter = 0;
		
		while (remainingnum == true)
		{
			num1 = num % 10;
			num2 = (unsigned int)num1;
			digits[counter] = num2;
			counter++;
			used++;
			num = num / 10;
			
			if (num == 0)
			{
				remainingnum = false;
			}
		}
		//used = capacity;
	} 

	// Constructor that receives a string; leading 0's will be ignored
	BigNum::BigNum(const string& strin)
	{
		string strincp;
		if(strin[0] == '-')
		{
			strincp = strin.substr(1,(strin.length()-1));
			positive = false;
			capacity = (unsigned int)(strincp.length());//modded
			digits = new unsigned int[capacity];
			lowerbound = 0;
			used = 0;
		}
		else
		{
			strincp = strin;
			positive = true;
			capacity = (unsigned int)(strincp.length());
			digits = new unsigned int[capacity];
			lowerbound = 0;
			used = 0;
		}
		unsigned int counter = 0;
		for (unsigned int i = (capacity-1); i >= lowerbound; i--)
		{
			char b = strincp[i];
			int c = b - '0';
			unsigned int num = (unsigned int)c;
			digits[counter] = num;
			counter++;
			used++;
			if (i == lowerbound)
			{
				break;
			}
		}
		trim();
		//used = capacity;
			
	}
 
    BigNum::BigNum(const BigNum& anotherBigNum)
    {
		positive = anotherBigNum.positive;
		lowerbound = anotherBigNum.lowerbound;
		capacity = anotherBigNum.capacity;
		digits = new unsigned int[capacity];
		used = anotherBigNum.used;
		for (unsigned int i = 0; i < capacity; i++)
		{
			digits[i] = anotherBigNum.digits[i];
		}
    }

    BigNum::~BigNum()
    {
		delete [] digits;
    }
    
    void BigNum::resize(unsigned int n)
	{
		unsigned int* oldarray = digits;
		digits = new unsigned int[n];
		for (unsigned int i = 0; i <= capacity-1; i++)
		{
			digits[i] = oldarray[i];
		}
		delete [] oldarray;
	}

	BigNum& BigNum::operator=(const BigNum& anotherBigNum)
	{
		if (&anotherBigNum == this){
			return *this;
		}
		else
		{
			positive = anotherBigNum.positive;
			lowerbound = anotherBigNum.lowerbound;
			capacity = anotherBigNum.capacity;
			resize(capacity);
			used = anotherBigNum.used;
			for (unsigned int i = 0; i < capacity; i++)
			{
				digits[i] = anotherBigNum.digits[i];
			}
			
			return *this;
		}
	}

  
	BigNum& BigNum::operator+=(const BigNum& addend)  
	{
		*this = *this + addend;
		return *this;
	}

	BigNum& BigNum::operator-=(const BigNum& subtractand)
	{
		*this = *this - subtractand;
		return *this;
	}

	BigNum& BigNum::operator*=(const BigNum& multiplicand)
	{
		*this = *this * multiplicand;
		return *this;
	}

	BigNum& BigNum::operator/=(const BigNum& divisor)
	{
		*this = *this / divisor;
		return *this;
	}

	BigNum& BigNum::operator%=(const BigNum& divisor)
	{
		*this = *this % divisor;
		return *this;
	}

	BigNum& BigNum::operator++()
	{
		BigNum adder = 1;
		*this = *this + adder;
		return *this;
	}

	BigNum& BigNum::operator--()
	{
		BigNum minus = 1;
		*this = *this - minus;
		return *this;
	}

	BigNum& BigNum::diff(const BigNum& a, const BigNum& b)
	{
		BigNum A = a;
		BigNum B = b;
		BigNum zerocomp;
		zerocomp.positive = false;
		bool broken;
		//cout << "made the copies" << endl;
		if (capacity <= a.used && a.used >= b.used)
		{
			while(capacity <= a.used)
			{
				resize(capacity*2);
				capacity *= 2;
			}
		}
		else if (capacity <= b.used && b.used >= a.used)
		{
			while(capacity <= b.used)
			{
				resize(capacity + b.used);
				capacity *= 2;
			}
		}
		used = 0;
		//unsigned int indexpz = 0;
		
		if (a >= b)
		{
			for (unsigned int i = 0; i < a.used; i++)
			{
				if (i >= b.used)
				{
					digits[i] = A.digits[i];
					used++;
				}
				else if (A.digits[i] < B.digits[i])
				{
					
					if (A.digits[i] == 0)
					{
						broken = false; //check this if not working
						for (unsigned int x = i; x < A.used; x++)
						{
							if (broken == true)
							{
								break;
							}
							if (A.digits[x] > 0)
							{
								A.digits[x] = A.digits[x] - 1;
								for (unsigned int z = (x-1); z >= i; z--)
								{
									if(z == i)
									{
										A.digits[z] = A.digits[z] + 10;
										broken = true;
										break;
									}
									else
									{
										A.digits[z] = 9;
									}
								}
							}
						}
					}
					else
					{
						broken = false;
						for (unsigned int x = (i+1); x < A.used; x++)
						{
							if (broken == true)
							{
								break;
							}
							if (A.digits[x] > 0)
							{
								A.digits[x] = A.digits[x] - 1;
								for (unsigned int z = (x-1); z >= i; z--)
								{
									if (z == i)
									{
										A.digits[z] = A.digits[z] + 10;
										broken = true;
										break;
									}
									else
									{
										A.digits[z] = 9;
									}
								}
							}
						}
					}
					digits[i] = A.digits[i] - B.digits[i];
					used++;
				}
				else
				{
					digits[i] = A.digits[i] - B.digits[i];
					used++;
				}
			}
		}
		trim();
		if (*this == zerocomp)
		{
			positive = true;
		}
		return *this;
	}
  

	BigNum& BigNum::mult(const BigNum& a, const BigNum& b)
	{
		BigNum acop = a;
		BigNum bcop = b;
		acop.positive = true;
		bcop.positive = true;
		unsigned int numarrays;
		BigNum* addarrays;
		int counter = 0;
		unsigned int next = 0;
		unsigned int placeh;
		unsigned int place;
		BigNum finalnum;
		numarrays = b.used;
		addarrays = new BigNum[numarrays];
		if (a >= b)
		{
			for (unsigned int i = 0; i < b.used; i++)
			{
				addarrays[i].used = 0;
				if (counter > 0)
				{
					for (int j = 0; j < counter; j++)
					{
						//cout << "added zero" << endl; //debugging
						addarrays[i].digits[j] = 0;
						addarrays[i].used++;
						if (addarrays[i].used >= addarrays[i].capacity)
						{
							addarrays[i].resize((addarrays[i].capacity) * 2);
							addarrays[i].capacity = (addarrays[i].capacity) * 2;
						}
					}
				}
				
				for (unsigned int x = 0; x < a.used; x++)
				{
					placeh = (acop.digits[x] * bcop.digits[i]) + next;
					place = placeh % 10;
					next = placeh / 10;
					addarrays[i].digits[x + counter] = place;
					addarrays[i].used++;
					//cout << addarrays[i].digits[x + counter] << endl; //debugging
					if (addarrays[i].used >= addarrays[i].capacity)
					{
						addarrays[i].resize((addarrays[i].capacity) * 2);
						addarrays[i].capacity = (addarrays[i].capacity) * 2;
					}
				}
				addarrays[i].digits[addarrays[i].used] = next;
				addarrays[i].used++;
				addarrays[i].trim();
				counter++;
				next = 0;
			}
			for (unsigned int i = 0; i < b.used; i++)
			{
				finalnum = finalnum + addarrays[i];
				//cout << "finalnum " << i << " " << finalnum << endl; //debugging
			}
			*this = finalnum;
			delete [] addarrays;
			//cout << *this << endl; //debugging
			
		}
			
		return *this;
	}
	
	BigNum& BigNum::sum(const BigNum& a, const BigNum& b) 
	{
		BigNum acop = a;
		acop.positive = true;
		BigNum bcop = b;
		bcop.positive = true;
		if (capacity <= a.used && a.used >= b.used)
		{
			while (capacity <= a.used)
			{
				resize(capacity + 10);
				capacity += 10;
			}
		}
		else if (capacity <= b.used && b.used >= a.used)
		{
			while (capacity <= b.used)
			{
				resize(capacity + 10);
				capacity += 10;
			}
		}
		
		used = 0;
		positive = true;
		unsigned int placeh = 0;
		unsigned int next = 0;
		unsigned int place = 0;
		
		if (acop >= bcop)
		{
			for (unsigned int i = 0; i < a.used; i++)
			{
				if (i >= b.used)
				{
					placeh = (a.digits[i]) + next;
					place = placeh % 10;
					next = ((int)placeh)/10;
					digits[i] = place;
					used++;
				}
				else
				{
					placeh = ((a.digits[i]) + next) + b.digits[i];
					place = placeh % 10;
					digits[i] = place;
					next = ((int)placeh)/10;
					used++;
				}
				
			}
			digits[used] = next;
			used++;
			trim();
		}
		else
		{
			for (unsigned int i = 0; i < b.used; i++)
			{
				if (i >= a.used)
				{
					placeh = (b.digits[i]) + next;
					place = placeh % 10;
					next = ((int)placeh)/10;
					digits[i] = place;
					used++;
				}
				else
				{
					placeh = (b.digits[i] + next) + a.digits[i];
					place = placeh % 10;
					digits[i] = place;
					next = ((int)placeh)/10;
					used++;
				}
			}
			digits[used] = next;
			used++;
			trim();
		}	
				
		return *this;
	}
	

	BigNum operator+(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		if (a.positive == true && b.positive == true)
		{
			result.sum(a, b);
		}
		else if (a.positive == false && b.positive == true)
		{
			BigNum acop = a;
			acop.positive = true;
			if (acop == b)
			{
				result.positive = true;
			}
			else if (acop > b)
			{
				result.diff(acop, b); //b - a
				result.positive = false;
			}
			else if (acop < b)
			{
				result.diff(b, acop);
				result.positive = true;
			}
		}
		else if (a.positive == true && b.positive == false)
		{
			BigNum bcop = b;
			bcop.positive = true;
			if (bcop == a)
			{
				result.positive = true;
			}
			else if (bcop > a)
			{
				result.diff(bcop, a); //a - b
				result.positive = false;
			}
			else if (bcop < a)
			{
				result.diff(a, bcop);
				result.positive = true;
			}
		}
		else if (a.positive == false && b.positive == false)
		{
			BigNum acop = a;
			BigNum bcop = b;
			acop.positive = true;
			bcop.positive = true;
			
			result.sum(acop, bcop);
			result.positive = false;
		}
		if (result == 0)
		{
			result.positive = true;
		}
		return result;
	}

	BigNum operator-(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		if (a.positive == true && b.positive == true)
		{
			if (a == b)
			{
				result.positive = true;
			}
			else if (a < b)
			{
				result.diff(b, a);
				result.positive = false;
			}
			else
			{
				result.diff(a, b);
				result.positive = true;
			}
		}
		else if (a.positive == true && b.positive == false)
		{
			if (a > b)
			{
				result.sum(a, b);
			}
			else
			{
				result.sum(b, a);
			}
			result.positive = true;
		}
		else if (a.positive == false && b.positive == true)
		{
			BigNum acop = a;
			acop.positive = true;
			result.sum(acop, b);
			result.positive = false;
		}
		else if (a.positive == false && b.positive == false)
		{
			BigNum acop = a;
			BigNum bcop = b;
			acop.positive = true;
			bcop.positive = true;
			
			if (acop == bcop)
			{
				result.positive = true;
			}
			else if (acop < bcop)
			{
				result.diff(bcop, acop);
			}
			else if (acop > bcop)
			{
				result.diff(acop, bcop);
				result.positive = false;
			}
		}
		return result;
	}
      
	BigNum operator*(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		BigNum acop = a;
		BigNum bcop = b;
		acop.positive = true;
		bcop.positive = true;
		if ((a.positive == true && b.positive == true) || (a.positive == false && b.positive == false))
		{
			if (acop >= bcop)
			{
				result.mult(acop, bcop);
			}
			else
			{
				result.mult(bcop, acop);
			}
		}
		else
		{
			if (acop >= bcop)
			{
				result.mult(acop, bcop);
			}
			else
			{
				result.mult(bcop, acop);
			}
			result.positive = false;
		}
		return result;
	}

	BigNum operator / (const BigNum& a, const BigNum& b)
	{
		BigNum result;
		BigNum comp = 0;
		BigNum acop = a;
		acop.positive = true;
		BigNum bcop = b;
		bcop.positive = true;
		BigNum counter = 0;
		
		if ((a.positive == true && b.positive == true) || (a.positive == false && b.positive == false))
		{
			while(acop >= comp)
			{
				acop = acop - bcop;
				result = counter;
				++counter;
			}
		}
		else
		{
			while(acop >= comp)
			{
				acop = acop - bcop;
				result = counter;
				++counter;
			}
			result.positive = false;
		}
		return result;
	}


	BigNum operator%(const BigNum& a, const BigNum& b)
	{
		BigNum acop = a;
		BigNum bcop = b;
		acop.positive = true;
		bcop.positive = true;
		BigNum result = acop;
		BigNum div;
		
		div = acop / bcop;
		
		for (BigNum i = 0; i < div; ++i)
		{
			result = result - bcop;
		}
		return result;
	}

	bool operator>(const BigNum& a, const BigNum& b)
	{
		if (a == b)
		{
			return false;
		}
		else if (a.positive == true && b.positive == false)
		{
			return true;
		}
		else if (a.positive == false && b.positive == true)
		{
			return false;
		}
		
		
		if (a.used > b.used)
		{
			return true;
		}
		else if (a.used < b.used)
		{
			return false;
		}
		else
		{
			for (unsigned int i = (a.used-1); i >= 0; i--)
			{
				if (a.digits[i] > b.digits[i])
				{
					return true;
				}
				else if (a.digits[i] < b.digits[i])
				{
					return false;
				} 
				if (i == 0)
				{
					break;
				}
			}
			return false;
		}
	}


	bool operator>=(const BigNum& a, const BigNum& b)
	{
		if (a > b)
			return true;
		else if (a == b)
			return true;
		else
			return false;
	}


	bool operator<(const BigNum& a, const BigNum& b)
	{
		if (a == b)
		{
			return false;
		}
		else
		{
			return (!(a > b));
		}
	}


	bool operator<=(const BigNum& a, const BigNum& b)
	{
		if (a < b)
		{
			return true;
		}
		else if (a == b)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	bool operator==(const BigNum& a, const BigNum& b)
	{
		if (a.positive == true && b.positive == false)
		{
			return false;
		}
		else if (a.positive == false && b.positive == true)
		{
			return false;
		}
		
		
		if (a.used > b.used)
		{
			return false;
		}
		else if (a.used < b.used)
		{
			return false;
		}
		else
		{
			for (unsigned int i = (a.used-1); i >= 0; i--)
			{
				if (a.digits[i] > b.digits[i])
				{
					return false;
				}
				else if (a.digits[i] < b.digits[i])
				{
					return false;
				}
				
				if (i == 0)
				{
					break;
				}
			}
			return true;
		}
	}


	bool operator!=(const BigNum& a, const BigNum& b)
	{
		return (!(a == b));
	}

	// trim leading zeros
	void BigNum::trim()
	{
		if (used > 1)
		{
			for(int i = (used-1); i >= 0; i--)
			{
				if(digits[i] == 0 && used > 1)
				{
					unsigned int* newer = digits;
					used--;
					digits = new unsigned int[capacity];
					for (int i = (used-1); i >= 0; i--)
					{
						digits[i] = newer[i];
					}
					delete [] newer;
				}
				else
				{
					break;
				}
			}
		}
	}
	void BigNum::printer()
	{
		if(positive)
		{
			cout << "Capacity: " << capacity << endl;
			for(unsigned int i = 0;i<capacity;i++)
			{
				cout << digits[i];
			}
			cout << endl;
		}
		else
		{
			cout << "Capacity: " << capacity << endl;
			cout << "-";
			for(unsigned int i = 0;i<capacity;i++)
			{
				cout << digits[i];
			}
			cout << endl;
		}
			
	} 
	
	
	std::ostream& operator<<(std::ostream &os, const BigNum& bignum)
	{
		if (!(bignum.positive))
		{
			os << '-';
		}
		for (int i = (bignum.used-1); i >= 0; i--) 
		{
			os << bignum.digits[i];
			if (i == 0)
			{
				break;
			}
		}
		return os;
	}	 

	std::istream& operator>>(std::istream &is, BigNum& bignum)
	{
		string input;
		is >> input;
		
		delete [] bignum.digits;
		
		string strincp;
		if(input[0] == '-')
		{
			strincp = input.substr(1,(input.length()-1));
			bignum.positive = false;
			bignum.capacity = (unsigned int)(strincp.length());//modded
			bignum.digits = new unsigned int[bignum.capacity];
			bignum.lowerbound = 0;
		}
		else
		{
			strincp = input;
			bignum.positive = true;
			bignum.capacity = (unsigned int)(strincp.length());
			bignum.digits = new unsigned int[bignum.capacity];
			bignum.lowerbound = 0;
		}
		unsigned int counter = 0;
		for (unsigned int i = (bignum.capacity-1); i >= bignum.lowerbound; i--)
		{
			char b = strincp[i];
			int c = b - '0';
			unsigned int num = (unsigned int)c;
			bignum.digits[counter] = num;
			counter++;
			bignum.used = counter;
			if (i == bignum.lowerbound)
			{
				break;
			}
		}
		bignum.trim();
		return is;
	}
	
	BigNum factorial(const BigNum& a)
	{
		BigNum result = 1;
		const BigNum lower = 1;
		const BigNum there = 0;
		if (a == there)
		{
			result = 1;
			return result;
		}
		BigNum acop = a;
		result = acop * (acop - lower);
		--acop;
		while (acop > lower)
		{
			//cout << result << " * " << (acop - lower) << endl;
			result = result * (acop - lower);
			--acop;
		}
		return result;
    }
  }



#endif



