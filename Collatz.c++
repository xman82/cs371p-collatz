// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert> // assert
#include <iostream> // endl, istream, ostream

#include "Collatz.h"

// ------------
// collatz_read
// ------------

bool collatz_read (std::istream& r, int& i, int& j){
    r >> i;
    if (!r)
        return false;
    r >> j;
    assert(i > 0);
    assert(j > 0);
    return true;}

// -------------
// collatz_cycle
// -------------

int collatz_cycle(int curr)
{
  assert(curr>0);
  int cnt=1;
  while(curr>1)
  {
    if(curr%2==0)
    {
      curr/=2;    
      ++cnt;
    }
    else
    {
      curr+=(curr>>1)+1;
      cnt+=2;
    }
  }
  if(curr<0)
  {
    curr==1;
    cnt=1;
  }
  assert(curr==1);
  assert(cnt>0);
  return cnt;
}

// -------------
// collatz_c_cycle
// -------------

int collatz_c_cycle(int curr, int* a, int str)
{
  assert(curr>0);
  int cnt=1;
  while(curr>1)
  {
    if(curr>=str && curr<str+2000)
      return cnt+a[curr-str]-1;
    if(curr%2==0)
    {
      curr/=2;
      ++cnt;
    }
    else
    {
      curr+=(curr>>1)+1;
      cnt+=2;
    }
  }
  if(curr<0)
  {
    curr==1;
    cnt=1;
  }
  assert(curr==1);
  assert(cnt>0);
  return cnt;
}


// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j)
{
    assert(i > 0);
    assert(j > 0);
    int v = 1;
    int ctemp = 1;
    int n;
    int str;

    if(i<j)
    {			      //[i, j]
      if(i<(j/2))		//if i<(j/2); lower bound changed
	  i=j/2;
    }
    else
    {			      //[j, i]
      n=j;			//n substitute for lower bound
      if(j<(i/2))		//if j<(i/2), lower bound changed 
	  n=i/2;
      j=i;			//[i, j]
      i=n;
    }

    if((j-i)>5000)
    {
      int a[2000];
      str=i;
      for(int k=0; k<2000; ++k)    //creates cache for large intervals
      {
        ctemp=collatz_cycle(i);
        a[k]=ctemp;
        if(ctemp>v)
          v=ctemp;
        ++i;
      }
      for(int cnt=i; cnt<=j; ++cnt)
      {
        ctemp=collatz_c_cycle(cnt, a, str); //c_cycle is version of cycle
        if(ctemp>v)
          v=ctemp;
      }
      return v;
    }

    for(int cnt=i; cnt<=j; ++cnt)
    {
      ctemp=collatz_cycle(cnt);  //fetches cycle length of current number
      if(ctemp > v)                //if new cycle length fetched is higher
	  v=ctemp;		           //becomes new v (longest cycle length)
    }
    assert(v > 0);
    return v;
}

// -------------
// collatz_print
// -------------

void collatz_print (std::ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << std::endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (std::istream& r, std::ostream& w) {
    int i;
    int j;
    while (collatz_read(r, i, j)) {
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
