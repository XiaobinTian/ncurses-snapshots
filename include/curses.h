
/***************************************************************************
*                            COPYRIGHT NOTICE                              *
****************************************************************************
*                ncurses is copyright (C) 1992-1995                        *
*                          Zeyd M. Ben-Halim                               *
*                          zmbenhal@netcom.com                             *
*                          Eric S. Raymond                                 *
*                          esr@snark.thyrsus.com                           *
*                                                                          *
*        Permission is hereby granted to reproduce and distribute ncurses  *
*        by any means and for any fee, whether alone or as part of a       *
*        larger distribution, in source or in binary form, PROVIDED        *
*        this notice is included with any such distribution, and is not    *
*        removed from any of its header files. Mention of ncurses in any   *
*        applications linked with it is highly appreciated.                *
*                                                                          *
*        ncurses comes AS IS with no warranty, implied or expressed.       *
*                                                                          *
***************************************************************************/


#ifndef __NCURSES_H
#define __NCURSES_H
#define CURSES 1
#define CURSES_H 1
#define NCURSES_VERSION "1.9.5"

#include <stdio.h>   
#include <unctrl.h>
#include <stdarg.h>
#ifdef XPG4_EXTENDED
#include <stddef.h>	/* we want wchar_t */
#endif /* XPG4_EXTENDED */

/* XSI and SVr4 specify that curses implements 'bool'.  However, C++ may also
 * implement it.  If so, we must use the C++ compiler's type to avoid conflict
 * with other interfaces.
 *
 * To simplify use with/without the configuration script, we define the symbols
 * CXX_BUILTIN_BOOL and CXX_TYPE_OF_BOOL; they're edited by the configure
 * script.
 */

#undef TRUE
#undef FALSE
#define CXX_BUILTIN_BOOL 1
#define CXX_TYPE_OF_BOOL char

#if defined(__cplusplus) && CXX_BUILTIN_BOOL
#define TRUE    ((CXX_TYPE_OF_BOOL)true)
#define FALSE   ((CXX_TYPE_OF_BOOL)false)
#else
typedef CXX_TYPE_OF_BOOL bool;
#define TRUE    ((bool)1)
#define FALSE   ((bool)0)
#endif

typedef unsigned long  chtype;

/* attributes */
#define A_ATTRIBUTES	0xffffff00
#define A_NORMAL	0x00000000
#define A_STANDOUT	0x00010000
#define A_UNDERLINE	0x00020000
#define A_REVERSE	0x00040000
#define A_BLINK		0x00080000
#define A_DIM		0x00100000
#define A_BOLD		0x00200000
#define A_ALTCHARSET	0x00400000
#define A_INVIS		0x00800000
#define A_PROTECT	0x01000000
#define A_HORIZONTAL	0x02000000	/* XSI Curses attr -- not yet used */
#define A_LEFT		0x04000000	/* XSI Curses attr -- not yet used */
#define A_LOW		0x08000000	/* XSI Curses attr -- not yet used */
#define A_RIGHT		0x10000000	/* XSI Curses attr -- not yet used */
#define A_TOP		0x20000000	/* XSI Curses attr -- not yet used */
#define A_VERTICAL	0x40000000	/* XSI Curses attr -- not yet used */
#define A_CHARTEXT	0x000000ff
#define A_COLOR		0x0000ff00
#define COLOR_PAIR(n)	(n << 8) 
#define PAIR_NUMBER(a)	((a & A_COLOR) >> 8)

/* extended attributes unique to ncurses */
#ifdef __i386__
#define A_PCCHARSET	A_PROTECT	/* corresponds to smpch/rmpch */
#endif /* __i386__ */

/*
 * XSI attributes.  In the ncurses implementation, they are identical to the
 * A_ attributes because attr_t is just an int.  The XSI Curses attr_* and
 * wattr_* entry points are all mapped to attr* and wattr* entry points.
 */
#define WA_ATTRIBUTES	0xffffff00
#define WA_NORMAL	0x00000000
#define WA_STANDOUT	0x00010000
#define WA_UNDERLINE	0x00020000
#define WA_REVERSE	0x00040000
#define WA_BLINK	0x00080000
#define WA_DIM		0x00100000
#define WA_BOLD		0x00200000
#define WA_ALTCHARSET	0x00400000
#define WA_INVIS	0x00800000
#define WA_PROTECT	0x01000000
#define WA_HORIZONTAL	0x02000000	/* XSI Curses attr -- not yet used */
#define WA_LEFT		0x04000000	/* XSI Curses attr -- not yet used */
#define WA_LOW		0x08000000	/* XSI Curses attr -- not yet used */
#define WA_RIGHT	0x10000000	/* XSI Curses attr -- not yet used */
#define WA_TOP		0x20000000	/* XSI Curses attr -- not yet used */
#define WA_VERTICAL	0x40000000	/* XSI Curses attr -- not yet used */

/* colors */
extern int COLORS;
extern int COLOR_PAIRS;
extern unsigned char *color_pairs;

#define COLOR_BLACK	0
#define COLOR_RED	1
#define COLOR_GREEN	2
#define COLOR_YELLOW	3
#define COLOR_BLUE	4
#define COLOR_MAGENTA	5
#define COLOR_CYAN	6
#define COLOR_WHITE	7

/* line graphics */

extern 	chtype acs_map[];

