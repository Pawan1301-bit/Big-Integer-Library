#include <bits/stdc++.h>

using namespace std;

class BigInt
{
    string digits;

public:
    // constructor
    BigInt(unsigned long long n = 0); // unsigned means all the non negative number
    BigInt(string &);                 // take the string by reference  as parameter
    BigInt(const char *);             // pointer pointing to the constant char
    BigInt(BigInt &);  

    // helper function
    friend void divide_by_2(BigInt &a);
    friend bool Null(const BigInt &);
    friend int Length(const BigInt &);

    /* ----- operator overloading ----- */
    int operator[](const int) const;

    // direct assignment
    BigInt &operator=(const BigInt &); // return type -->reference of the BigInt

    // post/pre -- incrementation
    BigInt &operator++();
    BigInt operator++(int temp); // for post we pass a dummy argument
    BigInt &operator--();
    BigInt operator--(int temp);

    // addition and subtraction
    friend BigInt &operator+=(BigInt &, const BigInt &);
    // we take 2 operators because the += operation will operate on 2  operands the second value will add on the first that why the first operator is not const
    friend BigInt operator+(const BigInt &, const BigInt &);
    friend BigInt &operator-=(BigInt &, const BigInt &);
    friend BigInt operator-(const BigInt &, const BigInt &);

    // comparision operators
    friend bool operator==(const BigInt &, const BigInt &);
    friend bool operator!=(const BigInt &, const BigInt &);

    friend bool operator>(const BigInt &, const BigInt &);
    friend bool operator>=(const BigInt &, const BigInt &);
    friend bool operator<(const BigInt &, const BigInt &);
    friend bool operator<=(const BigInt &, const BigInt &);

    // multiplication and division
    friend BigInt &operator*=(BigInt &, const BigInt &);
    friend BigInt operator*(const BigInt &, const BigInt &);
    friend BigInt &operator/=(BigInt &, const BigInt &);
    friend BigInt operator/(const BigInt &, const BigInt &);

    // modulo
    friend BigInt &operator%=(BigInt &, const BigInt &);
    friend BigInt operator%(const BigInt &, const BigInt &);

    // power function --> ????
    friend BigInt &operator^=(BigInt &, const BigInt &);
    friend BigInt operator^(BigInt &, const BigInt &);

    // square function
    friend BigInt sqrt(BigInt &a);

    // read and write
    friend ostream &operator<<(ostream &, const BigInt &);
    friend istream &operator>>(istream &,  BigInt &);

    // others
    friend BigInt Catalan(int n);
    friend BigInt Fibomacci(int n);
    friend BigInt Factorial(int n);
};

// implenting the  constructors
BigInt::BigInt(string &s)
{
    digits = "";
    int n = s.size();
    for (int i = n - 1; i >= 0; i--)
    {
        if (!isdigit(s[i]))
            throw("error  not a valid string of number");
        digits.push_back(s[i] - '0'); // this will convert it to int
    }
}
// here  we have  just assign the s to digits in reverse order

BigInt::BigInt(unsigned long long n)
{
    do
    {
        digits.push_back(n % 10);
        n /= 10;
    } while (n);
}

BigInt::BigInt(const char *s)
{
    digits = "";
    for (int i = strlen(s) - 1; i >= 0; i--)
    {
        if (!isdigit(s[i]))
            throw("error not a valid array of characters");
        digits.push_back(s[i] - '0');
    }
}
BigInt::BigInt(BigInt &a)
{
    digits = a.digits;
}


// implementing the helper functions
bool Null(const BigInt &a)
{
    if (a.digits.size() == 1 && a.digits[0] == 0)
        return true;
    return false;
}

int Length(const BigInt &a){
        return a.digits.size();
}

int BigInt::operator[](const int index)const{
    if(digits.size() <= index || index < 0)
        throw("error  value is not present in the given string");
    return digits[index];
}
///operator [] allow to access indivisual digits of the BigInt object

bool operator==(const BigInt &a, const BigInt &b){
    return a.digits == b.digits;
}

bool operator!=(const BigInt &a , const BigInt &b){
    return !(a.digits == b.digits);
}

