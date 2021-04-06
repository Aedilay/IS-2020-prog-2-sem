#include "polynomial.h"


Polynomial::Polynomial(int min, int max, int *pointer)
        : size(max - min + 1), minPow(min), maxPow(max), coefficents(pointer) {
}

Polynomial::Polynomial()
        : size(1), minPow(0), maxPow(0), coefficents(nullptr) {
}

int *duplicate_coeffs(const int *coeffs, int size) {
    if (coeffs == nullptr)
        return nullptr;
    int *result = new int[size];
    for (int i = 0; i < size; ++i) {
        result[i] = coeffs[i];
    }
    return result;
}

Polynomial::Polynomial(const Polynomial &other)
        : size(other.size), minPow(other.minPow), maxPow(other.maxPow),
          coefficents(duplicate_coeffs(other.coefficents, other.size)) {}

bool operator==(const Polynomial &poly1_, const Polynomial &poly2_) {
    if (poly1_.coefficents == nullptr && poly2_.coefficents == nullptr)
        return true;
    int max1 = poly1_.maxPow;
    int min1 = poly1_.minPow;
    int max2 = poly2_.maxPow;
    int min2 = poly2_.minPow;
    for (int i = poly1_.size - 1; i >= 0; --i) {
        if (poly1_.coefficents[i] == 0 && poly1_.minPow < poly1_.maxPow) {
            max1--;
        } else break;
    }
    for (int i = 0; i < poly1_.size; ++i) {
        if (poly1_.coefficents[i] == 0 && poly1_.minPow < poly1_.maxPow)
            min1++;
    }
    for (int i = poly2_.size - 1; i >= 0; --i) {
        if (poly2_.coefficents[i] == 0 && poly2_.minPow < poly2_.maxPow) {
            max2--;
        } else break;
    }
    for (int i = 0; i < poly2_.size; ++i) {
        if (poly2_.coefficents[i] == 0 && poly2_.minPow < poly2_.maxPow)
            min2++;
    }
    if (min1 != min2 && max2 != max1)
        return false;
    for (int i = 0; i < max1 - min1 + 1; i++) {
        if (poly1_.coefficents[i] != poly2_.coefficents[i])
            return false;
    }
    return true;
}

//fixed not default
Polynomial &Polynomial::operator=(const Polynomial &poly) {
    if (this == &poly) {
        return *this;
    } else if (poly.coefficents == nullptr){
        delete[] coefficents;
        coefficents = nullptr;
        return *this;
    } else{
        //fixed should copying arguments
        size = poly.size;
        int *new_coeffs = new int[poly.size];
        for (int i = 0; i < poly.size; i++) {
            new_coeffs[i] = poly.coefficents[i];
        }
        delete[] coefficents;
        coefficents = new_coeffs;
        minPow = poly.minPow;
        maxPow = poly.maxPow;
        return *this;
    }
}




Polynomial operator+(const Polynomial &poly1_, const Polynomial &poly2_) {
    Polynomial result = poly1_;
    result += poly2_;
    return result;
}

std::ostream &operator<<(std::ostream &out, const Polynomial &poly_) {
    if (poly_.coefficents == nullptr)
        return out << 0;
    int pow = poly_.maxPow;
    bool notFirst = false;
    for (int i = poly_.maxPow - poly_.minPow; i >= 0; i--) {
        if (poly_.coefficents[i] == 1 && pow == 1) {
            if (notFirst)
                out << "+";
            out << "x";
        } else if (poly_.coefficents[i] == -1 && pow == 1)
            out << "-x";

        else if (poly_.coefficents[i] > 0 && pow == 0) {
            if (notFirst)
                out << "+";
            out << poly_.coefficents[i];
        } else if (poly_.coefficents[i] < 0 && pow == 0) {
            out << poly_.coefficents[i];
        } else if (poly_.coefficents[i] == 1 && pow != 0) {
            if (notFirst)
                out << "+";
            out << "x" << "^" << pow;
        } else if (poly_.coefficents[i] == -1 && pow != 0)
            out << "-x" << "^" << pow;

        else if (poly_.coefficents[i] < 0 && pow == 1)
            out << poly_.coefficents[i] << "x";

        else if (poly_.coefficents[i] > 0 && pow == 1) {
            if (notFirst)
                out << "+";
            out << poly_.coefficents[i] << "x";
        } else if (poly_.coefficents[i] != 0 && pow == 0) {
            if (notFirst)
                out << "+";
            out << "1";
        } else if (poly_.coefficents[i] > 0) {
            if (notFirst)
                out << "+";
            out << poly_.coefficents[i] << "x" << "^" << pow;
        } else if (poly_.coefficents[i] < 0)
            out << poly_.coefficents[i] << "x" << "^" << pow;

        pow--;
        notFirst = true;
    }
    std::cout << " ";
    return out;
}

