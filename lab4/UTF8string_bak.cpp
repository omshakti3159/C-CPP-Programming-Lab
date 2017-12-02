#include "UTF8string.hpp"
#include "utf8.h"
#include <iostream>

// Macro copied from the sqlite code
// Kind of utf8-aware p++ (From utf8.h)
#define _utf8_incr(zIn) {                        \
      if ((*(zIn++)) >= 0xc0) {                        \
         while ((*zIn & 0xc0) == 0x80) { zIn++; }      \
      }                                                \
   }

#ifdef __cplusplus
extern "C" {
#endif

	extern int utf8_charlen(unsigned char *p);
	// Returns the length in bytes, 0 if invalid
	extern int isutf8(const unsigned char *u);
	// strchr-like function for utf8 characters. Returns NULL if
	// "needle" is an invalid utf8 character.
	extern unsigned char *utf8_search(const unsigned char *haystack, 
                                  const unsigned char *needle);

#ifdef __cplusplus
}
#endif

using namespace std;

size_t UTF8string::length() {
	unsigned char * s = (unsigned char *) m_s.c_str();
	if (isutf8(s)) {
		return utf8_charlen(s);
	}
	return 0;
}

size_t UTF8string::bytes() {
	unsigned char * s = (unsigned char *) m_s.c_str();
	int sum = 0;
	while(*s) {
		sum += isutf8(s);
		_utf8_incr(s);
	}
	return sum;
}

int  UTF8string::find(string substr) {
	unsigned char * s = utf8_search(
		(unsigned char *) m_s.c_str(), 
		(unsigned char *) substr.c_str());
	if (NULL == s) {
		return 0;
	}
	return length() - utf8_charlen(s) + 1;
}

void UTF8string::replace(UTF8string remove, UTF8string replacement) {

	int rem_len = remove.bytes();
	int rep_len = replacement.bytes();

	// If remove is empty or replacement is empty, then do nothing.
	// Otherwise, keep going.
	if (!rem_len || !rep_len) {
		return;
	}

	
	char * p = NULL;
	int offset = 0;

	while (NULL != (p = (char *)utf8_search(
							(unsigned char *) m_s.c_str() + offset,
							(unsigned char *) remove.value().c_str())
					)){
		offset = p - m_s.c_str() + rep_len;
		m_s = m_s.substr(0, p - m_s.c_str()) + replacement.value() +
			string(p + rem_len);
		// cout << m_s.c_str() << endl;
		// cout << offset << endl;
	}

}
