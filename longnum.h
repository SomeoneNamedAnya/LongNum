#ifndef LONGNUM_H_INCLUDED
#define LONGNUM_H_INCLUDED
#include<vector>
#include<algorithm>

class LongNum {
 public:
    explicit LongNum(std::string longnum) {
        sign_ = this -> find_sign(longnum);
        long_num_ = this -> to_vector(longnum);
        fract_length_ = this -> len_fract(longnum);
        this -> reduce_head();
        this -> reduce_tail();
    }

    LongNum() {
        sign_ = 1;
        fract_length_ = 0;
        long_num_.push_back(0);
    }

    explicit LongNum(std::vector<int> longnum, int len, int sign) {
        sign_ = sign;
        long_num_ = longnum;
        fract_length_ = len;
        this -> reduce_head();
        this -> reduce_tail();
    }

    int find_sign(std::string s) {
        if (s.size() == 0) return 1;
        if (s[0] == '-') return -1;
        return 1;
    }

    std::string getLongNum() {
        if (sign_ == -1){
            return '-' + this -> to_string();
        }

        return to_string();
    };

    void setSign(int new_sign) {
        sign_ = new_sign;
    }

    void changeSign(int coeff) {
        sign_ *= coeff;
    }

    std::string to_string() const {
        std::string str;
        for (int i = long_num_.size() - 1; i >=0; i--) {
            if (fract_length_ == i + 1) {
                str.push_back('.');
            }
            str.push_back('0' + long_num_[i]);
        }
        return str;
    }

    std::vector<int> to_vector(std::string num)  {
        std::vector<int> str;
        int last_ind = 0;
        if (num[0] == '-') {
            last_ind = 1;
        }
        for (int i = num.size() - 1; i >= last_ind; i--) {
            if (num[i] =='.') continue;
            str.push_back(num[i] - '0');
        }
        return str;
    }

    int len_fract(std::string num) {
        int t_ans = 0;
        int ans = 0;
        for (int i = num.size() - 1; i >= 0; i--) {
            t_ans += 1;
            if (num[i] == '.') {
                ans = t_ans - 1;
                break;
            }
        }
        return ans;
    }

    void Round(int cnt) {
        if (cnt < 0) return;
        if (fract_length_ <= cnt) return;
        std::reverse(long_num_.begin(), long_num_.end());
        while (fract_length_ > cnt) {
            long_num_.pop_back();
            fract_length_ -= 1;
        }
        std::reverse(long_num_.begin(), long_num_.end());
        return;
    }

    void reduce_head() {
        while (long_num_.size() > 0 && long_num_.back() == 0) {
            if (long_num_.size() == fract_length_ + 1) break;
            long_num_.pop_back();
        }
        return;
    }

    void reduce_tail() {
        std::reverse(long_num_.begin(), long_num_.end());
        int cur = 0;
        while (long_num_.size() > 0 && long_num_.back() == 0) {
            if (cur == fract_length_) break;
            long_num_.pop_back();
            cur += 1;
        }
        fract_length_ -= cur;
        std::reverse(long_num_.begin(), long_num_.end());
        return;
    }

    int ind_first_num() const {
        int ans = 0;
        int t_ans = 0;
        for (int i = long_num_.size() - 1; i >= 0; i--) {
            t_ans += 1;
            if (long_num_[i] != 0) {
                ans = t_ans;
                break;
            }
        }
        return ans;
    }

    LongNum Sum(const LongNum& second) const {
        int dif = abs(fract_length_ - second.fract_length_);
        int max_len;

        std::vector<int> ans_num;
        if (fract_length_ >= second.fract_length_) {
            max_len = std::max(long_num_.size(), second.long_num_.size() + dif);
            for (int i = 0; i < max_len; i++) {
                int cur = 0;
                if (i < long_num_.size()) {
                    cur += long_num_[i];
                }
                if (i - dif >= 0 && i - dif < second.long_num_.size()) {
                    cur += second.long_num_[i - dif];
                }
                ans_num.push_back(cur);
            }

        } else {
            max_len = std::max(long_num_.size() + dif, second.long_num_.size());
            for (int i = 0; i < max_len; i++) {
                int cur = 0;
                if (i - dif >= 0 && i - dif < long_num_.size()) {
                    cur += long_num_[i - dif];
                }
                if (i < second.long_num_.size()) {
                    cur += second.long_num_[i];
                }
                ans_num.push_back(cur);
            }
        }


        for (int i = 0; i < ans_num.size(); i++) {
            if (ans_num[i] >= 10) {
                ans_num[i] %= 10;
                if (ans_num.size() == i + 1) {
                    ans_num.push_back(1);
                } else {
                    ans_num[i + 1] += 1;
                }
            }
        }

        LongNum ans(ans_num, std::max(fract_length_, second.fract_length_), 1);
        ans.reduce_head();
        ans.reduce_tail();
        return ans;
    }

