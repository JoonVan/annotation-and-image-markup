/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef DJDECODE_H
#define DJDECODE_H

#include "dcmtk/config/osconfig.h"
#include "dcmtk/ofstd/oftypes.h"  /* for OFBool */
#include "dcmtk/dcmjpeg/djutils.h"

class DJCodecParameter;
class DJDecoderBaseline;
class DJDecoderExtended;
class DJDecoderLossless;
class DJDecoderP14SV1;
class DJDecoderProgressive;
class DJDecoderSpectralSelection;

/** singleton class that registers decoders for all supported JPEG processes.
 */
class DCMTK_DCMJPEG_EXPORT DJDecoderRegistration
{
public:
  /** registers decoders for all supported JPEG processes.
   *  If already registered, call is ignored unless cleanup() has
   *  been performed before.
   *  @param pCreateSOPInstanceUID flag indicating whether or not
   *    a new SOP Instance UID should be assigned upon decompression.
   *  @param pPlanarConfiguration flag indicating how planar configuration
   *    of color images should be encoded upon decompression.
   *  @param predictor6WorkaroundEnable enable workaround for buggy lossless compressed images with
   *           overflow in predictor 6 for images with 16 bits/pixel
   */
  static void registerCodecs(
    E_DecompressionColorSpaceConversion pDecompressionCSConversion = EDC_photometricInterpretation,
    E_UIDCreation pCreateSOPInstanceUID = EUC_default,
    E_PlanarConfiguration pPlanarConfiguration = EPC_default,
    OFBool predictor6WorkaroundEnable = OFFalse);

  /** deregisters decoders.
   *  Attention: Must not be called while other threads might still use
   *  the registered codecs, e.g. because they are currently decoding
   *  DICOM data sets through dcmdata.
   */
  static void cleanup();

private:

  /// flag indicating whether the decoders are already registered.
  static OFBool registered;

  /// pointer to codec parameter shared by all decoders
  static DJCodecParameter *cp;

  /// pointer to decoder for baseline JPEG
  static DJDecoderBaseline *decbas;

  /// pointer to decoder for extended JPEG
  static DJDecoderExtended *decext;

  /// pointer to decoder for spectral selection JPEG
  static DJDecoderSpectralSelection *decsps;

  /// pointer to decoder for progressive JPEG
  static DJDecoderProgressive *decpro;

  /// pointer to decoder for lossless SV1 JPEG
  static DJDecoderP14SV1 *decsv1;

  /// pointer to decoder for lossless JPEG
  static DJDecoderLossless *declol;

};

#endif
