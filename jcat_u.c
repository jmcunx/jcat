/*
 * Copyright (c) 2022 2023
 *     John McCue <jmccue@jmcunx.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * jcat_u.c -- common routines
 */

#ifndef _MSDOS
#include <sys/param.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>

#ifdef _MSDOS
#include <io.h>
#else
#ifdef _WIN32
#include <io.h>
#else
#include <sys/stat.h>
#endif
#endif

#include "jcat.h"

/*
 * is_numr() -- determines if all characters are numeric
 */
int is_numr(char *s)

{
  if (s == (char *) NULL)
    return((int) FALSE); /* NULL pointer */
  
  for ( ; (*s) != JLIB2_CHAR_NULL; s++)
    {
      if ( ! isdigit((int)(*s)) )
	return(FALSE);
    }
  
  return(TRUE);

}

/*
 * f_exist() -- determines if a file exists
 */
int f_exist(char *file_name)

{
  if (file_name == (char *) NULL)
    return((int) FALSE);

#ifdef _MSDOS
  if (access(file_name, 00) == -1)
    return (FALSE);
  else
    return (TRUE);
#else
  struct stat file_info;
  if (stat(file_name, &file_info) == 0)
    return (TRUE);
  else
    return (FALSE);
#endif

}

/*
 * sleepm() -- sleep for milliseconds
 */
void sleepm(long int micro)
{
  struct timespec req;
  int secs = 0;

  if (micro < 1000L)
    {
      req.tv_sec = (time_t) 0;
      req.tv_nsec = micro * 1000000L;
    }
  else
    {
      secs = micro;
      req.tv_sec = (time_t) 0;
      req.tv_nsec = 0L;
      while (secs > 1000L)
	{
	  req.tv_sec++;
	  secs -= 1000L;
	  if (secs < 1000L)
	    req.tv_nsec = secs * 1000000L;
	}
    }

  nanosleep(&req, NULL);
  
}

/*
 * init_finfo() -- initialize out file structure
 */
void init_finfo(struct s_file_info *f)

{

  f->fp    = (FILE *) NULL;
  f->fname = (char *) NULL;

} /* init_finfo() */

/*
 * open_in() -- open in file
 */
int open_in(FILE **in, char *fname, FILE *fp_err)

{

  if (fname == (char *) NULL)
    {
      (*in) = stdin;
      return((int) TRUE);
    }
  if (strcmp(fname, FILE_NAME_STDIN) == 0)
    {
      (*in) = stdin;
      return((int) TRUE);
    }

  (*in) = fopen(fname, "r");

  if ((*in) == (FILE *) NULL)
    {
      fprintf(fp_err, MSG_WARN_W002, fname, strerror(errno));
      return((int) FALSE);
    }
  
  return((int) TRUE);

} /* open_in() */

/*
 * close_in() -- Close an input file
 */
void close_in(FILE **in, char *fname)

{
  if (fname == (char *) NULL)
    return;
  if (strcmp(fname, FILE_NAME_STDIN) == 0)
    return;
  
  if ((*in) != (FILE *) NULL)
    {
      fclose((*in));
      (*in) = stdin;
    }

} /* close_in() */

/*
 * open_out() -- save the file anem and check status
 */
int open_out(FILE *wfp, struct s_file_info *f, char *prog_name, int force)

{

  if (f->fname == (char *) NULL)
    return((int) FALSE);
  if (strcmp(f->fname, FILE_NAME_STDOUT) == 0)
    return((int) FALSE);

  if (force == (int) FALSE)
    {
      if ( f_exist(f->fname) )
	{
	  fprintf(wfp, MSG_ERR_E025, f->fname);
	  fprintf(wfp, MSG_ERR_E000, prog_name, SWITCH_CHAR, ARG_HELP);
	  exit(EXIT_FAILURE);
	}
    }

  f->fp = fopen(f->fname, "w");
  if (f->fp == (FILE *) NULL)
    {
      fprintf(wfp, MSG_ERR_E002, f->fname);
      fprintf(wfp, "\t%s\n", strerror(errno));
      fprintf(wfp, MSG_ERR_E000, prog_name, SWITCH_CHAR, ARG_HELP);
      exit(EXIT_FAILURE);
    }

  return((int) TRUE);

} /* open_out() */

/*
 * close_out() -- close output
 */
void close_out(struct s_file_info *f)

{
  if (f->fname == (char *) NULL)
    return;
  if (strcmp(f->fname, FILE_NAME_STDOUT) == 0)
    return;

  fclose(f->fp);
  free(f->fname);
  f->fname = (char *) NULL;

} /* close_out() */