    LongNum Dif(const LongNum& second) const {
        int dif = abs(fract_length_ - second.fract_length_);
        std::vector<int> ans_num;
        int max_len;
        if (fract_length_ >= second.fract_length_) {
            max_len = std::max(long_num_.size(), second.long_num_.size() + dif);

            for (int i = 0; i < max_len; i++) {
                int cur = 0;
                if (i < long_num_.size()) {
                    cur += long_num_[i];
                }
                if (i - dif >= 0 && i - dif < second.long_num_.size()) {
                    cur -= second.long_num_[i - dif];
                }
                ans_num.push_back(cur);
            }
        } else {
            max_len = std::max(long_num_.size() + dif, long_num_.size());

            for (int i = 0; i < max_len; i++) {
                int cur = 0;
                if (i - dif >= 0 && i - dif < long_num_.size()) {
                    cur += long_num_[i - dif];
                }
                if (i < second.long_num_.size()) {
                    cur -= second.long_num_[i];
                }
                ans_num.push_back(cur);
            }
        }
        int last = ans_num.size();
        for (int i = ans_num.size() - 1; i >= 0; i--) {
            if (ans_num[i] != 0) {
                last = i;
                break;
            }
        }
        int sign = 1;
        for (int i = 0; i < ans_num.size(); i++) {
            if (ans_num[i] < 0) {
                if (i == last) {
                    ans_num[i] = abs(ans_num[i]);
                    sign = -1;
                    break;
                }
               ans_num[i] += 10;
               ans_num[i + 1] -= 1;
            }
        }

        LongNum ans(ans_num, std::max(fract_length_, second.fract_length_), sign);

        ans.reduce_head();
        ans.reduce_tail();
        return ans;

    }

    LongNum Div(const LongNum& second, int count_symbols) const {

        LongNum t_f = *this;
        t_f.setSign(1);
        LongNum nul("0");

        if (second == nul) {
            std::cout << "Error! Division by zero\n";
            return *this;
        }

        std::vector<int> ans;
        int st_sec = second.long_num_.size() - second.fract_length_ - second.ind_first_num();
        int st_fir = long_num_.size() - fract_length_ - ind_first_num();
        int dif = st_fir - st_sec;
        int exp = dif < 0 ? abs(dif) - 1: 0;
        int max_exp = count_symbols;//std::max(first.fract_length_, second.fract_length_);
        for (int i = 0; i + dif < 0; i++) {
            ans.push_back(0);
        }
        while (dif >= 0 || exp < max_exp) {
            std::vector<int> div = second.long_num_;
            int len = second.fract_length_;
            if (dif > 0 && second.fract_length_ < dif) {
                len = 0;
                std::reverse(div.begin(), div.end());
                int cnt = 0;
                while (second.fract_length_ + cnt < dif) {
                    cnt += 1;
                    div.push_back(0);
                }
                std::reverse(div.begin(), div.end());
            } else if (dif < 0 && second.long_num_.size() - second.fract_length_ <= -dif) {
                len = second.fract_length_ - dif;
                int cnt = 0;
                while (second.long_num_.size() - second.fract_length_ + cnt <= -dif) {
                    cnt += 1;
                    div.push_back(0);
                }
            } else {
                len = second.fract_length_ - dif;
            }
            ans.push_back(0);
            LongNum t_s(div, len, 1);
            t_s.reduce_head();

            while ((t_f > t_s) || t_f == t_s) {

                t_f = t_f - t_s;
                ans[ans.size() - 1] += 1;
            }
            if (dif < 0) {
                exp += 1;
            }
            dif -= 1;

        }

        std::reverse(ans.begin(), ans.end());
        LongNum ans_num(ans, max_exp, sign_ * second.sign_);

        ans_num.reduce_head();
        ans_num.reduce_tail();

        return ans_num;

    }

    friend LongNum operator+(const LongNum& first, const LongNum& second) {
        LongNum t_ans;
        if (first.sign_ == 1 && second.sign_ == 1) {
            t_ans = second.Sum(first);
        } else if (first.sign_ == -1 && second.sign_ == -1) {
            t_ans = first.Sum(second);
            t_ans.setSign(-1);
        } else if (first.sign_ == -1 && second.sign_ == 1) {
            LongNum temp = first;
            temp.setSign(1);
            if (temp < second) {
                t_ans = second.Dif(first);
            } else {
                t_ans = first.Dif(second);
                t_ans.changeSign(-1);
            }

        } else {
            LongNum temp = second;
            temp.setSign(1);
            if (first < temp) {
                t_ans = second.Dif(first);
                t_ans.changeSign(-1);
            } else {
                t_ans = first.Dif(second);
            }
        }
        return t_ans;
    };

