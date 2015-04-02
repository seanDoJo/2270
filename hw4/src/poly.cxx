#include "poly.h"
using namespace std;

namespace main_savitch_5
{
	polynomial::polynomial(double c, unsigned int exponent)
	{
		// store machine epsilon
		EPSILON = std::numeric_limits<double>::epsilon();
		if (c == 0 && exponent  == 0)
		{
			head_ptr = new polynode();
			tail_ptr = nullptr;
			recent_ptr = head_ptr;
			current_degree = 0;
		}
		else if (c != 0 && exponent == 0)
		{
			head_ptr = new polynode(c,0);
			tail_ptr = nullptr;
			recent_ptr = head_ptr;
			current_degree = 0;
		}
		else if (c == 0 && exponent > 0)
		{
			head_ptr = new polynode();
			tail_ptr = nullptr;
			recent_ptr = head_ptr;
			current_degree = 0;
			
		}
		else if (c!= 0 && exponent > 0)
		{
			head_ptr = new polynode();
			tail_ptr = new polynode(c, exponent);
			head_ptr -> set_back(nullptr);
			head_ptr -> set_fore(tail_ptr);
			tail_ptr -> set_fore(nullptr);
			tail_ptr -> set_back(head_ptr);
			assign_coef(c, exponent);
			recent_ptr = tail_ptr;
			current_degree = exponent;
		}

    }

    polynomial& polynomial::operator=(const polynomial& source)
    {
		// store machine epsilon
		EPSILON = std::numeric_limits<double>::epsilon();
		// write the rest
		if (this == &source)
		{
			return *this;
		}
		clear();
		polynode* copyptr = source.head_ptr;
		polynode* nextnode;
		double c;
		int x;
		head_ptr -> set_coef(copyptr -> coef());
		recent_ptr = head_ptr;
		current_degree = 0;
		copyptr = copyptr -> fore();
		while (current_degree < source.current_degree)
		{
			c = copyptr -> coef();
			x = copyptr -> exponent();
			nextnode = new polynode(c, x);
			nextnode -> set_back(recent_ptr);
			nextnode -> set_fore(nullptr);
			recent_ptr -> set_fore(nextnode);
			current_degree = x;
			recent_ptr = recent_ptr -> fore();
			if (copyptr != source.tail_ptr)
			{
				copyptr = copyptr -> fore();
			}
		}
		tail_ptr = recent_ptr;
		copyptr = new polynode();
		nextnode = new polynode();
		delete copyptr;
		delete nextnode;
		return *this;
	}
	
    polynomial::polynomial(const polynomial& source)
    {
		// store machine epsilon
		EPSILON = std::numeric_limits<double>::epsilon();
		// write the rest
		polynode* copyptr = source.head_ptr;
		polynode* nextnode;
		double c;
		int x;
		head_ptr = new polynode();
		head_ptr -> set_back(nullptr);
		head_ptr -> set_fore(nullptr);
		head_ptr -> set_coef(copyptr -> coef());
		recent_ptr = head_ptr;
		current_degree = 0;
		copyptr = copyptr -> fore();
		while (current_degree < source.current_degree)
		{
			c = copyptr -> coef();
			x = copyptr -> exponent();
			nextnode = new polynode(c, x);
			nextnode -> set_back(recent_ptr);
			nextnode -> set_fore(nullptr);
			recent_ptr -> set_fore(nextnode);
			current_degree = x;
			recent_ptr = recent_ptr -> fore();
			if (copyptr != source.tail_ptr)
			{
				copyptr = copyptr -> fore();
			}
		}
		tail_ptr = recent_ptr;
		copyptr = new polynode();
		nextnode = new polynode();
		delete copyptr;
		delete nextnode;
			
    }

    polynomial::~polynomial()
    {
		clear();
		delete head_ptr;
		head_ptr = nullptr;
		tail_ptr = nullptr;
		recent_ptr = nullptr;
    }

    void polynomial::clear()
    {
		set_recent(current_degree);
		tail_ptr = nullptr;
		while (recent_ptr != head_ptr)
		{
			polynode* deleteable = recent_ptr;
			recent_ptr = recent_ptr -> back();
			delete deleteable;
		}
		head_ptr -> set_fore(nullptr);
		head_ptr -> set_coef(0);
		current_degree = 0;
    }
    
