/*
 bigGraph.c                                              sudowrestler@gmail.com
 
 usage: bigGraph <num vertices> <whole integer that is half the vertex degree>
  
 stitch the output of this to some of the dense subgraphs in the graph directory
 Copyright (C) 2010 James Long
 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char *argv[])
{
  int i, j, k, halfDegree, numNodes;
  
  numNodes   = (int) strtol(argv[1], NULL, 10);
  halfDegree = (int) strtol(argv[2], NULL, 10);
  
  printf("%d # number of nodes\n", numNodes);
  
  for(i=0; i<numNodes; i++)
  {
    printf("%d\t", i);
    
    /*
      each vertex connects to 'halfDegree' vertices behind, 
      and 'halfDegree' vertices ahead
    */
    for(j=-halfDegree; j<halfDegree+1; j++)
    {
      k = i + j;
      if(k<0)         {printf("%d ", i+j+numNodes); continue;}
      if(j==0)        continue;
      if(k>=numNodes) {printf("%d ", i+j-numNodes); continue;}
      printf("%d ", i+j);
    }
    
    printf("\n");
  }
}
