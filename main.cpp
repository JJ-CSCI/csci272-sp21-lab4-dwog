//------------------------------
//  DO NOT MODIFY NEXT LINE
//------------------------------
#include <string>
#include "catch.hpp"
using Catch::Matchers::Equals;
//------------------------------

// Fix the following class
#include <array>
#include <ctype.h>







class Complex
{
private:

    std::array<int, 2> coefficients;

    public:

    Complex(int a=0, int b=0);
    void operator>>(std::string&) const;
    void operator<<(const std::string&);
    int re() const;
    int im() const;

};





Complex::Complex(int a, int b)
{
    coefficients = {a, b};
}

void Complex::operator>>(std::string& output) const
{
     std::string real{std::to_string(coefficients[0])}, imaginary{std::to_string(coefficients[1]) + "i"};
     output = (real + ((coefficients[1] < 0) ? "" : "+") + imaginary);
}

void Complex::operator<<(const std::string& input)
{
    std::array<std::string, 2> temp;
    bool seen{false};
    int index{0};

    for (const auto& i : input)
    {
        if ((isdigit(static_cast<int>(i))) && (!seen))
        seen = true;
    
        if ((seen) && ((i == '-') || (i == '+')))
        index++;
        
        temp[index] += i;
    }

    index = 0;
    for (const auto& i : temp)
    {
        coefficients[index] = std::stoi(i);
        index++;
    }

}

int Complex::re() const
{
    return coefficients[0];
}

int Complex::im() const
{
    return coefficients[1];
}





//------------------------------
//   DO NOT MODIFY TEST CASES
//------------------------------
TEST_CASE( "Assignment" ) {
    SECTION( "c1" ) {
        Complex c;
        REQUIRE( c.re() == 0 );
        REQUIRE( c.im() == 0 );
    }
    SECTION( "c2" ) {
        Complex c{1};
        REQUIRE( c.re() == 1 );
        REQUIRE( c.im() == 0 );
    }
    SECTION( "c3" ) {
        Complex c{1,1};
        REQUIRE( c.re() == 1 );
        REQUIRE( c.im() == 1 );
    }
    SECTION( "o1" ) {
        Complex c; std::string s{""};
        c >> s;
        REQUIRE_THAT( s, Equals("0+0i") );
    }
    SECTION( "o2" ) {
        Complex c{1, 2}; std::string s{""};
        c >> s;
        REQUIRE_THAT( s, Equals("1+2i") );
    }
    SECTION( "o3" ) {
        Complex c{2, -2}; std::string s{""};
        c >> s;
        REQUIRE_THAT( s, Equals("2-2i") );
    }
    SECTION( "o4" ) {
        Complex c{-2, 2}; std::string s{""};
        c >> s;
        REQUIRE_THAT( s, Equals("-2+2i") );
    }
    SECTION( "p1" ) {
        Complex c;
        c << "1+1i";
        REQUIRE( c.re() == 1 );
        REQUIRE( c.im() == 1 );
    }
    SECTION( "p2" ) {
        Complex c;
        c << "1-1i";
        REQUIRE( c.re() == 1 );
        REQUIRE( c.im() == -1 );
    }
    SECTION( "p3" ) {
        Complex c;
        c << "-1+0i";
        REQUIRE( c.re() == -1 );
        REQUIRE( c.im() == 0 );
    }
    SECTION( "p4" ) {
        Complex c;
        c << "-1-2i";
        REQUIRE( c.re() == -1 );
        REQUIRE( c.im() == -2 );
    }
}
//------------------------------
