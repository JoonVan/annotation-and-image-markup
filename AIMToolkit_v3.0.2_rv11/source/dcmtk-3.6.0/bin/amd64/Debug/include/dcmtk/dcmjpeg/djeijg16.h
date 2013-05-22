/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef DJEIJG16_H
#define DJEIJG16_H

#include "dcmtk/config/osconfig.h"
#include "dcmtk/ofstd/oflist.h"
#include "dcmtk/dcmjpeg/djencabs.h"

extern "C"
{
  struct jpeg_compress_struct;
  typedef struct jpeg_compress_struct * j_compress_ptr;
  struct jpeg_decompress_struct;
  typedef struct jpeg_decompress_struct * j_decompress_ptr;
}

class DJCodecParameter;


/** this class encapsulates the compression routines of the
 *  IJG JPEG library configured for 16 bits/sample. 
 */
class DJCompressIJG16Bit: public DJEncoder
{
public:

  /** constructor for lossless JPEG
   *  @param cp codec parameters
   *  @param prediction predictor
   *  @param ptrans point transform
   */
  DJCompressIJG16Bit(const DJCodecParameter& cp, EJ_Mode mode, int prediction, int ptrans);

  /// destructor
  virtual ~DJCompressIJG16Bit();

  /** single frame compression routine for 16-bit raw pixel data.
   *  May only be called if bytesPerSample() == 2.
   *  @param columns columns of frame
   *  @param rows rows of frame
   *  @param interpr photometric interpretation of input frame
   *  @param samplesPerPixel samples per pixel of input frame
   *  @param image_buffer pointer to frame buffer
   *  @param to compressed frame returned in this parameter upon success
   *  @param length length of compressed frame (in bytes) returned in this parameter
   *    upon success; length guaranteed to be always even.
   *  @return EC_Normal if successful, an error code otherwise.
   */
  virtual OFCondition encode(
    Uint16 columns,
    Uint16 rows,
    EP_Interpretation interpr,
    Uint16 samplesPerPixel,
    Uint16 *image_buffer,
    Uint8 *&to,
    Uint32 &length);

  /** single frame compression routine for 8-bit raw pixel data.
   *  May only be called if bytesPerSample() == 1.
   *  @param columns columns of frame
   *  @param rows rows of frame
   *  @param interpr photometric interpretation of input frame
   *  @param samplesPerPixel samples per pixel of input frame
   *  @param image_buffer pointer to frame buffer
   *  @param to compressed frame returned in this parameter upon success
   *  @param length length of compressed frame (in bytes) returned in this parameter
   *    upon success; length guaranteed to be always even.
   *  @return EC_Normal if successful, an error code otherwise.
   */
  virtual OFCondition encode(
    Uint16 columns,
    Uint16 rows,
    EP_Interpretation interpr,
    Uint16 samplesPerPixel,
    Uint8 *image_buffer,
    Uint8 *&to,
    Uint32 &length);

  /** returns the number of bytes per sample that will be expected when encoding.
   */
  virtual Uint16 bytesPerSample() const { return 2; }

  /** returns the number of bits per sample that will be expected when encoding.
   */
  virtual Uint16 bitsPerSample() const { return 16; }

  /** callback for IJG compress destination manager.
   *  Internal use only, not to be called by client code.
   *  @param cinfo pointer to compress info
   */
  void initDestination(jpeg_compress_struct *cinfo);

  /** callback for IJG compress destination manager.
   *  Internal use only, not to be called by client code.
   *  @param cinfo pointer to compress info
   */
  int emptyOutputBuffer(jpeg_compress_struct *cinfo);

  /** callback for IJG compress destination manager.
   *  Internal use only, not to be called by client code.
   *  @param cinfo pointer to compress info
   */
  void termDestination(jpeg_compress_struct *cinfo);

  /** callback function used to report warning messages and the like.
   *  Should not be called by user code directly.
   *  @param arg opaque pointer to JPEG compress structure
   *  @param msg_level -1 for warnings, 0 and above for trace messages
   */
  virtual void emitMessage(void *arg, int msg_level) const;

private:

  /// private undefined copy constructor
  DJCompressIJG16Bit(const DJCompressIJG16Bit&);

  /// private undefined copy assignment operator
  DJCompressIJG16Bit& operator=(const DJCompressIJG16Bit&);

  /// cleans up pixelDataList, called from destructor and error handlers
  void cleanup();

  /// codec parameters
  const DJCodecParameter *cparam;
  
  /// for lossless compression, defines selection value
  int psv;

  /// for lossless compression, defines point transform
  int pt;

  /// enum for mode of operation (baseline, sequential, progressive etc.)
  EJ_Mode modeofOperation;

  /// list of compressed pixel data blocks  
  OFList<unsigned char *> pixelDataList;

  /// filled number of bytes in last block in pixelDataList
  size_t bytesInLastBlock;

};

#endif

/*
 * CVS/RCS Log
 * $Log: djeijg16.h,v $
 * Revision 1.5  2010-10-14 13:17:17  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.4  2009-11-18 16:17:54  uli
 * Use more than just the INFO log level.
 *
 * Revision 1.3  2005-12-08 16:59:26  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.2  2001/11/19 15:13:28  meichel
 * Introduced verbose mode in module dcmjpeg. If enabled, warning
 *   messages from the IJG library are printed on ofConsole, otherwise
 *   the library remains quiet.
 *
 * Revision 1.1  2001/11/13 15:56:24  meichel
 * Initial release of module dcmjpeg
 *
 *
 */
