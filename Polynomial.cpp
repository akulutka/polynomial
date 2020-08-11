#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
class Polynomial {
 public:
    std::vector<T> __coef;

    Polynomial(const std::vector<T>& _coef) {
        if (_coef.size() == 0) {
            __coef.resize(1);
            __coef[0] = static_cast<T>(0);
        } else {
            __coef.reserve(_coef.size());
            for (size_t i = 0; i < _coef.size(); ++i) {
                __coef.emplace_back(_coef[i]);
            }
            while (__coef.size() > 1 && __coef.back() == static_cast<T>(0)) {
                __coef.pop_back();
            }
        }
    }

    Polynomial(const T& scal) {
        __coef.resize(1);
        __coef[0] = scal;
    }

    Polynomial() {
        T scal = static_cast<T>(0);
        __coef.resize(1);
        __coef[0] = scal;
    }

    template <typename IterType>
    Polynomial(IterType begin, IterType end) {
        IterType start = begin;
        __coef.resize(0);
        while (start != end) {
            __coef.push_back(*start);
            ++start;
        }
        while (__coef.size() > 1 && __coef.back() == static_cast<T>(0)) {
            __coef.pop_back();
        }
    }

    const T operator[](size_t deg) const {
        if (deg >= __coef.size() || deg < 0) {
            return static_cast<T>(0);
        }
        return __coef[deg];
    }

    T operator()(const T& arg) const {
        if (__coef.size() == 0) {
            return static_cast<T>(0);
        }
        T res = static_cast<T>(0);
        T argdeg = static_cast<T>(1);
        for (size_t i = 0; i < __coef.size(); ++i) {
            res += __coef[i] * argdeg;
            argdeg *= arg;
        }
        return res;
    }

    int Degree() const {
        int res = static_cast<int>(__coef.size()) - 1;
        if (res == -1) {
            return res;
        }
        while (res >= 0 && __coef[res] == static_cast<T>(0)) {
            --res;
        }
        return res;
    }

    typedef typename std::vector<T>::const_iterator ConstPolyIter;

    ConstPolyIter begin() const {
        return __coef.cbegin();
    }

    ConstPolyIter end() const {
        return __coef.cend();
    }
};

template <typename T>
bool operator==(const Polynomial<T>& l, const Polynomial<T>& r) {
    Polynomial<T> sub = l - r;
    return (sub.Degree() == -1);
}

template <typename T>
bool operator==(const Polynomial<T>& l, const T& r) {
    return l == Polynomial<T>(r);
}

template <typename T>
bool operator==(const T& l, const Polynomial<T>& r) {
    return Polynomial<T>(l) == r;
}

template <typename T>
bool operator!=(const Polynomial<T>& l, const Polynomial<T>& r) {
    return !(l == r);
}

template <typename T>
bool operator!=(const Polynomial<T>& l, const T& r) {
    return !(l == r);
}

template <typename T>
bool operator!=(const T& l, const Polynomial<T>& r) {
    return !(l == r);
}

template <typename T>
Polynomial<T> operator+(const Polynomial<T>& l, const Polynomial<T>& r) {
    std::vector<T> ncoef;
    size_t mnsize = std::min(l.__coef.size(), r.__coef.size());
    size_t mxsize = std::max(l.__coef.size(), r.__coef.size());
    ncoef.reserve(mxsize);
    for (size_t i = 0; i < mnsize; ++i) {
        ncoef.emplace_back(l.__coef[i] + r.__coef[i]);
    }
    if (l.__coef.size() <= r.__coef.size()) {
        for (size_t i = mnsize; i < mxsize; ++i) {
            ncoef.emplace_back(r.__coef[i]);
        }
    } else {
        for (size_t i = mnsize; i < mxsize; ++i) {
            ncoef.emplace_back(l.__coef[i]);
        }
    }
    return Polynomial<T>(ncoef);
}

template <typename T>
Polynomial<T> operator+(const Polynomial<T>& l, const T& r) {
    return l + Polynomial<T>(r);
}

