#define MAXSTRSIZE 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * This function removes repeated adjacent characters and whitespaces *
 * from a given string, compacting it in place.                       *
 * @param str - Original string to compact.                           *
 * @return - Compacted string.                                        *
 */
char *string_manip(char *str) {
  int newlen = 1;
  int i = 0;
  int j = i + 1;
  while (str[j] != '\0') {
    while ((str[j] == str[i]) || (str[j] == ' ')) {
      ++j;
      if(str[j] == '\0')
        break;
    }
    if(str[j] == '\0') {
      break;
    } else {
      str[newlen] = str[j];
      newlen = newlen + 1;
      i = j;
      j = j + 1;
    }
  }
  str[newlen] = '\0';
  return str;
}

int main(int argc,char *argv[]) {
  char *filename;
  char str1[MAXSTRSIZE];
  if (argc > 1) {
    filename = argv[1];
  } else {
    fprintf(stderr,"\nUsage:StringManipulation <path to input file>\n");
    exit(1);
  }

  FILE *fp = fopen(filename,"r");
  if (fp == NULL) {
    perror("Error reading input file");
    fclose(fp);
    exit(1);
  }
  if (fgets(str1,MAXSTRSIZE,fp) == NULL) {
    perror("Error reading input from file");
    fclose(fp);
    exit(1);
  }
  fclose(fp);

  printf("\nInput String: %s",str1);

  char *str2 = string_manip(str1);
  printf("\nManipulated String:%s\n",str2); 
}
