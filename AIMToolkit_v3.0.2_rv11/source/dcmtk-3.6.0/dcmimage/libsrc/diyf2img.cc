/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"

#include "dcmtk/dcmdata/dctypes.h"

#include "dcmtk/dcmimage/diyf2img.h"
#include "dcmtk/dcmimage/diyf2pxt.h"
#include "dcmtk/dcmimage/dilogger.h"
#include "dcmtk/dcmimgle/diinpx.h"
#include "dcmtk/dcmimgle/didocu.h"


/*----------------*
 *  constructors  *
 *----------------*/

DiYBR422Image::DiYBR422Image(const DiDocument *docu,
                             const EI_Status status)
  : DiColorImage(docu, status, 2, !(docu->getFlags() & CIF_KeepYCbCrColorModel) /* RGBColorModel */)
{
    if ((Document != NULL) && (InputData != NULL) && (ImageStatus == EIS_Normal))
    {
        Init();                                                 // create intermediate representation
    }
}


/*--------------*
 *  destructor  *
 *--------------*/

DiYBR422Image::~DiYBR422Image()
{
}


/*********************************************************************/


void DiYBR422Image::Init()
{
    switch (InputData->getRepresentation())
    {
        case EPR_Uint8:
            InterData = new DiYBR422PixelTemplate<Uint8, Uint8>(Document, InputData, ImageStatus, BitsPerSample, RGBColorModel);
            break;
        case EPR_Sint8:
            InterData = new DiYBR422PixelTemplate<Sint8, Uint8>(Document, InputData, ImageStatus, BitsPerSample, RGBColorModel);
            break;
        case EPR_Uint16:
            InterData = new DiYBR422PixelTemplate<Uint16, Uint16>(Document, InputData, ImageStatus, BitsPerSample, RGBColorModel);
            break;
        case EPR_Sint16:
            InterData = new DiYBR422PixelTemplate<Sint16, Uint16>(Document, InputData, ImageStatus, BitsPerSample, RGBColorModel);
            break;
        case EPR_Uint32:
            InterData = new DiYBR422PixelTemplate<Uint32, Uint32>(Document, InputData, ImageStatus, BitsPerSample, RGBColorModel);
            break;
        case EPR_Sint32:
            InterData = new DiYBR422PixelTemplate<Sint32, Uint32>(Document, InputData, ImageStatus, BitsPerSample, RGBColorModel);
            break;
    }
    deleteInputData();
    checkInterData();
}


/*********************************************************************/


int DiYBR422Image::processNextFrames(const unsigned long fcount)
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
 * $Log: diyf2img.cc,v $
 * Revision 1.11  2010-10-14 13:14:15  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.10  2009-11-25 14:48:46  joergr
 * Adapted code for new approach to access individual frames of a DICOM image.
 *
 * Revision 1.9  2005/12/08 15:42:37  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.8  2003/12/23 10:54:28  joergr
 * Updated copyright header.
 *
 * Revision 1.7  2001/09/28 13:56:35  joergr
 * Added new flag (CIF_KeepYCbCrColorModel) which avoids conversion of YCbCr
 * color models to RGB.
 *
 * Revision 1.6  2001/06/01 15:49:36  meichel
 * Updated copyright header
 *
 * Revision 1.5  2000/03/08 16:21:58  meichel
 * Updated copyright header.
 *
 * Revision 1.4  1999/04/28 13:45:30  joergr
 * Corrected some typos, comments and formatting.
 *
 * Revision 1.3  1998/11/27 14:35:30  joergr
 * Added copyright message.
 * Renamed variable 'Status' to 'ImageStatus' because of possible conflicts
 * with X windows systems.
 *
 * Revision 1.2  1998/05/11 14:52:39  joergr
 * Added CVS/RCS header to each file.
 *
 *
 */
