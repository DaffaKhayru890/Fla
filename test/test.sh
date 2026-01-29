if [ $# -eq 0 ]; then
    echo "Tidak ada argumen. Gunakan: ./my_script.sh <argumen>"
    exit 1
fi

arg=$1

if [ "$arg" = "lexer" ]; then
    gcc ../src/lexer/lexer.c ../src/utils/utils.c ./test_lexer.c -o TinyC
    ./TinyC
    rm ./TinyC
elif [ "$arg" = "ast" ]; then
    gcc ../src/ast/ast.c ./test_ast.c -o TinyC
    ./TinyC
    rm ./TinyC
elif [ "$arg" = "symbol_table" ]; then
    gcc ../src/semantic/symbol_table.c ./test_symbol_table.c -o TinyC
    ./TinyC
    rm ./TinyC
fi

