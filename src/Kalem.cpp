/* MIT License
#
# Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */


#include <iostream>
#include <string>

#include "../include/Kalem.hpp"
#include "../include/Kalem_Structure.hpp"
#include "../include/Kalem_Codegen.hpp"

#include "../include/libs/FileSystemPlusPlus.hpp"
#include "../include/libs/ExecutePlusPlus.hpp"
#include "../include/libs/StringTools.hpp"

kalem_t
Kalem::Init(std::string kl_file_name) {
    kalem_t init;
    
    init.kl_file_name = kl_file_name;
    init.kl_file_data = fsplusplus::ReadFileWithReturn(kl_file_name);
    
    return init;
}


int main(int argc, char** argv) {
    if(argc < 2) {
        std::cout << "Fegeya Kalem compiler\n";
        std::cout << "Usage: " << argv[0] << " [options] file...\n";
        std::cout << "Options:\n" <<
            "--cpp : Output C++ code\n";
        
        return 0;
    }
    
    Kalem kalem;
    KalemStructure _structure;
    ExecutePlusPlus _exec;
    
    bool option = false;

    std::string kl_source_file(argv[1]);
    
    if(kl_source_file == "--cpp" && argc > 2) {
        kl_source_file.erase();

        kl_source_file.append(argv[2]);

        option = true;
    }

    kl_source_file = stringtools::EraseAllSubString(kl_source_file, ".kalem");
    
    kalem_t _main = kalem.Init(kl_source_file + ".kalem");
    
    kl_codegen __codegen_ = _structure.ReadSource(_main);
    
    fsplusplus::CreateFile(kl_source_file + ".cpp", __codegen_.kl_generated);
    
    _exec.RunFunction("clang++ -std=c++17 " + kl_source_file + ".cpp -o " + kl_source_file);

    if(option == false) {
        _exec.RunFunction("rm -f " + kl_source_file + ".cpp");
    }
    
    return 0;
}
