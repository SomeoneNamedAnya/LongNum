#include "longnum.h"
namespace LongNumLib {
    // Функция рассчета числа пи с помощью формула суммы 
    // 1/16^i * (4 / (8i + 1) - 2 / (8i + 4) - 1 / (8i + 5) - (1 / (8i + 6)) 
    LongNum PiCalculation(int symbol_cmp){
        LongNum ans("0.0");
        LongNum coef("1");
        LongNum j("0");
        for (int i = 0; i < symbol_cmp + 2; i++) {
            ans = ans + ((1_LN).Div(coef, symbol_cmp + 1)) *
                        ((4_LN).Div(8_LN * j + 1_LN, symbol_cmp + 1) -
                         (2_LN).Div(8_LN * j + 4_LN, symbol_cmp + 1) -
                         (1_LN).Div(8_LN * j + 5_LN, symbol_cmp + 1) -
                         (1_LN).Div(8_LN * j + 6_LN, symbol_cmp + 1));
            j = j + 1_LN;
            coef = coef * 16_LN;
         }
    
         ans.Round(symbol_cmp);
         return ans;
    }
}