bool operator<(const BigInt &a, const BigInt &b){
    int n = Length(a), m = Length(b);
    if(n != m)
            return (n<m);
    while(n--){
        if(a.digits[n] != b.digits[n])
            return a.digits[n] < b.digits[n];
        return false;
    }
}

// -- ????
bool operator>(const BigInt &a, const BigInt &b){
    return b < a;   //using the preivious define operator < here
}

bool operator>=(const BigInt &a, const BigInt &b){
    return !(a < b);
}

bool operator<=(const BigInt &a, const BigInt &b){
    return !(a >  b);
}

BigInt &BigInt::operator=(const BigInt &a){
    digits = a.digits;
    return *this;
}

BigInt &BigInt::operator++(){
    int i, n = digits.size();
    for(int i=0; i<n && digits[i] == 9; i++)
        digits[i] == 0;
    if(i == n)
        digits.push_back(1);
    else
        digits[i++];
    return *this;
    
}

BigInt BigInt::operator++(int temp){
    BigInt tp = *this;
    ++(*this);
    return tp;
}

BigInt &BigInt::operator--(){
    if(digits[0] == 0 && digits.size() == 1){
        throw("Underflow value cannot be negative");
    }
    int i, n= digits.size();
    for(i=0; digits[i] == 0 && i<n; i++)
        digits[i] == 9;
    digits[i--];
    if(n>1 && digits[n-1] == 0)
        digits.pop_back();
    return *this;
}

BigInt BigInt::operator--(int temp){
    BigInt tx = (*this);
    --(*this);
    return tx;
}

BigInt &operator +=(BigInt &a, const BigInt &b){
    int carry=0, s, i;
    int n = Length(a), m = Length(b);
    if(m > n)
        a.digits.append(m-n, 0);
    n = Length(a);
    for( i=0; i<n; i++){
        if(i < m)
            s = (a.digits[i] + b.digits[i]) + carry;
        else 
            s = a.digits[i] + carry;
        carry = s/10;
        a.digits[i] = (s%10);
    }
    if(carry)   
        a.digits.push_back(carry);
    return a;
}

BigInt operator+(const BigInt &a, const BigInt &b){
    BigInt temp;
    temp = a;
    return temp += b;
}

// ----  ????
BigInt &operator-=(BigInt &a, const BigInt &b){
    if(a <b)
        throw("Underflow first number  is smaller than second");
    int n = Length(a), m = Length(b);
    int i, borrow = 0, s;
    for(i=0; i<n; i++){
        if(i < m)
            s = a.digits[i] - b.digits[i] + borrow;
        else 
            s = a.digits[i] + borrow;
        if(s < 0)
            s += 10, borrow = -1;
        else    
            borrow = 0;
        a.digits[i] = s;
    }
    while(n > 1 && a.digits[n-1] == 0){
        a.digits.pop_back();
        n--;
    }
    return a;
}

BigInt operator-(const BigInt &a, const BigInt & b){
    BigInt temp;
    temp = a;
    temp -= b;
    return temp;
}

BigInt &operator*=(BigInt &a, const BigInt &b){
    if(Null(a) || Null(b)){
        a = BigInt();
        return a;
    }

    int n= a.digits.size(), m= b.digits.size();
    vector<int> v(n+m, 0);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            v[i+j] += (a.digits[i])*(b.digits[j]);
        }
    }

    n += m;
    a.digits.resize(v.size());
    for( int s, i=0, t =0; i<n; i++ ){
        s = t + v[i];
        v[i] = s% 10;
        t = s/10;
        a.digits[i] = v[i];
    }
    for(int i=n-1; i>=1 && !v[i]; i--){
        a.digits.pop_back();
    }
    return a;
    }

BigInt operator*(const BigInt &a, const BigInt &b){ 
    BigInt temp;
    temp = a;
    temp *= b;
    return temp;
}

