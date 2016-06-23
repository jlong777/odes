/*
 denseSG.c                                                   jlong@jimlong.org
 
 A driver for ODES, an algorithm to find dense subgraphs with density >= 1/2
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

#ifndef ODES_H
  #include "odes.h"
  #define ODES_H
#endif

void PrintUsage(void)
{
  printf("usage: denseSG <graph file> <min density> <min nodes>\n");
  printf("       <graph file>  - a graph description file, see ReadGraph() for format.\n");
  printf("       <min density> - min density for a subgraph\n");
  printf("       <min nodes>   - min number of nodes for a subgraph\n");
}

int main(int argc, char *argv[])
{
  int i, minNodes;
  double density;
  gnGraph *g, **denseSubGraphSet;
  
#ifdef EXCLUDED_EDGES /* experimental, set in odes.h */
  char * exclude[]={"10 1","0 10","1 0",'\0'}; /* must be NULL terminated */
#endif
  
  if(argc!=4)
  {
    PrintUsage();
    return 1;
  }
  
  density = strtod(argv[2], NULL);
  if(density<0.5 || density>1.0)
  {
    fprintf(stderr, "denseSG: density out of range, must be 0.5 <= den <= 1.0, returning...\n");
    return 1;
  }
  
  minNodes = (int) strtol(argv[3], NULL, 10);
  if(minNodes < 2)
  {
    fprintf(stderr, "denseSG: minNodes must be > 1, and should be > 3, exiting...\n");
    return 1;
  }
    
  printf("===============================================================\n");
  
  g = ReadGraph(argv[1]); //PrintGraph(g); continue;

#ifdef EXCLUDED_EDGES
  denseSubGraphSet = ODES(g, density, minNodes, exclude);
#else
  denseSubGraphSet = ODES(g, density, minNodes);
#endif

  if(denseSubGraphSet!=NULL)
  {
    printf("\nDense subgraphs of: %s\n", argv[1]);
    printf("===================\n");
    
    i = 0;
    while(denseSubGraphSet[i]!=NULL)
      PrintGraph(denseSubGraphSet[i++]);

    FreeGraph(g);
    i = 0;
    while(denseSubGraphSet[i]!=NULL)
    {
      FreeGraph(denseSubGraphSet[i]);
      denseSubGraphSet[i] = NULL;
      i++;
    }
    
    printf("\n\n");
  }
  else
  {
    fprintf(stderr, "denseSG: denseSubGraphSet is NULL for %s, returning...\n", argv[1]);
    return 0;
  }
  
  
  return 0;
}
