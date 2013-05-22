/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"

/* We assume ANSI C and don't support DOS, 
 * so the following settings need not be tested 
 */
#define HAVE_PROTOTYPES 
#define HAVE_UNSIGNED_CHAR 
#define HAVE_UNSIGNED_SHORT 
#undef NEED_FAR_POINTERS
#undef INCOMPLETE_TYPES_BROKEN

/* the following settings are derived from osconfig.h */

#ifndef HAVE_C_CONST
#define const
#endif

#ifdef C_CHAR_UNSIGNED
#define CHAR_IS_UNSIGNED
#endif

#ifdef HAVE_STRINGS_H
#ifndef HAVE_STRING_H
#define NEED_BSD_STRINGS
#endif
#endif

#ifdef HAVE_SYS_TYPES_H
#define NEED_SYS_TYPES_H
#endif

/* must always be defined for our implementation */
#define NEED_SHORT_EXTERNAL_NAMES

#ifdef JPEG_INTERNALS

#ifdef C_RIGHTSHIFT_UNSIGNED
#define RIGHT_SHIFT_IS_UNSIGNED
#endif

#define INLINE C_INLINE

/* These are for configuring the JPEG memory manager. */
#undef DEFAULT_MAX_MEM
#undef NO_MKTEMP

/* We don't want to use getenv which is thread unsafe on some platforms */
#define NO_GETENV

#endif /* JPEG_INTERNALS */