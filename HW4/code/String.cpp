#include "String.h"

String::String() : size_(0), capacity_(1), str_(new char[1]) {
    str_[0] = '\0';
}

String::String(const char *t) : size_(strlen(t)), capacity_(size_ + 1), str_(new char[size_ + 1]) {
    strncpy(str_, t, size_ + 1);
}

String::String(const String &t) : size_(t.size_), capacity_(t.capacity_), str_(new char[size_ + 1]) {
    strncpy(str_, t.str_, size_ + 1);
}

String::~String() {
    delete[] str_;
}

size_t String::size() {
    return size_;
}

size_t String::capacity() {
    return capacity_;
}

const char * String::c_str() const {
    return str_;
}

void String::reserve(size_t n) {
    if(n >= capacity_) {
        while(capacity_ < n) capacity_ <<= 1;
        char *newStr = new char[capacity_];
        strncpy(newStr, str_, size_ + 1);
        delete[] str_;
        str_ = newStr;
    }
}

void String::clear() {
    size_ = 0;
    str_[0] = '\0';
}

void String::swap(String &t) {
    size_ ^= t.size_;
    t.size_ ^= size_;
    size_ ^= t.size_;
    capacity_ ^= t.capacity_;
    t.capacity_ ^= capacity_;
    capacity_ ^= t.capacity_;
    char *tmp = str_;
    str_ = t.str_;
    t.str_ = tmp;
}

char & String::operator[] (size_t pos) {
    return str_[pos];
}

const char & String::operator[] (size_t pos) const {
    return str_[pos];
}

String & String::operator+= (const char *t) {
    size_t tLen = strlen(t);
    size_t newSize = size_ + tLen;
    if(newSize + 1 > capacity_) reserve(newSize);
    strncpy(str_ + size_, t, tLen + 1);
    size_ = newSize;
    return *this;
}

String & String::operator+= (const String &t) {
    return operator+= (t.str_);
}

String & String::operator+= (char c) {
    char str[2] = {c, '\0'};
    return operator+= (str);
}

String & String::operator= (const char *t) {
    size_t tLen = strlen(t);
    if(tLen + 1 > capacity_) reserve(tLen);
    strncpy(str_, t, tLen + 1);
    size_ = tLen;
    return *this;
}

String & String::operator= (const String &t) {
    return operator= (t.str_);
}

String & String::operator= (char c) {
    char str[2] = {c, '\0'};
    return operator= (str);
}

String operator+ (const String &lhs, const char *rhs) {
    String tmp(lhs);
    tmp.operator += (rhs);
    return tmp;
}

String operator+ (const String &lhs, const String &rhs) {
    return operator+ (lhs, rhs.str_);
}

String operator+ (const char *lhs, const String &rhs) {
    return operator+ (rhs, lhs);
}

String operator+ (const String &lhs, char rhs) {
    char str[2] = {rhs, '\0'};
    return operator+ (lhs, str);
}

String operator+ (char lhs, const String &rhs) {
    char str[2] = {lhs, '\0'};
    return operator+ (rhs, str);
}

bool operator== (const String &lhs, const char *rhs) {
    return strncmp(lhs.str_, rhs, std::max(lhs.size_, strlen(rhs))) == 0;
}

bool operator== (const String &lhs, const String &rhs) {
    return strncmp(lhs.str_, rhs.str_, std::max(lhs.size_, rhs.size_)) == 0;
}

bool operator== (const char *lhs, const String &rhs) {
    return operator==(rhs, lhs);
}

bool operator!= (const String &lhs, const String &rhs) {
    return !operator== (lhs, rhs);
}

bool operator!= (const char *lhs, const String &rhs) {
    return !operator== (lhs, rhs);
}

bool operator!= (const String &lhs, const char *rhs) {
    return !operator== (lhs, rhs);
}

bool operator< (const String &lhs, const char *rhs) {
    return strncmp(lhs.str_, rhs, std::max(lhs.size_, strlen(rhs))) < 0;
}

bool operator< (const String &lhs, const String &rhs) {
    return strncmp(lhs.str_, rhs.str_, std::max(lhs.size_, rhs.size_)) < 0;
}

bool operator< (const char *lhs, const String &rhs) {
    return operator<(rhs, lhs);
}

bool operator<= (const String &lhs, const String &rhs) {
    return !operator>(lhs, rhs);
}

bool operator<= (const char *lhs, const String &rhs) {
    return !operator>(lhs, rhs);
}

bool operator<= (const String &lhs, const char *rhs) {
    return !operator>(lhs, rhs);
}

bool operator> (const String &lhs, const char *rhs) {
    return strncmp(lhs.str_, rhs, std::max(lhs.size_, strlen(rhs))) > 0;
}

bool operator> (const String &lhs, const String &rhs) {
    return strncmp(lhs.str_, rhs.str_, std::max(lhs.size_, rhs.size_)) > 0;
}

bool operator> (const char *lhs, const String &rhs) {
    return operator>(rhs, lhs);
}

bool operator>= (const String &lhs, const String &rhs) {
    return !operator<(lhs, rhs);
}

bool operator>= (const char *lhs, const String &rhs) {
    return !operator<(lhs, rhs);
}

bool operator>= (const String &lhs, const char *rhs) {
    return !operator<(lhs, rhs);
}

std::istream & operator>> (std::istream &is, String &t) {
    t.clear();
    char c;
    while(is.get(c) && isspace(c));
    is.putback(c);
    while(is.get(c) && !isspace(c))
        t += c;
    is.putback(c);
    return is;
}

std::ostream & operator<< (std::ostream &os, const String &t) {
    return os << t.str_;
}