BigInt &operator /= (BigInt& a, const BigInt &b){
    if(Null(b))
        throw("error cannot be divisible by 0");
    if(a < b){
        a = BigInt();
        return a;
    }
    if(a == b){
        a = BigInt(1);
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Length(a), m = Length(b);
    vector<int> cat(n, 0);
    BigInt t;
    for(i = n-1; t*10 + a.digits[i] < b; i--){
        t *= 10;
        t += a.digits[i];
    }
    for(; i>=0; i--){
        t = t*10 + a.digits[i];
        for(cc = 9; cc*b>t; cc--);
            t -= cc * b;
            cat[lgcat++] = cc;
    }
    a.digits.resize(cat.size());
    for(int i=0; i<lgcat; i++){
        a.digits[i] = cat[lgcat - i - 1];
    }
    a.digits.resize(lgcat);
    return a;
}

BigInt operator/(const BigInt &a,const BigInt &b){
    BigInt temp;
    temp = a;
    temp /= b;
    return temp;
}

BigInt &operator%=(BigInt& a, const BigInt& b){
    if(Null(b))
        throw("error module by 0 is not possible");
    if(a < b)
        return a;
    if(a == b)  {
        a = BigInt();
        return a;
    }

    int i, lgcat=0, cc;
    int n= Length(a), m = Length(b);
    vector<int> cat(n, 0);
    BigInt t;
    for(i = n-1; t*10+a.digits[i] < b; i--){
        t *= 10;
        t += a.digits[i];
    }
    for (; i >= 0; i--){
        t = t * 10 + a.digits[i];
        for (cc = 9; cc * b > t;cc--);
        t -= cc * b;
        cat[lgcat++] = cc;
    }
    a = t;
    return a;
}

BigInt operator%(const BigInt &a,const BigInt &b){
    BigInt temp;
    temp = a;
    temp %= b;
    return temp;
}

BigInt &operator^=(BigInt &a, const BigInt &b){
    BigInt expo, base(a);
    expo = b;
    a = 1;
    while(!Null(expo)){
        if(expo[0] & 1)
            a *= base;
        base *= base;
        divide_by_2(expo);
    }
    return a;
}

BigInt operator^(BigInt & a,BigInt & b){
    BigInt temp(a);
    temp ^= b;
    return temp;
}

void divide_by_2(BigInt &a){
    int add =0;
    for(int i = a.digits.size()-1; i>=0; i--){
        int digit = (a.digits[i] >> 1) + add;   //we use right shift operator to divide it by 2
        add = ((a.digits[i] & 1) * 5);
        a.digits[i] = digit;
    }
    while(a.digits.size() > 1 && !a.digits.back()){
        a.digits.pop_back();
    }
}

BigInt sqrt(BigInt &a){
    BigInt left(1), right(a), v(1), mid, prod;
    divide_by_2(right);
    while(left <= right){
        mid += left;
        mid += right;
        divide_by_2(mid);
        prod = mid*mid;
        if(prod <= a){
            v = mid;
            ++mid;
            left = mid;
        }else{
            --mid;
            right = mid;
        }
        mid = BigInt();
    }
    return v;
}

BigInt Catalan(int n){
    BigInt a(1), b;
    for(int i=2; i<=n; i++){
        a *= i;
    b = a;
    for(int i = n+1; i <= 2*n; i++)
        b *= i;
    a *= a;
    a *= (n+1);
    b /= a;
    return b;
    }
}

BigInt Fibomacci(int n){
    BigInt a(1), b(1), c;
    if(!n)
        return c;
    n--;
    while(n--){
        c = a + b;
        b = a;
        a = c;
    }
    return b;
}
 
BigInt Factorial(int n){
    BigInt f(1);
    for (int i = 2; i <= n;i++)
        f *= i;
    return f;
}
 
istream &operator>>(istream &in,BigInt&a){
    string s;
    in >> s;
    int n = s.size();
    for (int i = n - 1; i >= 0;i--){
        if(!isdigit(s[i]))
            throw("INVALID NUMBER");
        a.digits[n - i - 1] = s[i];
    }
    return in;
}
 
ostream &operator<<(ostream &out,const BigInt &a){
    for (int i = a.digits.size() - 1; i >= 0;i--)
        cout << (short)a.digits[i];
    return cout;
}
int main()
{
    cout << "hello world";
    return 0;
}