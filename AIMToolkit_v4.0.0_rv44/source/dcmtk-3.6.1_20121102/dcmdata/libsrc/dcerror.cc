/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/dcmdata/dcerror.h"

makeOFConditionConst(EC_InvalidTag,                  OFM_dcmdata,  1, OF_error, "Invalid tag"                                );
makeOFConditionConst(EC_TagNotFound,                 OFM_dcmdata,  2, OF_error, "Tag not found"                              );
makeOFConditionConst(EC_InvalidVR,                   OFM_dcmdata,  3, OF_error, "Invalid VR"                                 );
makeOFConditionConst(EC_InvalidStream,               OFM_dcmdata,  4, OF_error, "Invalid stream"                             );
makeOFConditionConst(EC_EndOfStream,                 OFM_dcmdata,  5, OF_error, "End of stream"                              );
makeOFConditionConst(EC_CorruptedData,               OFM_dcmdata,  6, OF_error, "Corrupted data"                             );
makeOFConditionConst(EC_IllegalCall,                 OFM_dcmdata,  7, OF_error, "Illegal call, perhaps wrong parameters"     );
makeOFConditionConst(EC_SequEnd,                     OFM_dcmdata,  8, OF_error, "Sequence end"                               );
makeOFConditionConst(EC_DoubledTag,                  OFM_dcmdata,  9, OF_error, "Doubled tag"                                );
makeOFConditionConst(EC_StreamNotifyClient,          OFM_dcmdata, 10, OF_error, "I/O suspension or premature end of stream"  );
makeOFConditionConst(EC_WrongStreamMode,             OFM_dcmdata, 11, OF_error, "Mode (R/W, random/sequence) is wrong"       );
makeOFConditionConst(EC_ItemEnd,                     OFM_dcmdata, 12, OF_error, "Item end"                                   );
makeOFConditionConst(EC_RepresentationNotFound,      OFM_dcmdata, 13, OF_error, "Pixel representation not found"             );
makeOFConditionConst(EC_CannotChangeRepresentation,  OFM_dcmdata, 14, OF_error, "Pixel representation cannot be changed"     );
makeOFConditionConst(EC_UnsupportedEncoding,         OFM_dcmdata, 15, OF_error, "Unsupported compression or encryption"      );
// error code 16 is reserved for zlib-related error messages
makeOFConditionConst(EC_PutbackFailed,               OFM_dcmdata, 17, OF_error, "Parser failure: Putback operation failed"   );
// error code 18 is reserved for file read error messages
// error code 19 is reserved for file write error messages
makeOFConditionConst(EC_DoubleCompressionFilters,    OFM_dcmdata, 20, OF_error, "Too many compression filters"               );
makeOFConditionConst(EC_ApplicationProfileViolated,  OFM_dcmdata, 21, OF_error, "Storage media application profile violated" );
// error code 22 is reserved for dcmodify error messages
makeOFConditionConst(EC_InvalidOffset,               OFM_dcmdata, 23, OF_error, "Invalid offset"                             );
makeOFConditionConst(EC_TooManyBytesRequested,       OFM_dcmdata, 24, OF_error, "Too many bytes requested"                   );
// error code 25 is reserved for tag path parsing error messages
makeOFConditionConst(EC_InvalidBasicOffsetTable,     OFM_dcmdata, 26, OF_error, "Invalid basic offset table"                 );
makeOFConditionConst(EC_ElemLengthLargerThanItem,    OFM_dcmdata, 27, OF_error, "Length of element larger than explicit length of surrounding item" );
makeOFConditionConst(EC_FileMetaInfoHeaderMissing,   OFM_dcmdata, 28, OF_error, "File meta information header missing"       );
makeOFConditionConst(EC_SeqOrItemContentOverflow,    OFM_dcmdata, 29, OF_error, "Item or sequence content exceeds maximum of 32-bit length field");
makeOFConditionConst(EC_ValueRepresentationViolated, OFM_dcmdata, 30, OF_error, "Value Representation violated"              );
makeOFConditionConst(EC_ValueMultiplicityViolated,   OFM_dcmdata, 31, OF_error, "Value Multiplicity violated"                );
makeOFConditionConst(EC_MaximumLengthViolated,       OFM_dcmdata, 32, OF_error, "Maximum VR length violated"                 );
makeOFConditionConst(EC_ElemLengthExceeds16BitField, OFM_dcmdata, 33, OF_error, "Length of element value exceeds maximum of 16-bit length field" );
makeOFConditionConst(EC_SequDelimitationItemMissing, OFM_dcmdata, 34, OF_error, "Sequence Delimitation Item missing"         );
// error codes 35..36 are reserved for specific character set error messages (see below)
// error code 37 is reserved for XML conversion error messages (see below)
makeOFConditionConst(EC_ItemDelimitationItemMissing, OFM_dcmdata, 38, OF_error, "Item Delimitation Item missing"             );

const unsigned short EC_CODE_CannotSelectCharacterSet  = 35;
const unsigned short EC_CODE_CannotConvertCharacterSet = 36;
const unsigned short EC_CODE_CannotConvertToXML        = 37;

const char *dcmErrorConditionToString(OFCondition cond)
{
  return cond.text();
}