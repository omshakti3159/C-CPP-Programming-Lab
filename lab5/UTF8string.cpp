#include "UTF8string.hpp"
#include "utf8.h"
#include <iostream>


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
		// Here, we need to keep track of the "offset" for utf8_search
		// so that the program won't be stuck in an infinite loop
		// if the "remove" string is part of the "replacement" string.
		offset = p - m_s.c_str() + rep_len;
		m_s = m_s.substr(0, p - m_s.c_str()) + replacement.value() +
			string(p + rem_len);
		// cout << m_s.c_str() << endl;
		// cout << offset << endl;
	}

}

// Lab 5
ostream &operator<<(ostream &os,
					const UTF8string &ustring) {
	os << ustring.m_s;
	return os;
}

UTF8string &operator+(UTF8string &ustring1, 
						UTF8string &ustring2) {
	UTF8string *sum = new UTF8string(ustring1.value() + ustring2.value());
	return *sum;
}

void UTF8string::operator+=(const UTF8string &ustring) {
	m_s += ustring.m_s;
}

UTF8string &operator*(UTF8string &ustring, int times) {
	UTF8string *result = new UTF8string("");
	int i;
	for (i = 0; i < times; i++) {
		*result += ustring;
	}
	return *result;
}

UTF8string &operator*(int times, UTF8string &ustring) {
	return ustring * times;
}

UTF8string &operator!(UTF8string &ustring) {

	UTF8string *result = new UTF8string("");

	unsigned char * s = (unsigned char *) ustring.m_s.c_str();
	int length = 0;
	while(*s) {
		length = isutf8(s);
		result->m_s.insert(0, (const char*) s, length);
		_utf8_incr(s);
	}
	return *result;
}