#define ACS_ULCORNER	(acs_map['l'])	/* upper left corner */
#define ACS_LLCORNER	(acs_map['m'])	/* lower left corner */
#define ACS_URCORNER	(acs_map['k'])	/* upper right corner */
#define ACS_LRCORNER	(acs_map['j'])	/* lower right corner */
#define ACS_LTEE	(acs_map['t'])	/* tee pointing right */
#define ACS_RTEE	(acs_map['u'])	/* tee pointing left */
#define ACS_BTEE	(acs_map['v'])	/* tee pointing up */
#define ACS_TTEE	(acs_map['w'])	/* tee pointing down */
#define ACS_HLINE	(acs_map['q'])	/* horizontal line */
#define ACS_VLINE	(acs_map['x'])	/* vertical line */
#define ACS_PLUS	(acs_map['n'])	/* large plus or crossover */
#define ACS_S1		(acs_map['o'])	/* scan line 1 */
#define ACS_S9		(acs_map['s'])	/* scan line 9 */
#define ACS_DIAMOND	(acs_map['`'])	/* diamond */
#define ACS_CKBOARD	(acs_map['a'])	/* checker board (stipple) */
#define ACS_DEGREE	(acs_map['f'])	/* degree symbol */
#define ACS_PLMINUS	(acs_map['g'])	/* plus/minus */
#define ACS_BULLET	(acs_map['~'])	/* bullet */
#define ACS_LARROW	(acs_map[','])	/* arrow pointing left */
#define ACS_RARROW	(acs_map['+'])	/* arrow pointing right */
#define ACS_DARROW	(acs_map['.'])	/* arrow pointing down */
#define ACS_UARROW	(acs_map['-'])	/* arrow pointing up */
#define ACS_BOARD	(acs_map['h'])	/* board of squares */
#define ACS_LANTERN	(acs_map['I'])	/* lantern symbol */
#define ACS_BLOCK	(acs_map['0'])	/* solid square block */

#if	!defined(ERR) || ((ERR) != -1)
#define ERR     (-1)
#endif

#if	!defined(OK) || ((OK) != 0)
#define OK      (0)
#endif

/* values for the _flags member */
#define _SUBWIN         0x01	/* is this a sub-window? */
#define _ENDLINE        0x02	/* is the window flush right? */
#define _FULLWIN        0x04	/* is the window full-screen? */
#define _SCROLLWIN      0x08	/* bottom edge is at screen bottom? */
#define _ISPAD	        0x10	/* is this window a pad? */
#define _HASMOVED       0x20	/* has cursor moved since last refresh? */
#define _NEED_WRAP	0x40	/* cursor wrap pending */

/*
 * this value is used in the firstchar and lastchar fields to mark 
 * unchanged lines
 */
#define _NOCHANGE       -1

/*
 * this value is used in the oldindex field to mark lines created by insertions
 * and scrolls.
 */
#define NEWINDEX	-1

typedef struct screen  SCREEN;
typedef struct _win_st WINDOW;

typedef	chtype	attr_t;		/* ...must be at least as wide as chtype */

#ifdef XPG4_EXTENDED
#ifndef _WCHAR_T
typedef wchar_t	unsigned long;
#endif /* _WCHAR_T */
#ifndef _WINT_T
typedef wint_t	long int;
#endif /* _WINT_T */

#define CCHARW_MAX	5
typedef 
{
    attr_t	attr;
    wchar_t	chars[CCHARW_MAX];
}
cchar_t;
#endif /* XPG4_EXTENDED */

struct _win_st {
	short   _cury, _curx;	/* current cursor position */

	/* window location and size */
	short   _maxy, _maxx;	/* maximums of x and y, NOT window size */
	short   _begy, _begx;	/* screen coords of upper-left-hand corner */

	short   _flags;		/* window state flags */

	/* attribute tracking */
	attr_t  _attrs;		/* current attribute for non-space character */
	chtype  _bkgd;		/* current background char/attribute pair */

	/* option values set by user */
	bool	_notimeout;	/* no time out on function-key entry? */
	bool    _clear;		/* consider all data in the window invalid? */
	bool    _leave;		/* OK to not reset cursor on exit? */
	bool    _scroll;	/* OK to scroll this window? */
	bool    _idlok;		/* OK to use insert/delete line? */
	bool    _idcok;		/* OK to use insert/delete char? */
	bool	_immed;		/* window in immed mode? (not yet used) */
	bool	_sync;		/* window in sync mode? */
	bool    _use_keypad;    /* process function keys into KEY_ symbols? */
	int	_delay;		/* 0 = nodelay, <0 = blocking, >0 = delay */

	/* the actual line data */
	struct ldat
	{
	    chtype  *text;	/* text of the line */
	    short   firstchar;  /* first changed character in the line */
	    short   lastchar;   /* last changed character in the line */
	    short   oldindex;	/* index of the line at last update */
	}
	*_line;

	/* global screen state */
	short	_regtop;	/* top line of scrolling region */
	short	_regbottom;	/* bottom line of scrolling region */

	/* these are used only if this is a sub-window */
	int	_parx;		/* x coordinate of this window in parent */
	int	_pary;		/* y coordinate of this window in parent */
	WINDOW	*_parent;	/* pointer to parent if a sub-window */
};

extern WINDOW   *stdscr, *curscr, *newscr;

extern int	LINES, COLS, TABSIZE;

