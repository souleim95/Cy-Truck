#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "other.h"

int max(int a, int b) {
  if (a >= b) {
    return a;
  }
  return b;
}

int min(int a, int b) {
  if (a >= b) {
    return b;
  }
  return a;
}

int min2(int a, int b, int c) {
 return min(min(a, b), c); 
 }

int max2(int a, int b, int c) { 
return max(max(a, b), c); 
}