    friend LongNum operator-(const LongNum& first, const LongNum& second) {
        LongNum t_ans;
        if (first.sign_ == 1 && second.sign_ == 1) {
            if (first > second) {
                t_ans = first.Dif(second);
            } else {
                t_ans = second.Dif(first);
                t_ans.changeSign(-1);
            }

        } else if (first.sign_ == -1 && second.sign_ == -1) {
            if (second > first) {
                t_ans = second.Dif(first);
            } else {
                t_ans = first.Dif(second);
                t_ans.changeSign(-1);
            }

        } else if (first.sign_ == -1 && second.sign_ == 1) {
            t_ans = first.Sum(second);
            t_ans.setSign(-1);

        } else {
            t_ans = first.Sum(second);
        }
        return t_ans;

    }
    friend LongNum operator*(const LongNum first, const LongNum second) {

        std::vector<int> ans(first.long_num_.size() + second.long_num_.size());
        int f_start = -1, s_start = -1;

        for (int i = 0; i < first.long_num_.size(); i++) {
            if (first.long_num_[i] != 0) {
                f_start = i;
                break;
            }
        }

        for (int i = 0; i < second.long_num_.size(); i++) {
            if (second.long_num_[i] != 0) {
                s_start = i;
                break;
            }
        }

        if (f_start == -1 || s_start == -1) {
            ans.resize(first.fract_length_ + second.fract_length_ + 1);

        } else {

            for (int i = f_start; i < first.long_num_.size(); i++) {
                for (int j = s_start; j < second.long_num_.size(); j++) {
                    ans[i + j] += second.long_num_[j] * first.long_num_[i];
                }
            }

            for (int i = 0; i < ans.size(); i++) {
                if (ans[i] > 9) {
                    ans[i + 1] += ans[i] / 10;
                    ans[i] %= 10;
                }
            }

        }
        LongNum num(ans, first.fract_length_ + second.fract_length_, first.sign_ * second.sign_);

        num.reduce_head();
        num.reduce_tail();

        return num;

    }
    friend LongNum operator/(const LongNum first, const LongNum second) {

        return first.Div(second, std::max(first.fract_length_, second.fract_length_));
    }

    friend bool operator==(const LongNum first, const LongNum second) {
        if (first.sign_ == first.sign_) {
            return first.long_num_ == second.long_num_;
        }
        std::vector<int> nul = {0};
        if (first.long_num_ == nul && first.long_num_ == nul) {
            return true;
        }
        return false;
    }
    friend bool operator!=(const LongNum first, const LongNum second) {
        return !(first == second);
    }
    friend bool operator<(const LongNum first, const LongNum second) {
        if (first == second) return false;
        if (first.sign_ < second.sign_) {
            return true;
        } else if (first.sign_ > second.sign_) {
            return false;
        }
        if (first.long_num_.size() - first.fract_length_ > second.long_num_.size() - second.fract_length_) {
            return false;
        }
        if (first.long_num_.size() - first.fract_length_ < second.long_num_.size() - second.fract_length_) {
            return true;
        }
        bool ans = true;
        for (int i = first.long_num_.size() - 1,
            j = second.long_num_.size() - 1;
            i >= 0 && j >= 0; i--, j--) {
            if (first.long_num_[i] < second.long_num_[j]) {
                ans = true;
                break;
            }
            if (first.long_num_[i] > second.long_num_[j]) {
                ans = false;
                break;
            }
            if (i == 0) {
                ans = false;
                while (j > 0) {
                    j -= 1;
                    if (second.long_num_[j] != 0) {
                        ans = true;
                        break;
                    }
                }
            } else if (j == 0) {
                ans = false;
            }
        }

        if (first.sign_ < second.sign_) return true;
        return ans;
    }
    friend bool operator>(const LongNum first, const LongNum second) {
        return !(first < second) && !(first == second);
    }

 private:
    std::vector<int> long_num_;
    int fract_length_;
    int sign_;

};

 LongNum operator "" _LN(const char* str) {
        LongNum ans(str);
        return ans;
}
// Функция рассчета числа пи с помощью формула суммы 
// 1/16^i * (4 / (8i + 1) - 2 / (8i + 4) - 1 / (8i + 5) - (1 / (8i + 6)) 
LongNum pi_calculation(int symbol_cmp){
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
#endif  LONGNUM_H_INCLUDED