#ifdef __cplusplus
extern "C" {
#endif

extern char ttytype[];		/* needed for backward compatibility */

/*
 * GCC (and some other compilers) define '__attribute__'; we're using this
 * macro to alert the compiler to flag inconsistencies in printf/scanf-like
 * function calls.  Just in case '__attribute__' isn't defined, make a dummy.
 */
#if !defined(__GNUC__) && !defined(__attribute__)
#define __attribute__(p) /* nothing */
#endif

/* Debugging : use with libncurses_g.a */

extern void _tracef(char *, ...) __attribute__((format(printf,1,2)));
extern void _tracedump(char *, WINDOW *);
extern char *_traceattr(attr_t mode);
extern char *_tracechar(const unsigned char);
extern void trace(const unsigned int tracelevel);

/* trace masks */
#define TRACE_DISABLE	0x00	/* turn off tracing */
#define TRACE_UPDATE	0x01	/* trace update actions, old & new screens */
#define TRACE_MOVE	0x02	/* trace cursor moves and scrolls */
#define TRACE_CHARPUT	0x04	/* trace all character outputs */
#define TRACE_ORDINARY	0x07	/* trace all update actions */
#define TRACE_CALLS	0x08	/* trace all curses calls */
#define TRACE_VIRTPUT	0x10	/* trace virtual character puts */
#define TRACE_FIFO	0x20	/* also fifo actions by getch() */
#define TRACE_MAXIMUM	0xff	/* maximum trace level */

#ifdef TRACE
extern bool no_optimize;	/* suppress optimization */
#endif /* TRACE */

/* function prototypes */

extern int baudrate(void);
extern int beep(void);
extern int cbreak(void);
extern int clearok(WINDOW *,bool);
extern int copywin(WINDOW *,WINDOW *,int,int,int,int,int,int,int);
extern int curs_set(int);
extern int def_prog_mode(void);
extern int def_shell_mode(void);
extern int delay_output(float);
extern void delscreen(SCREEN *SP);
extern int delwin(WINDOW *);
extern WINDOW *derwin(WINDOW *,int,int,int,int);
extern int doupdate(void);
extern WINDOW *dupwin(WINDOW *);
extern int echo(void);
extern int endwin(void);
extern char erasechar(void);
extern void filter(void);
extern int flash(void);
extern int flushinp(void);
extern WINDOW *getwin(FILE *fp);
extern int halfdelay(int);
extern int has_ic(void);
extern int has_il(void);
extern int idcok(WINDOW *, bool);
extern int idlok(WINDOW *, bool);
extern int immedok(WINDOW *, bool);
extern int intrflush(WINDOW *,bool);
extern int is_linetouched(WINDOW *,int);
extern int is_wintouched(WINDOW *);
extern WINDOW *initscr(void);
extern int isendwin(void);
extern char *keyname(int);
extern int keypad(WINDOW *,bool);
extern char killchar(void);
extern int leaveok(WINDOW *,bool);
extern char *longname(void);
extern int meta(WINDOW *,bool);
extern int mvcur(int,int,int,int);
extern int mvderwin(WINDOW *, int, int);
extern int mvprintw(int,int,const char *,...);
extern int mvscanw(int,int,const char *,...);
extern int mvwin(WINDOW *,int,int);
extern int mvwprintw(WINDOW *,int,int,const char *,...);
extern int mvwscanw(WINDOW *,int,int,const char *,...);
extern int napms(int);
extern WINDOW *newpad(int,int);
extern SCREEN *newterm(const char *,FILE *,FILE *);
extern WINDOW *newwin(int,int,int,int);
extern int nl(void);
extern int nocbreak(void);
extern int nodelay(WINDOW *,bool);
extern int noecho(void);
extern int nonl(void);
extern int noqiflush(void);
extern int noraw(void);
extern int notimeout(WINDOW *,bool);
extern int overlay(WINDOW *const,WINDOW *);
extern int overwrite(WINDOW *const,WINDOW *);
extern int pechochar(WINDOW *, chtype);
extern int pnoutrefresh(WINDOW *,int,int,int,int,int,int);
extern int prefresh(WINDOW *,int,int,int,int,int,int);
extern int printw(const char *,...);
extern int putwin(WINDOW *, FILE *);
extern int qiflush(void);
extern int raw(void);
extern int reset_prog_mode(void);
extern int reset_shell_mode(void);
extern int resetty(void);
extern int ripoffline(int line, int (*init)(WINDOW *, int));
extern int savetty(void);
extern int scanw(const char *,...);
extern int scr_dump(const char *file);
extern int scr_init(const char *file);
extern int scr_restore(const char *file);
extern int scr_set(const char *file);
extern int scrollok(WINDOW *,bool);
extern SCREEN *set_term(SCREEN *);
extern WINDOW *subpad(WINDOW *orig, int l, int c, int begy, int begx);
extern WINDOW *subwin(WINDOW *,int,int,int,int);
extern int syncok(WINDOW *win, bool bf);
extern attr_t termattrs(void);
extern char *termname(void);
extern int timeout(int);
extern int typeahead(int);
extern int ungetch(int);
extern void use_env(bool);
extern int vidattr(attr_t);
extern int vidputs(attr_t,int (*)(int));
extern int vwscanw(WINDOW *,const char *,va_list);
extern int vwprintw(WINDOW *,const char *,va_list);
extern int waddch(WINDOW *, const chtype);
#ifdef XPG4_EXTENDED
extern int waddchnwstr(WINDOW *,const chtype *,int);
extern int waddnwstr(WINDOW *,const char *,int);
#else
extern int waddchnstr(WINDOW *,const chtype *,int);
extern int waddnstr(WINDOW *,const char *,int);
#endif /* XPG4_EXTENDED */
extern int wattron(WINDOW *,const attr_t);
extern int wattroff(WINDOW *,const attr_t);
extern int wbkgd(WINDOW *,const chtype);
extern int wborder(WINDOW *,chtype,chtype,chtype,chtype,chtype,chtype,chtype,chtype);
extern int wchgat(WINDOW *, int, attr_t, short, void *const);
extern int wclear(WINDOW *);
extern int wclrtobot(WINDOW *);
extern int wclrtoeol(WINDOW *);
extern void wcursyncup(WINDOW *);
extern int wdelch(WINDOW *);
extern int wechochar(WINDOW *, chtype);
extern int werase(WINDOW *);
extern int wgetch(WINDOW *);
extern int wgetnstr(WINDOW *,char *,int maxlen);
extern int whline(WINDOW *,chtype,int);
extern int winchnstr(WINDOW*, chtype*, int);
extern int winsch(WINDOW *,chtype);
extern int winsdelln(WINDOW *,int);
extern int winnstr(WINDOW *win,char *str,int n);
extern int winsnstr(WINDOW *,const char *,int);
extern int wmove(WINDOW *,int,int);
extern int wnoutrefresh(WINDOW *);
extern int wprintw(WINDOW *,const char *,...);
extern int wredrawln(WINDOW *,int,int);
extern int wrefresh(WINDOW *);
extern int wscanw(WINDOW *,const char *,...);
extern int wscrl(WINDOW *,int);
extern int wsetscrreg(WINDOW *,int,int);
extern void wsyncdown(WINDOW *);
extern void wsyncup(WINDOW *);
extern int wtimeout(WINDOW *,int);
extern int wtouchln(WINDOW *,int,int,int);
extern int wvline(WINDOW *,chtype,int);

extern bool can_change_color(void);
extern int color_content(short,short *,short *, short *);
extern int has_colors(void);
extern int init_color(short,short,short,short);
extern int init_pair(short,short,short);
extern int pair_content(short,short*,short*);
extern int start_color(void);

extern int slk_init(int);
extern int slk_set(int,const char *,int);
extern int slk_refresh(void);
extern int slk_noutrefresh(void);
extern char *slk_label(int);
extern int slk_clear(void);
extern int slk_restore(void);
extern int slk_touch(void);
extern int slk_attrset(attr_t);
extern int slk_attron(attr_t);
extern int slk_attroff(attr_t);

/* non-XSI extensions */
extern int resizeterm (int, int);
extern int wresize (WINDOW *, int, int);

#ifdef __cplusplus
}
#endif

