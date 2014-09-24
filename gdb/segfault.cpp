#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int foo_len (const char *s)
{
  return strlen (s);
}
 
int main (int argc, char *argv[])
{
  const char *a = NULL;
 
  printf ("size of a = %d\n", foo_len (a));
 
  exit (0);
}
