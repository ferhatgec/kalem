/* MIT License
#
# Copyright (c) 2020-2021 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */


#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "../include/Kalem_Codegen.hpp"

#include "../include/libs/StringTools.hpp"

void
Kalem_Codegen::Kl_Codegen(KALEM_TOKEN _token, std::string _variable, std::string _append,
    std::string _arguments) {
    switch(_token) {
        case KALEM_IMPORT:
        {
            _codegen.kl_generated.append(_CPP_KALEM_INCLUDE);

            stringtools::replaceAll(_append, "ios"    , "iostream");
            stringtools::replaceAll(_append, "vect"   , "vector");
            stringtools::replaceAll(_append, "stdstr" , "string");
            stringtools::replaceAll(_append, "cstdstr", "cstring");
            stringtools::replaceAll(_append, "iom"    , "iomanip");
            stringtools::replaceAll(_append, "filesys", "filesystem");
            stringtools::replaceAll(_append, "fst"    , "fstream");
            stringtools::replaceAll(_append, ".kalem", ".hpp");

            _codegen.kl_generated.append(_append);
            
            break;
        }

        case KALEM_INCLUDE:
        {
            if(_append.length() < 2) break;

            _codegen.kl_generated.append(_CPP_KALEM_INCLUDE);

            if(stringtools::Find(_append, ".kalem"))
                stringtools::replaceAll(_append, ".kalem", ".hpp");
            else {
                char last = _append.back();

                _append.pop_back();

                _append.append(".hpp");
                _append.push_back(last);
            }

            _codegen.kl_generated.append(_append);

            break;
        }

        case KALEM_STRING:
        {
            _codegen.kl_generated.append(_CPP_KALEM_STRING);
            _codegen.kl_generated.append(" " + _variable);

            if(_append != "") {
                _codegen.kl_generated.append(" = " + _append);
            }

            _codegen.kl_generated.append(";");

            break;
        }

        case KALEM_INT:
        {
            /* int a = 10 */
            _codegen.kl_generated.append(_KALEM_INT);
            _codegen.kl_generated.append(" " + _variable);

            if(_append != "") {
                _codegen.kl_generated.append("=");
                _codegen.kl_generated.append(_append);
            }

            _codegen.kl_generated.append(";");

            break;
        }

        case KALEM_UNSIGNED:
        {
            /* unsign a = 10 */
            _codegen.kl_generated.append(_CPP_KALEM_UNSIGNED);
            _codegen.kl_generated.append(" " + _variable);

            if(_append != "") {
                _codegen.kl_generated.append("=");
                _codegen.kl_generated.append(_append);
            }

            _codegen.kl_generated.append(";");

            break;
        }

        case KALEM_CHAR:
        {
            // char c 'a'
            _codegen.kl_generated.append(_KALEM_CHAR);
            _codegen.kl_generated.append(" " + _variable);

            if(_append != "") {
                _codegen.kl_generated.append("=");
                _codegen.kl_generated.append(_append);
            }

            _codegen.kl_generated.append(";");

            break;
        }

        case KALEM_FUNCTION:
        {
            /* @test void { }*/
            _codegen.kl_generated.append(_variable);
            _codegen.kl_generated.append(" ");

            _append = _append.erase(0, 1);

            _codegen.kl_generated.append(_append);


            _codegen.kl_generated.append("(");

            if(_arguments != "") {
                stringtools::replaceAll(_arguments, "string ", "std::string ");
                stringtools::replaceAll(_arguments, "vect ", "std::vector ");
                stringtools::replaceAll(_arguments, "unsign ", "unsigned ");

                _codegen.kl_generated.append(_arguments);
            }

            _codegen.kl_generated.append(")");

            break;
        }

        case KALEM_FUNCTION_CALL:
        {
            /* @test */
            _append = _append.erase(0, 1);

            _codegen.kl_generated.append(_append);

            if(_arguments != "") {
                _codegen.kl_generated.append("(" + _arguments + ");");
            } else {
                if(stringtools::Find(_append, "()")) {
                    _codegen.kl_generated.append(";");
                } else {
                    _codegen.kl_generated.append("();");
                }
            }


            break;
        }

        case KALEM_NAMESPACE:
        {
            /* @test namespace { } */
            _codegen.kl_generated.append(_KALEM_NAMESPACE);
            _codegen.kl_generated.append(" ");

            _append = _append.erase(0, 1);

            _codegen.kl_generated.append(_append);

            break;
        }

        case KALEM_CLASS:
        {
            _codegen.kl_generated.append(_KALEM_CLASS);
            _codegen.kl_generated.append(" ");

            _append = _append.erase(0, 1);

            _codegen.kl_generated.append(_append);

            break;
        }

        case KALEM_DEFINE:
        {
            /* #defn TEST "test" */
            _codegen.kl_generated.append(_CPP_KALEM_DEFINE);
            _codegen.kl_generated.append(" " + _variable + " ");
            _codegen.kl_generated.append(_append);

            break;
        }

        case KALEM_MAIN:
        {
            _codegen.kl_generated.append(_append);
            _codegen.kl_generated.append(" ");
            _codegen.kl_generated.append(_CPP_KALEM_MAIN);
            _codegen.kl_generated.append("(int argc, char** argv)");
            
            break;
        }

        case KALEM_RETURN:
        {
            _codegen.kl_generated.append(_CPP_KALEM_RETURN);
            _codegen.kl_generated.append(" " + _append);
            _codegen.kl_generated.append(";");

            break;
        }
        
        case KALEM_PRINT:
        {
            _codegen.kl_generated.append(_CPP_KALEM_PRINT);
            _codegen.kl_generated.append("<<");
            _codegen.kl_generated.append(_append);
            _codegen.kl_generated.append(";");

            break;
        }
        
        case KALEM_GOTO:
        {
            /* @goto test */
            _codegen.kl_generated.append(_CPP_KALEM_GOTO);
            _codegen.kl_generated.append(" " + _append);
            _codegen.kl_generated.append(";");

            break;
        }

        case KALEM_GOTO_CALL:
        {
            /* @test: ..... */
            _append = _append.erase(0, 1);

            _codegen.kl_generated.append(_append);

            break;
        }

        case KALEM_LEFT_CURLY_BRACKET:
        {
            _codegen.kl_generated.append(_KALEM_LEFT_CURLY_BRACKET);
            
            break;
        }
        
        case KALEM_RIGHT_CURLY_BRACKET:
        {
            _codegen.kl_generated.append(_KALEM_RIGHT_CURLY_BRACKET + _append);
            
            break;
        }
        
        case KALEM_NEWLINE:
        {
            _codegen.kl_generated.append(_KALEM_NEWLINE);

            break;
        }

        case KALEM_LINK:
        {
            _variable = _variable.erase(0, 1);

            _codegen.kl_generated.append(_variable);

            break;
        }

        case KALEM_ELSE:
        {
            _codegen.kl_generated.append(_CPP_KALEM_ELSE);
            _codegen.kl_generated.append(" ");

            break;
        }
        
        case KALEM_ELSE_IF:
        {
            /*
            if (...) {
             
            } 
            elsif (...) {
            
            } 
            els {
            
            }
            */
            _codegen.kl_generated.append(_CPP_KALEM_ELSE);
            _codegen.kl_generated.append(" ");
            _codegen.kl_generated.append(_KALEM_IF);
            _codegen.kl_generated.append(" ");
            _codegen.kl_generated.append("(");
            _codegen.kl_generated.append(_append);
            _codegen.kl_generated.append(")");
            
            break;
        }

        case KALEM_LOOP:
        {
            /* loop {
             * ...
             * }
             * */

            _codegen.kl_generated.append(_CPP_KALEM_LOOP);
            _codegen.kl_generated.append("(1)");

            break;
        }

        // TODO: Create Kalem_Flags.hpp & Kalem_Flags.cpp
        // for all supported flags.
        case KALEM_FLAG:
        {
            // C++ compiler standard !flag("cpp-standard=c++17")
            // Kalem output file     !flag("output=test")
            _append = stringtools::GetBetweenString(_variable, "(", ")");

            std::string flag, append_flag;

            unsigned i = 1;

            for(; _append[i] != '='; i++) {
                flag.push_back(_append[i]);
            }

            for(++i; _append[i] != '"'; i++) {
                append_flag.push_back(_append[i]);
            }

            if(flag == "output") {
                _codegen.kl_output = append_flag;
            }
            else if(flag == "cpp-standard") {
                _codegen.kl_cpp_standard = append_flag;
            }
            else if(flag == "cpp-output") {
                if(append_flag == "true") {
                    _codegen.kl_cpp_output = true;
                } else {
                    _codegen.kl_cpp_output = false;
                }
            }
            else if(flag == "cpp-flags") {
                if(append_flag != "false") {
                    _codegen.kl_cpp_flags = append_flag;
                }
            }
            else if(flag == "cpp-compiler") {
                if(append_flag != "default") {
                    _codegen.kl_cpp_compiler = append_flag;
                }
            }
            else if(flag == "cpp-sysroot") {
                if(append_flag != "false") {
                    _codegen.kl_cpp_sysroot = "--sysroot=" + append_flag;
                }
            }
            else if(flag == "hash-cache") {
                if(append_flag == "false") {
                    _codegen.kl_hash_cache = false;
                } else {
                    _codegen.kl_hash_cache = true;
                }
            }

            break;
        }

        case KALEM_REQUIRED_FLAG:
        {
            if(stringtools::GetBetweenString(_variable, "(\"", "\")") == "library") {
                 _codegen.kl_header_file = true;

                 stringtools::replaceAll(_append, ".kalem", "");

                 _codegen.kl_generated = "#ifndef "
                                        + _append
                                        + "_HPP\n"
                                        + "#define "
                                        + _append
                                        + "_HPP\n"
                                        + _codegen.kl_generated;
             }

            break;
        }


        case KALEM_INCLUDE_DIR:
        {
            _append = stringtools::GetBetweenString(_variable, "(\"", "\")");


            if(_append != "false" && _append != "error") {
                _codegen.kl_cpp_include_dirs.append("-I" + _append + " ");
            } else { _codegen.kl_cpp_include_dirs = ""; }

            break;
        }

        case KALEM_ADD_SOURCE:
        {
            _append = stringtools::GetBetweenString(_variable, "(\"", "\"");

            if(_append != "false" && _append != "error") {
                _codegen.kl_source_files.push_back(_append);
            }

            break;
        }

        case KALEM_BREAK:
        {
            _codegen.kl_generated.append(_KALEM_BREAK);
            _codegen.kl_generated.append(";");

            break;
        }

        case KALEM_CONTINUE:
        {
            _codegen.kl_generated.append(_KALEM_CONTINUE);
            _codegen.kl_generated.append(";");

            break;
        }

        case KALEM_REGULAR:
        {
            _codegen.kl_generated.append(_append);

            break;
        }

        case KALEM_NONE:
        {
            _codegen.kl_generated.append(_variable + ";");

            break;
        }
    }
}