/*
 * pseudo functions
 */
#define wgetstr(w, s)		wgetnstr(w, s, -1)
#define getnstr(w, s, n)	wgetnstr(stdscr, s, n)

#define setterm(term)		setupterm(term, 1, (int *)0)

#define fixterm()		reset_prog_mode()
#define resetterm()		reset_shell_mode()
#define saveterm()		def_prog_mode()
#define crmode()		cbreak()
#define nocrmode()		nocbreak()
#define gettmode()		

#define getyx(win,y,x)   	(y = (win)->_cury, x = (win)->_curx)
#define getbegyx(win,y,x)	(y = (win)->_begy, x = (win)->_begx)
#define getmaxyx(win,y,x)	(y = (win)->_maxy + 1, x = (win)->_maxx + 1)
#define getparyx(win,y,x)	(y = (win)->_pary, x = (win)->_parx)
#define getsyx(y,x)		getyx(stdscr, y, x)
#define setsyx(y,x)		(stdscr->_cury = y, stdscr->_curx = x)

#define wbkgdset(win,ch)	((win)->_bkgd = ch)

/* It seems older SYSV curses versions define these */
#define getattrs(win)		((win)->_attrs)
#define getmaxx(win)		((win)->_maxx + 1)
#define getmaxy(win)		((win)->_maxy + 1)

#define winch(win)       	((win)->_line[(win)->_cury].text[(win)->_curx])
#define wstandout(win)      	(wattrset(win,A_STANDOUT))
#define wstandend(win)      	(wattrset(win,A_NORMAL))
#define wattrset(win,at)    	((win)->_attrs = (at))

#define scroll(win)		wscrl(win,1)

#define touchwin(win)		wtouchln((win), 0, (win)->_maxy + 1, 1)
#define touchline(win, s, c)	wtouchln((win), s, c, 1)
#define untouchwin(win)		wtouchln((win), 0, (win)->_maxy + 1, 0)

#define box(win, v, h)		wborder(win, v, v, h, h, 0, 0, 0, 0)
#define border(ls, rs, ts, bs, tl, tr, bl, br)	wborder(stdscr, ls, rs, ts, bs, tl, tr, bl, br)
#define hline(ch, n)		whline(stdscr, ch, n)
#define vline(ch, n)		wvline(stdscr, ch, n)

#define winstr(w, s)		winnstr(w, s, -1)
#define winchstr(w, s)		winchnstr(w, s, -1)
#define winsstr(w, s)		winsnstr(w, s, -1)

#define redrawwin(w)		wredrawln(w, 0, w->_maxy+1)
#define waddstr(win,str)	waddnstr(win,str,-1)
#define waddchstr(win,str)	waddchnstr(win,str,-1)

#ifdef XPG4_EXTENDED
#define waddchnstr(win,str,-1)	waddchnwstr(win,mbstowcs(str),-1)
#define waddnstr(win,str,-1)	waddnwstr(win,mbstowcs(str),-1)
#endif /* XPG4_EXTENDED */

/*
 * pseudo functions for standard screen
 */

