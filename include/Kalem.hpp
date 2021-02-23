/* MIT License
#
# Copyright (c) 2020-2021 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */


#ifndef KALEM_HPP
#define KALEM_HPP

#include <iostream>
#include <string>

#define KALEM_VERSION "0.1-beta-1"

#define _KALEM_INT      "int"
#define _KALEM_UNSIGNED "unsign"
#define _KALEM_STRING   "string"
#define _KALEM_CHAR     "char"
#define _KALEM_STR      "str"

#define _KALEM_IMPORT    "#import"
#define _KALEM_MAIN      "@main"
#define _KALEM_RETURN    "@return"
#define _KALEM_PRINT     "@print"
#define _KALEM_GOTO      "@goto"
#define _KALEM_DEFINE    "#defn"

#define _KALEM_TYPED     "typed"

#define _KALEM_NAMESPACE "namespace"
#define _KALEM_CLASS     "class"

#define _KALEM_FLAG      "!flag"
#define _KALEM_LOOP      "loop"
#define _KALEM_BREAK     "break"
#define _KALEM_CONTINUE  "continue"
#define _KALEM_SWITCH    "switch"
#define _KALEM_CASE      "case"

#define _KALEM_IF        "if"
#define _KALEM_WHILE     "while"
#define _KALEM_ELSE      "els"
#define _KALEM_ELSE_IF   "elsif"

#define _KALEM_NIL       "nil"

#define _KALEM_VOID   "void"

#define _KALEM_LEFT_CURLY_BRACKET  "{"
#define _KALEM_RIGHT_CURLY_BRACKET "}"

#define _KALEM_NEWLINE "\n"

#define _CPP_KALEM_UNSIGNED "unsigned"
#define _CPP_KALEM_STR      "char"

#define _CPP_KALEM_INCLUDE "#include"
#define _CPP_KALEM_STRING  "std::string"
#define _CPP_KALEM_MAIN    "main"
#define _CPP_KALEM_RETURN  "return"
#define _CPP_KALEM_PRINT   "std::cout"
#define _CPP_KALEM_GOTO    "goto"
#define _CPP_KALEM_DEFINE  "#define"
#define _CPP_KALEM_TYPED   "typedef"

#define _CPP_KALEM_LOOP    "while"
#define _CPP_KALEM_SWITCH  "switch"
#define _CPP_KALEM_CASE    "case"

#define _CPP_KALEM_ELSE    "else"

enum KALEM_FLAG {
    KALEM_OUTPUT = 1
};

enum KALEM_TOKEN {
	KALEM_INT = 1,
	KALEM_UNSIGNED,
	KALEM_STRING,
    KALEM_CHAR,
    KALEM_STR,

	KALEM_IMPORT,
	KALEM_INCLUDE,

	KALEM_MAIN,
	KALEM_RETURN,
	KALEM_PRINT,
	KALEM_GOTO,
	KALEM_GOTO_CALL,

	KALEM_FUNCTION,
	KALEM_FUNCTION_CALL,

	KALEM_DEFINE,
    KALEM_TYPED,

	KALEM_NAMESPACE,
    KALEM_CLASS,
    KALEM_CLASS_MEMBER_VISIBILITY,

    KALEM_FLAG,
    KALEM_REQUIRED_FLAG,
    KALEM_INCLUDE_DIR,
    KALEM_ADD_SOURCE,

    KALEM_LOOP,

    KALEM_SWITCH,
    KALEM_CASE,

    KALEM_BREAK,
    KALEM_CONTINUE,

	KALEM_LEFT_CURLY_BRACKET,
	KALEM_RIGHT_CURLY_BRACKET,
	
	KALEM_NEWLINE,
	KALEM_LINK,
	KALEM_REGULAR,

	KALEM_ELSE,
	KALEM_ELSE_IF,

	KALEM_NONE
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
