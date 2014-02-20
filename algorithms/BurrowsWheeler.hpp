#ifndef BURROWSWHEELER_HPP
#define BURROWSWHEELER_HPP

// sequential version
std::pair<char*,int> seq_bwt_encode(char *input, int length);
char* seq_bwt_decode(std::pair<char*,int>, int length);

// parallel version
std::pair<char*,int> par_bwt_encode(char *input, int length);
char* par_bwt_decode(std::pair<char*,int>, int length);
void par_suffix_array(char *input, int length, int *SUF);

#endif