#define bkgdset(ch)		wbkgdset(stdscr,ch)
#define bkgd(ch)		wbkgd(stdscr,ch)
#define inch()       		winch(stdscr)
#define standout()     		wstandout(stdscr)
#define standend()     		wstandend(stdscr)
#define attron(at)     		wattron(stdscr,at)
#define attroff(at)    		wattroff(stdscr,at)
#define attrset(at)    		wattrset(stdscr,at)
#define addch(ch)      		waddch(stdscr,ch)
#define echochar(c)		wechochar(stdscr, c)
#define getch()        		wgetch(stdscr)
#define addstr(str)    		waddnstr(stdscr,str,-1)
#define getstr(str)    		wgetstr(stdscr,str)
#define move(y, x)     		wmove(stdscr,y,x)
#define clear()        		wclear(stdscr)
#define erase()        		werase(stdscr)
#define clrtobot()     		wclrtobot(stdscr)
#define clrtoeol()     		wclrtoeol(stdscr)
#define insertln()     		winsdelln(stdscr, 1)
#define winsertln(w)     	winsdelln(w, 1)
#define deleteln()     		winsdelln(stdscr, -1)
#define wdeleteln(w)     	winsdelln(w, -1)
#define refresh()      		wrefresh(stdscr)
#define insch(c)       		winsch(stdscr,c)
#define delch()        		wdelch(stdscr)
#define setscrreg(t,b) 		wsetscrreg(stdscr,t,b)
#define scrl(n)			wscrl(stdscr,n)
#define timeout(delay)		wtimeout(stdscr, delay)
#define addnstr(str,n)		waddnstr(stdscr,str,n)
#define addchstr(str)		waddchstr(stdscr,str)
#define addchnstr(str,n)	waddchnstr(stdscr,str, n)
#define insdelln(n)		winsdelln(stdscr, n)
#define insstr(s)		winsstr(stdscr, s)
#define insnstr(s,n)		winsnstr(stdscr, s, n)
#define instr(s)		winstr(stdscr, s)
#define innstr(s,n)		winnstr(stdscr, s, n)
#define inchstr(s)		winchstr(stdscr, s)
#define inchnstr(s,n)		winchnstr(stdscr, s, n)

/*
 * mv functions
*/

#define mvwaddch(win,y,x,ch)    	(wmove(win,y,x) == ERR ? ERR : waddch(win,ch))
#define mvwgetch(win,y,x)       	(wmove(win,y,x) == ERR ? ERR : wgetch(win))
#define mvwaddchnstr(win,y,x,str,n)	(wmove(win,y,x) == ERR ? ERR : waddchnstr(win,str,n))
#define mvwaddchstr(win,y,x,str)  	(wmove(win,y,x) == ERR ? ERR : waddchnstr(win,str,-1))
#define mvwaddnstr(win,y,x,str,n)	(wmove(win,y,x) == ERR ? ERR : waddnstr(win,str,n))
#define mvwaddstr(win,y,x,str)  	(wmove(win,y,x) == ERR ? ERR : waddnstr(win,str,-1))
#define mvwgetstr(win,y,x,str)      	(wmove(win,y,x) == ERR ? ERR : wgetstr(win,str))
#define mvgetnstr(win,y,x,str,n)    	(wmove(win,y,x) == ERR ? ERR : wgetnstr(stdscr,str,n))
#define mvwgetnstr(win,y,x,str,n)    	(wmove(win,y,x) == ERR ? ERR : wgetnstr(win,str,n))
#define mvwinch(win,y,x)        	(wmove(win,y,x) == ERR ? ERR : winch(win))
#define mvwdelch(win,y,x)       	(wmove(win,y,x) == ERR ? ERR : wdelch(win))
#define mvwinsch(win,y,x,c)     	(wmove(win,y,x) == ERR ? ERR : winsch(win,c))
#define mvaddch(y,x,ch)         	mvwaddch(stdscr,y,x,ch)
#define mvaddchnstr(y,x,str,n)		mvwaddchnstr(stdscr,y,x,str,n)
#define mvaddchstr(y,x,str)		mvwaddchstr(stdscr,y,x,str)
#define mvgetch(y,x)            	mvwgetch(stdscr,y,x)
#define mvaddnstr(y,x,str,n)		mvwaddnstr(stdscr,y,x,str,n)
#define mvaddstr(y,x,str)       	mvwaddstr(stdscr,y,x,str)
#define mvgetstr(y,x,str)           	mvwgetstr(stdscr,y,x,str)
#define mvinch(y,x)             	mvwinch(stdscr,y,x)
#define mvdelch(y,x)            	mvwdelch(stdscr,y,x)
#define mvinsch(y,x,c)          	mvwinsch(stdscr,y,x,c)
#define mvwinsstr(w, y, x, s)		(wmove(w,y,x) == ERR ? ERR : winsstr(w,s))
#define mvwinsnstr(w, y, x, s, n)	(wmove(w,y,x) == ERR ? ERR : winsnstr(w,s,n))
#define mvinsstr(y,x,s)			mvwinsstr(stdscr,y,x,s)
#define mvinsnstr(y,x,s,n)		mvwinsnstr(stdscr,y,x,s,n)
#define mvwinstr(w, y, x, s)		(wmove(w,y,x) == ERR ? ERR : winstr(w,s))
#define mvwinnstr(w, y, x, s, n)	(wmove(w,y,x) == ERR ? ERR : winnstr(w,s,n))
#define mvinstr(y,x,s)			mvwinstr(stdscr,y,x,s)
#define mvinnstr(y,x,s,n)		mvwinnstr(stdscr,y,x,s,n)
#define mvwinchstr(w, y, x, s)		(wmove(w,y,x) == ERR ? ERR : winstr(w,s))
#define mvwinchnstr(w, y, x, s, n)	(wmove(w,y,x) == ERR ? ERR : winnstr(w,s,n))
#define mvinchstr(y,x,s)		mvwinstr(stdscr,y,x,s)
#define mvinchnstr(y,x,s,n)		mvwinnstr(stdscr,y,x,s,n)