    double polynomial::coefficient(unsigned int exponent) const
    {
		double returnable;
		if (exponent > current_degree)
		{
			return 0;
		}
		else
		{
			set_recent(exponent);
			if (recent_ptr -> exponent() != exponent)
			{
				return 0;
			}
			else
			{
				return recent_ptr -> coef();
			}
		}
		return returnable;
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent)
    {
		
		if (amount == 0)
		{
		}
		else if (exponent == 0)
		{
			double c = amount + (head_ptr -> coef());
			head_ptr -> set_coef(c);
		}
		else if (amount != 0 && exponent > 0)
		{
			set_recent(exponent);
			double c;
			if (recent_ptr -> fore() == nullptr && recent_ptr -> exponent() != exponent)
			{
				polynode* nextpoly = new polynode(amount, exponent);
				nextpoly -> set_fore(nullptr);
				nextpoly -> set_back(recent_ptr);
				recent_ptr -> set_fore(nextpoly);
				current_degree = exponent;
				tail_ptr = nextpoly;
				nextpoly = new polynode();
				set_recent(exponent);
			}
			else if (recent_ptr -> fore() == nullptr)
			{
				c = amount + (tail_ptr -> coef());
				if (c == 0.0)
				{
					assign_coef(0, exponent);
				}
				else
				{
					tail_ptr -> set_coef(c);
				}
			}
			else if (recent_ptr -> exponent() < exponent)
			{
				polynode* nextpoly = new polynode(amount, exponent);
				nextpoly -> set_fore(recent_ptr -> fore());
				nextpoly -> set_back(recent_ptr);
				recent_ptr -> fore() -> set_back(nextpoly);
				recent_ptr -> set_fore(nextpoly);
				nextpoly = new polynode();
				set_recent(exponent);
			}
			else
			{
				c = amount + (recent_ptr -> coef());
				if (c == 0)
				{
					assign_coef(0, exponent);
						
				}
				else
				{	
					recent_ptr -> set_coef(c);
				}
			}
		}
			
				
				
		
	}

    void polynomial::assign_coef(double coefficient, unsigned int exponent)
    {
		if (coefficient == 0 && exponent > current_degree)
		{
		}
		else if (coefficient != 0 && exponent > 0)
		{
			set_recent(exponent);
			if (recent_ptr -> fore() == nullptr && recent_ptr -> exponent() < exponent)
			{
				polynode* nextpoly = new polynode(coefficient,exponent);
				nextpoly -> set_fore(nullptr);
				nextpoly -> set_back(recent_ptr);
				recent_ptr -> set_fore(nextpoly);
				current_degree = exponent;
				tail_ptr = nextpoly;
				nextpoly = new polynode();
				set_recent(exponent);
			}
			else if (recent_ptr -> fore() == nullptr)
			{
				tail_ptr -> set_coef(coefficient);
			}
			else if (recent_ptr -> exponent() < exponent)
			{
				polynode* nextpoly = new polynode(coefficient,exponent);
				nextpoly -> set_fore(recent_ptr -> fore());
				nextpoly -> set_back(recent_ptr);
				recent_ptr -> fore() -> set_back(nextpoly);
				recent_ptr -> set_fore(nextpoly);
				recent_ptr = recent_ptr -> fore();
				nextpoly = new polynode();
			}
			
			else
			{
				recent_ptr -> set_coef(coefficient);
			}
		}
		else if (exponent == 0)
		{
			head_ptr -> set_coef(coefficient);
		}
		else if (coefficient == 0)
		{
			set_recent(exponent);
			if (recent_ptr -> exponent() != exponent)
			{
			}
			else if (recent_ptr -> fore() == nullptr)
			{
				polynode* deleteable = tail_ptr;
				tail_ptr = tail_ptr -> back();
				tail_ptr -> set_fore(nullptr);
				delete deleteable;
				recent_ptr = tail_ptr;
				current_degree = tail_ptr -> exponent();
			}
			else
			{
				polynode* deletable = recent_ptr;
				recent_ptr = recent_ptr -> back();
				recent_ptr -> set_fore(recent_ptr -> fore() -> fore());
				recent_ptr -> fore() -> set_back(recent_ptr);
				delete deletable;
			}
		}
				
			
    }

    unsigned int polynomial::next_term(unsigned int exponent) const
    {
		set_recent(exponent);
		if (recent_ptr -> fore() == nullptr)
		{
			return 0;
		}
		else
		{
			while (recent_ptr -> exponent() <= exponent)
			{
				recent_ptr = recent_ptr -> fore();
			}
		}
		return recent_ptr -> exponent();
    }

	unsigned int polynomial::previous_term(unsigned int exponent) const
    {
		set_recent(exponent);
		unsigned int returnable;
		if (exponent <= 0)
		{
			returnable = UINT_MAX;
		}
		else if (recent_ptr -> back() == nullptr)
		{
			returnable = UINT_MAX;
		}
		else
		{
			while (recent_ptr -> exponent() >= exponent)
			{
				recent_ptr = recent_ptr -> back();
			}
			if (recent_ptr -> coef() == 0)
			{
				returnable = UINT_MAX;
			}
			else
			{
				returnable = recent_ptr -> exponent();
			}
		}
		return returnable;
    }
    
