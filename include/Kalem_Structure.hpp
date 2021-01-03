/* MIT License
#
# Copyright (c) 2020-2021 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */


#ifndef KALEM_STRUCTURE_HPP
#define KALEM_STRUCTURE_HPP

#include <iostream>
#include <string>
#include <vector>

#include "Kalem.hpp"
#include "Kalem_Codegen.hpp"

class KalemStructure {
public:
	kl_codegen ReadSource(kalem_t kalem);
	
	std::vector<std::string> MakeTokenizable(std::string _data);
};


#endif // KALEM_STRUCTURE_HPP
