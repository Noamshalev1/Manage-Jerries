/* Defs.h
   This file is for me - to make the returned values easy to understand and act accordingly */
#ifndef DEFS_H
#define DEFS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* true or false - used at the "isExistPhc" function at Jerry.c */
typedef enum e_bool { false, true } bool;
/* success or failure - used for all the functions that don't return pointers (like add, delete...) */
typedef enum e_status { success, failure } status;

#endif