/*
 * XSI curses macros for XPG4 conformance.
 * The underling functions needed to make these work are:
 * waddnwstr(), waddchnwstr(), wadd_wch(), wborder_set(), wchgat(),
 * wecho_wchar(), wgetn_wstr(), wget_wch(), whline_set(), vhline_set(),
 * winnwstr(), wins_nwstr(), wins_wch(), win_wch(), win_wchnstr().
 * Except for wchgat(), these are not yet implemented.  They will be someday.
 */
#define addnwstr(wstr, n)	waddnwstr(stdscr, wstr, n)
#define addwstr(wstr, n)	waddnwstr(stdscr, wstr, -1)
#define mvaddnwstr(y,x,wstr, n)	(wmove(stdscr,y,x) == ERR ? ERR : waddnwstr(stdscr, wstr, n))
#define mvaddwstr(y,x,wstr, n)	(wmove(stdscr,y,x) == ERR ? ERR : waddnwstr(stdscr, wstr, -1))
#define mvwaddnwstr(y,x,win,wstr,n)	(wmove(win,y,x) == ERR ? ERR : waddnwstr(stdscr, wstr, n))
#define mvwaddwstr(y,x,win,wstr,n)	(wmove(win,y,x) == ERR ? ERR : waddnwstr(stdscr, wstr, -1))
#define waddwstr(win, wstr, n)	waddnwstr(win, wstr, -1)
#define add_wch(c)		wadd_wch(stsdscr, c)
#define mvadd_wch(y,x,c)	(wmove(stdscr,y,x) == ERR ? ERR : wadd_wch(stsdscr, c))
#define mvwadd_wch(y,x,win,c)	(wmove(win,y,x) == ERR ? ERR : wadd_wch(stsdscr, c))
#define wattr_get(win, a)	((win)->_attrs)
#define wattr_off(win, a)	attroff(win, a)
#define wattr_on(win, a)	attron(win, a)
#define wattr_set(win, a)	attrset(win, a)
#define attr_get()		wattr_get(stdscr)
#define attr_off(a)		wattr_off(stdscr, a)
#define attr_on(a)		wattr_on(stdscr, a)
#define attr_set(a)		wattr_set(stdscr, a)
#define wgetbkgd(win)		((win)->_bkgd)
#define box_set(w,v,h)		wborder_set(w,v,v,h,h,0,0,0,9)
#define chgat(n, a, c, o)	wchgat(stdscr, n, a, c, o)
#define mvchgat(y,x, n,a,c, o)	(move(y,x)==ERR ? ERR : wchgat(stdscr,n,a,c,o))
#define mvwchgat(y,x,w,n,a,c,o)	(wmove(w,y,x) == ERR ? ERR : wchgat(w,n,a,c,o))
#define echo_wchar(c)		wecho_wchar(stdscr, c)
#define getn_wstr(t, n)		wgetn_wstr(stdscr, t, n)
#define get_wstr(t)		wgetn_wstr(stdscr, t, -1)
#define mvgetn_wstr(y, x, t, n)	(move(y,x)==ERR ? ERR:wgetn_wstr(stdscr,t,n))
#define mvget_wstr(y, x, t)	(move(y,x)==ERR ? ERR:wgetn_wstr(stdscr,t,-1))
#define mvwgetn_wstr(w,y,x,t,n)	(wmove(w,y,x)==ERR ? ERR : wgetn_wstr(w,t,n))
#define mvwget_wstr(w, y, x, t)	(wmove(w,y,x)==ERR ? ERR : wgetn_wstr(w,t,-1))
#define wget_wstr(w, t)		wgetn_wstr(w, t, -1)
#define get_wch(c)		wget_wch(stdscr, c)
#define mvget_wch(y, x, c)	(move(y,x) == ERR ? ERR : wget_wch(stdscr, c))
#define mvwget_wch(y, x, c)	(wmove(w,y,x) == ERR ? ERR : wget_wch(w, n))
#define hline_set(c, n)		whline_set(stdscr, c, n)
#define mvhline_set(y,x,c,n)	(move(y,x)==ERR ? ERR : whline_set(stdscr,c,n))
#define mvvline_set(y,x,c,n)	(move(y,x)==ERR ? ERR : wvline_set(stdscr,c,n))
#define mvwhline_set(w,y,x,c,n)	(wmove(w,y,x)==ERR ? ERR : whline_set(w,c,n))
#define mvwvline_set(w,y,x,c,n)	(wmove(w,y,x)==ERR ? ERR : wvline_set(w,c,n))
#define vline_set(c, n)		vhline_set(stdscr, c, n)
#define innwstr(c, n)		winnwstr(stdscr, c, n)
#define inwstr(c)		winnwstr(stdscr, c, -1)
#define mvinnwstr(y, x, c, n)	(move(y,x)==ERR ? ERR : winnwstr(stdscr, c, n))
#define mvinwstr(y, x, c)	(move(y,x)==ERR ? ERR : winnwstr(stdscr, c,-1))
#define mvwinnwstr(w,y,x,c,n)	(wmove(w,y,x)==ERR ? ERR:winnwstr(stdscr,c,n))
#define mvwinwstr(w,y,x,c)	(wmove(w,y,x)==ERR ? ERR:winnwstr(stdscr,c,-1))
#define winwstr(w, c)		winnwstr(w, c, -1)
#define ins_nwstr(t, n)		wins_nwstr(stdscr, t, n)
#define ins_wstr(t)		wins_nwstr(stdscr, t, -1)
#define mvins_nwstr(y,x,t,n)	(move(y,x)==ERR ? ERR: wins_nwstr(stdscr,t,n))
#define mvins_wstr(y,x,t)	(move(y,x)==ERR ? ERR: wins_nwstr(stdscr,t,-1))
#define mvwins_nwstr(w,y,x,t,n)	(wmove(w,y,x)==ERR?ERR:wins_nwstr(stdscr,t,n))
#define mvwins_wstr(w,y,x,t)	(wmove(w,y,x)==ERR?ERR:wins_nwstr(stdscr,t,-1))
#define wins_wstr(w, t)		wins_nwstr(w, t, -1)
#define ins_wch(c)		wins_wch(stdscr, c)
#define mvins_wch(y,x,c)	(move(y,x) == ERR ? ERR : wins_wch(c))
#define mwvins_wch(w,y,x,c)	(wmove(w,y,x) == ERR ? ERR : wins_wch(c))
#define in_wch(c)		win_wch(stdscr, c)
#define mvin_wch(y,x,c)		(move(y,x) == ERR ? ERR : win_wch(stdscr, c))
#define mvwin_wch(w,y,x,c)	(wmove(w, y,x) == ERR ? ERR : win_wch(w, c))
#define in_wchnstr(c, n)	win_wchnstr(stdscr, c, n)
#define in_wchstr(c)		win_wchnstr(stdscr, c, -1)
#define mvin_wchnstr(y,x,c,n)	(move(y,x)==ERR ? ERR:win_wchnstr(stdscr,c,n))
#define mvin_wchstr(y, x, c)	(move(y,x)==ERR ? ERR:win_wchnstr(stdscr,c,-1))
#define mvwin_wchnstr(w,y,x,c,n)	(wmove(w,y,x)==ERR ? ERR:win_wchnstr(stdscr,c,n))
#define mvwin_wchstr(w,y,x,c)	(wmove(w,y,x)==ERR ? ERR:win_wchnstr(stdscr,c,-1))
#define win_wchstr(w, c)	win_wchnstr(w, c, -1)


