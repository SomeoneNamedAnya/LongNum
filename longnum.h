#ifndef LONGNUM_H_INCLUDED
#define LONGNUM_H_INCLUDED
#include<vector>
#include<algorithm>

std::string to_string(std::vector<int> vec, int len){
    std::string str;
    for (int i = vec.size() - 1; i >=0; i--) {
        if (len == i + 1) {
            str.push_back('.');
        }
        str.push_back('0' + vec[i]);

    }
    return str;
}

std::vector<int> to_vector(std::string vec){
    std::vector<int> str;

    int last_ind = 0;
    if (vec[0] == '-') {
        last_ind = 1;
    }

    for (int i = vec.size() - 1; i >= last_ind; i--) {
        if (vec[i] =='.') continue;
        str.push_back(vec[i] - '0');
    }
    return str;
}

int len_fract(std::string vec){
    int t_ans = 0;
    int ans = 0;
    for (int i = vec.size() - 1; i >= 0; i--) {
        t_ans += 1;
        if (vec[i] == '.') {
            ans = t_ans - 1;
            break;
        }
    }
    return ans;
}


int find_sign(std::string s) {
    if (s.size() == 0) return 1;
    if (s[0] == '-') return -1;
    return 1;
}

void reduce(std::vector<int> & num, int tail) {

    while (num.size() > tail + 1 && num.back() == 0) {
        num.pop_back();
    }
    return;
}


int ind_first_num(std::vector<int> num) {

    int ans = 0;
    int t_ans = 0;
    for (int i = num.size() - 1; i >= 0; i--) {
        t_ans += 1;
        if (num[i] != 0) {
            ans = t_ans;
            break;
        }
    }
    return ans;
}

class LongNum {
 public:
    LongNum(std::string longnum) {
        sign_ = find_sign(longnum);
        long_num_ = to_vector(longnum);
        fract_length_ = len_fract(longnum);
    }
    LongNum() {
        sign_ = 1;
        fract_length_ = 0;
        long_num_.push_back(0);
    }
    LongNum(std::vector<int> longnum, int len, int sign) {
        sign_ = sign;
        long_num_ = longnum;
        fract_length_ = len;
    }

    ~LongNum() {
        long_num_.clear();
    }

    std::string getLongNum() {
        if (sign_ == -1){
            return '-' + to_string(long_num_, fract_length_);
        }

        return to_string(long_num_, fract_length_);
    };

    int getLength() {
        return fract_length_;
    }
    int getSign() {
        return sign_;
    }

    void setSign(int new_sign) {
        sign_ = new_sign;
    }
    void changeSign(int coeff) {
        sign_ *= coeff;
    }

