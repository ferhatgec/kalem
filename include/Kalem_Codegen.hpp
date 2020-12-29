/* MIT License
#
# Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */


#ifndef KALEM_CODEGEN_HPP
#define KALEM_CODEGEN_HPP

#include <iostream>
#include <string>

#include "Kalem.hpp"

typedef struct {
public:
	std::string kl_generated = "/* Generated by Kalem - DO NOT MODIFY */\n";
} kl_codegen;

class Kalem_Codegen {
public:
	kl_codegen _codegen;
		
	void Kl_Codegen(KALEM_TOKEN _token, std::string _variable, std::string _append);
};

#endif // KALEM_CODEGEN_HPP
