# viterbi
A viterbi path finder, implemented in C++11

# usage: 
`viterbi [options] <seq>,`
where <seq> is a string of observed emmissions, (zero indexed)
options:
  -h, --help	 show this help
  --remap:	remaps sequence to [1 if 6 else 0]]

# examples:
If a sequence of heads heads tails tails heads is observed one would run: 
`viterbi 00110`
for a sequence of 1 through 6es one would use 
`viterbi --remap 132645`
which would be read then as 0001000
