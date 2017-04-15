#include "viterbi.h"
#include "ui.h"
#include <cmath> //for std::log10
#include <string.h> //for strcmp


//change the dimensionality in viterbi.h if changing nr_emission/nr_states here.
struct rules_set<2, 2> rules = {
	2,
	2,
	{{ std::log10(5.f/6),   std::log10(1.f/6)}, //P_emit(0|state = 0), P_emit(1|state = 0)
	{  std::log10(1.f/2),   std::log10(1.f/2)}}  //P_emit(0|state = 1), P_emit(1|state = 1)
	,
    {{ std::log10(0.9f),    std::log10(0.1f)}, //Ptransition_to(state = 0 | prev_state = 0), P(0| prev_state = 1) 
    {  std::log10(0.05f),    std::log10(0.9f)}}//Ptransition_to(state = 1 | prev_state = 0), P(1| prev_state = 1)
	,
	{  std::log10(0.5f),     std::log10(0.5f) } //P_index_0(state = 0), P_index_0(state = 1)
};


int main(int argc, char ** argv) 
{
    if (argc >=  2 && (!strcmp(argv[1],  "-h") || !strcmp(argv[1],  "--help")))
        return print_help();
    
    char * instring = argv[argc - 1];
    int (*chartoint)(char);
    
    if (argc > 2 && argv[1][0] == '-')
        if (!strcmp(argv[1], "--remap"))
            chartoint = remap_binary;
        else
            return raise_inv_arg(argv[1]);
    else if (argc == 2)
        chartoint= subtract_zero;
    else
        return raise_inv_argc(argc);
    
    int em_len = strlen(instring);
    int em_seq[em_len];
    
    if (!char_to_intarr(instring, em_seq, chartoint))
        return raise_inv_input();
    eval(em_seq, em_len);
    return 0;
}