/*
 * XSI curses deprecates SVr4 vwprintw/vwscanw, which are supposed to use
 * varargs.h.  It adds new calls vw_printw/vw_scanw, which are supposed to
 * use POSIX stdarg.h.  The ncurses versions of vwprintw/vwscanw already
 * use stdarg.h, so...
 */
#define vw_printw		vwprintw
#define vw_scanw		vwscanw

/*
 * Pseudo-character tokens outside ASCII range.  The curses wgetch() function
 * will return any given one of these only if the corresponding k- capability
 * is defined in your terminal's terminfo entry.
 */
#define KEY_CODE_YES	0400		/* A wchar_t contains a key code */
#define KEY_MIN		0401		/* Minimum curses key */
#define KEY_BREAK       0401            /* Break key (unreliable) */
#define KEY_DOWN        0402            /* Down-arrow */
#define KEY_UP          0403		/* Up-arrow */
#define KEY_LEFT        0404		/* Left-arrow */
#define KEY_RIGHT       0405            /* Right-arrow */
#define KEY_HOME        0406            /* Home key (upward+left arrow) */
#define KEY_BACKSPACE   0407            /* Backspace (unreliable) */
#define KEY_F0          0410            /* Function keys.  Space for 64 */
#define KEY_F(n)        (KEY_F0+(n))    /* Value of function key n */
#define KEY_DL          0510            /* Delete line */
#define KEY_IL          0511            /* Insert line */
#define KEY_DC          0512            /* Delete character */
#define KEY_IC          0513            /* Insert char or enter insert mode */
#define KEY_EIC         0514            /* Exit insert char mode */
#define KEY_CLEAR       0515            /* Clear screen */
#define KEY_EOS         0516            /* Clear to end of screen */
#define KEY_EOL         0517            /* Clear to end of line */
#define KEY_SF          0520            /* Scroll 1 line forward */
#define KEY_SR          0521            /* Scroll 1 line backward (reverse) */
#define KEY_NPAGE       0522            /* Next page */
#define KEY_PPAGE       0523            /* Previous page */
#define KEY_STAB        0524            /* Set tab */
#define KEY_CTAB        0525            /* Clear tab */
#define KEY_CATAB       0526            /* Clear all tabs */
#define KEY_ENTER       0527            /* Enter or send (unreliable) */
#define KEY_SRESET      0530            /* Soft (partial) reset (unreliable) */
#define KEY_RESET       0531            /* Reset or hard reset (unreliable) */
#define KEY_PRINT       0532            /* Print */
#define KEY_LL          0533            /* Home down or bottom (lower left) */

/* The keypad is arranged like this: */
/* a1    up    a3   */
/* left   b2  right  */
/* c1   down   c3   */

