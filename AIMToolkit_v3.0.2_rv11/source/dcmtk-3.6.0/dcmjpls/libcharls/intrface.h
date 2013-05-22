/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef JLS_INTERFACE
#define JLS_INTERFACE

#include "pubtypes.h"
#include "dcmtk/ofstd/ofstd.h" /* for size_t */

#ifndef CHARLS_IMEXPORT
#define CHARLS_IMEXPORT(returntype) returntype
#endif


#ifdef __cplusplus
extern "C"
{
#endif
  CHARLS_IMEXPORT(enum JLS_ERROR) JpegLsEncode(void* compressedData, size_t compressedLength, size_t* pcbyteWritten,
	    const void* uncompressedData, size_t uncompressedLength, struct JlsParameters* pparams);

  CHARLS_IMEXPORT(enum JLS_ERROR) JpegLsDecode(void* uncompressedData, size_t uncompressedLength,
		const void* compressedData, size_t compressedLength,
		struct JlsParameters* info);


  CHARLS_IMEXPORT(enum JLS_ERROR) JpegLsDecodeRect(void* uncompressedData, size_t uncompressedLength,
		const void* compressedData, size_t compressedLength,
		struct JlsRect rect, struct JlsParameters* info);

  CHARLS_IMEXPORT(enum JLS_ERROR) JpegLsReadHeader(const void* uncompressedData, size_t uncompressedLength,
		struct JlsParameters* pparams);

  CHARLS_IMEXPORT(enum JLS_ERROR) JpegLsVerifyEncode(const void* uncompressedData, size_t uncompressedLength,
		const void* compressedData, size_t compressedLength);

#ifdef __cplusplus
}
#endif

#endif
