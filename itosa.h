
  /* ______________________________________________________________________________________________________________ *\
    |                                                                                                              |
    |    File : rlx/itosa.h                                                                                        |
    |  Author : LimikEcho                                                                                          |
    |  Source : https://github.com/LimikEcho/rlx/blob/main/itosa.h                                                 |
    |  Manual : Introduces alternative integer-to-ASCII-like functions where the returned character array (or C++  |
    |           string) has a prefix for alphabetical sorting.  The prefix is set to "%c_", where %c is a base-62  |
    |           alphanumeric character (0-9, A-Z, a-z) representing the length of the number.                      |
    |    Note : If NULL is passed to the character array buffer, memory will be dynamically allocated, and should  |
    |           be freed when it is no longer in use.  This library does not handle freeing that memory.           |
    |    Note : This library includes <math.h>.  If you are compiling C code, you may have to link "libm.a".  You  |
    |           can do this in most compilers by adding the optional argument "-l m" (or equivalent).              |
    |______________________________________________________________________________________________________________|
  \*                                                                                                                */

#if defined(__cplusplus) && !defined(RLX_ITOSA_HPP)
#define RLX_ITOSA_HPP(name, type) \
string name(type number, short int radix) { \
	char length = number ? floor(log2(number) / log2(radix)) + 1 : 1; \
	char size = length + 47; \
	string buffer; \
	if (size > 57) { \
		size += 7; \
		if (size > 90) { \
			size += 6; \
		} \
	} \
	buffer.push_back(size); \
	buffer.push_back('_'); \
	for (short int i = length - 1; i > -1; --i) { \
		unsigned short digit = number / pow(radix, i); \
		digit %= radix; \
		digit += 48; \
		if (digit > 57) { \
			digit += 7; \
			if (digit > 90) { \
				digit += 6; \
			} \
		} \
		buffer.push_back(digit); \
	} \
	return buffer; \
}

#include <climits>
#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;

RLX_ITOSA_HPP(stosa, short int);
RLX_ITOSA_HPP(ustosa, unsigned short int);
RLX_ITOSA_HPP(itosa, int);
RLX_ITOSA_HPP(utosa, unsigned int);
RLX_ITOSA_HPP(ltosa, long int);
RLX_ITOSA_HPP(ultosa, unsigned long int);

#if defined(LLONG_MAX) && defined(ULLONG_MAX)

RLX_ITOSA_HPP(lltosa, long long int);
RLX_ITOSA_HPP(ulltosa, unsigned long long int);

#endif

#else

#include <limits.h>
#include <math.h>
#include <stdlib.h>

#endif

#ifndef RLX_ITOSA_H
#define RLX_ITOSA_H(name, type) \
void name(type number, short int radix, char **buffer) { \
	char length = number ? floor(log2(number) / log2(radix)) + 1 : 1; \
	if (!*buffer) { \
		*buffer = (char *)malloc(sizeof(char) * (length + 3)); \
	} \
	for (short int i = 0; i < length; ++i) { \
		unsigned short digit = number / pow(radix, i); \
		digit %= radix; \
		digit += 48; \
		if (digit > 57) { \
			digit += 7; \
			if (digit > 90) { \
				digit += 6; \
			} \
		} \
		(*buffer)[length - i + 1] = digit; \
	} \
	length += 47; \
	if (length > 57) { \
		length += 7; \
		if (length > 90) { \
			length += 6; \
		} \
	} \
	(*buffer)[0] = length; \
	(*buffer)[1] = '_'; \
}

RLX_ITOSA_H(stosa, short int);
RLX_ITOSA_H(ustosa, unsigned short int);
RLX_ITOSA_H(itosa, int);
RLX_ITOSA_H(utosa, unsigned int);
RLX_ITOSA_H(ltosa, long int);
RLX_ITOSA_H(ultosa, unsigned long int);

#if defined(LLONG_MAX) && defined(ULLONG_MAX)

RLX_ITOSA_H(lltosa, long long int);
RLX_ITOSA_H(ulltosa, unsigned long long int);

#endif

#endif