template <typename T>
Polynomial<T> operator+(const T& l, const Polynomial<T>& r) {
    return Polynomial<T>(l) + r;
}

template <typename T>
Polynomial<T> operator-(const Polynomial<T>& l, const Polynomial<T>& r) {
    std::vector<T> ncoef;
    size_t mnsize = std::min(l.__coef.size(), r.__coef.size());
    size_t mxsize = std::max(l.__coef.size(), r.__coef.size());
    ncoef.reserve(mxsize);
    for (size_t i = 0; i < mnsize; ++i) {
        ncoef.emplace_back(l.__coef[i] - r.__coef[i]);
    }
    if (l.__coef.size() <= r.__coef.size()) {
        for (size_t i = mnsize; i < mxsize; ++i) {
            ncoef.emplace_back(-r.__coef[i]);
        }
    } else {
        for (size_t i = mnsize; i < mxsize; ++i) {
            ncoef.emplace_back(l.__coef[i]);
        }
    }
    return Polynomial<T>(ncoef);
}

template <typename T>
Polynomial<T> operator-(const Polynomial<T>& l, const T& r) {
    return l - Polynomial<T>(r);
}

template <typename T>
Polynomial<T> operator-(const T& l, const Polynomial<T>& r) {
    return Polynomial<T>(l) - r;
}

template <typename T>
Polynomial<T>& operator+=(Polynomial<T>& l, const Polynomial<T>& r) {
    l = l + r;
    return l;
}

template <typename T>
Polynomial<T>& operator+=(Polynomial<T>& l, const T& r) {
    l = l + r;
    return l;
}

template <typename T>
Polynomial<T>& operator-=(Polynomial<T>& l, const Polynomial<T>& r) {
    l = l - r;
    return l;
}

template <typename T>
Polynomial<T>& operator-=(Polynomial<T>& l, const T& r) {
    l = l - r;
    return l;
}

template <typename T>
Polynomial<T> operator-(const Polynomial<T>& l) {
    Polynomial<T> res(l.__coef);
    for (size_t i = 0; i < res.__coef.size(); ++i) {
        res.__coef[i] = -res.__coef[i];
    }
    return res;
}

template <typename T>
Polynomial<T> operator+(const Polynomial<T>& l) {
    return l;
}

template <typename T>
Polynomial<T> operator*(const Polynomial<T>& l, const Polynomial<T>& r) {
    std::vector<T> mulRes(l.__coef.size() + r.__coef.size() - 1);
    for (size_t i = 0; i < l.__coef.size(); ++i) {
        for (size_t j = 0; j < r.__coef.size(); ++j) {
            mulRes[i + j] += l.__coef[i] * r.__coef[j];
        }
    }
    while (mulRes.size() > 0 && mulRes.back() == static_cast<T>(0)) {
        mulRes.pop_back();
    }
    Polynomial<T> res(mulRes);
    return res;
}

template <typename T>
Polynomial<T> operator*(const Polynomial<T>& l, const T& r) {
    return l * Polynomial<T>(r);
}

template <typename T>
Polynomial<T> operator*(const T& l, const Polynomial<T>& r) {
    return Polynomial<T>(l) * r;
}

template <typename T>
Polynomial<T>& operator*=(Polynomial<T>& l, const Polynomial<T>& r) {
    l = l * r;
    return l;
}

template <typename T>
Polynomial<T>& operator*=(Polynomial<T>& l, const T& r) {
    l = l * r;
    return l;
}

template <typename T>
Polynomial<T> operator/(const Polynomial<T>& l, const Polynomial<T>& r) {
    if (l.Degree() < r.Degree()) {
        return Polynomial<T>(static_cast<T>(0));
    }
    Polynomial<T> quo;
    Polynomial<T> rem = Polynomial<T>(l.__coef);

    while (!(rem == static_cast<T>(0)) && rem.Degree() >= r.Degree()) {
        std::vector<T> tmpCoeffs;
        tmpCoeffs.resize(rem.Degree() - r.Degree() + 1);
        tmpCoeffs[tmpCoeffs.size() - 1] = rem.__coef.back() / r.__coef.back();
        Polynomial<T> tmp(tmpCoeffs);
        quo += tmp;
        rem -= tmp * r;
    }
    return quo;
}

