if [ $# -eq 0 ]; then
    echo "Tidak ada argumen. Gunakan: ./my_script.sh <argumen>"
    exit 1
fi

arg=$1

if [ "$arg" = "lexer" ]; then
    gcc ../src/lexer/lexer.c ./unity.c ./test_lexer.c -o fla
    ./fla
    rm ./fla
elif [ "$arg" = "ast" ]; then
    gcc ../src/ast/*.c ./unity.c ./test_ast.c -o fla
    ./fla
    rm ./fla
elif [ "$arg" = "symbol_table" ]; then
    gcc ../src/semantic/symbol_table.c ./unity.c ./test_symbol_table.c -o fla
    ./fla
    rm ./fla
elif [ "$arg" = "parser" ]; then
    gcc ../src/parser/parser.c ../src/lexer/lexer.c ../src/ast/ast.c ./unity.c ./test_parser.c -o fla
    ./fla
    rm ./fla
fi

