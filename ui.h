#ifndef ui_header
#define ui_header

bool char_to_intarr(char* char_in, int* int_seq, int (*chartoint)(char));

/*functions to convert input to emissions*/
int subtract_zero(char ch);
int remap_binary(char ch);

/*help and errors*/
int print_help();
int raise_inv_argc(int argc);
int raise_inv_arg(char* arg);
int raise_inv_input();

#endif
