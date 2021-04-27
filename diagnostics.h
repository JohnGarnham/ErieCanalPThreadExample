/*
 * diagnostics.h has debugging/reporting tools.
 *
 * Version:
 *     $Id: diagnostics.h,v 1.1 2006/10/18 18:04:45 bks Exp bks $
 *
 * Revisions:
 *     $Log: diagnostics.h,v $
 *     Revision 1.1  2006/10/18 18:04:45  bks
 *     Initial revision
 *
 *
 */

#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

/*
 * The debug flag takes no storage because we don't really
 * need to be able to turn it on/off without recompiling/relinking.
 */

#define _DEBUG_ 1

/*
 * REPORT is either nothing or some arbitrary statement to include and execute.
 *
 */

#ifdef _DEBUG_

#define REPORT( statement )  { statement; }

#else

#define REPORT( statement )  

#endif // _DEBUG_

#endif // DIAGNOSTICS_H

