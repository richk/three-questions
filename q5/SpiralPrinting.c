#define MAXROWS 1000
#define MAXCOLS 1000
#include <stdio.h>
#include <stdlib.h>

/**
 * Prints the matrix in a spiral order                               *
 * @param A -  input matrix                                          *
 * @param s1 - start row index for the matrix from top. The function *
 *             cannot access the row indices less this value.        *
 * @param e1 - end row index for the matrix from bottom. The         *
 *             function cannot access the row indices more than this *
 *             value.                                                *
 * @param s2 - start column index for the matrix from left. The      *
 *             function cannot access the column indices less this   *
 *             value.                                                *
 * @param e2 - end column index for the matrix from bottom. The      *
 *             function cannot access the row indices more than this *
               value.                                                *
 */
void spireIterative(int A[][MAXCOLS],int s1,int e1,int s2,int e2) {
  int i,j;
  while((e1 > s1) || (e2 > s2)) {
    for(j=s2;j<=e2-1;++j) {
      printf("\t%d",A[s1][j]);
    }
    for(i=s1;i<=e1-1;++i) {
      printf("\t%d",A[i][e2]);
    }
    for(j=e2;j>=s2+1;--j) {
      printf("\t%d",A[e1][j]);
    }
    for(i=e1;i>=s1+1;--i) {
      printf("\t%d",A[i][s2]);
    }
    s1 = s1 + 1;e1 = e1 - 1;
    s2 = s2 + 1;e2 = e2 - 1;
  }
  if ((s1==e1) && (s2==e2)) {
      printf("\t%d",A[s1][s2]);
  }
}

/**
 * Reads the input from file and assigns them to variables passed by *
 * reference to the function.                                        *
 * @param filename - input file path                                 *
 * @param m - pointer to number of rows in the input matrix          *
 * @param n - pointer to the number of columns in the input matrix   *
 * @param a - pointer to the array for storing the matrix            *
 */
void readInput(char *filename,int *m,int *n,int a[][MAXCOLS]) {
  FILE *fp = fopen(filename,"r");
  int i = 0,j = 0;
  while(fscanf(fp,"%d",&a[i][j]) > 0) {
    char c;
    if (fscanf(fp,"%c",&c) < 0) {
      fprintf(stderr,"\nError reading input\n");
      fclose(fp);
      exit(1);
    }
    if ((c == ' ') || (c == '\t')) {
      ++j;
    } else if(c == '\n') {
      if (i == 0) {
        *n = j + 1;
      }
      ++i;j=0;
    }
  }
  fclose(fp);
  *m = i;
}


int main(int argc, char* argv[]) {
  char *filename;
  int m=0,n=0;
  int i,j;
  int a[MAXROWS][MAXCOLS];
  if (argc > 1) {
    filename = argv[1];
  } else {
    fprintf(stderr,"\nUsage:SpiralPrint <path to input file>\n");
    exit(1);
  }
  readInput(filename,&m,&n,a);
  printf("\nOriginal Matrix:\n");
  for (i = 0;i < m; ++i) { 
    printf("\n");
    for (j = 0;j < n; ++j) {
      printf(" %d ",a[i][j]);
    }
  }
  printf("\n");
  printf("\nPrinting in Spiral Pattern\n");
  spireIterative(a,0,m-1,0,n-1);
  printf("\n");
} 
