if [ $# -eq 0 ]; then
    echo "Tidak ada argumen. Gunakan: ./my_script.sh <argumen>"
    exit 1
fi

arg=$1

if [ "$arg" = "lexer" ]; then
    gcc ../src/lexer.c ./unity.c ./test_lexer.c -o fla
    ./fla
    rm ./fla
fi

# elif [ "$arg" = "parser" ]; then
#     gcc ../src/lexer/*.c ../src/ast/*.c ../src/parser/*.c ./unity.c ./test_ast_parser.c -o fla
#     ./fla
#     rm ./fla
# elif [ "$arg" = "symbol_table" ]; then
#     gcc ../src/symbol_table/symbol_table.c ./unity.c ./test_symbol_table.c -o fla
#     ./fla
#     rm ./fla
# fi

