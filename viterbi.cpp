#include <iostream> 
#include <math.h> //for log10f
#include "viterbi.h"


max_struct get_max(float * scores)
{
	unsigned int max_pos = 0;
	float max_score = 0;
	bool is_max = true;
	for (unsigned int i = 0; i < rules.states; i++)
	{
		is_max = true;
		for (unsigned int j = 0; j < rules.states && is_max; j++)
			if (scores[i] < scores[j])
				is_max = false;
		if (is_max)
		{
			max_score = scores[i];
			max_pos |= 1 << i; /* rightshift once for each, 
			so that if i = 0, and i = 1 is max leads to max_pos = 0b11,
			if exclusively i = 0 is max => max_pos = 0b01, 
			and if exclusively i = 1 is max, max_pos = 0b10 */
		}					 
	}
	return max_struct {max_score, max_pos};
}

max_struct score_likelihood(float * prev_states, 
								float * p_trans_to_this, 
								float p_emit_this)
{
	float scores[rules.states];
	for (unsigned int prev_state = 0; prev_state < rules.states; prev_state++)
		scores[prev_state] = prev_states[prev_state] + (p_trans_to_this[prev_state]) + p_emit_this;
        //we calc p(current_state = this_state, emission  = this_emission,previous_state = prev_state)
        //but we add log10 probabilities, rather than multiply non-log probabilities (to prevent underflow)
        //for non-log number we would use:
        //scores[state] = prev_states[state] * (p_trans_to_this[state]) * p_emit_this;
	return get_max(scores); //obtain the maxima of these 
}

/*recursively trace back the maxpath(s), and print to stdout the path found*/
void backtrack(char * path,unsigned int index, unsigned int state, unsigned int ** max_lk)
{
    path[index] = '0' + state;
    if (index == 0)
    {
        std::cout << path << std::endl;
        return;
    }
    for (unsigned int prev_state = 0; prev_state < rules.states; prev_state++)
    {
        if (max_lk[index][state] & (1 << prev_state)) //this is a maxpath predecessor
            backtrack(path, index - 1, prev_state, max_lk); //its fine to pass by reference here, because we are searching depth first, so changes always happen at the end of the chain.
    }
}

/* "parent" for backtrack function */
void print_maxpaths(unsigned int max_end_bitarray, unsigned int ** max_lk, int len_seq)
{
    char path[len_seq + 1];
    path[len_seq] = '\0';
    for (unsigned int end_state = 0; end_state < rules.states; end_state++)
        if (max_end_bitarray & (1 << end_state))
            backtrack(path, len_seq - 1, end_state, max_lk);
}


void eval(int * em_seq, int len_seq) 
{
	float p_state [2][rules.states]; //2d array p_state[index % 2][state] of viterbi(state|index)
	//we only need two indices, as only the current and previous score is needed, 
	//for backtracking we use max_lk_prev 
	unsigned int ** max_lk_prev = new unsigned int *[len_seq]; //2d array max_lk_prev[index][state] of bitarrays for following maxpaths
    for (unsigned int i = 0; i < len_seq; i++) //used dynamically allocated memory here so that we can easily pass **unsigned int to backtrack and print_maxpaths,
        max_lk_prev[i] = new unsigned int[rules.states];
    
    //set probablities at index 0
	for (unsigned int i = 0; i < rules.states; i++) 
	{
		p_state[0][i] = rules.initial_state_dist[i]; 
		max_lk_prev[0][i] = 0;
	}
	
	for (unsigned int index = 1; index < len_seq ; index++ )
	{
		for (unsigned int state = 0; state < rules.states; state++)
		{
			max_struct this_score = score_likelihood(p_state[(index - 1) % 2], 
							 rules.p_trans[state], 
							rules.p_emi[state][em_seq[index]]);
			max_lk_prev[index][state] = this_score.max_pos;
			p_state[index % 2][state] = this_score.prob;
            //std::cout << this_score.prob << '\t' << this_score.max_pos << '|';
		}
		//std::cout << std::endl;
	}
	print_maxpaths(get_max(p_state[(len_seq - 1) % 2]).max_pos, max_lk_prev, len_seq);
    
    //free memory
    for (unsigned int i = 0; i < len_seq; i++)
        delete[] max_lk_prev[i];
    delete[] max_lk_prev;
}
