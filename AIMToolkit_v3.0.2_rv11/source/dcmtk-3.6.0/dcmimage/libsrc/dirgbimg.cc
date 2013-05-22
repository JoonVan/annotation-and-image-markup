/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"

#include "dcmtk/dcmdata/dctypes.h"

#include "dcmtk/dcmimage/dirgbimg.h"
#include "dcmtk/dcmimage/dirgbpxt.h"
#include "dcmtk/dcmimage/dilogger.h"
#include "dcmtk/dcmimgle/diinpx.h"


/*----------------*
 *  constructors  *
 *----------------*/

DiRGBImage::DiRGBImage(const DiDocument *docu,
                       const EI_Status status)
  : DiColorImage(docu, status, 3)
{
    if ((Document != NULL) && (InputData != NULL) && (ImageStatus == EIS_Normal))
    {
        Init();                                                 // create intermediate representation
    }
}


/*--------------*
 *  destructor  *
 *--------------*/

DiRGBImage::~DiRGBImage()
{
}


/*********************************************************************/


void DiRGBImage::Init()
{
    /* number of pixels per plane */
    const unsigned long planeSize = OFstatic_cast(unsigned long, Columns) * OFstatic_cast(unsigned long, Rows);
    switch (InputData->getRepresentation())
    {
        case EPR_Uint8:
            InterData = new DiRGBPixelTemplate<Uint8, Uint8>(Document, InputData, ImageStatus, planeSize, BitsPerSample);
            break;
        case EPR_Sint8:
            InterData = new DiRGBPixelTemplate<Sint8, Uint8>(Document, InputData, ImageStatus, planeSize, BitsPerSample);
            break;
        case EPR_Uint16:
            InterData = new DiRGBPixelTemplate<Uint16, Uint16>(Document, InputData, ImageStatus, planeSize, BitsPerSample);
            break;
        case EPR_Sint16:
            InterData = new DiRGBPixelTemplate<Sint16, Uint16>(Document, InputData, ImageStatus, planeSize, BitsPerSample);
            break;
        case EPR_Uint32:
            InterData = new DiRGBPixelTemplate<Uint32, Uint32>(Document, InputData, ImageStatus, planeSize, BitsPerSample);
            break;
        case EPR_Sint32:
            InterData = new DiRGBPixelTemplate<Sint32, Uint32>(Document, InputData, ImageStatus, planeSize, BitsPerSample);
            break;
    }
    deleteInputData();
    checkInterData();
}


/*********************************************************************/


int DiRGBImage::processNextFrames(const unsigned long fcount)
{
    if (DiImage::processNextFrames(fcount))
    {
        delete InterData;
        InterData = NULL;
        Init();
        return (ImageStatus == EIS_Normal);
    }
    return 0;
}


/*
 *
 * CVS/RCS Log:
 * $Log: dirgbimg.cc,v $
 * Revision 1.12  2010-10-14 13:14:15  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.11  2009-11-25 14:48:46  joergr
 * Adapted code for new approach to access individual frames of a DICOM image.
 *
 * Revision 1.10  2005/12/08 15:42:35  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.9  2003/12/17 16:34:57  joergr
 * Adapted type casts to new-style typecast operators defined in ofcast.h.
 *
 * Revision 1.8  2002/06/26 16:30:43  joergr
 * Corrected decoding of multi-frame, planar images.
 *
 * Revision 1.7  2001/06/01 15:49:36  meichel
 * Updated copyright header
 *
 * Revision 1.6  2000/03/08 16:21:57  meichel
 * Updated copyright header.
 *
 * Revision 1.5  1999/04/28 13:44:18  joergr
 * Corrected some typos, comments and formatting.
 *
 * Revision 1.4  1998/11/27 14:33:24  joergr
 * Added copyright message.
 * Renamed variable 'Status' to 'ImageStatus' because of possible conflicts
 * with X windows systems.
 *
 * Revision 1.3  1998/05/11 14:52:37  joergr
 * Added CVS/RCS header to each file.
 *
 *
 */