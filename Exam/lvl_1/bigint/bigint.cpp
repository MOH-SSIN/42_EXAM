#include "bigint.hpp"

//0
unsigned long long bigint::StringToNull(const std::string &str) const
{
    unsigned long long result;
    for (std::string::size_type i  = 0; i < str.size(); i++)
    {
        char c = str[i];
        if (!isdigit(c))
            throw std::invalid_argument("Error format !\n");
        result = result * 10 + (c - '0');
    }
    return (result);
}

void bigint::remove_zeros()
{
    while (value.size() > 1 && value[0] == '0') 
        value.erase(0,1);//Supprimer 1 caractère à partir de la position 0.
    
}

std::string bigint::add_string(const std::string &num1, const std::string &num2) const
{
    std::string result;
    int i = num1.size() - 1;   
    int j = num1.size() - 1;
    int carry = 0 ;

    while (i >= 0 || j >= 0 || carry)
    {
        int sum = carry;
        if (i >= 0)
            sum += num1[i--] - '0'; 
        if (j >= 0)
            sum += num2[j--] - '0'; 
        result += (sum % 10) + '0';
        carry = sum / 10;
    }
    std::reverse(result.begin(), result.end());
    return (result);
}


//1

bigint::bigint() : value("0") {}

bigint::bigint(unsigned long long num): value(std::to_string(num)){}

bigint::bigint(const std::string &str)
{
    remove_zeros();
}

bigint::bigint(const bigint &other) : value(other.value) {}


//2
bigint& bigint::operator=(const bigint &other)
{
    if (this != &other)
        value = other.value;
    return (*this);
}

//3
bigint bigint::operator+(const bigint &other) const
{
    return bigint(add_string(value, other.value));
}

bigint bigint::operator+(unsigned long long num) const
{
    return (*this + bigint(num));
}

bigint& bigint::operator+=(const bigint&other)
{
    value = add_string(value, other.value);
    return (*this);
}

bigint& bigint::operator+=(unsigned long long num)
{
    return (*this += bigint(num));
}

//4
bigint& bigint::operator++()
{
    *this += 1;
    return(*this);
}

bigint bigint::operator++(int)
{
    bigint tmp(*this);
    ++(*this);
    return (tmp);
}

//5
bigint bigint::operator<<(int shift) const
{
    if (shift <= 0)
        return (*this);
    return (bigint(value + std::string(shift,'0')));
}

bigint bigint::operator>>(int shift)const
{
    if (shift <= 0 || shift >= static_cast<int>(value.size()) )
        return (bigint(0));
    return (bigint(value.substr(0, value.size() - shift)));
}

bigint& bigint::operator<<=(int shift)
{
    if (shift > 0)
        value += std::string(shift , '0');
    remove_zeros();
    return (*this);
}

bigint& bigint::operator>>=(int shift)
{
    if (shift <= 0 || shift >= static_cast<int>(value.size()) )
        value = "0";
    else
        value = value.substr(0, value.size() - shift);
    remove_zeros();
    return (*this);
}

//6
bigint bigint::operator<<(const bigint& shift)const
{
    return (*this << StringToNull(shift.value));
}

bigint bigint::operator>>(const bigint& shift)const
{
    return (*this >> StringToNull(shift.value));
}

bigint& bigint::operator<<=(const bigint& shift)
{
    remove_zeros();
    return (*this <<= StringToNull(shift.value));
}

bigint& bigint::operator>>=(const bigint& shift)
{
    remove_zeros();
    return (*this >>= StringToNull(shift.value));
}

//7

bool bigint::operator<(const bigint& shift) const
{
    if (value.size() != shift.value.size())
        return (value.size() < shift.value.size());
    return (value < shift.value);
}

bool bigint::operator>(const bigint& shift) const
{
    return (shift < *this);
}

bool bigint::operator<=(const bigint& shift) const
{
    return !(shift < *this);
}

bool bigint::operator>=(const bigint& shift) const
{
    return !(*this < shift);
}

bool bigint::operator==(const bigint& other) const
{
	return value == other.value;
}
bool bigint::operator!=(const bigint& other) const
{
	return value != other.value;
}

//8
std::ostream& operator<< (std::ostream& os, const bigint& big)
{
    os << big.value;
    return (os);
}