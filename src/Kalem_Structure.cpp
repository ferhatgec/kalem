/* MIT License
#
# Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */


#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "../include/Kalem_Structure.hpp"
#include "../include/Kalem_Codegen.hpp"

#include "../include/libs/StringTools.hpp"

kl_codegen
KalemStructure::ReadSource(kalem_t kalem) {
    std::istringstream _source(kalem.kl_file_data);
    
    std::string _data;
    std::string _token;
    
    std::vector<std::string> _tokens; 
        
    Kalem_Codegen __codegen;

    bool is_argument = false;

    int vect_size;

    /* #import */
    while(std::getline(_source, _data)) {
         _tokens = MakeTokenizable(_data);
          vect_size = std::ssize(_tokens);

         for(int i = 0; i < _tokens.size(); i++) {
            _tokens[i] = stringtools::ltrim(_tokens[i]);

            switch(_tokens[i][0]) {
                case '#':
                {
                    /* #import */    
                    if(_tokens[i] == _KALEM_IMPORT) {
                        __codegen.Kl_Codegen(KALEM_IMPORT, "", _tokens[i + 1]);
                    } else if(_tokens[i] == _KALEM_DEFINE) {
                        if(_tokens[i + 2][0] == '"') {
                            std::string _str_data;

                            for(unsigned f = i + 2;;) {
                                _str_data.append(_tokens[f]);

                                if(_tokens[f][_tokens[f].length() - 1] == '"') {
                                    break;
                                } else {
                                    _str_data.append(" ");
                                    f++;
                                }
                            }

                             __codegen.Kl_Codegen(KALEM_DEFINE, _tokens[i + 1], _str_data);
                        } else {
                            __codegen.Kl_Codegen(KALEM_DEFINE, _tokens[i + 1], _tokens[i + 2]);
                        }
                    }
                
                    break;
                }
                
                case '@':
                {

                    /* @main int */
                    if(_tokens[i] == _KALEM_MAIN) {
                        /* TODO:
                            Create checkINT() function 
                        */

                        __codegen.Kl_Codegen(KALEM_MAIN, "", _tokens[i + 1]);
                        is_argument = true;
                    } else if(_tokens[i] == _KALEM_RETURN) {
                        __codegen.Kl_Codegen(KALEM_RETURN, "", _tokens[i + 1]);
                    } else if(_tokens[i] == _KALEM_PRINT) {
                        if(_tokens[i + 1][0] == '"') {
                            std::string _str_data;
                            
                            for(unsigned f = i+1;;) {
                                _str_data.append(_tokens[f]);
                                
                                if(_tokens[f][_tokens[f].length() - 1] == '"') {
                                    break;
                                } else {
                                    _str_data.append(" ");
                                    f++;
                                }
                            }
                            
                             __codegen.Kl_Codegen(KALEM_PRINT, "", _str_data);
                        } else {
                            __codegen.Kl_Codegen(KALEM_PRINT, "", _tokens[i + 1]);
                        }
                    } else {
                        if(i + 2 < vect_size) {
                            if(_tokens[i + 2][0] == '{') {
                                if(is_argument == false) {
                                    __codegen.Kl_Codegen(KALEM_FUNCTION, _tokens[i + 1], _tokens[i]);
                                }
                            } else {
                                /* Function call */
                                __codegen.Kl_Codegen(KALEM_FUNCTION_CALL, "", _tokens[i]);
                            }
                        } else {
                            /* Function call */
                            __codegen.Kl_Codegen(KALEM_FUNCTION_CALL, "", _tokens[i]);
                        }
                    }
                    
                    break;
                }
                
                case '/':
                {
                    if(_tokens[i][1] == '/') {
                        continue;
                    }
                    
                    break;
                }
                
                case '{':
                {
                    __codegen.Kl_Codegen(KALEM_LEFT_CURLY_BRACKET, "", "");
                    break;
                }
                
                case '}':
                {
                    __codegen.Kl_Codegen(KALEM_RIGHT_CURLY_BRACKET, "", "");
                    break;
                }

                default:
                {
                    /* string test = "kalem" */
                    if(_tokens[i] == _KALEM_STRING) {
                        if(_tokens[i + 2][0] == '=') {
                            if(_tokens[i + 3][0] == '"') {
                                std::string _str_data;

                                for(unsigned f = i+1;;) {
                                    _str_data.append(_tokens[f]);

                                    if(_tokens[f][_tokens[f].length() - 1] == '"') {
                                        break;
                                    } else {
                                        _str_data.append(" ");
                                        f++;
                                    }
                                }

                                 __codegen.Kl_Codegen(KALEM_STRING, "", _str_data);
                            } else {
                                /* Syntax error (string x =)*/
                            }
                        }
                    } else if(_tokens[i] == _KALEM_UNSIGNED
                        || _tokens[i] == _KALEM_INT) {

                        /* unsign test = 10; */
                        if(is_argument == true) {
                            is_argument = false;
                            break;
                        } else if(_tokens[i + 2][0] == '=') {
                            __codegen.Kl_Codegen((_tokens[i] == _KALEM_INT)
                                ? KALEM_INT
                                : KALEM_UNSIGNED, _tokens[i + 1], _tokens[i + 3]);
                        } else {

                        }
                    }

                    break;
                }
            }
                
         } 
         
         __codegen.Kl_Codegen(KALEM_NEWLINE, "", "");
    }
    
    return __codegen._codegen;
}

std::vector<std::string>
KalemStructure::MakeTokenizable(std::string _data) {
    std::vector<std::string> _kalem_tokens;
    std::istringstream _kalem_stream(_data);
    std::string _append;
    
    while(std::getline(_kalem_stream, _append, ' ')) {
        _kalem_tokens.push_back(_append); 
    }
    
    return _kalem_tokens;
}
