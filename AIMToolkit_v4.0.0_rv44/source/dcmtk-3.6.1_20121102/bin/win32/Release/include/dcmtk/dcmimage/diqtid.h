/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef DIQTID_H
#define DIQTID_H


#include "dcmtk/config/osconfig.h"


class DcmQuantPixel;


/** pseudo error diffusion class implementing an identity transformation.
 *  This class implements a public API mostly identical to that
 *  of class DcmQuantFloydSteinberg.
 *  Since several methods of the error diffusion class are called for each
 *  single image pixel during conversion of a color image to palette color,
 *  we do not use virtual methods and a common abstract base class here.
 *  Instead we implement all methods inline, and use a template to select
 *  the appropriate class at compile time.  With a decent optimizer this
 *  reduces the overhead for using this class to zero.
 */
class DCMTK_DCMIMAGE_EXPORT DcmQuantIdent
{
public:

  /// constructor
  DcmQuantIdent(unsigned long cols)
  : columns(cols)
  {
  }

  /// destructor
  ~DcmQuantIdent()
  {
  }

  /// dummy method needed for API compatibility with DcmQuantFloydSteinberg
  inline void adjust(DcmQuantPixel&, long, long)
  {
  }

  /// dummy method needed for API compatibility with DcmQuantFloydSteinberg
  inline void propagate(const DcmQuantPixel&, const DcmQuantPixel&, long)
  {
  }

  /** starts a new row. The initial and last column of the current row are determined.
   *  @param col initial column for the current row returned in this parameter
   *  @param limitcol limit column (one past the last valid column) for the
   *    current row returned in this parameter.
   */
  inline void startRow(long& col, long& limitcol)
  {
     col = 0;
     limitcol = columns;
  }

  /// dummy method needed for API compatibility with DcmQuantFloydSteinberg
  inline void finishRow()
  {
  }

  /** increases the column number
   *  @param col column number
   */
  inline void nextCol(long& col) const
  {
    ++col;
  }

private:

  /// number of columns in image
  unsigned long columns;

};


#endif
