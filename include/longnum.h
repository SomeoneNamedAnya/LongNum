#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <exception>

namespace LongNumLib {

  class LongNum {
      public:
    
        LongNum();
        explicit LongNum(std::string longnum);
        explicit LongNum(std::vector<int> longnum, int len, int sign);
    
        std::string GetLongNum();
        void Round(int cnt);
    
        LongNum Sum(const LongNum& second) const;
        LongNum Dif(const LongNum& second) const;
        LongNum Div(const LongNum& second, int count_symbols) const;
    
        friend LongNum operator+(const LongNum& first, const LongNum& second);
        friend LongNum operator-(const LongNum& first, const LongNum& second);
        friend LongNum operator-(const LongNum& first);
        friend LongNum operator*(const LongNum& first, const LongNum& second);
        friend LongNum operator/(const LongNum& first, const LongNum& second);
    
        friend bool operator==(const LongNum& first, const LongNum& second);
        friend bool operator!=(const LongNum& first, const LongNum& second);
        friend bool operator<(const LongNum& first, const LongNum& second);
        friend bool operator>(const LongNum& first, const LongNum& second);
    
        private:
        std::vector<int> long_num_;
        int fract_length_;
        int sign_;
    
        void ReduceHead();
    
        void ReduceTail();
    
        int IndFirstNum() const;
    
        void SetSign(int new_sign);
    
        void ChangeSign(int coeff);
    
        std::string ToString() const;
    
        std::vector<int> ToVector(const std::string& num);
    
        int LenFract(const std::string& num);
    
        int FindSign(const std::string& s);

  };

  LongNum operator "" _LN(const char* str);

  LongNum PiCalculation(int symbol_cmp);
}
