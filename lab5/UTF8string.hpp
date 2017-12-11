#ifndef UTF8STRING_HPP
#define UTF8STRING_HPP

#include <iostream>
#include <string>

// Well, as instructed by the professor, this time
// I can modify this file whatever I want hahahahaha

class UTF8string {
      std::string  m_s;

  public:
      // Constructors - No code required
      UTF8string(){ };
      UTF8string(const char *s) {m_s = std::string(s);};
      UTF8string(std::string s) {m_s = s;};
      // 
      // The four following functions need to be coded
      // in UTF8string.cpp
      //
      size_t  length();  // Number of UTF-8 characters in the string
      size_t  bytes();   // Number of bytes in the string
      // IMPORTANT: for find(), 1st character = 1 (not zero)
      // Return 0 if not found
      int     find(std::string substr);
      void    replace(UTF8string remove, UTF8string replacement);
      // ---------------------------------------
      // value() is for checking what was done
      // No code required
      std::string  value() {return m_s;}; 

      // Lab 5
      // Operator <<
      friend std::ostream &operator<<(std::ostream &os,
                                    const UTF8string &ustring);
      // Operator +
      friend UTF8string &operator+(UTF8string &ustring1, 
                                    UTF8string &ustring2);
      // Operator +=
      void operator+=(const UTF8string &ustring);
      // Operator *
      friend UTF8string &operator*(UTF8string &ustring,
                                    int times);
      friend UTF8string &operator*(int times, 
                                    UTF8string &ustring);
      // Operator !
      friend UTF8string &operator!(UTF8string &ustring);
      };

#endif
