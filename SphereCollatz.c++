// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream

// ------------
// collatz_read
// ------------

bool collatz_read (std::istream& r, int& i, int& j) {
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

//gives cycle length assuming "current" is passed with "cnt" initialized to 1.

int collatz_cycle(int curr)
{
  int cnt=1;
  while(curr>1)
  {
    if(curr%2==0)
    {
      curr = curr/2;
      cnt++;
    }
    else
    {
      curr+=(curr>>1)+1;
      cnt+=2;
    }
  }
  return cnt;
}

// -------------
// collatz_c_cycle
// -------------

int collatz_c_cycle(int curr, int* a, int str)
{
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
    cnt=1;
  return cnt;
}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    int v = 1;
    int ctemp = 1;
    int str;
    int n;

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
      for(int k=0; k<2000; ++k)
      {
        ctemp=collatz_cycle(i);
        a[k]=ctemp;
        if(ctemp>v)
          v=ctemp;
        ++i;
      }
      for(int cnt=i; cnt<=j; ++cnt)
      {
        ctemp=collatz_c_cycle(cnt, a, str);
        if(ctemp>v)
          v=ctemp;
      }
      return v;
    }
   
    for(int ct=i; ct<=j; ++ct)
    {
      ctemp=collatz_cycle(ct);  //fetches cycle length of current number
      if(ctemp > v)		     //replace old max if new cycle length is greater
        v=ctemp;
    }
    return v;
}

// -------------
// collatz_print
// -------------

void collatz_print (std::ostream& w, int i, int j, int v) {
    assert(i > 0);
    assert(j > 0);
    assert(v > 0);
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

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    collatz_solve(cin, cout);
    return 0;}

