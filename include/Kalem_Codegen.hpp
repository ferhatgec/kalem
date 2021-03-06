/* MIT License
#
# Copyright (c) 2020-2021 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */


#ifndef KALEM_CODEGEN_HPP
#define KALEM_CODEGEN_HPP

#include <iostream>
#include <string>
#include <bits/stdc++.h>

#include "Kalem.hpp"

typedef struct {
public:
    std::string kl_generated = "/* Generated by Kalem - DO NOT MODIFY */\n";
    std::string kl_output    = "";

    std::string kl_cpp_standard     = "c++17";
    std::string kl_cpp_flags        = "-lstdc++fs";
    std::string kl_cpp_compiler     = "clang++";
    std::string kl_cpp_include_dirs = "-I/usr/include/kalem/stl/ ";
    std::string kl_cpp_sysroot      = "";

    std::vector<std::string> kl_source_files;

    bool        kl_cpp_output   = false;
    bool        kl_hash_cache   = true;

    bool        kl_header_file  = false;
} kl_codegen;

class Kalem_Codegen {
public:
    kl_codegen _codegen;
		
    void Kl_Codegen(KALEM_TOKEN _token, std::string _variable, std::string _append,
        std::string _arguments);
};

#endif // KALEM_CODEGEN_HPP
