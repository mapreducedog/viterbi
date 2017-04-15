#ifndef viterbi_header
#define viterbi_header

template <int states_, int emissions_> 
struct rules_set 
{
    unsigned int states;
	unsigned int emissions;
	float  p_emi[states_][emissions_]; //p_emit[given state][symbol]
	float  p_trans[states_][states_]; //p_trans[to][given from]
	float  initial_state_dist[states_];
};

//global rules
extern struct rules_set<2,2> rules;

struct max_struct 
{
	float prob;
	unsigned int max_pos;
};

max_struct get_max(float * scores);

max_struct score_likelihood(float * prev_states, float * p_trans_to_this, float p_emit_this);

/*recursively trace back the maxpath(s), and print to stdout the path found*/
void backtrack(char * path,unsigned int index, unsigned int state, unsigned int ** max_lk);

void print_maxpaths(unsigned int max_end_bitarray, unsigned int ** max_lk, int len_seq);

void eval(int * em_seq, int len_seq);

#endif

