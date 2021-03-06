#pragma once
/**
 * @author Thomas Brandstaetter
 * @date 14.07.2018
 */

#include <string>

// TODO: #include <ast/ast.h>
#include "../ast/ast.h"


namespace openloco {
namespace lang {
namespace codegen {

    class code_visitor
    {
        namespace ast = openloco::lang::ast;

        /** @addtogroup Object lifecycle */
        /** @{ */

    public:
        code_visitor()
        {
        }

        virtual ~code_visitor()
        {
        }

        /** @} */

#pragma mark - B.1 Common elements

        /** @addtogroup lang constants */
        /** @{ */
    public:
        void operator()(ast::NumericLiteral &nl)
        {
        }

        void operator()(ast::TimeLiteral)
        {
        }

        /** @} */


    };

}}}