template <typename T>
Polynomial<T> operator%(const Polynomial<T>& l, const Polynomial<T>& r) {
    if (l.Degree() < r.Degree()) {
        return l;
    }
    Polynomial<T> quo;
    Polynomial<T> rem = Polynomial<T>(l.__coef);

    while (!(rem == static_cast<T>(0)) && rem.Degree() >= r.Degree()) {
        std::vector<T> tmpCoeffs;
        tmpCoeffs.resize(rem.Degree() - r.Degree() + 1);
        tmpCoeffs[tmpCoeffs.size() - 1] = rem.__coef.back() / r.__coef.back();
        Polynomial<T> tmp(tmpCoeffs);
        quo += tmp;
        rem -= tmp * r;
    }
    return rem;
}

template <typename T>
Polynomial<T> operator,(const Polynomial<T>& l, const Polynomial<T>& r) {
    if (r == Polynomial<T>(static_cast<T>(0))) {
        return l / Polynomial<T>(l.__coef.back());
    }
    return (r, l % r);
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Polynomial<T> r) {
    if (r.__coef.size() == 0) {
        out << 0;
        return out;
    }
    if (r.__coef.size() == 1) {
        out << r.__coef[0];
        return out;
    }
    T one = static_cast<T>(1);
    T zero = static_cast<T>(0);
    T mone = static_cast<T>(-1);
    bool first = true;
    for (size_t i = r.__coef.size() - 1; i >= 0; --i) {
        if (r.__coef[i] == zero) {
            if (i == 0) {
                break;
            }
            continue;
        }
        if (first) {
            if (r.__coef[i] == one) {
                if (i > 0) {
                    out << "x";
                } else {
                    out << "1";
                }
                if (i > 1) {
                    out << "^" << i;
                }
            } else if (r.__coef[i] == mone) {
                if (i > 0) {
                    out << "-x";
                } else {
                    out << "-1";
                }
                if (i > 1) {
                    out << "^" << i;
                }
            } else {
                if (i > 0) {
                    out << r.__coef[i] << "*x";
                } else {
                    out << r.__coef[i];
                }
                if (i > 1) {
                    out << "^" << i;
                }
            }
            first = false;
        } else {
            if (r.__coef[i] == one) {
                if (i > 0) {
                    out << "+x";
                } else {
                    out << "+1";
                }
                if (i > 1) {
                    out << "^" << i;
                }
            } else if (r.__coef[i] == mone) {
                if (i > 0) {
                    out << "-x";
                } else {
                    out << "-1";
                }
                if (i > 1) {
                    out << "^" << i;
                }
            } else {
                if (i > 0) {
                    if (r.__coef[i] > zero) {
                        out << "+" << r.__coef[i] << "*x";
                    } else if (r.__coef[i] < zero) {
                        out << r.__coef[i] << "*x";
                    }
                } else {
                    if (r.__coef[i] > zero) {
                        out << "+" << r.__coef[i];
                    } else if (r.__coef[i] < zero) {
                        out << r.__coef[i];
                    }
                }
                if (i > 1) {
                    out << "^" << i;
                }
            }
        }
        if (i == 0) {
            break;
        }
    }
    return out;
}

template <typename T>
Polynomial<T> operator&(const Polynomial<T>& l, const Polynomial<T>& r) {
    Polynomial<T> npol;
    Polynomial<T> argdeg = Polynomial<T>(1);
    for (size_t i = 0; i < l.__coef.size(); i++) {
        npol += (l.__coef[i] * argdeg);
        argdeg *= r;
    }
    return npol;
}

template <typename T>
Polynomial<T> operator&(const Polynomial<T>& l, const T& r) {
    Polynomial<T> rpol = Polynomial<T>(r);
    return l & rpol;
}

template <typename T>
Polynomial<T> operator&(const T& l, const Polynomial<T>& r) {
    Polynomial<T> lpol = Polynomial<T>(l);
    return lpol & r;
}