    void polynomial::set_recent(unsigned int exponent) const
    {
		recent_ptr = head_ptr;
		while (recent_ptr -> exponent() < exponent)
		{
			if (exponent == 0)
			{
				recent_ptr = head_ptr;
			}
			else if (exponent >= current_degree)
			{
				if (tail_ptr == nullptr)
				{
					recent_ptr = head_ptr;
				}
				else
				{
					recent_ptr = tail_ptr;
				}
				break;
			}
			else if (recent_ptr -> exponent() == exponent)
			{
				break;
			}
			else if (recent_ptr -> fore() == nullptr)
			{
				break;
			}
			else
			{
				recent_ptr = recent_ptr -> fore();
				if (recent_ptr -> exponent() > exponent)
				{
					recent_ptr = recent_ptr -> back();
					break;
				}
			}
		}		
	}
    
    double polynomial::eval(double x) const
    {
		double total = 0;
		unsigned int expo = 0;
		double current;
		if (x == 0)
		{
		}
		else 
		{
			total = coefficient(expo);
			expo = next_term(expo);
			while (expo != 0)
			{
				current = x;
				for (unsigned int i = 1; i < expo; i++)
				{
					current = current * x;
				}
				current = current * (coefficient(expo));
				total += current;
				expo = next_term(expo);
			}
		}
		
		return total;
    }

    polynomial polynomial::derivative() const
    {
		polynomial p_prime;
		unsigned int expo2 = 0;
		unsigned int expo = 0;
		double c;
		do
		{
			c = expo * coefficient(expo);
			if (expo != 0)
			{
				expo2 = expo - 1;
			}
			p_prime.assign_coef(c, expo2);
			expo = next_term(expo);
		}
		while (expo != 0);
		return p_prime;
    }
    
    polynomial operator+(const polynomial& p1, const polynomial& p2)
    {
		polynomial p;
		unsigned int expo = 0;
		do
		{
			p.assign_coef(p2.coefficient(expo), expo);
			expo = p2.next_term(expo);
		}
		while (expo != 0);
		expo = 0;
		do
		{
			p.add_to_coef(p1.coefficient(expo), expo);
			expo = p1.next_term(expo);
		}
		while (expo != 0);
					 
		return p;
    }
    
    polynomial operator-(const polynomial& p1, const polynomial& p2)
    {
		polynomial p;
		unsigned int expo = 0;
		do
		{
			p.assign_coef(p1.coefficient(expo), expo);
			expo = p1.next_term(expo);
		}
		while (expo != 0);
		expo = 0;
		do
		{
			p.add_to_coef((p2.coefficient(expo) * -1), expo);
			expo = p2.next_term(expo);
		}
		while (expo != 0);
		return p;
    }
    
    polynomial operator*(const polynomial& p1, const polynomial& p2)
    {		
		polynomial p;
		unsigned int expo2 = 0;
		unsigned int expo1 = 1;
		double mult;
		unsigned int sum;
		do
		{
			do
			{
				mult = p2.coefficient(expo2) * p1.coefficient(expo1);
				sum = expo1 + expo2;
				p.add_to_coef(mult, sum);
				expo2 = p2.next_term(expo2);
			}
			while (expo2 != 0);
			expo1 = p1.next_term(expo1);
		}
		while (expo1 != 0);
		
		
		return p;
    }

    ostream& operator << (ostream& out, const polynomial& p)
    {
		unsigned int expo = 0;
		do
		{
			out << p.coefficient(expo) << "*x^" << expo;
			expo = p.next_term(expo);
			if (expo != 0) out << "+";
		}while(expo != 0);
		return out;
    }
    
    void polynomial::find_root(
	double& answer,
	bool& success,
	unsigned int& iterations,
	double guess,
	unsigned int maximum_iterations,
	double epsilon) const
    {
		iterations = 0;
		polynomial deriv = derivative();
		double prev = guess;
		while (iterations < maximum_iterations)
		{
			if (abs(deriv.eval(guess)) <= epsilon)
			{
				answer = guess;
				success = false;
				break;
			}
			else if (abs(eval(guess)) <= epsilon)
			{
				answer = guess;
				success = true;
				break;
			}
			else
			{
				prev = guess;
				guess = guess - ((eval(guess))/(deriv.eval(guess)));
				iterations ++;
			}
		}
		if (iterations >= maximum_iterations)
		{
			answer = prev;
			success = false;
			iterations = maximum_iterations;
		}
	}
}