#define KEY_A1		0534		/* Upper left of keypad */
#define KEY_A3		0535		/* Upper right of keypad */
#define KEY_B2		0536		/* Center of keypad */
#define KEY_C1		0537		/* Lower left of keypad */
#define KEY_C3		0540		/* Lower right of keypad */
#define KEY_BTAB	0541		/* Back tab */
#define KEY_BEG		0542		/* Beg (beginning) */
#define KEY_CANCEL	0543		/* Cancel */
#define KEY_CLOSE	0544		/* Close */
#define KEY_COMMAND	0545		/* Cmd (command) */
#define KEY_COPY	0546		/* Copy */
#define KEY_CREATE	0547		/* Create */
#define KEY_END		0550		/* End */
#define KEY_EXIT	0551		/* Exit */
#define KEY_FIND	0552		/* Find */
#define KEY_HELP	0553		/* Help */
#define KEY_MARK	0554		/* Mark */
#define KEY_MESSAGE	0555		/* Message */
#define KEY_MOVE	0556		/* Move */
#define KEY_NEXT	0557		/* Next */
#define KEY_OPEN	0560		/* Open */
#define KEY_OPTIONS	0561		/* Options */
#define KEY_PREVIOUS	0562		/* Prev (previous) */
#define KEY_REDO	0563		/* Redo */
#define KEY_REFERENCE	0564		/* Ref (reference) */
#define KEY_REFRESH	0565		/* Refresh */
#define KEY_REPLACE	0566		/* Replace */
#define KEY_RESTART	0567		/* Restart */
#define KEY_RESUME	0570		/* Resume */
#define KEY_SAVE	0571		/* Save */
#define KEY_SBEG	0572		/* Shifted Beg (beginning) */
#define KEY_SCANCEL	0573		/* Shifted Cancel */
#define KEY_SCOMMAND	0574		/* Shifted Command */
#define KEY_SCOPY	0575		/* Shifted Copy */
#define KEY_SCREATE	0576		/* Shifted Create */
#define KEY_SDC		0577		/* Shifted Delete char */
#define KEY_SDL		0600		/* Shifted Delete line */
#define KEY_SELECT	0601		/* Select */
#define KEY_SEND	0602		/* Shifted End */
#define KEY_SEOL	0603		/* Shifted Clear line */
#define KEY_SEXIT	0604		/* Shifted Dxit */
#define KEY_SFIND	0605		/* Shifted Find */
#define KEY_SHELP	0606		/* Shifted Help */
#define KEY_SHOME	0607		/* Shifted Home */
#define KEY_SIC		0610		/* Shifted Input */
#define KEY_SLEFT	0611		/* Shifted Left arrow */
#define KEY_SMESSAGE	0612		/* Shifted Message */
#define KEY_SMOVE	0613		/* Shifted Move */
#define KEY_SNEXT	0614		/* Shifted Next */
#define KEY_SOPTIONS	0615		/* Shifted Options */
#define KEY_SPREVIOUS	0616		/* Shifted Prev */
#define KEY_SPRINT	0617		/* Shifted Print */
#define KEY_SREDO	0620		/* Shifted Redo */
#define KEY_SREPLACE	0621		/* Shifted Replace */
#define KEY_SRIGHT	0622		/* Shifted Right arrow */
#define KEY_SRSUME	0623		/* Shifted Resume */
#define KEY_SSAVE	0624		/* Shifted Save */
#define KEY_SSUSPEND	0625		/* Shifted Suspend */
#define KEY_SUNDO	0626		/* Shifted Undo */
#define KEY_SUSPEND	0627		/* Suspend */
#define KEY_UNDO	0630		/* Undo */
#define	KEY_MOUSE	0631		/* Mouse event has occurred */
#define KEY_MAX		0777		/* Maximum key value */

/* mouse interface */

/* event masks */
#define	BUTTON1_RELEASED	000000000001L
#define	BUTTON1_PRESSED		000000000002L
#define	BUTTON1_CLICKED		000000000004L
#define	BUTTON1_DOUBLE_CLICKED	000000000010L
#define	BUTTON1_TRIPLE_CLICKED	000000000020L
#define BUTTON1_RESERVED_EVENT	000000000040L
#define	BUTTON2_RELEASED	000000000100L
#define	BUTTON2_PRESSED		000000000200L
#define	BUTTON2_CLICKED		000000000400L
#define	BUTTON2_DOUBLE_CLICKED	000000001000L
#define	BUTTON2_TRIPLE_CLICKED	000000002000L
#define BUTTON2_RESERVED_EVENT	000000004000L
#define	BUTTON3_RELEASED	000000010000L
#define	BUTTON3_PRESSED		000000020000L
#define	BUTTON3_CLICKED		000000040000L
#define	BUTTON3_DOUBLE_CLICKED	000000100000L
#define	BUTTON3_TRIPLE_CLICKED	000000200000L
#define BUTTON3_RESERVED_EVENT	000000400000L
#define	BUTTON4_RELEASED	000001000000L
#define	BUTTON4_PRESSED		000002000000L
#define	BUTTON4_CLICKED		000004000000L
#define	BUTTON4_DOUBLE_CLICKED	000010000000L
#define	BUTTON4_TRIPLE_CLICKED	000020000000L
#define BUTTON4_RESERVED_EVENT	000040000000L
#define BUTTON_CTRL		000100000000L
#define BUTTON_SHIFT		000200000000L
#define BUTTON_ALT		000400000000L
#define	ALL_MOUSE_EVENTS	000777777777L
#define	REPORT_MOUSE_POSITION	001000000000L

/* macros to extract single event-bits from masks */
#define	BUTTON_RELEASED(e, x)		((e) & (001 << (6 * ((x) - 1))))
#define	BUTTON_PRESSED(e, x)		((e) & (002 << (6 * ((x) - 1))))
#define	BUTTON_CLICKED(e, x)		((e) & (004 << (6 * ((x) - 1))))
#define	BUTTON_DOUBLE_CLICKED(e, x)	((e) & (010 << (6 * ((x) - 1))))
#define	BUTTON_TRIPLE_CLICKED(e, x)	((e) & (020 << (6 * ((x) - 1))))
#define	BUTTON_RESERVED_EVENT(e, x)	((e) & (040 << (6 * ((x) - 1))))

typedef unsigned long mmask_t;

typedef struct
{
    short id;		/* ID to distinguish multiple devices */
    int x, y, z;	/* event coordinates (character-cell) */
    mmask_t bstate;	/* button state bits */
}
MEVENT;

int getmouse(MEVENT *event);
int ungetmouse(MEVENT *event);
mmask_t mousemask(mmask_t newmask, mmask_t *oldmask);
bool wenclose(WINDOW *win, int y, int x);
int mouseinterval(int);

#endif /* __NCURSES_H */
