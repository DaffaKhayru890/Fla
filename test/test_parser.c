#include "../include/ast.h"
#include "../include/parser.h"
#include "../include/utils.h"

#include <stddef.h>
#include <stdio.h>

const char* node_type_to_string(NodeType type) {
    switch(type) {
        case NODE_PROGRAM: return "Program";
        case NODE_MODULE: return "Module";
        case NODE_PARAMETER: return "Parameter";
        case NODE_FUNCTION_DECLARATION: return "FunctionDecl";
        case NODE_RETURN_STATEMENT: return "Return";
        case NODE_BLOCK_STATEMENT: return "Block";
        case NODE_VARIABLE_DECLARATION: return "VarDecl";
        case NODE_IF_STATEMENT: return "If";
        case NODE_WHILE_STATEMENT: return "While";
        case NODE_FOR_STATEMENT: return "For";
        case NODE_BREAK_STATEMENT: return "Break";
        case NODE_CONTINUE_STATEMENT: return "Continue";
        case NODE_SWITCH_STATEMENT: return "Switch";
        case NODE_IDENTIFIER_EXPRESSION: return "Identifier";
        case NODE_BINARY_EXPRESSION: return "Binary";
        case NODE_UNARY_EXPRESSION: return "Unary";
        case NODE_TERNARY_EXPRESSION: return "Ternary";
        case NODE_GROUPING_EXPRESSION: return "Grouping";
        case NODE_COMPOUND_EXPRESSION: return "Compound";
        case NODE_FUNCTION_CALL_EXPRESSION: return "FunctionCall";
        case NODE_LITERAL_EXPRESSION: return "Literal";
        case NODE_ARRAY: return "Array";
        case NODE_ASSIGNMENT: return "Assignment";
        default: return "Unknown";
    }
}

