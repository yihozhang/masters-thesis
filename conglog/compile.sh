SOUFFLE_PATH=/usr/local/bin

# change -jN to use N threads
$SOUFFLE_PATH/souffle -p out.log $1 --disable-transformers=SemanticChecker -g out.cpp
tail -n +7 out.cpp > out-stub.cpp
cat helper.lines out-stub.cpp > out.cpp
printf "#define eqfind(x) `grep -m 1 -o "rel_eql_[0-9a-e]*" out.cpp`->ind.findNode(x)" > helper.h
# $SOUFFLE_PATH/souffle-compile.py -o ./out out.cpp
