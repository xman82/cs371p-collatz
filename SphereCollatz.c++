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
// collatz_seek
// -------------

  


// -------------
// collatz_cycle
// -------------

//gives cycle length assuming "current" is passed with "cnt" initialized to 1.

int collatz_cycle(int curr, int cnt){
  assert(curr>0);
  assert(cnt>0);
  while(curr>1){
    if(curr%2==0){
      curr = curr/2;
      cnt++;
      }
    else{
      curr+=(curr>>1)+1;
      cnt+=2;
    }
  }
  return cnt;
}




// -------------
// collatz_c_cycle
// -------------

int collatz_c_cycle(int curr, int* a, int str, int cnt)
{
  assert(curr>0);
  cnt=1;
  while(curr>1)
  {
    if(curr>=str && curr<str+500)
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
  assert(cnt>0);
  return cnt;
}




// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    assert(i > 0);
    assert(j > 0);
    int v = 1;
    int ctemp = 1;

/*varfortestingthing*/
    int str;
/*varfortestingthing*/

    if(i<=j){			//i is lower bound, j upper
      if(i<(j/2))		//if i<(j/2); longest cycle found in [j/2, j] range
	i=j/2;			//set lower bound to j/2
    }
    else{			//j is lower bound, i upper
      int n=j;			
      if(j<(i/2))		//if j<(i/2), longest cycle in [i/2, i] range
	n=i/2;			//sets n to i/2
      j=i;			//set j to upper bound
      i=n;			//set i to lower bound (either j or i/2)
    } 


    /*testingsomethingoutbro*/

    if((j-i)>1000){
      int a[500];
      str=i;
      for(int k=0; k<500; ++k){
        ctemp=collatz_cycle(i,1);
        a[k]=ctemp;
        if(ctemp>v)
          v=ctemp;
        ++i;
      }
      for(int cnt=i; cnt<=j; ++cnt){
        ctemp=collatz_c_cycle(cnt, a, str, 1);
        if(ctemp>v)
          v=ctemp;
      }
      return v;
    }

    /*testingthatthingdonebro*/

   
    for(int ct=i; ct<=j; ++ct){
      ctemp=collatz_cycle(ct, 1);  //fetches cycle length of current number
      assert(ctemp>0);		//cycle length returned must be >= 1
      if(ctemp > v)		//if new cycle length fetched is higher
	v=ctemp;		//becomes new v (longest cycle length)
    }
				//END OF ADDITION TO collat_eval
    assert(v > 0);
    return v;}

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

