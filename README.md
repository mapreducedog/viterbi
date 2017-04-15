# viterbi
A viterbi path finder, implemented in C++11


# usage: 
'viterbi [options] <seq>,  where <seq> is a string of observed emmissions, (zero indexed)'
options:
-h, --help	 show this help
--remap:	remaps sequence to [1 if 6 else 0]]
e.g. if a sequence of heads heads tails tails heads is observed one would run: 
'viterbi 00110'
