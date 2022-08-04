naive: naive.dl N.in
	mkdir -p naive
	souffle -Dnaive naive.dl

leader: leader.dl N.in
	mkdir -p leader
	souffle --disable-transformers=SemanticChecker -Dleader leader.dl 

subsumption: subsumption.dl N.in
	mkdir -p subsumption
	souffle --disable-transformers=SemanticChecker -Dsubsumption subsumption.dl

hack: hack.dl
	mkdir -p hack
	./compile.sh hack.dl