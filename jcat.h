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

#ifndef JCAT_H

#define JCAT_H "INCLUDED"

#define PROG_NAME  "jcat"

#ifndef NULL
#define NULL '\0'
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef JLIB2_CHAR_NULL
#define JLIB2_CHAR_NULL  ((char) '\0')
#endif

/*** structures ***/
struct s_file_info
{
  FILE *fp;
  char *fname;
} ;

struct s_work
{
  struct s_file_info err;         /* default stderr        */
  char *prog_name;                /* real program name     */
  int num_files;                  /* # of files to process */
  int verbose;                    /* TRUE or FALSE         */
  long int milliseconds;          /* milliseconds          */
  int force;                      /* Force Create, T or F  */
} ;

/*** messages ***/
#define SWITCH_CHAR       '-'
#define FILE_NAME_STDIN   "-"
#define FILE_NAME_STDOUT  "-"
#define ARG_ERR           'e'  /* Output Error File                  */
#define ARG_FORCE         'f'  /* force create files                 */
#define ARG_HELP          'h'  /* Show Help                          */
#define ARG_PAUSE         's'  /* Pause for for microseconds         */
#define ARG_VERBOSE       'v'  /* Verbose                            */
#define ARG_VERSION       'V'  /* Show Version Information           */

#define LIT_C80           "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
#define LIT_INFO_01       "\tBuild: %s %s\n"
#define LIT_REV           "Revision"
#define LIT_STDIN         "(standard input)"
#define LIT_STDOUT        "(standard output)"

#define USG_MSG_OPTIONS                  "Options\n"
#define USG_MSG_USAGE                    "usage:\t%s [OPTIONS] [FILES ...]\n"
#define USG_MSG_ARG_ERR                  "\t%c%c file\t\t: Write errors to file 'file', default stderr\n"
#define USG_MSG_ARG_FORCE                "\t%c%c\t\t: force create of files when found\n"
#define USG_MSG_ARG_HELP                 "\t%c%c\t\t: Show brief help and exit\n"
#define USG_MSG_ARG_PAUSE                "\t%c%c n\t\t: Sleep for 'n' microseconds\n"
#define USG_MSG_ARG_VERBOSE_8            "\t%c%c\t\t: verbose level, each time specified level increases\n"
#define USG_MSG_ARG_VERSION              "\t%c%c\t\t: Show revision information and exit\n"

#define MSG_ERR_E000  "Try '%s %c%c' for more information\n"
#define MSG_ERR_E002  "ERROR E002: Cannot open '%s' for write, processing aborted\n"
#define MSG_ERR_E008  "ERROR E008: '%s' is an invalid value for %c%c, must be numeric\n"
#define MSG_ERR_E025  "ERROR E025: File %s cannot be created, already exists\n"
#define MSG_ERR_E074  "ERROR E074: 'Too many Arguments specified for %c%c\n"
#define MSG_ERR_E080  "ERROR E080: cannot allocate initial memory : %s\n"
#define MSG_INFO_I072 "I072:    Lines Reads:  %9ld - File %s\n"
#define MSG_INFO_I080 "I080:   Lines Writes:  %9ld - File %s\n"
#define MSG_INFO_I096 "I096:     Read Bytes:  %9ld - File %s\n"
#define MSG_INFO_I097 "I097:    Write Bytes:  %9ld - File %s\n"
#define MSG_WARN_W002 "W002: Open Error Bypass File '%s' : %s\n"

/*** prototypes ***/
void init(int, char **, struct s_work *);
void init_finfo(struct s_file_info *);
void show_brief_help(FILE *, char *);
void show_rev(FILE *, char *);
void process_arg(int, char **, struct s_work *);
int  open_in(FILE **, char *, FILE *);
void close_in(FILE **, char *);
int open_out(FILE *, struct s_file_info *, char *, int);
void close_out(struct s_file_info *);
void sleepm(long int);
int is_numr(char *);

#endif /*  JCAT_H  */

/* END: jcat.h */
