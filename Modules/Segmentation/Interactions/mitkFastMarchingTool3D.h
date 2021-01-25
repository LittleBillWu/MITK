/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#ifndef mitkFastMarchingTool3D_h_Included
#define mitkFastMarchingTool3D_h_Included

#include "mitkFastMarchingBaseTool.h"

#include <MitkSegmentationExports.h>

namespace mitk
{
  /**
    \brief FastMarching semgentation tool.

    The segmentation is done by setting one or more seed points on the image
    and adapting the time range and threshold. The pipeline is:
      Smoothing->GradientMagnitude->SigmoidFunction->FastMarching->Threshold
    The resulting binary image is seen as a segmentation of an object.

    For detailed documentation see ITK Software Guide section 9.3.1 Fast Marching Segmentation.
  */
  class MITKSEGMENTATION_EXPORT FastMarchingTool3D : public FastMarchingBaseTool
  {
  public:
    mitkClassMacro(FastMarchingTool3D, FastMarchingBaseTool);
    itkFactorylessNewMacro(Self);
    itkCloneMacro(Self);

    /* icon stuff */
    const char *GetName() const override;

  protected:
    FastMarchingTool3D();
    ~FastMarchingTool3D() override;
  };

} // namespace

#endif
