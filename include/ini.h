// SPDX-License-Identifier: BSD-3-Clause
/*
 * inih -- simple .INI file parser
 *
 * Copyright (c) 2009, Brush Technology
 * Copyright (c) 2012:
 *              Joe Hershberger, National Instruments, joe.hershberger@ni.com
 * All rights reserved.
 *
 * Go to the project home page for more info:
 * http://code.google.com/p/inih/
 */

#ifndef __INI_H_
#define __INI_H_	1


/* Parse given INI-style file. May have [section]s, name=value pairs
   (whitespace stripped), and comments starting with ';' (semicolon). Section
   is "" if name=value pair parsed before any section heading. name:value
   pairs are also supported as a concession to Python's ConfigParser.

   For each name=value pair parsed, call handler function with given user
   pointer as well as section, name, and value (data only valid for duration
   of handler call). Handler should return nonzero on success, zero on error.

   Returns 0 on success, line number of first error on parse error (doesn't
   stop on first error).
*/
static int ini_parse(char *filestart, size_t filelen,
	int (*handler)(void *, char *, char *, char *),	void *user);

#endif	/* __INI_H_ */
