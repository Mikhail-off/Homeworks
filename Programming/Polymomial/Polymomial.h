#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

template <typename T>
class Polynomial {
private:
    std::vector<T> data;
    // Remove of zeros
    void Remove_zeros() {
        while (data.empty() == false && data.back() == 0) {
            data.pop_back();
        }
    }

public:
    // Constructor from vector
    Polynomial(const std::vector<T>& d) : data(d) {
        Remove_zeros();
    }
    // Constructor from one coefficient
    Polynomial(const T& temp = T()) {
        data.push_back(temp);
        Remove_zeros();
    }
    // Constructor from iterators
    template <typename Iter>
    Polynomial(Iter first, const Iter& last) {
        while (first != last) {
            data.push_back(*first);
            ++first;
        }
        Remove_zeros();
    }
    // Degree of polinmial
    const int Degree() const {
        return data.size() - 1;
    }
    // const access from index
    const T operator[] (size_t i) const {
        if (i >= data.size())
            return 0;
        return data[i];
    }
    // Bool operators
    bool operator == (const Polynomial<T>& other) const {
        return data == other.data;
    }
    bool operator == (const T& other) const {
        return *this == Polynomial(other);
    }
    bool operator != (const Polynomial<T>& other) const {
        return !(*this == other);
    }
    bool operator != (const T& other) const {
        return !(*this == Polynomial(other));
    }
    // @= operators
    Polynomial<T>& operator += (const Polynomial<T>& other) {
        data.resize(std::max(data.size(), other.data.size()));
        for (size_t i = 0; i != data.size(); ++i) {
            data[i] += other[i];
        }
        Remove_zeros();
        return *this;
    }
    Polynomial<T>& operator += (const T& other) {
        *this += Polynomial(other);
        Remove_zeros();
        return *this;
    }
    Polynomial<T>& operator -= (const Polynomial<T>& other) {
        data.resize(std::max(data.size(), other.data.size()));
        for (size_t i = 0; i != data.size(); ++i) {
            data[i] -= other[i];
        }
        Remove_zeros();
        return *this;
    }
    Polynomial<T>& operator -= (const T& other) {
        *this -= Polynomial(other);
        Remove_zeros();
        return *this;
    }
    Polynomial<T>& operator *= (const Polynomial<T>& other) {
        std::vector<T> result(data.size() + other.data.size());
        for (size_t i = 0; i != data.size(); ++i) {
            for (size_t j = 0; j != other.data.size(); ++j) {
                result[i + j] += data[i] * other.data[j];
            }
        }
        data = result;
        Remove_zeros();
        return *this;
    }
    Polynomial<T>& operator /= (const Polynomial<T>& other) {
        Polynomial result, devidend(*this);
        if ((*this).Degree() < other.Degree()) {
            data = std::vector<int>(0);
            return *this;
        }
        result.data.resize(devidend.Degree() - other.Degree() + 1);
        while (devidend.Degree() >= other.Degree()) {
            size_t i = devidend.Degree() - other.Degree();
            result.data[i] = devidend.data.back() / other.data.back();
            Polynomial<T> temp(result);
            temp.data[i] *= 2;
            temp -= result;
            devidend -= temp * other;
        }
        data = result.data;
        Remove_zeros();
        return *this;
    }
    // Iterators
    typename std::vector<T>::const_iterator begin() const {
        return data.begin();
    }
    typename std::vector<T>::const_iterator end() const {
        return data.end();
    }
    // value f(x)
    const T operator() (T x) const {
        T result = data.back();
        for (size_t i = 1; i != data.size(); ++i) {
            result = result * x + data[data.size() - i - 1];
        }
        return result;
    }
    // Composition f(g(x))
    Polynomial<T> operator & (Polynomial<T> x) const {
        Polynomial<T> result(data.back());
        for (size_t i = 1; i != data.size(); ++i) {
            result = result * x + data[data.size() - i - 1];
        }
        return result;
    }
    // Mod
    Polynomial<T> operator % (const Polynomial<T>& other) const {
        return (*this) - ((*this / other) * other);
    }
    // gcd
    Polynomial<T> operator , (const Polynomial<T>& other) const {
        if (other == 0) {
            return ((*this) / Polynomial((*this).data.back()));
        }
        return (other, (*this) % other);
    }
};

// operators +, -, *
template <typename T>
const Polynomial<T> operator + (const Polynomial<T>& self, const Polynomial<T>& other) {
    Polynomial<T> result(self);
    result += other;
    return result;
}
template <typename T>
const Polynomial<T> operator + (const Polynomial<T>& self, const T& other) {
    Polynomial<T> result(self);
    result += other;
    return result;
}
template <typename T>
const Polynomial<T> operator + (const T& other, const Polynomial<T>& self) {
    return self + other;
}
template <typename T>
const Polynomial<T> operator - (const Polynomial<T>& self, const Polynomial<T>& other) {
    Polynomial<T> result(self);
    result -= other;
    return result;
}
template <typename T>
const Polynomial<T> operator - (const Polynomial<T>& self, const T& other) {
    Polynomial<T> result(self);
    result -= other;
    return result;
}
template <typename T>
const Polynomial<T> operator - (const T& other, const Polynomial<T>& self) {
    Polynomial<T> second(other);
    return second - self;
}
template <typename T>
const Polynomial<T> operator * (const Polynomial<T>& self, const Polynomial<T>& other) {
    Polynomial<T> result(self);
    result *= other;
    return result;
}
template <typename T>
const Polynomial<T> operator * (const Polynomial<T>& self, const T& other) {
    Polynomial<T> result(self);
    result *= other;
    return result;
}
template <typename T>
const Polynomial<T> operator * (const T& other, const Polynomial<T>& self) {
    return self * other;
}
template<typename T>
const Polynomial<T> operator / (const Polynomial<T>& self, const Polynomial<T>& other) {
    Polynomial<T> temp(self);
    temp /= other;
    return temp;
}

// out
template <typename T>
std::ostream& operator <<(std::ostream& out, const Polynomial<T>& self) {
    std::string result = "";
    if (self.Degree() == -1) {
        out << 0;
        return out;
    }
    for (int i = 0; i != self.Degree() + 1; ++i) {
        if (self[i] == 0)
            continue;
        std::string degr, coef;
        coef = "";
        if (self[i] > 0)
            coef = "+";
        if (self[i] == -1 && i != 0)
            coef = "-";
        if ((self[i] != 1 && self[i] != -1) || i == 0) {
            coef += std::to_string(self[i]);
            if (i != 0)
                coef += "*";
        }
        degr = "";
        if (i != 0 && i != 1)
            degr = "x^" + std::to_string(i);
        if (i == 1)
            degr = "x";
        result = coef + degr + result;
    }
    if (result[0] == '+')
        result = result.substr(1);
    out << result;
    return out;
}
