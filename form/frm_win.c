
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
/*                                                                         *
*  Author : Juergen Pfeifer, Juergen.Pfeifer@T-Online.de                   *
*                                                                          *
***************************************************************************/

#include "form.priv.h"

MODULE_ID("$Id: frm_win.c,v 1.3 1997/04/16 22:29:04 juergen Exp $")

/*---------------------------------------------------------------------------
|   Facility      :  libnform  
|   Function      :  int set_form_win(FORM *form,WINDOW *win)
|   
|   Description   :  Set the window of the form to win. 
|
|   Return Values :  E_OK       - success
|                    E_POSTED   - form is posted
+--------------------------------------------------------------------------*/
int set_form_win(FORM * form, WINDOW * win)
{
  if (form && (form->status & _POSTED))	
    RETURN(E_POSTED);

  Normalize_Form( form )->win = win;
  RETURN(E_OK);
}	

/*---------------------------------------------------------------------------
|   Facility      :  libnform  
|   Function      :  WINDOW *form_win(const FORM *)
|   
|   Description   :  Retrieve the window of the form.
|
|   Return Values :  The pointer to the Window or stdscr if there is none.
+--------------------------------------------------------------------------*/
WINDOW *form_win(const FORM * form)
{
  const FORM* f = Normalize_Form( form );
  return (f->win ? f->win : stdscr);
}

/*---------------------------------------------------------------------------
|   Facility      :  libnform  
|   Function      :  int set_form_sub(FORM *form, WINDOW *win)
|   
|   Description   :  Set the subwindow of the form to win. 
|
|   Return Values :  E_OK       - success
|                    E_POSTED   - form is posted
+--------------------------------------------------------------------------*/
int set_form_sub(FORM * form, WINDOW * win)
{
  if (form && (form->status & _POSTED))	
    RETURN(E_POSTED);

  Normalize_Form( form )->sub = win;
  RETURN(E_OK);
}	

/*---------------------------------------------------------------------------
|   Facility      :  libnform  
|   Function      :  WINDOW *form_sub(const FORM *)
|   
|   Description   :  Retrieve the window of the form.
|
|   Return Values :  The pointer to the Subwindow.
+--------------------------------------------------------------------------*/
WINDOW *form_sub(const FORM * form)
{
  const FORM* f = Normalize_Form( form );
  return Get_Form_Window(f);
}

/* frm_win.c ends here */