    friend LongNum Sum(LongNum first, LongNum second) {
        int dif = abs(first.fract_length_ - second.fract_length_);
        int max_len;

        std::vector<int> ans_num;
        if (first.fract_length_ >= second.fract_length_) {
            max_len = std::max(first.long_num_.size(), second.long_num_.size() + dif);
            for (int i = 0; i < max_len; i++) {
                int cur = 0;
                if (i < first.long_num_.size()) {
                    cur += first.long_num_[i];
                }
                if (i - dif >= 0 && i - dif < second.long_num_.size()) {
                    cur += second.long_num_[i - dif];
                }
                ans_num.push_back(cur);
            }

        } else {
            max_len = std::max(first.long_num_.size() + dif, second.long_num_.size());
            for (int i = 0; i < max_len; i++) {
                int cur = 0;
                if (i - dif >= 0 && i - dif < first.long_num_.size()) {
                    cur += first.long_num_[i - dif];
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

        LongNum ans(ans_num, std::max(first.fract_length_, second.fract_length_), 1);
        return ans;
    }

    friend LongNum Dif(LongNum first, LongNum second) {
        int dif = abs(first.fract_length_ - second.fract_length_);
        std::vector<int> ans_num;
        int max_len;
        if (first.fract_length_ >= second.fract_length_) {
            max_len = std::max(first.long_num_.size(), second.long_num_.size() + dif);

            for (int i = 0; i < max_len; i++) {
                int cur = 0;
                if (i < first.long_num_.size()) {
                    cur += first.long_num_[i];
                }
                if (i - dif >= 0 && i - dif < second.long_num_.size()) {
                    cur -= second.long_num_[i - dif];
                }
                ans_num.push_back(cur);
            }


        } else {
            max_len = std::max(first.long_num_.size() + dif, second.long_num_.size());

            for (int i = 0; i < max_len; i++) {
                int cur = 0;
                if (i - dif >= 0 && i - dif < first.long_num_.size()) {
                    cur += first.long_num_[i - dif];
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

        reduce(ans_num, std::max(first.fract_length_, second.fract_length_));


        LongNum ans(ans_num, std::max(first.fract_length_, second.fract_length_), sign);
        return ans;

    }

    friend LongNum operator+(const LongNum first, const LongNum second) {
        LongNum t_ans;
        if (first.sign_ == 1 && second.sign_ == 1) {
            t_ans = Sum(second, first);
        } else if (first.sign_ == -1 && second.sign_ == -1) {
            t_ans = Sum(first, second);
            t_ans.setSign(-1);
        } else if (first.sign_ == -1 && second.sign_ == 1) {
            LongNum temp = first;
            temp.setSign(1);
            if (temp < second) {
                t_ans = Dif(second, first);
            } else {
                t_ans = Dif(first, second);
                t_ans.changeSign(-1);
            }

        } else {
            LongNum temp = second;
            temp.setSign(1);
            if (first < temp) {
                t_ans = Dif(second, first);
                t_ans.changeSign(-1);
            } else {
                t_ans = Dif(first, second);
            }
        }
        return t_ans;
    };

    friend LongNum operator-(const LongNum first, const LongNum second) {
        LongNum t_ans;
        if (first.sign_ == 1 && second.sign_ == 1) {
            if (first > second) {
                t_ans = Dif(first, second);
            } else {
                t_ans = Dif(second, first);
                t_ans.changeSign(-1);
            }

        } else if (first.sign_ == -1 && second.sign_ == -1) {
            if (second > first) {
                t_ans = Dif(second, first);
            } else {
                t_ans = Dif(first, second);
                t_ans.changeSign(-1);
            }

        } else if (first.sign_ == -1 && second.sign_ == 1) {
            t_ans = Sum(first, second);
            t_ans.setSign(-1);

        } else {
            t_ans = Sum(first, second);
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

        reduce(ans, first.fract_length_ + second.fract_length_);

        LongNum num(ans, first.fract_length_ + second.fract_length_, first.sign_ * second.sign_);
        return num;

    }
    friend LongNum operator/(const LongNum first, const LongNum second) {
        LongNum t_f = first;

        t_f.setSign(1);
        LongNum nul("0");

        if (second == nul) {

            std::cout << "Error! Division by zero\n";
            return first;
        }

        std::vector<int> ans;
        int st_sec = second.long_num_.size() - second.fract_length_ - ind_first_num(second.long_num_);
        int st_fir = first.long_num_.size() - first.fract_length_ - ind_first_num(first.long_num_);
        int dif = st_fir - st_sec;
        int exp = dif < 0 ? abs(dif) - 1: 0;
        int max_exp = std::max(first.fract_length_, second.fract_length_);
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
            reduce(div, len);
            LongNum t_s(div, len, 1);
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
        reduce(ans, max_exp);

        LongNum ans_num(ans, max_exp, first.sign_ * second.sign_);
        return ans_num;

    }

    friend bool operator==(const LongNum first, const LongNum second) {
        if (first.long_num_.size() - first.fract_length_ != second.long_num_.size() - second.fract_length_) {
            return false;
        }
        bool ans = true;
        bool is_null = true;
        for (int i = first.long_num_.size() - 1,
             j = second.long_num_.size() - 1;
             i >= 0 && j >= 0; i--, j--) {

            if (first.long_num_[i] != 0) {
                is_null = false;
            }
            if (second.long_num_[j] != 0) {
                is_null = false;
            }
            if (first.long_num_[i] != second.long_num_[j]) {
                ans = false;
                break;
            }
            if (i == 0) {
                while (j > 0) {
                    j -= 1;
                    if (second.long_num_[j] != 0) {
                        is_null = false;
                    }
                    if (second.long_num_[j] != 0) {
                        ans = false;
                        break;
                    }
                }
            } else if (j == 0) {
                 while (i > 0) {
                    i -= 1;
                    if (first.long_num_[i] != 0) {
                        is_null = false;
                    }
                    if (first.long_num_[i] != 0) {
                        ans = false;
                        break;
                    }
                }
            }
        }
        if (is_null) return true;
        if (first.sign_ != second.sign_) return false;
        return ans;
    }
    friend bool operator!=(const LongNum first, const LongNum second) {
        return !(first == second);
    }
    friend bool operator<(const LongNum first, const LongNum second) {
        if (first == second) return false;
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
#endif  LONGNUM_H_INCLUDED
