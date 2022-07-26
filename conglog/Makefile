naive: naive.dl
	mkdir -p naive
	souffle -Dnaive naive.dl

leader: leader.dl
	mkdir -p leader
	souffle --disable-transformers=SemanticChecker -Dleader leader.dl 

subsumption: subsumption.dl
	mkdir -p subsumption
	souffle --disable-transformers=SemanticChecker -Dsubsumption subsumption.dl

hack: hack.dl
	mkdir -p hack
	souffle --disable-transformers=SemanticChecker -Dhack hack.dl
