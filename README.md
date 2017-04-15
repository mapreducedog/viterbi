# viterbi
A viterbi path finder, implemented in C++11

# usage: 
`viterbi [options] <seq>,`
where `<seq>` is a string of observed emmissions, (zero indexed)
## options to be used with input sequence
  `-r`, `--remap` 	remaps `<seq>` to [1 if 6 else 0]]  
  `-V`, `--verbose` enable verbose output  
## options to be used without input sequence
  `-h`, `--help`	 shows help  
  `-l`, `--list-states` shows the state-character-map
  

  


# examples:
If a sequence of `heads heads tails tails heads` is observed one would run:  
`viterbi 00110`  
for a sequence of 1 through 6es one would use:  
`viterbi --remap 132645`  
which would be read then as 0001000


# Interpreting output
if output is not set to verbose, the only outputs are the maxpaths for the given input sequence. Note that this might be more than one, as some paths might have equal probability. This is a sequence of chars indicating the most likely sequence of state, with each being denoted as `char state = '0' + index of state`, so if more than 10 states are present,the 10th indexed state, (because of 0-indexing), will be mapped to char('0' + 10).  
you can use `--list-states` to show the lookup table of states and their respective character.

In verbose output, you will also see the sequence of probabilities (in log10) of ending op at a state and emitting a certain symbol, and the most likely previous states.
this will be denoted as:  
`<Emission> '|' <Probability> \t <ML_Previous_states> '|'` (with the last part between '|'s repeated for each state)
As the most likely previous states are denoted as a bitarray, but printed as an unsigned int, this means that a state with index S is a Most likely previous state if the for the outputted value V is true `V mod (2 ^ S) == 0`.  
e.g, there is an output 
`1|-2.0 1| -2.7 3`  
this means that at this position, there is a 10^-2 probability of ending up in state 0 and emitting symbol 1, and its most likely previous state (0b00000001) is state 0.
and that there is a 10^2.7 chance of ending up in state 1 and emitting symbol 1, and its most likely previous state (0b00000011) are 0 and 1 (both are equally likely).
