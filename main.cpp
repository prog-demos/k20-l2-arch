#include <iostream>
#include <vector>

class Multiplication;

class LongInt {
    
    private:

        // Base is 1000
        // for example, number 123456789 is stored as [789, 456, 123]
        // 123456789 = 123 * 1000^2 + 456 * 1000 + 789
        // 123,456,789
        std::vector<int> value;
        bool isNegative;

        // static int multMethod;

        static Multiplication* multMethod;

    public:
        LongInt() {
            value.push_back(0);
        }

        LongInt(u_int64_t num) {
            while (num) {
                value.push_back(num % 10);
                num /= 10;
            }
        }

        LongInt(std::string str) {
            for (int i = str.length() - 1; i >= 0; i--) {
                value.push_back(str[i] - '0');
            }
        }

        static void setMultMethod(Multiplication* method) {
            multMethod = method;
        }

        LongInt operator=(std::string str) {
           
            value.clear();
            for (int i = str.length() - 1; i >= 0; i--) {
                value.push_back(str[i] - '0');
            }
            return *this;
        }

        // operator >
        bool operator>(LongInt other) {
            if (value.size() != other.value.size()) {
                return value.size() > other.value.size();
            }
            for (int i = value.size() - 1; i >= 0; i--) {
                if (value[i] != other.value[i]) {
                    return value[i] > other.value[i];
                }
            }
            return false;
        }

        LongInt operator-(LongInt other) {
            LongInt result;
            int carry = 0;
            if(other > *this) {
                result.isNegative = true;
                std::swap(*this, other);
            }
            else {
                result.isNegative = false;
            }


            for (int i = 0; i < value.size() || i < other.value.size(); i++) {
                int diff = carry;
                if (i < value.size()) {
                    diff += value[i];
                }
                if (i < other.value.size()) {
                    diff -= other.value[i];
                }
                if (diff < 0) {
                    diff += 10;
                    carry = -1;
                } else {
                    carry = 0;
                }

       result.value.push_back(diff);
            }
            while (result.value.size() > 1 && result.value.back() == 0) {
                result.value.pop_back();
            }
            return result;
        }

        LongInt add(LongInt other) {
            LongInt result;
            int carry = 0;
            for (int i = 0; i < value.size() || i < other.value.size(); i++) {
                int sum = carry;
                if (i < value.size()) {
                    sum += value[i];
                }
                if (i < other.value.size()) {
                    sum += other.value[i];
                }
                result.value.push_back(sum % 10);
                carry = sum / 10;
            }
            if (carry) {
                result.value.push_back(carry);
            }
            return result;
        }

        LongInt kara_mult(LongInt other) {
            return other;
        }

        LongInt naive_mult(LongInt other) {
            LongInt result;
            for (int i = 0; i < value.size(); i++) {
                LongInt temp;
                int carry = 0;
                for (int j = 0; j < other.value.size(); j++) {
                    int prod = value[i] * other.value[j] + carry;
                    temp.value.push_back(prod % 10);
                    carry = prod / 10;
                }
                if (carry) {
                    temp.value.push_back(carry);
                }
                for (int j = 0; j < i; j++) {
                    temp.value.insert(temp.value.begin(), 0);
                }
                //result = result + temp;
            }
            return result;
        }

        LongInt operator*(LongInt other);

        friend std::ostream& operator<<(std::ostream& os, const LongInt& obj) {
            for (int i = obj.value.size() - 1; i >= 0; i--) {
                os << obj.value[i];
            }
            return os;
        }

};

Multiplication* LongInt::multMethod = nullptr;

class Multiplication {
    public:
        // pure virtual function
        virtual LongInt multiply(LongInt a, LongInt b) = 0;
};

class Naive : public Multiplication {
    public:
        LongInt multiply(LongInt a, LongInt b) {
            return a;
        }
};

class Karatsuba : public Multiplication {
    public:
        LongInt multiply(LongInt a, LongInt b) {
            return a;
        }
};

class Toom3 : public Multiplication {
    public:
        LongInt multiply(LongInt a, LongInt b) {
            return a;
        }
};

LongInt LongInt::operator*(LongInt other) {
    multMethod->multiply(*this, other);
}

int main() {
    // Demo of our class usage
    LongInt a("32487582746592834756982374659823795823745982374659823"), b(123456), c;

    // select multiplication method

    // Use Karatsuba multiplication

    LongInt::setMultMethod(new Karatsuba());
    c = b * a;
    std::cout << "Kara result: " << c << std::endl;

    // Use naive multiplication
    LongInt::setMultMethod(new Naive());
    c = a * b;
    std::cout << "Naive result: " << c << std::endl;

    // Use TOOM-3 multiplication
    LongInt::setMultMethod(new Toom3());
    c = a*b;
    std::cout << "Toom-3 result: " << c << std::endl;



    return 0;
}
