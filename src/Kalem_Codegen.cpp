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

#include "../include/Kalem_Codegen.hpp"

void
Kalem_Codegen::Kl_Codegen(KALEM_TOKEN _token, std::string _variable, std::string _append) {
    switch(_token) {
        case KALEM_IMPORT:
        {
            _codegen.kl_generated.append(_CPP_KALEM_INCLUDE);
            _codegen.kl_generated.append(_append);
            
            break;
        }
        
        case KALEM_STRING:
        {
            _codegen.kl_generated.append(_CPP_KALEM_STRING);
            _codegen.kl_generated.append(" " + _variable);

            if(_append != "") {
                _codegen.kl_generated.append(_append);
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

        case KALEM_FUNCTION:
        {
            /* @test void { }*/
            _codegen.kl_generated.append(_variable);
            _codegen.kl_generated.append(" ");

            _append = _append.erase(0, 1);

            _codegen.kl_generated.append(_append);

            /* arguments are not supported */
            _codegen.kl_generated.append("()");

            break;
        }

        case KALEM_FUNCTION_CALL:
        {
            /* @test */
            _append = _append.erase(0, 1);

            _codegen.kl_generated.append(_append);
            _codegen.kl_generated.append("();");

            break;
        }

        case KALEM_MAIN:
        {
            _codegen.kl_generated.append(_append);
            _codegen.kl_generated.append(" ");
            _codegen.kl_generated.append(_CPP_KALEM_MAIN);
            
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
        
        
        case KALEM_LEFT_CURLY_BRACKET:
        {
            _codegen.kl_generated.append(_KALEM_LEFT_CURLY_BRACKET);
            
            break;
        }
        
        case KALEM_RIGHT_CURLY_BRACKET:
        {
            _codegen.kl_generated.append(_KALEM_RIGHT_CURLY_BRACKET);
            
            break;
        }
        
        case KALEM_NEWLINE:
        {
            _codegen.kl_generated.append(_KALEM_NEWLINE);
            break;
        }
    }
}
