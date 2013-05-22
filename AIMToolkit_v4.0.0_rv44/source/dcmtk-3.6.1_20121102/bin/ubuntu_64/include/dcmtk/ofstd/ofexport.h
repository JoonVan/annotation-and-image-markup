/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef OFEXPORT_H
#define OFEXPORT_H

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */


#ifdef DCMTK_SHARED
#ifdef _WIN32
/* Defines needed for building DLLs on windows */
#define DCMTK_DECL_EXPORT __declspec(dllexport)
/* Only use dllimport when DCMTK gets linked into multiple shared libraries. */
#if !(defined(DCMTK_BUILD_SINGLE_SHARED_LIBRARY) && defined(DCMTK_BUILD_IN_PROGRESS))
#define DCMTK_DECL_IMPORT __declspec(dllimport)
#else
/* We are building a single shared library and are currently inside the DCMTK.
 * Mark imported symbols as exported to avoid compiler warnings.
 */
#define DCMTK_DECL_IMPORT __declspec(dllexport)
#endif
#elif defined(HAVE_HIDDEN_VISIBILITY)
/* GCC hides everything when given -fvisibility=hidden. The symbols which
 * should be visible have to get a default visibility again.
 */
#define DCMTK_DECL_EXPORT __attribute__ ((visibility("default")))
#endif
#endif

#ifndef DCMTK_DECL_EXPORT
#define DCMTK_DECL_EXPORT
#endif

#ifndef DCMTK_DECL_IMPORT
#define DCMTK_DECL_IMPORT
#endif


#endif