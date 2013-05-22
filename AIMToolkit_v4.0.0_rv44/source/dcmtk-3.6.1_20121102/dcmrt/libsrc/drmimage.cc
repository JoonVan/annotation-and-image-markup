/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"     /* make sure OS specific configuration is included first */
#include "dcmtk/dcmrt/drmimage.h"

DRTImage::DRTImage()
: format_()
, dataset_(NULL)
, image_(NULL)
{
}

DRTImage::~DRTImage()
{
    reset();
}

void DRTImage::reset()
{
    delete image_;
    delete dataset_;
    format_.clear();
    image_ = NULL;
    dataset_ = NULL;
}

void DRTImage::clear()
{
    reset();
    DRTImageIOD::clear();
}

OFCondition DRTImage::loadFile(const OFFilename &filename,
                               const E_FileReadMode readMode,
                               const E_TransferSyntax readXfer)
{
    /* get rid of the old image before we mess with its dataset */
    reset();

    OFCondition cond = format_.loadFile(filename, readXfer, EGL_noChange,
                                        DCM_MaxReadLength, readMode);
    if (cond.good())
    {
        cond = DRTImageIOD::read(*format_.getDataset());
        if (cond.good())
        {
            image_ = new DicomImage(&format_,
                    format_.getDataset()->getOriginalXfer(),
                    CIF_MayDetachPixelData);
        }
    }
    if (cond.bad())
        clear();
    return cond;
}

OFCondition DRTImage::read(DcmItem *dataset)
{
    /* get rid of the old image before we mess with its dataset */
    reset();

    dataset_ = dataset;
    OFCondition cond = DRTImageIOD::read(*format_.getDataset());
    if (cond.good())
    {
        image_ = new DicomImage(&format_,
                EXS_Unknown, CIF_MayDetachPixelData);
    }
    else
        clear();
    return cond;
}

OFCondition DRTImage::getOutputData(OFVector<Uint8>& result, const unsigned long frame)
{
    result.clear();

    if (image_ == NULL)
        return RT_EC_UnsupportedValue;

    // For now we can only do 8 bit gray
    const int bits = 8;
    const unsigned long size = image_->getOutputDataSize(bits);
    result.resize(size);

    return statusToCondition(image_->getOutputData(&result[0], result.size(), bits, frame));
}
