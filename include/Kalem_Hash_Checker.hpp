/* MIT License
#
# Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#ifndef KALEM_HASH_CHECKER_HPP
#define KALEM_HASH_CHECKER_HPP

#include <iostream>
#include <string>
#include <cstddef>

typedef struct {
    std::size_t old_hash,
                hash;

    std::string file;

    bool changed = false;
} kl_hash;

class KalemHashChecker {
    kl_hash hash;
public:
    bool HashInit(std::string file);

    void HashCreate(std::string file);
};


#endif //KALEM_HASH_CHECKER_HPP