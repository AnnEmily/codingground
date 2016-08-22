#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool AsciiToNum (char *src, int &num)
{
    num = 0 ;
    vector<int> digits ;
    char *ptr = src ;
    
    while (*ptr != 0)
    {
        int val = static_cast<int>(*ptr - '0') ;
        
        if (val < 0 || val > 9)
            return false ;
        else
            digits.push_back (val) ;
            
        ptr++ ;
    } ;
    
    reverse (digits.begin(), digits.end()) ;
    int mult = 1 ;
    
    for (int digit : digits)
    {
        num  += digit * mult ;
        mult *= 10 ;
    }
    
    return true ;
}

int main (int argc, char **argv)
{
    if (argc < 3)
    {
        cout << " Need two numbers" << endl;
        return 1;
    }
    
    int num ;
    
    if (!AsciiToNum(argv[1], num))
    {
        cout << argv[1] << " is not an integer" << endl ;
        return 1 ;
    }
     
    int den ;
    
    if (!AsciiToNum(argv[2], den))
    {
        cout << argv[2] << " is not an integer" << endl ;
        return 1 ;
    }
    
    if (den != 0)
    {
        cout << " Remainder is " << num % den << endl;
    }
    else
    {
        cout << " Remainder is infinite" << endl;
    }
   
   return 0;
}
