#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>

class bigint 
{
	private:
		std::string value;
	//0
		std::string add_string(const std::string &num1, const std::string &num2) const;
		unsigned long long String_to_Ull(const std::string &str) const;
		void remove_zeros();
	
	public:
	//1
		bigint();
		bigint(unsigned long long num);
		bigint(const std::string &str);
		bigint(const bigint& other);
	//2
		bigint& operator=(const bigint& other);
	//3
		bigint operator+(const bigint& other) const;
		bigint operator+(unsigned long long num) const;
		bigint& operator+=(const bigint& other);
		bigint& operator+=(unsigned long long num);
	//4
		bigint& operator++();
		bigint operator++(int);
	//5
		bigint operator<<(int shift) const;
		bigint operator>>(int shift) const;
		bigint& operator<<=(int shift);
		bigint& operator>>=(int shift);
	//6
		bigint operator<<(const bigint& shift) const;
		bigint operator>>(const bigint& shift) const;
		bigint& operator<<=(const bigint& shift);
		bigint& operator>>=(const bigint& shift);
	//7
		bool operator<(const bigint& shift) const;
		bool operator>(const bigint& shift) const;
		bool operator<=(const bigint& shift) const;
		bool operator>=(const bigint& shift) const;
		bool operator==(const bigint& shift) const;
		bool operator!=(const bigint& shift) const;
	//8
		friend std::ostream& operator<<(std::ostream& os, const bigint& bi);
};

#endif
