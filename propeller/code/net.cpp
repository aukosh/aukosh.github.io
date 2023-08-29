//net.cpp
#include "net.h"

list<long long*> the_chunk; 

string itoa(int i)
{  
  string s;
  stringstream out;
  out << i;
  s = out.str();
  return s;
}


/* This initializes the chunk of vectors used when we refine at a point*/
void initialize_the_chunk(int interval_length)
{
  /*********************************************************
   * Input: int interval length
   *                                                      
   * Output: void
   *
   * Description: This initializes ``the_chunk'', which is the
   *              lattice of vectors used to perform refinements.
   *********************************************************/

  long long v[8][3] = { {1,1,1},{ 1,1,-1},{ 1,-1,1},{ -1,1,1},{1,-1,-1},{-1,1,-1},{-1,-1,1},{-1,-1,-1}};

  for(int i =0;i<=interval_length/2;i++)
    {
        for(int j =0;j<=interval_length/2;j++)
	  {
	    for(int k =0;k<=interval_length/2;k++)
	      {
		long long * point = new long long[3];
		point[0] = i; point[1]=j;point[2]=k;
		for(int l = 0;l < 8;l++)
		  {
		    the_chunk.push_back(multiply(v[l],point));
		  }
		delete[] point;
	      }

	  }
    }
  the_chunk.sort(leq);
  the_chunk.unique(areequal);
  printf("The chunk has been created %lli\n",(long long)the_chunk.size());
  
  
}




long long* pt_to_netpt(long long n, long long N)
{

  /*********************************************************
   * Input: long long n, long long N
   *                                                      
   * Output: point corresponding to n when there is a grid
   *         spacing of Pi/(N-1). 
   *
   * Description: This is used to go from the integer labelling
   *              of the cube of N^3 grid points to the cube 
   *              itself.
   *********************************************************/
  long long * ret = new long long[3];

  ret[0] = n % N;
  ret[1] = (n/N) % N;
  ret[2]= (n/(N*N)) % N;
  
  return ret;
}


long long netpt_to_pt(long long net_pt[], long long N)
{
  /*********************************************************
   * Input: long long net_pt[3], long long N
   *                                                      
   * Output: The integer label corresponding to grid point 
   *         net_pt
   *
   * Description: This is used to generate the integer labelling
   *              of the cube of N^3 grid points. 
   *********************************************************/
  return (net_pt[0] + net_pt[1]*N + net_pt[2]*N*N);
}



list<long long> create_new_net(list<long long>  old_net, long long old_N, long long new_N)
{
  /*********************************************************
   * Input: list<long long> old_net, long long old_N, long long new_N
   *                                                      
   * Output: a refined version of old_net with a new grid spacing of new_N
   *
   * Description: This takes old_net, whose original grid spacing
   *              was Pi/(old_N-1) and refines the grid to a new spacing of
   *              Pi/(new_N-1). We do this by going through the net 
   *              point by point and refining around each point.
   *              We refine around each point by translating the_chunk
   *              so that it is centered at that point and appropriately
   *              rescaling it. 
   *********************************************************/

  if(new_N  < old_N){
    throw "create_new_net: old_N > new_N";
  }

  list<long long> new_net;


  for(list<long long>::iterator iter1 = old_net.begin();iter1 != old_net.end();iter1++)
    {	      
      long long * temp1 =pt_to_netpt(*iter1,old_N); // take an element of the original grid
      long long * temp2 =multiply(temp1,(new_N-1)/(old_N-1)); //dilate it to place in new grid spacing
      delete[] temp1;

      for(list<long long*>::iterator iter2 = the_chunk.begin(); iter2 != the_chunk.end();iter2++) //here we translate and rescale the chunk
	{
	  long long * temp3 = add(*iter2,temp2); // translate
	  long long new_point = netpt_to_pt(temp3,new_N); //convert

	  if(new_point>=0)
	    {
	      new_net.push_back(new_point);
	    }
	  delete[] temp3;
	}
      delete[] temp2;
    } 
  new_net.sort();
  new_net.unique();

  return new_net;
}


void write_list(list<long long> &l, const char * filename)
{
 /*********************************************************
   * Input: list<long long> &l, const char * filename
   *                                                      
   * Output: a file filename
   *
   * Description: This takes the contents of the list l
   *              and dumps it in to filename
   *********************************************************/
  ofstream SaveFile(filename,ofstream::out);
  for(list<long long>::iterator iter = l.begin();iter != l.end(); iter++)
    {
      SaveFile << *iter << '\n';
    }
  SaveFile.close();
}


list<long long> read_list(const char * filename,long long begin, long long end)
{
 /*********************************************************
   * Input:  const char * filename, long long begin, long long end
   *                                                      
   * Output: a list<long long> with the contents of read_list from line begin
   *         to line end
   *
   * Description: This reads filename and generates a list
   *              with its contents starting from line begin
   *              and ending with line end 
   *********************************************************/

  ifstream ReadFile(filename,ifstream::in);
  list<long long> l,to_return;

  while(ReadFile)
    {
      char number[50];
      ReadFile.getline(number,50);
      if(number[0] != EOF)
	{
	  l.push_back(atoll(number));
	}
    }
  printf("Size of list: %i\n",(int) l.size());


  if(end == -1 || end > l.size()) { end = l.size();}

  list<long long>::iterator iter = l.begin();
  int i = 0;
  for(;i < begin;i++){iter++;}
  for(;i < end;i++)
    {
      to_return.push_back(*iter);
      iter++;
    }
  ReadFile.close();
  return to_return;
}

void write_vectors(list<long long>&l,long long N,const char * filename)
{
 /*********************************************************
   * Input: list<long long> &l, long long N, const char * filename
   *                                                      
   * Output: a file filename
   *
   * Description: This takes the contents of the list l
   *              generates the vectors corresponding to
   *              the elements of the list and writes these
   *              vectors to file
   *********************************************************/

  ofstream SaveFile(filename,ofstream::out);
  for(list<long long>::iterator iter = l.begin();iter != l.end(); iter++)
    {
      long long * pt = pt_to_netpt(*iter,N);
      double * temp = times_pi_by_N(pt,N);
      SaveFile << temp[0] << " " << temp[1] << " " << temp[2]<< '\n';
    }
  SaveFile.close();
}




void test_refinement()
{
  printf("testing net.cpp....\n");
  list<long long> l;

  for(int i = 1; i < 11*11*11; i++)
    { 
      l.push_back(i);
    }

  write_list(l,"test_labels_1.l");
  write_vectors(l,11,"test_vects_1.l");

  l = read_list("test_labels_1.l", 119+50,119+54);
  write_list(l,"test_labels_2.l");
  write_vectors(l,11,"test_vects_2.l");

  l = create_new_net(l,11,101);
  write_list(l,"test_labels_3.l");
  write_vectors(l,101,"test_vects_3.l");
  printf("Please run test_refinement.py in this directory.\n\n\n");
}
