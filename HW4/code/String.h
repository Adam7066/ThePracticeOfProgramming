#ifndef _String_H
#define _String_H
#include <iostream>
#include <cstring>
#include <cctype>

class String {
  private:
    size_t size_ = 0, capacity_ = 0;
    char *str_ = nullptr;
  public:
    String();
    String(const char *);
    String(const String &);
    String(std::nullptr_t) = delete;
    ~String();
    size_t size();
    size_t capacity();
    const char *c_str() const;
    void reserve(size_t);
    void clear();
    void swap(String &);
    char &operator[] (size_t);
    const char &operator[] (size_t) const;
    String & operator+= (const char *);
    String & operator+= (const String &);
    String & operator+= (char);
    String & operator= (const String &);
    String & operator= (const char *);
    String & operator= (char);
    // Non-member function
    friend String operator+ (const String &, const String &);
    friend String operator+ (const String &, const char *);
    friend String operator+ (const char *, const String &);
    friend String operator+ (const String &, char);
    friend String operator+ (char, const String &);
    friend bool operator== (const String &, const String &);
    friend bool operator== (const char *, const String &);
    friend bool operator== (const String &, const char *);
    friend bool operator!= (const String &, const String &);
    friend bool operator!= (const char *, const String &);
    friend bool operator!= (const String &, const char *);
    friend bool operator< (const String &, const String &);
    friend bool operator< (const char *, const String &);
    friend bool operator< (const String &, const char *);
    friend bool operator<= (const String &, const String &);
    friend bool operator<= (const char *, const String &);
    friend bool operator<= (const String &, const char *);
    friend bool operator> (const String &, const String &);
    friend bool operator> (const char *, const String &);
    friend bool operator> (const String &, const char *);
    friend bool operator>= (const String &, const String &);
    friend bool operator>= (const char *, const String &);
    friend bool operator>= (const String &, const char *);
    // I/O stream
    friend std::istream & operator>> (std::istream &, String &);
    friend std::ostream & operator<< (std::ostream &, const String &);
};

#endif