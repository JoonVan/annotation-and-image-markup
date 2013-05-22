/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmjpeg/djdecext.h"
#include "dcmtk/dcmjpeg/djcparam.h"
#include "dcmtk/dcmjpeg/djrploss.h"
#include "dcmtk/dcmjpeg/djdijg8.h"
#include "dcmtk/dcmjpeg/djdijg12.h"


DJDecoderExtended::DJDecoderExtended()
: DJCodecDecoder()
{
}


DJDecoderExtended::~DJDecoderExtended()
{
}


E_TransferSyntax DJDecoderExtended::supportedTransferSyntax() const
{
  return EXS_JPEGProcess2_4;
}


DJDecoder *DJDecoderExtended::createDecoderInstance(
    const DcmRepresentationParameter * /* toRepParam */,
    const DJCodecParameter *cp,
    Uint8 bitsPerSample,
    OFBool isYBR) const
{
  if (bitsPerSample > 8) return new DJDecompressIJG12Bit(*cp, isYBR);
  else return new DJDecompressIJG8Bit(*cp, isYBR);
}