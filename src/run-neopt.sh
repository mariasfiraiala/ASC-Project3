#!/bin/bash

make

./tema3_neopt ../input/input

for i in {1..3}; do
        ./compare out$i ../references/out$i 0.0001
        rm out$i
done

valgrind --tool=memcheck --leak-check=full ./tema3_neopt ../input/input_valgrind 2> ../memory/neopt.memory
rm out*

valgrind --tool=cachegrind --branch-sim=yes --cache-sim=yes ./tema3_neopt ../input/input_valgrind 2> ../cache/neopt.cache
rm out*
