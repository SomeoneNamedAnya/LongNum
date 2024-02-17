#include "longnum.h"
namespace LongNumLib {
LongNum::LongNum() {
    sign_ = 1;
    fract_length_ = 0;
    long_num_.push_back(0);
}

 LongNum::LongNum(std::string longnum) {
    sign_ = this -> FindSign(longnum);
    long_num_ = this -> ToVector(longnum);
    fract_length_ = this -> LenFract(longnum);
    this -> ReduceHead();
    this -> ReduceTail();
}


 LongNum::LongNum(std::vector<int> longnum, int len, int sign) {
    sign_ = sign;
    long_num_ = longnum;
    fract_length_ = len;
    this -> ReduceHead();
    this -> ReduceTail();
}

int LongNum::FindSign(std::string& s) {
    if (s.size() == 0) return 1;
    if (s[0] == '-') return -1;
    return 1;
}

std::string LongNum::GetLongNum() {

    if (this -> long_num_ == std::vector<int> (1)) {
        return this -> ToString();
    }

    if (sign_ == -1){
        return '-' + this -> ToString();
    }

    return ToString();
};


void LongNum::SetSign(int new_sign) {
    sign_ = new_sign;
}

void LongNum::ChangeSign(int coeff) {
    sign_ *= coeff;
}

std::string LongNum::ToString() const {
    std::string str;
    for (int i = long_num_.size() - 1; i >=0; i--) {
        if (fract_length_ == i + 1) {
            str.push_back('.');
        }
        str.push_back('0' + long_num_[i]);
    }
    return str;
}

std::vector<int> LongNum::ToVector(std::string& num)  {
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

int LongNum::LenFract(std::string& num) {
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

void LongNum::Round(int cnt) {
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

void LongNum::ReduceHead() {
    while (long_num_.size() > 0 && long_num_.back() == 0) {
        if (long_num_.size() == fract_length_ + 1) break;
        long_num_.pop_back();
    }
    return;
}

void LongNum::ReduceTail() {
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

int LongNum::IndFirstNum() const {
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

LongNum LongNum::Sum(const LongNum& second) const {
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
    ans.ReduceHead();
    ans.ReduceTail();
    return ans;
}

LongNum LongNum::Dif(const LongNum& second) const {
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

    ans.ReduceHead();
    ans.ReduceTail();
    return ans;

}

LongNum LongNum::Div(const LongNum& second, int count_symbols) const {

    LongNum t_f = *this;
    t_f.SetSign(1);
    LongNum nul("0");

    if (second == nul) {
        throw "DivisionByZero";
    }

    std::vector<int> ans;
    int st_sec = second.long_num_.size() - second.fract_length_ - second.IndFirstNum();
    int st_fir = long_num_.size() - fract_length_ - IndFirstNum();
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
        t_s.ReduceHead();
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

    ans_num.ReduceHead();
    ans_num.ReduceTail();

    return ans_num;

}

LongNum operator+(const LongNum& first, const LongNum& second) {
    LongNum t_ans;
    if (first.sign_ == 1 && second.sign_ == 1) {
        t_ans = second.Sum(first);
    } else if (first.sign_ == -1 && second.sign_ == -1) {
        t_ans = first.Sum(second);
        t_ans.SetSign(-1);
    } else if (first.sign_ == -1 && second.sign_ == 1) {
        LongNum temp = first;
        temp.SetSign(1);
        if (temp < second) {
            t_ans = second.Dif(first);
        } else {
            t_ans = first.Dif(second);
            t_ans.ChangeSign(-1);
        }

    } else {
        LongNum temp = second;
        temp.SetSign(1);
        if (first < temp) {
            t_ans = second.Dif(first);
            t_ans.ChangeSign(-1);
        } else {
            t_ans = first.Dif(second);
        }
    }
    return t_ans;
}

LongNum operator-(const LongNum& first, const LongNum& second) {
    LongNum t_ans;
    if (first.sign_ == 1 && second.sign_ == 1) {
        if (first > second) {
            t_ans = first.Dif(second);
        } else {
            t_ans = second.Dif(first);
            t_ans.ChangeSign(-1);
        }

    } else if (first.sign_ == -1 && second.sign_ == -1) {
        if (second > first) {
            t_ans = second.Dif(first);
        } else {
            t_ans = first.Dif(second);
            t_ans.ChangeSign(-1);
        }

    } else if (first.sign_ == -1 && second.sign_ == 1) {
        t_ans = first.Sum(second);
        t_ans.SetSign(-1);

    } else {
        t_ans = first.Sum(second);
    }
    return t_ans;

}

LongNum operator-(const LongNum& first) {
    LongNum result = first;
    result.ChangeSign(-1);
    return result;
}

LongNum operator*(const LongNum& first, const LongNum& second) {

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

    num.ReduceHead();
    num.ReduceTail();

    return num;

}

LongNum operator/(const LongNum& first, const LongNum& second) {

    return first.Div(second, std::max(first.fract_length_, second.fract_length_));
}

bool operator==(const LongNum& first, const LongNum& second) {
    if (first.sign_ == second.sign_) {
        return first.long_num_ == second.long_num_;
    }
    std::vector<int> nul = {0};
    if (first.long_num_ == nul && second.long_num_ == nul) {
        return true;
    }
    return false;
}

bool operator!=(const LongNum& first, const LongNum& second) {
    return !(first == second);
}

bool operator<(const LongNum& first, const LongNum& second) {
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

bool operator>(const LongNum& first, const LongNum& second) {
    return !(first < second) && !(first == second);
}


LongNum operator "" _LN(const char* str) {
        LongNum ans(str);
        return ans;
}

}
