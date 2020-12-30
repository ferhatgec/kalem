/* MIT License
#
# Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */


#ifndef KALEM_HPP
#define KALEM_HPP

#include <iostream>
#include <string>

#define _KALEM_INT      "int"
#define _KALEM_UNSIGNED "unsign"
#define _KALEM_STRING   "string"
#define _KALEM_CHAR     "char"

#define _KALEM_IMPORT "#import"
#define _KALEM_MAIN   "@main"
#define _KALEM_RETURN "@return"
#define _KALEM_PRINT  "@print"

#define _KALEM_VOID   "void"

#define _KALEM_LEFT_CURLY_BRACKET "{"
#define _KALEM_RIGHT_CURLY_BRACKET "}"

#define _KALEM_NEWLINE "\n"

#define _CPP_KALEM_UNSIGNED "unsigned"

#define _CPP_KALEM_INCLUDE "#include"
#define _CPP_KALEM_STRING "std::string"
#define _CPP_KALEM_MAIN "main()"
#define _CPP_KALEM_RETURN "return"
#define _CPP_KALEM_PRINT "std::cout"

enum KALEM_TOKEN {
	KALEM_INT = 1,
	KALEM_UNSIGNED,
	KALEM_STRING,
	KALEM_IMPORT,
	KALEM_MAIN,
	KALEM_RETURN,
	KALEM_PRINT,
	KALEM_FUNCTION,
	KALEM_FUNCTION_CALL,
	
	KALEM_LEFT_CURLY_BRACKET,
	KALEM_RIGHT_CURLY_BRACKET,
	
	KALEM_NEWLINE,
};

typedef struct {
public:
	std::string kl_file_name;
	std::string kl_file_data;
} kalem_t;

class Kalem {
public:
	kalem_t Init(std::string kl_file_name);
};


#endif // KALEM_HPP