//fixed * from *=
Polynomial &Polynomial::operator*=(const Polynomial &poly_){
    if (coefficents == nullptr || poly_.coefficents == nullptr) {
        *this = Polynomial();
        return *this;
    }
    int result_min = minPow + poly_.minPow;
    int result_max = maxPow + poly_.maxPow;
    int res_size = result_max - result_min + 1;
    int *result_coeffs = new int[res_size];
    for (int i = 0; i < res_size; ++i) {
        result_coeffs[i] = 0;
    }
    for (int i = size - 1; i >= 0; i--) {
        for (int j = poly_.size - 1; j >= 0; j--) {
            result_coeffs[i + j] += coefficents[i] * poly_.coefficents[j];
        }
    }
    size = res_size;
    delete[] coefficents;
    minPow = result_min;
    maxPow = result_max;
    coefficents = result_coeffs;
    return *this;
}

Polynomial operator*(const Polynomial &poly1_, const Polynomial &poly2_) {
    auto result = Polynomial(poly1_);
    result *= poly2_;
    return result;
}

Polynomial operator*(const int &coef, const Polynomial &poly_) {
    int *result = new int[poly_.size];
    for (int i = 0; i < poly_.size; ++i) {
        result[i] = poly_.coefficents[i];
        result[i] *= coef;
    }
    return Polynomial(poly_.minPow, poly_.maxPow, result);
}

Polynomial operator*(const Polynomial &poly2_, const int &coef) {
    return coef * poly2_;
}

Polynomial &Polynomial::operator/=(const int &coef) {
    //fixed for_each - fixed
    auto division = [coef](int &n) { n /= coef; };
    std::for_each(coefficents, coefficents + size, division);
    //fixed make another function for it - fixed
    removeZero();
    return *this;
}

//fixed methods not from capital letter
Polynomial &Polynomial::removeZero(){
    int i = 0;
    bool not_null = false;
    while (!not_null) {
        if (coefficents[i] == 0) {
            i++;
            minPow++;
        } else
            not_null = true;
    }
    int from = i;
    i = size - 1;
    not_null = false;
    while (!not_null) {
        if (coefficents[i] == 0) {
            i--;
            maxPow--;
        } else
            not_null = true;
    }
    i = 0;
    int to = i;
    int *result = new int[maxPow - minPow + 1];
    for (int j = 0; j <= to - from + 1; ++j) {
        result[j] = coefficents[j + from];
    }
    delete[] coefficents;
    coefficents = result;
    return *this;
}

Polynomial operator/(const Polynomial &poly_, int coef) {
    Polynomial result(poly_);
    result /= coef;
    return result;
}


std::istream &operator>>(std::istream &in, Polynomial &poly_) {
    in >> poly_.minPow;
    in >> poly_.maxPow;
    int *result = new int[poly_.size];
    for (int i = 0; i < poly_.size; ++i) {
        in >> result[i];
    }
    poly_.coefficents = result;
    return in;
}

int &Polynomial::operator[](const int coef) {
    if (coef > maxPow) {
        int *result_coeffs = new int[coef - minPow + 1];
        for (int i = 0; i < size; ++i) {
            result_coeffs[i] = coefficents[i];
        }
        delete[] coefficents;
        coefficents = result_coeffs;
        int new_size = coef - minPow + 1;
        for (int i = size; i < new_size; ++i) {
            coefficents[i] = 0;
        }
        maxPow = coef;
        size = new_size;
    }
    return coefficents[maxPow - minPow];
}

