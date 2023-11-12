#include "CompilerParser.h"
#include <string>
#include <list>

/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */
CompilerParser::CompilerParser(std::list<Token*> tokens) {
    std::list<Token*> tlist = tokens;
    it = tlist.begin();
}

/**
 * Generates a parse tree for a single program
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileProgram() {
    if (current()->getValue() == "class") {
        if (current()->getValue() == "class") {
            return compileClass();
        }
    } else {
        throw ParseException();
    }
    return NULL;
}

/**
 * Generates a parse tree for a single class
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClass() {
    ParseTree *tree = new ParseTree("class", "");
    if (current()->getValue() != "class") {
        throw ParseException();
    }

    tree->addChild(current());
    next();
    tree->addChild(current());
    next();
    tree->addChild(current());
    next();

    auto is_varDec = [](ParseTree* a) {
        if (a->getType() == "keyword") {
            if (a->getValue() == "static" || "field") {
                return true;
            }
        }
        return false;
    };

    auto is_subRoutine = [](ParseTree* a) {
        if (a->getType() == "keyword") {
            if (a->getValue() == "function" || "method" || "constructor") {
                return true;
            }
        }
        return false;
    };

    auto is_end = [](ParseTree* a) {
        if (a->getType() == "symbol") {
            if (a->getValue() == "}") {
                return true;
            }
        }
        return false;
    };

    do {
        auto currentToken = current();
        if (is_varDec(currentToken) == true) {
            tree->addChild(compileClassVarDec());
        } else if (is_subRoutine(currentToken) == true) {
            tree->addChild(compileSubroutine());
        } else {
            tree->addChild(current());
            next();
        }
    } while (is_end(tree->getChildren().back()) == false);
    
    return tree;
}

/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClassVarDec() {
    ParseTree *tree = new ParseTree("classVarDec", "");
    tree->addChild(current());
    next();
    tree->addChild(current());
    next();
    tree->addChild(current());
    next();

    auto isComma = [](ParseTree* a) {
        if (a->getType() == "symbol") {
            if (a->getValue() == ",") {
                return true;
            }
        }
        return false;
    };

    ParseTree *currentValue = current();
    while (isComma(currentValue) == true) {
        tree->addChild(current());
        next();
        tree->addChild(current());
        next();
        currentValue  = current();
    }

    tree->addChild(current());
    return tree;
}

/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutine() {
    ParseTree *tree = new ParseTree("subroutine", "");
    tree->addChild(current());
    next();
    tree->addChild(current());
    next();
    tree->addChild(current());
    next();
    tree->addChild(current());
    next();

    tree->addChild(compileParameterList());

    tree->addChild(current());
    next();
    
    tree->addChild(compileSubroutineBody());
    
    return tree;
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    ParseTree *tree = new ParseTree("parameterList", "");
    tree->addChild(current());
    next();

    auto isBracket = [](ParseTree* a) {
        if (a->getType() == "symbol") {
            if (a->getValue() == ")") {
                return true;
            }
        }
        return false;
    };

    ParseTree *currentValue = current();
    while (isBracket(currentValue) == false) {
        tree->addChild(current());
        next();
        currentValue  = current();
    }

    return tree;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    ParseTree *tree = new ParseTree("subroutineBody", "");
    tree->addChild(current());
    next();

    auto isEnd = [](ParseTree* a) {
        if (a->getType() == "symbol") {
            if (a->getValue() == "}") {
                return true;
            }
        }
        return false;
    };

    ParseTree *currentValue = current();
    while (isEnd(currentValue) == false) {
        if (currentValue->getType() == "keyword" && currentValue->getValue() == "var") {
            tree->addChild(compileVarDec());
        } else {
            tree->addChild(compileStatements());
        }
        currentValue  = current();
    }

    return tree;

}
/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    ParseTree *tree = new ParseTree("varDec", "");
    tree->addChild(current());
    next();
    tree->addChild(current());
    next();
    tree->addChild(current());
    next();

    auto isComma = [](ParseTree* a) {
        if (a->getType() == "symbol") {
            if (a->getValue() == ",") {
                return true;
            }
        }
        return false;
    };

    ParseTree *currentValue = current();
    while (isComma(currentValue) == true) {
        tree->addChild(current());
        next();
        tree->addChild(current());
        next();
        currentValue  = current();
    }

    tree->addChild(current());
    return tree;
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {
    return NULL;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {
    return NULL;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileIf() {
    return NULL;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileWhile() {
    return NULL;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileDo() {
    return NULL;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    return NULL;
}

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpression() {
    return NULL;
}

/**
 * Generates a parse tree for an expression term
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileTerm() {
    return NULL;
}

/**
 * Generates a parse tree for an expression list
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpressionList() {
    return NULL;
}

/**
 * Advance to the next token
 */
void CompilerParser::next(){
    if (it != tlist.end()) {
        ++it;
    }
    return;
}

/**
 * Return the current token
 * @return the Token
 */
Token* CompilerParser::current(){
    return *it;
}

/**
 * Check if the current token matches the expected type and value.
 * @return true if a match, false otherwise
 */
bool CompilerParser::have(std::string expectedType, std::string expectedValue){
    if (current()->getType() == expectedType && current()->getValue() == expectedValue) {
        return true;
    } else {
        throw ParseException();
    }
    return NULL;
}

/**
 * Check if the current token matches the expected type and value.
 * If so, advance to the next token, returning the current token, otherwise throw a ParseException.
 * @return the current token before advancing
 */
Token* CompilerParser::mustBe(std::string expectedType, std::string expectedValue){
    if (have(expectedType, expectedValue) == true) {
        auto current = *it;
        it++;
        return current;
    } else {
        throw ParseException();
    }
    throw ParseException();
}

/**
 * Definition of a ParseException
 * You can use this ParseException with `throw ParseException();`
 */
const char* ParseException::what() {
    return "An Exception occurred while parsing!";
}
