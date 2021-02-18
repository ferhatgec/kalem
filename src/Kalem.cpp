/* MIT License
#
# Copyright (c) 2020-2021 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */


#include <iostream>
#include <string>
#include <vector>

#include "../include/Kalem.hpp"
#include "../include/Kalem_Structure.hpp"
#include "../include/Kalem_Codegen.hpp"
#include "../include/Kalem_Hash_Checker.hpp"

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
        std::cout << "Fegeya Kalem compiler - "
                  << KALEM_VERSION
                  << "\nUsage: " << argv[0] << " [options] file..."
                  << "\nOptions:"
                  << "\n--cpp : Output C++ code\n-----"
                  << "\nkalem file.kalem -o=output_object\n";
        
        return 0;
    }
    
    Kalem kalem;
    KalemStructure _structure;
    KalemHashChecker hash_checker;

    ExecutePlusPlus _exec;

    kl_codegen __codegen_;
    kl_codegen temp_codegen;

    kalem_t _main;

    bool option = false;

    /* kalem test1.kalem test1.kalem */
    std::string kl_source_file(argv[1]);
    std::string kl_output_file = "";
    
    if(kl_source_file == "--cpp" && argc > 2) {
        kl_source_file.erase();

        kl_source_file.append(argv[2]);

        option = true;
    }

    for(auto i = int{1}; i < argc; i++) {
        if(argv[i][0] == '-' && argv[i][1] == 'o' && argv[i][2] == '=') {
            kl_output_file.append(argv[i]);
            kl_output_file = kl_output_file.erase(0, 3);
        }
    }

    kl_source_file = stringtools::EraseAllSubString(kl_source_file, ".kalem");

    _main = kalem.Init(kl_source_file + ".kalem");

    if(hash_checker.HashInit(kl_source_file + ".kalem") == false) {
        __codegen_ = _structure.ReadSource(_main);
    }

    if(fsplusplus::IsExistFile(fsplusplus::GetCurrentWorkingDir()
        + "/"
        + kl_source_file
        + ".cpp")) {
        _exec.RunFunction("rm -f " + kl_source_file + ".cpp");
    }

    fsplusplus::CreateFile(kl_source_file + ".cpp", __codegen_.kl_generated);

    for (auto i = __codegen_.kl_source_files.begin(); i != __codegen_.kl_source_files.end(); ++i) {
        _main = kalem.Init(*i + ".kalem");


        if(__codegen_.kl_hash_cache == true) {
            if(hash_checker.HashInit(*i + ".kalem") == true) {
                std::cout << "Skipped : " + *i + ".kalem\n";
            }
        }

        temp_codegen = _structure.ReadSource(_main);

        if(fsplusplus::IsExistFile(fsplusplus::GetCurrentWorkingDir()
                                   + "/"
                                   + *i
                                   + ".hpp")) {
            _exec.RunFunction("rm -f " + *i + ".hpp");
        }

        if(temp_codegen.kl_header_file == true) {
            temp_codegen.kl_generated.append("\n#endif");
        }

        fsplusplus::CreateFile(*i + ".hpp", temp_codegen.kl_generated);

        if(__codegen_.kl_hash_cache == true) {
            hash_checker.HashCreate(*i + ".kalem");
        }
    }

    if(kl_output_file == "") {
        kl_output_file = kl_source_file;
    }

    if(__codegen_.kl_output != "") {
        kl_output_file = __codegen_.kl_output;
    }

    // TODO: Create !flag("stdflag=...")
    _exec.RunFunction(__codegen_.kl_cpp_compiler
        + " "
        + __codegen_.kl_cpp_include_dirs
        + " -std="
        + __codegen_.kl_cpp_standard
        + " "
        + __codegen_.kl_cpp_flags
        + " "
        + __codegen_.kl_cpp_sysroot
        + " "
        + kl_source_file
        + ".cpp -o " + kl_output_file);

    if(option == false && __codegen_.kl_cpp_output == false) {
        _exec.RunFunction("rm -f " + kl_source_file + ".cpp");
    }
    
    return 0;
}
