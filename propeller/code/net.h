//net.h
#include <list>
#include "propeller.h" //N.B. THIS imports "list_arith.h" and "my_math.h" as well.
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
using namespace std;

string itoa(int i);

long long* pt_to_netpt(long long n, long long N);
long long netpt_to_pt(long long netpt[], long long N);


list<long long> create_new_net(list<long long> net,long long old_N, long long new_N);
list<long long> read_list(const char * filename="list.l",long long begin=0, long long end=-1);
void write_list(list<long long> & l, const char * filename="list.l");
void initialize_the_chunk(int interval_length);

// functions used only for the functional test suite
void write_vectors(list<long long> &l, long long N,const char *filename="vectors.l");
void test_refinement();