int Polynomial::operator[](int coef) const {
    if (coef > size)
        return 0;
    return coefficents[coef];
}

bool operator!=(const Polynomial &poly1_, const Polynomial &poly2_) {
    return !(poly2_ == poly1_);
}

[[maybe_unused]] double Polynomial::get(int root) const {
    double result = 0;
    for (int i = 0; i < size; ++i) {
        result += coefficents[i] * pow(root, minPow + i);
    }
    return result;
}

Polynomial operator-(const Polynomial &poly_) {
    int *result = new int[poly_.size];
    for (int i = 0; i < poly_.size; ++i) {
        result[i] = -poly_.coefficents[i];
    }
    return Polynomial(poly_.minPow, poly_.maxPow, result);
}

Polynomial &Polynomial::operator+=(const Polynomial &poly_) {
    plusOrMinus(false, poly_);
    return *this;
}

//fixed copy-paste from +=
Polynomial &Polynomial::operator-=(const Polynomial &poly_) {
    plusOrMinus(true, poly_);
    return *this;
}

Polynomial &Polynomial::plusOrMinus(bool isNegative, const Polynomial &poly_) {
    if (poly_.coefficents == nullptr)
        return *this;
    else if (coefficents == nullptr && !isNegative) {
        delete[] coefficents;
        *this = poly_;
        return *this;
    } else if (coefficents == nullptr) {
        delete[] coefficents;
        *this = -poly_;
        return *this;
    }
    bool equal_min = false;
    bool not_equal = false;
    int result_min = std::min(minPow, poly_.minPow);
    int result_max = std::max(maxPow, poly_.maxPow);
    int counter_min = abs(minPow - poly_.minPow);
    int counter_max = result_max - result_min - counter_min + 1 - std::abs(maxPow - poly_.maxPow);
    int *result_coeff = new int[result_max - result_min + 1];
    int k = 0;
    for (int i = 0; i < result_max - result_min + 1; ++i) {
        if (i == counter_min)
            equal_min = true;
        if (k > counter_max)
            not_equal = true;
        if (!equal_min && !isNegative) {
            if (minPow < poly_.minPow)
                result_coeff[i] = coefficents[i];
            else
                result_coeff[i] = poly_.coefficents[i];
        }
        else if (!equal_min && isNegative) {
            if (minPow < poly_.minPow)
                result_coeff[i] = coefficents[i];
            else
                result_coeff[i] = -poly_.coefficents[i];
        } else if (!not_equal && !isNegative) {
            if (minPow < poly_.minPow) {
                result_coeff[i] = coefficents[i] + poly_.coefficents[k];
                k++;
            } else {
                result_coeff[i] = coefficents[k] + poly_.coefficents[i];
                k++;
            }
        } else if (!not_equal && isNegative) {
            if (minPow < poly_.minPow) {
                result_coeff[i] = coefficents[i] - poly_.coefficents[k];
                k++;
            } else {
                result_coeff[i] = coefficents[k] - poly_.coefficents[i];
                k++;
            }
        }else if (!isNegative){
            if (maxPow > poly_.maxPow) {
                result_coeff[i] = coefficents[k];
                k++;
            } else {
                result_coeff[i] = poly_.coefficents[k];
                k++;
            }
        }else {
            if (maxPow > poly_.maxPow) {
                result_coeff[i] = coefficents[k];
                k++;
            } else {
                result_coeff[i] = -poly_.coefficents[k];
                k++;
            }
        }
    }
    delete[] coefficents;
    coefficents = result_coeff;
    minPow = result_min;
    maxPow = result_max;
    return *this;
}

//fixed change to fixed, not add it
Polynomial operator-(const Polynomial &poly1_, const Polynomial &poly2_) {
    Polynomial result = poly1_;
    result -= poly2_;
    return result;
}