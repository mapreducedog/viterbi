#include <iostream>
#include "viterbi.h"
#include "ui.h"
/*copies numerical values of char array to int_array, 
 *returns true if all values are digits succes*/
bool char_to_intarr(char* char_in, int* int_seq, int (*chartoint)(char))
{
    int value;
    for (int i = 0; char_in[i] != '\0'; i++)
    {
        value = chartoint(char_in[i]);
        if (value < 0 || value > rules.emissions)
            return false;
        int_seq[i] = value;
    }
    return true;
}

int subtract_zero(char ch)
{
    return ch - '0';
}

int remap_binary(char ch)
{
    return (ch == '0' + 6);
}

int print_help()
{
    std::cout << 
    "viterbi by MDP\n"
    "usage: viterbi [options] <seq>,  where <seq> is a string of observed emmissions, (zero indexed)\n"
    "options:\n"
    "-h, --help\t show this help\n"
    "--remap:\tremaps sequence to [1 if 6 else 0]]\n"
    "example usage\n"
    "e.g. if a sequence of heads heads tails tails heads is observed one would run: \n"
    "viterbi 00110\n"
    "for a sequence of 1 through 6es one would use:\n"
    "viterbi --remap 132645\n"
    "which would be read then as 0001000"
    << std::endl;
    return 0;
}
int raise_inv_arg(char* arg)
{
    std::cout << "Unknown argument: " << arg << std::endl;
    print_help();
    return 1;
}


int raise_inv_argc(int argc)
{
    std::cout <<  "expected one argument, got " <<  argc - 1 << " arguments" << std::endl;
    std::cout <<  std::endl;
    print_help();
    return 1;
}

int raise_inv_input()
{
    char valid_inputs[rules.emissions + 1];
    valid_inputs[rules.emissions] = '\0';
    for (unsigned int i = 0; i < rules.emissions; i++)
        valid_inputs[i] = '0' + i;
    
    std::cout << "invalid input: not a valid emission sequence" << std::endl;
    std::cout << "valid inputs for emissions 0 to " <<  rules.emissions - 1 <<  " are :" << std::endl;
    std::cout <<  valid_inputs <<  std::endl;
    return 1;
}

