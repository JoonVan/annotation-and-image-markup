/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef DIFLIPT_H
#define DIFLIPT_H

#include "dcmtk/config/osconfig.h"

#include "dcmtk/dcmimgle/dipixel.h"
#include "dcmtk/dcmimgle/ditranst.h"


/*---------------------*
 *  class declaration  *
 *---------------------*/

/** Template class to flip images (on pixel data level).
 *  horizontally and vertically
 */
template<class T>
class DiFlipTemplate
  : public DiTransTemplate<T>
{

 public:

    /** constructor.
     *  This method is used to flip an image and store the result in the same storage area.
     *
     ** @param  pixel    pointer to object where the pixel data are stored
     *  @param  columns  width of the image
     *  @param  rows     height of the image
     *  @param  frames   number of frames
     *  @param  horz     flags indicating whether to flip horizontally or not
     *  @param  vert     flags indicating whether to flip vertically or not
     */
    DiFlipTemplate(DiPixel *pixel,
                   const Uint16 columns,
                   const Uint16 rows,
                   const Uint32 frames,
                   const int horz,
                   const int vert)
      : DiTransTemplate<T>(0, columns, rows, columns, rows, frames)
    {
        if (pixel != NULL)
        {
            this->Planes = pixel->getPlanes();
            if ((pixel->getCount() > 0) && (this->Planes > 0) &&
                (pixel->getCount() == OFstatic_cast(unsigned long, columns) * OFstatic_cast(unsigned long, rows) * frames))
            {
                if (horz && vert)
                    flipHorzVert(OFstatic_cast(T **, pixel->getDataArrayPtr()));
                else if (horz)
                    flipHorz(OFstatic_cast(T **, pixel->getDataArrayPtr()));
                else if (vert)
                    flipVert(OFstatic_cast(T **, pixel->getDataArrayPtr()));
            } else {
                DCMIMGLE_WARN("could not flip image ... corrupted data");
            }
        }
    }

    /** constructor.
     *  This method is used to perform only the preparation and to start flipping later with method 'flipData()'
     *
     ** @param  planes   number of planes (1 or 3)
     *  @param  columns  width of the image
     *  @param  rows     height of the image
     *  @param  frames   number of frames
     */
    DiFlipTemplate(const int planes,
                   const Uint16 columns,
                   const Uint16 rows,
                   const Uint32 frames)
      : DiTransTemplate<T>(planes, columns, rows, columns, rows, frames)
    {
    }

    /** destructor
     */
    virtual ~DiFlipTemplate()
    {
    }

    /** choose algorithm depending on flipping mode
     *
     ** @param  src   array of pointers to source image pixels
     *  @param  dest  array of pointers to destination image pixels
     *  @param  horz  flags indicating whether to flip horizontally or not
     *  @param  vert  flags indicating whether to flip vertically or not
     */
    inline void flipData(const T *src[],
                         T *dest[],
                         const int horz,
                         const int vert)
    {
        if ((src != NULL) && (dest != NULL))
        {
            if (horz && vert)
                flipHorzVert(src, dest);
            else if (horz)
                flipHorz(src, dest);
            else if (vert)
                flipVert(src, dest);
            else
                this->copyPixel(src, dest);
        }
    }


 protected:

   /** flip source image horizontally and store result in destination image
    *
    ** @param  src   array of pointers to source image pixels
    *  @param  dest  array of pointers to destination image pixels
    */
    inline void flipHorz(const T *src[],
                         T *dest[])
    {
        if ((src != NULL) && (dest != NULL))
        {
            register Uint16 x;
            register Uint16 y;
            register const T *p;
            register T *q;
            register T *r;
            for (int j = 0; j < this->Planes; ++j)
            {
                p = src[j];
                r = dest[j];
                for (Uint32 f = this->Frames; f != 0; --f)
                {
                    for (y = this->Src_Y; y != 0; --y)
                    {
                        q = r + this->Dest_X;
                        for (x = this->Src_X; x != 0; --x)
                            *--q = *p++;
                        r += this->Dest_X;
                    }
                }
            }
        }
    }

   /** flip source image vertically and store result in destination image
    *
    ** @param  src   array of pointers to source image pixels
    *  @param  dest  array of pointers to destination image pixels
    */
    inline void flipVert(const T *src[],
                         T *dest[])
    {
        if ((src != NULL) && (dest != NULL))
        {
            register Uint16 x;
            register Uint16 y;
            register const T *p;
            register T *q;
            register T *r;
            const unsigned long count = OFstatic_cast(unsigned long, this->Dest_X) * OFstatic_cast(unsigned long, this->Dest_Y);
            for (int j = 0; j < this->Planes; ++j)
            {
                p = src[j];
                r = dest[j];
                for (Uint32 f = this->Frames; f != 0; --f)
                {
                    r += count;
                    for (y = this->Src_Y; y != 0; --y)
                    {
                        q = r - this->Dest_X;
                        for (x = this->Src_X; x != 0; --x)
                            *q++ = *p++;
                        r -= this->Dest_X;
                    }
                    r += count;
                }
            }
        }
    }

   /** flip source image horizontally and vertically and store result in destination image
    *
    ** @param  src   array of pointers to source image pixels
    *  @param  dest  array of pointers to destination image pixels
    */
    inline void flipHorzVert(const T *src[],
                             T *dest[])
    {
       if ((src != NULL) && (dest != NULL))
       {
            register unsigned long i;
            register const T *p;
            register T *q;
            const unsigned long count = OFstatic_cast(unsigned long, this->Dest_X) * OFstatic_cast(unsigned long, this->Dest_Y);
            for (int j = 0; j < this->Planes; ++j)
            {
                p = src[j];
                q = dest[j];
                for (Uint32 f = this->Frames; f != 0; --f)
                {
                    q += count;
                    for (i = count; i != 0; --i)
                        *--q = *p++;
                    q += count;
                }
            }
        }
    }

 private:

   /** flip image horizontally and store result in the same storage area
    *
    ** @param  data  array of pointers to source/destination image pixels
    */
    inline void flipHorz(T *data[])
    {
        register Uint16 x;
        register Uint16 y;
        register T *p;
        register T *q;
        register T t;
        T *r;
        for (int j = 0; j < this->Planes; ++j)
        {
            r = data[j];
            for (Uint32 f = this->Frames; f != 0; --f)
            {
                for (y = this->Src_Y; y != 0; --y)
                {
                    p = r;
                    r += this->Dest_X;
                    q = r;
                    for (x = this->Src_X / 2; x != 0; --x)
                    {
                        t = *p;
                        *p++ = *--q;
                        *q = t;
                    }
                }
            }
        }
    }

   /** flip image vertically and store result in the same storage area
    *
    ** @param  data  array of pointers to source/destination image pixels
    */
    inline void flipVert(T *data[])
    {
        register Uint16 x;
        register Uint16 y;
        register T *p;
        register T *q;
        register T *r;
        register T t;
        T *s;
        const unsigned long count = OFstatic_cast(unsigned long, this->Dest_X) * OFstatic_cast(unsigned long, this->Dest_Y);
        for (int j = 0; j < this->Planes; ++j)
        {
            s = data[j];
            for (Uint32 f = this->Frames; f != 0; --f)
            {
                p = s;
                s += count;
                r = s;
                for (y = this->Src_Y / 2; y != 0; --y)
                {
                    r -= this->Dest_X;
                    q = r;
                    for (x = this->Src_X; x != 0; --x)
                    {
                        t = *p;
                        *p++ = *q;
                        *q++ = t;
                    }
                }
            }
        }
    }

   /** flip image horizontally and vertically and store result in the same storage area
    *
    ** @param  data  array of pointers to source/destination image pixels
    */
    inline void flipHorzVert(T *data[])
    {
        register unsigned long i;
        register T *p;
        register T *q;
        register T t;
        T *s;
        const unsigned long count = OFstatic_cast(unsigned long, this->Dest_X) * OFstatic_cast(unsigned long, this->Dest_Y);
        for (int j = 0; j < this->Planes; ++j)
        {
            s = data[j];
            for (Uint32 f = this->Frames; f != 0; --f)
            {
                p = s;
                q = s + count;
                for (i = count / 2; i != 0; --i)
                {
                    t = *p;
                    *p++ = *--q;
                    *q = t;
                }
                s += count;
            }
        }
    }
};


#endif
