#!/bin/bash

# parse arguments
filename=""
run_flag=false

for arg in "$@"; do
    if [ "$arg" = "--run" ]; then
        run_flag=true
    else
        filename=$arg
    fi
done

# pass the file to compiler
if ! ./compiler < $filename; then
    echo ""
    echo "❌ Compilation failed!"
    exit 1
fi
echo "✅ Compiled [$filename] (1/2)"

# result is stored in out.xsm

# pass the out.xsm to linker
cd linker
if ! ./linker ../out.xsm; then
    echo ""
    echo "❌ Linking failed!"
    exit 1
fi
echo "✅ Linked (2/2)"

# copy the new out.xsm file to root folder
cp out.xsm ../..

# run if --run flag is provided
if [ "$run_flag" = true ]; then
    cd ../..
    ./xsm -l library.lib -e out.xsm
fi