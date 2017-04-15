#include "viterbi.h"
#include "ui.h"
#include <cmath> //for std::log10
#include <string.h> //for strcmp
#include <iostream>


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
    char * instring = argv[argc - 1];
    bool verbose = false;
    int (*chartoint)(char);
    
    if (argc > 2 && argv[1][0] == '-')
        for (int i = 1; i < argc - 1; i++)
            if (!strcmp(argv[i], "--remap") || !strcmp(argv[i], "-r"))
                chartoint = remap_binary;
            else if (!strcmp(argv[i], "-V") || !strcmp(argv[i], "--verbose"))
                verbose = true;
            else
                return raise_inv_arg(argv[i]);
    else if (argc == 2)
        if (!strcmp(argv[1],  "-h") || !strcmp(argv[1],  "--help"))
            return print_help();
        else if (!strcmp(argv[1], "-l") || !strcmp(argv[1], "--list-states"))
            return list_states(); 
        else if (argv[1][0] == '-')
            return raise_inv_arg(argv[1]);
        else
            chartoint= subtract_zero;
    else
        return raise_inv_argc(argc);
    
    int em_len = strlen(instring);
    int em_seq[em_len];
    
    if (!char_to_intarr(instring, em_seq, chartoint))
        return raise_inv_input();
    if (verbose)
    {
        std::cout << "input array:" << std::endl;
        print_arr(em_seq, em_len);
    }
    eval(em_seq, em_len, verbose);
    return 0;
}
