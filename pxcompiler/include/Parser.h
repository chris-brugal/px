
#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <ast/AST.h>
#include <ast/Expression.h>
#include <ast/Statement.h>
#include "Error.h"
#include "Scanner.h"

namespace px {

    class Parser
    {
    public:
        Parser(SymbolTable *symbols, ErrorLog *errors);
        ~Parser() = default;
        ast::AST *parse(const Utf8String &fileName, std::istream &in);

    private:
        std::unique_ptr<Scanner> scanner;
        std::unique_ptr<Token> currentToken;
        SymbolTable * const symbols;
        ErrorLog * const errors;

        void accept();
        bool accept(TokenType type);
        void expect(TokenType type);
        void rewind();

        void compilerError(const SourcePosition & location, const Utf8String & message);
        int getPrecedence(TokenType type);
        ast::BinaryOperator getBinaryOp(TokenType type);

        std::unique_ptr<ast::Statement> parseStatement();
        std::unique_ptr<ast::Statement> parseExpressionStatement();
        std::unique_ptr<ast::Statement> parseReturnStatement();
        std::unique_ptr<ast::Statement> parseVariableDeclaration();
        std::unique_ptr<ast::Expression> parseExpression();
        std::unique_ptr<ast::Expression> parseAssignment();
        std::unique_ptr<ast::Expression> parseBinary(int precedence);
        std::unique_ptr<ast::Expression> parseUnary();
        std::unique_ptr<ast::Expression> parseValue();
    };

}

#endif