void print_ast_tree(ASTNode* node, const char* prefix, bool is_last) {
    if (!node) return;
    
    printf("%s%s%s", prefix, is_last ? "└── " : "├── ", node_type_to_string(node->node_type));
    
    switch(node->node_type) {
        case NODE_MODULE:
            printf(" [name: %s]", node->module.name);
        break;
            
        case NODE_PARAMETER:
            printf(" [name: %s, type: %s]", 
                node->parameter.name, 
                node->parameter.type
            );
        break;
            
        case NODE_FUNCTION_DECLARATION:
            printf(" [name: %s, return: %s, params: %d]",
                node->function_delcaration.identifier,
                node->function_delcaration.return_type,
                node->function_delcaration.param_count
            );
        break;
            
        case NODE_VARIABLE_DECLARATION:
            printf(" [name: %s, type: %s]",
                node->variable_declaration.identifier,
                node->variable_declaration.type
            );
        break;
            
        case NODE_BINARY_EXPRESSION:
            printf(" [op: %s]", node->binary.op);
        break;
            
        case NODE_UNARY_EXPRESSION:
            printf(" [op: %s]", node->unary.op);
        break;
            
        case NODE_FUNCTION_CALL_EXPRESSION:
            printf(" [name: %s, args: %d]",
                node->function_call.function_name,
                node->function_call.arg_count
            );
        break;

        case NODE_IDENTIFIER_EXPRESSION:
            printf(" [name: %s]",
                node->identifier.identifier
            );
        break;

        break;
            
        case NODE_LITERAL_EXPRESSION:
            printf(" [");

            switch(node->literal.literal_type) {
                case LITERAL_INT:
                    printf("int: %d", *node->literal.int_value);
                break;
                
                case LITERAL_DOUBLE:
                    printf("double: %f", *node->literal.double_value);
                break;
                
                case LITERAL_FLOAT:
                    printf("float: %f", *node->literal.float_value);
                break;
                
                case LITERAL_CHAR:
                    printf("char: '%c'", *node->literal.char_value);
                break;

                case LITERAL_STRING:  
                    printf("string: \"%s\"", node->literal.string_value);
                break;

                case LITERAL_BOOLEAN:  
                    printf("boolean: %s", node->literal.boolean_value == true ? "true" : "false");
                break;
            }

            printf("]");
        break;
            
        case NODE_SWITCH_STATEMENT:
            printf(" [cases: %d]", node->switch_statement.case_count);
        break;
            
        case NODE_BLOCK_STATEMENT:
            printf(" [statements: %d]", node->block_statement.statements_count);
        break;

        case NODE_ARRAY:
            printf(" [literals count: %d]", node->array.literal_count);
        break;

        case NODE_ASSIGNMENT:
            printf(" [left: %s]", node->assignment.left);
        break;
    }
    
    printf("\n");
    
    char new_prefix[512];
    snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_last ? "    " : "│   ");
    
    switch(node->node_type) {
        case NODE_PROGRAM:
            if (node->body) {
                print_ast_tree(node->body, new_prefix, true);
            }
        break;

        case NODE_MODULE:
            if (node->module.body) {
                for (int i = 0; node->module.body[i] != NULL; i++) {
                    print_ast_tree(node->module.body[i], new_prefix, node->module.body[i+1] == NULL);
                }
            }
        break;
            
        case NODE_FUNCTION_DECLARATION:
            if(node->function_delcaration.parameters) {
                for (int i = 0; i < node->function_delcaration.param_count; i++) {
                    print_ast_tree(
                        node->function_delcaration.parameters[i], 
                        new_prefix, 
                        i == node->function_delcaration.param_count - 1 && node->function_delcaration.parameters[i] == NULL
                    );
                }
            }

            if (node->function_delcaration.body) {
                print_ast_tree(
                    node->function_delcaration.body, 
                    new_prefix, 
                    node->function_delcaration.body != NULL
                );
            }
        break;
            
        case NODE_BLOCK_STATEMENT:
            for (int i = 0; i < node->block_statement.statements_count; i++) {
                print_ast_tree(
                    node->block_statement.statements[i], 
                    new_prefix,
                    i == node->block_statement.statements_count - 1
                );
            }
        break;
            
        case NODE_VARIABLE_DECLARATION:
            if (node->variable_declaration.init) {
                print_ast_tree(node->variable_declaration.init, new_prefix, true);
            }
        break;
            
        case NODE_RETURN_STATEMENT:
            if (node->return_function.expression) {
                print_ast_tree(node->return_function.expression, new_prefix, true);
            }
        break;
            
        case NODE_BINARY_EXPRESSION:
            print_ast_tree(node->binary.left, new_prefix, false);
            print_ast_tree(node->binary.right, new_prefix, true);
        break;
            
        case NODE_UNARY_EXPRESSION:
            print_ast_tree(node->unary.operand, new_prefix, true);
        break;
            
        case NODE_TERNARY_EXPRESSION:
            print_ast_tree(node->tenary.condition, new_prefix, false);
            print_ast_tree(node->tenary.then_expr, new_prefix, false);
            print_ast_tree(node->tenary.else_expr, new_prefix, true);
            break;
            
        case NODE_FUNCTION_CALL_EXPRESSION:
            for (int i = 0; i < node->function_call.arg_count; i++) {
                print_ast_tree(
                    node->function_call.arguments[i], new_prefix,
                    i == node->function_call.arg_count - 1
                );
            }
        break;
            
        case NODE_IF_STATEMENT:
            print_ast_tree(node->if_statement.condition, new_prefix, false);
            
            if (node->if_statement.than_branch) {
                print_ast_tree(node->if_statement.than_branch, new_prefix, false);
            }

            if (node->if_statement.else_branch) {
                print_ast_tree(node->if_statement.else_branch, new_prefix, true);
            }
        break;
            
        case NODE_WHILE_STATEMENT:
            print_ast_tree(node->while_statement.condition, new_prefix, false);
            if (node->while_statement.body) {
                for (int i = 0; node->while_statement.body[i] != NULL; i++) {
                    print_ast_tree(node->while_statement.body[i], new_prefix,
                                   node->while_statement.body[i+1] == NULL);
                }
            }
            break;
            
        case NODE_FOR_STATEMENT:
            if (node->for_statement.preclause)
                print_ast_tree(node->for_statement.preclause, new_prefix, false);
            if (node->for_statement.condition)
                print_ast_tree(node->for_statement.condition, new_prefix, false);
            if (node->for_statement.postclause)
                print_ast_tree(node->for_statement.postclause, new_prefix, 
                               node->for_statement.body == NULL);
            if (node->for_statement.body) {
                for (int i = 0; node->for_statement.body[i] != NULL; i++) {
                    print_ast_tree(node->for_statement.body[i], new_prefix,
                                   node->for_statement.body[i+1] == NULL);
                }
            }
            break;
            
        case NODE_SWITCH_STATEMENT:
            print_ast_tree(node->switch_statement.expression, new_prefix, false);
            if (node->switch_statement.body) {
                for (int i = 0; node->switch_statement.body[i] != NULL; i++) {
                    print_ast_tree(
                        node->switch_statement.body[i], new_prefix,
                        node->switch_statement.body[i+1] == NULL
                    );
                }
            }
            break;
        case NODE_ARRAY:
            if(node->array.literal) {
                for(int i = 0; i < node->array.literal_count; i++) {
                    print_ast_tree(
                        node->array.literal[i],
                        new_prefix,
                        i == node->array.literal_count - 1
                    );
                } 
            }   
        break;

        case NODE_ASSIGNMENT:
            print_ast_tree(node->assignment.expression, new_prefix, true);
        break;
    }
}

int main() {
    char *source = readFileToString("../example/ifStatement.fla");

    Lexer lexer;
    Token token;

    createLexer(&lexer, source);
    
    Parser parser;

    createParser(&parser, &lexer);

    ASTNode *program = parseProgram(&parser, &lexer);

    print_ast_tree(program, "", true);

    freeAstNode(program, true);

    return 0;
}