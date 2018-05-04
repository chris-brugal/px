
#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <ast/AST.h>
#include <ast/Expression.h>
#include <ast/Statement.h>
#include <ast/Declaration.h>
#include "Error.h"
#include "Scanner.h"

namespace px {

    class Parser
    {
    public:
        Parser(ErrorLog *errors);

        std::unique_ptr<ast::Module> parse(const Utf8String &fileName, std::istream &in);

    private:
        std::unique_ptr<Scanner> scanner;
        std::unique_ptr<Token> currentToken;
        ErrorLog * const errors;

        void accept();
        bool accept(TokenType type);
        void expect(TokenType type);
        void rewind();

        void compilerError(const SourcePosition & location, const Utf8String & message);
        int getPrecedence(TokenType type);
        ast::BinaryOperator getBinaryOp(TokenType type);

        std::unique_ptr<ast::Statement> parseStatement();
        std::unique_ptr<ast::AssignmentStatement> parseAssignment();
        std::unique_ptr<ast::BlockStatement> parseBlockStatement();
        std::unique_ptr<ast::ExpressionStatement> parseExpressionStatement();
        std::unique_ptr<ast::FunctionDeclaration> parseFunctionDeclaration();
        std::unique_ptr<ast::IfStatement> parseIfStatement();
        std::unique_ptr<ast::ReturnStatement> parseReturnStatement();
        std::unique_ptr<ast::VariableDeclaration> parseVariableDeclaration();
        std::unique_ptr<ast::Expression> parseExpression();
        std::unique_ptr<ast::Expression> parseBinary(int precedence = 1);
        std::unique_ptr<ast::Expression> parseUnary();
        std::unique_ptr<ast::Expression> parseValue();
    };

}

#endif
