/* MIT License
#
# Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <string>
#include <fstream>
#include <functional>
#include <sstream>

#include "../include/Kalem_Hash_Checker.hpp"

#include "../include/libs/FileSystemPlusPlus.hpp"

bool KalemHashChecker::HashInit(std::string file) {
    std::string _data = fsplusplus::ReadFileWithReturn(file);

    hash.hash = std::hash<std::string>{}(_data);

    _data.erase();

    if(fsplusplus::IsExistFile(fsplusplus::GetCurrentWorkingDir()
        + "/"
        + file
        + ".__kalem_hash_cache__")) {
        const std::string old_hash = fsplusplus::ReadFileWithReturn(file
            + ".__kalem_hash_cache__");

        // TODO: Implement size_t to string converter
        std::stringstream temp_stream(old_hash);

        std::size_t temp_hash;

        temp_stream >> temp_hash;

        if(hash.hash == temp_hash) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }

    return false;
}

void KalemHashChecker::HashCreate(std::string file) {
    std::string _data = fsplusplus::ReadFileWithReturn(file);

    hash.hash = std::hash<std::string>{}(_data);

    _data.erase();

    if(fsplusplus::IsExistFile(fsplusplus::GetCurrentWorkingDir()
                               + "/"
                               + file
                               + ".__kalem_hash_cache__") == false) {
        fsplusplus::CreateFile(file + ".__kalem_hash_cache__", std::to_string(hash.hash));
    } else {
        _data = fsplusplus::ReadFileWithReturn(file
                + ".__kalem_hash_cache__");

        if(std::to_string(hash.hash) != _data) {
            std::ofstream output_stream;
            output_stream.open(fsplusplus::GetCurrentWorkingDir()
                               + "/"
                               + file
                               + ".__kalem_hash_cache__", std::ofstream::trunc);

            output_stream << std::to_string(hash.hash);

            output_stream.close();
        }
    }
}