#define SHIFT 5
#define BITSPERWORD 32
#define UINT_MAX (2^32 -1)
#define MASK 0x1F
#define NSIZE 10
#define MAXINPUTNUM 1000
#include <stdio.h>
#include <stdlib.h>

/**
 * This function sets the ith element in the bit*
 * array represented by an array of integers.   *
 * @param a - bit vector implemented as an      *
 *             array of integers. Each integer  *
 *             represents a bit word worth of   *
 *             integers.                        *
 * @param n - number of elements in array b     *
 * return - array used with ith bit set         * 
 */

int * set(unsigned int a[],int i) {
  a[i >> SHIFT] |= (1 << (i & MASK));
  return a;
}

/**
 * This function sets the jth element in the bit*
 * array represented by an array of integers.   *
 * @param used - bit vector implemented as an   *
 *             array of integers. Each integer  *
 *             represents a bit word worth of   *
 *             integers.                        *
 * @param n - number of elements in array b     *
 * return - array used with jth bit set         * 
 */
int * setUsed(unsigned int used[],int j) {
  used = set(used,j);
  return used;
}

/**
 * This function finds the first non-used       *
 * integer in the array from left(lowe indices).*
 * @param used - bit vector implemented as an   *
 *             array of integers. Each integer  *
 *             represents a bit word worth of   *
 *             integers.                        *
 * @param n - number of elements in array b     *
 * return - index of the first element not      *
 *          visited in any traversal yet        *       
 */
int hasNonUsed(unsigned int used[],int n) {
  int k = 1 + (n/BITSPERWORD);
  int firstNonUsed = n;
  int foundUsed = 0;
  int pos = 0;
  int i = 0;
  while((i < k)) {
    if (used[i] == 0) {
      return 0;
    } else if (used[i] == UINT_MAX) {
      ++i;
      pos += BITSPERWORD;
    } else {
      unsigned int s = used[i];
      while ((s != 0) && (pos < n)) {
        if (!(s & 1)) {
          return pos;
        } else {
          s = s >> 1;
          ++pos;
        }
      }
      ++i;
    }
  }
  return n;
}

/**
 * This function reads the input values and     *
 * follows the pointers. The elements already   *
 * traversed are marked by setting the bit.     *
 * Each traversal starts the with the leftmost  *
 * element in the array that hasn't been visited*
 * yet, tracked by a bit vector and ends when   *
 * either the same element is visited where the * 
 * traversal started from indicating a cycle or *
 * a -1 is encountered indicating no cycles     *
 * along this path                              * 
 * The traversal stops when no more elements    *
 * remain to be traversed. All the cycles       *
 * during the traversals are counted and        *
 * returned.                                    *
 * Worst case complexity is O(nk) where n is    *
 * number of elements in the array and k is     *
 * total number of paths that can be traversed  *
 * through the array                            *
 * parameters passed to the function            *
 * @param b - array representing the graph.     *
 * @param used - bit vector implemented as an   *
 *             array of integers. Each integer  *
 *             represents a bit word worth of   *
 *             integers.                        *
 * @param n - number of elements in array b     *
 * @return - number of cycles in the array      *   
 */

int followP(int b[],unsigned int used[],int n) {
  int i,j;
  int cycles = 0;
  int k = hasNonUsed(used,n);
  while (k < n) {
    i = k;
    j = b[k];
    used = setUsed(used,i);
    while ((i != j) && (j != -1)) {
      used = setUsed(used,j);
      j = b[j];
    }
    if(i == j) {
      ++cycles;
      used = setUsed(used,j);
    }
    k = hasNonUsed(used,n);
  }
  return cycles;
}

/**
 * This function reads input from the file, and *
 * assigns the input values to the inout        *
 * parameters passed to the function            *
 * @param filename - path to input file         *
 * @param n - pointer to the variable for       *
 *            number of elements in input array *
 * @param b - pointer to the array for holding  *
 *            input values for the graph        *    
 */
void readInput(char *filename,int *n, int *b) {
  FILE *fp;
  char str[NSIZE];
  int i;

  fp = fopen(filename,"r");
  if (fp == NULL) {
    perror("\nError Opening File\n");
    fclose(fp);
    exit(1);
  }
  fgets(str,NSIZE,fp);
  if (fgets == NULL) {
    perror("\nError reading input from file\n");
    fclose(fp);
    exit(1);
  }
  *n = atoi(str);
  for(i = 0;i < *n;++i) {
    if(fgets(str,NSIZE,fp) != NULL) {
      b[i] = atoi(str);
    } else {
      perror("\nError reading input from file\n");
      fclose(fp);
      exit(1);
    }
  }
  fclose(fp);
}

int main(int argc,char *argv[]) {
  char *filename;
  int b[MAXINPUTNUM];
  int i,n = 0;
  int cycles = 0;
  if (argc > 1) {
    filename = argv[1];
  } else {
    fprintf(stderr,"\nUsage:FollowPointers <path to input file>\n");
    exit(1);
  }
  readInput(filename,&n,b);
  printf("\nNumber of elements=%d\n",n);
  printf("\nInput\n");
  for(i = 0;i < n;++i) {
    printf("\t%d",b[i]);
  }
  printf("\n");

  int k = 1 + (n/BITSPERWORD);
  unsigned int used[n];
  for (i = 0;i < n;++i) {
    used[i] = 0;
  }

  cycles = followP(b,used,n);
  printf("\nNumber of cycles=%d\n",cycles);
}
