#ifndef STRING_PROCESS_H
#define STRING_PROCESS_H

#include <stdio.h>
#include <string.h>
#include "include/types.h"

/*
 * Get string with length restriction
 * @ return succ(1)/fail(0):boolean
 */
boolean getString(string s, const Int32 maxLen, const boolean isFixed, const boolean allowEmpty);

#endif