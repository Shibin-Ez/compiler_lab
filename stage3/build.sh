#!/bin/bash

# compiler
echo ""
echo "╔════════════════════════════════════════╗"
echo "║     🔧 Building Compiler [1/2]         ║"
echo "╚════════════════════════════════════════╝"
echo ""

cd ast && lex ast.l && yacc -d ast.y && cd ..
if ! gcc -Wall ast/y.tab.c ast/lex.yy.c ast/ast.c exprtree/exprtree.c generator/generator.c -o compiler; then
    echo ""
    echo "❌ Compiler build failed!"
    exit 1
fi

echo ""
echo "✅ Compiler built successfully! [1/2]"

# linker
echo ""
echo "╔════════════════════════════════════════╗"
echo "║     🔗 Building Linker [2/2]           ║"
echo "╚════════════════════════════════════════╝"
echo ""

cd linker && lex linker.l
if ! gcc -Wall lex.yy.c linker.c -o linker; then
    echo ""
    echo "❌ Linker build failed!"
    exit 1
fi

echo ""
echo "✅ Linker built successfully! [2/2]"
echo ""
echo "🎉 Build complete!"

