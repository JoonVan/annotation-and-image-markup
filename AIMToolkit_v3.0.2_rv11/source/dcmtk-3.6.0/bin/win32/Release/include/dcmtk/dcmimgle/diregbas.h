/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef DIREGBAS_H
#define DIREGBAS_H

#include "dcmtk/config/osconfig.h"

#include "dcmtk/dcmimgle/diutils.h"


/*------------------------*
 *  forward declarations  *
 *------------------------*/

class DiImage;
class DiColorImage;
class DiMonoPixel;
class DiDocument;
class DiRegisterBase;


/*---------------------*
 *  class declaration  *
 *---------------------*/

/** Abstract base class to register additional libraries
 */
class DiRegisterBase
{

 public:

    /** constructor, default
     */
    DiRegisterBase()
    {
    }

    /** destructor
     */
    virtual ~DiRegisterBase()
    {
    }

    /** create color image representation (abstract)
     *
     ** @param  docu    pointer to dataset (encapsulated)
     *  @param  status  image status
     *  @param  photo   photometric interpretation
     *
     ** @return pointer to new DiImage object (NULL if an error occurred)
     */
    virtual DiImage *createImage(const DiDocument *docu,
                                 const EI_Status status,
                                 const EP_Interpretation photo) = 0;

    /** create monochrome pixel data of color image (abstract)
     *
     ** @param  image  pointer to color image
     *  @param  red    coefficient by which the red component is weighted
     *  @param  green  coefficient by which the green component is weighted
     *  @param  blue   coefficient by which the blue component is weighted
     *
     ** @return pointer to new DiImage object (NULL if an error occurred)
     */
    virtual DiMonoPixel *createMonoImageData(const DiColorImage *image,
                                             const double red,
                                             const double green,
                                             const double blue) = 0;

    /// global pointer to registered 'dcmimage' library
    static DiRegisterBase *Pointer;
};


#endif


/*
 *
 * CVS/RCS Log:
 * $Log: diregbas.h,v $
 * Revision 1.8  2010-10-14 13:16:27  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.7  2005-12-08 16:48:07  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.6  2003/12/08 19:28:05  joergr
 * Removed leading underscore characters from preprocessor symbols (reserved
 * symbols). Updated CVS header. Updated copyright header.
 *
 * Revision 1.5  2001/06/01 15:49:50  meichel
 * Updated copyright header
 *
 * Revision 1.4  2000/03/08 16:24:23  meichel
 * Updated copyright header.
 *
 * Revision 1.3  1999/09/17 12:48:28  joergr
 * Added/changed/completed DOC++ style comments in the header files.
 *
 * Revision 1.2  1999/03/24 17:20:24  joergr
 * Added/Modified comments and formatting.
 *
 * Revision 1.1  1998/11/27 13:08:07  joergr
 * Added registration class to allow easy combination of both modules.
 * Added copyright message to all source files.
 *
 *
 */