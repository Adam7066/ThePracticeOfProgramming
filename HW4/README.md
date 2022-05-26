# HW4 - Simulating `std::string`

```cpp
class String {
    public:
        // 1. default constructor
        // 2. copy constructor
        // 3. constructor with one parameter with type const char *
        // 4. destructor
        // 5. size()
        // 6. c_str()
        // 7. operator []
        // 8. operator +=
        // 9. clear()
        // 10. operator =
        // 11. swap()
    private:
        char *str_ = nullptr;
        size_t size_ = 0, capacity_ = 0;
};
// A. relational operators (<, >, <=, >=, ==, !=)
// B. operator <<, >>
// C. operators +
```