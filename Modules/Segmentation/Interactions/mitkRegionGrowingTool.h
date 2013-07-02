/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#ifndef mitkRegionGrowingTool_h_Included
#define mitkRegionGrowingTool_h_Included

#include "mitkFeedbackContourTool.h"
#include "mitkLegacyAdaptors.h"
#include "SegmentationExports.h"

struct mitkIpPicDescriptor;

class ModuleResource;

namespace mitk
{

/**
  \brief A slice based region growing tool.

  \sa FeedbackContourTool

  \ingroup Interaction
  \ingroup ToolManagerEtAl

  When the user presses the mouse button, RegionGrowingTool will use the gray values at that position
  to initialize a region growing algorithm (in the affected 2D slice).

  By moving the mouse up and down while the button is still pressed, the user can change the parameters
  of the region growing algorithm (selecting more or less of an object).
  The current result of region growing will always be shown as a contour to the user.

  After releasing the button, the current result of the region growing algorithm will be written to the
  working image of this tool's ToolManager.

  If the first click is <i>inside</i> a segmentation that was generated by region growing (recently),
  the tool will try to cut off a part of the segmentation. For this reason a skeletonization of the segmentation
  is generated and the optimal cut point is determined.

  \warning Only to be instantiated by mitk::ToolManager.

  $Author$
*/
class Segmentation_EXPORT RegionGrowingTool : public FeedbackContourTool
{
  public:

    mitkClassMacro(RegionGrowingTool, FeedbackContourTool);
    itkNewMacro(RegionGrowingTool);

    virtual const char** GetXPM() const;
    ModuleResource GetIconResource() const;
    virtual const char* GetName() const;

  protected:

    RegionGrowingTool(); // purposely hidden
    virtual ~RegionGrowingTool();

    virtual void Activated();
    virtual void Deactivated();

    virtual bool OnMousePressed (Action*, const StateEvent*);
    virtual bool OnMousePressedInside (Action*, const StateEvent*, mitkIpPicDescriptor* workingPicSlice, int initialWorkingOffset);
    virtual bool OnMousePressedOutside (Action*, const StateEvent*);
    virtual bool OnMouseMoved   (Action*, const StateEvent*);
    virtual bool OnMouseReleased(Action*, const StateEvent*);

    mitkIpPicDescriptor* PerformRegionGrowingAndUpdateContour();

    Image::Pointer m_ReferenceSlice;
    Image::Pointer m_WorkingSlice;

    ScalarType m_LowerThreshold;
    ScalarType m_UpperThreshold;
    ScalarType m_InitialLowerThreshold;
    ScalarType m_InitialUpperThreshold;

    Point2I m_LastScreenPosition;
    int m_ScreenYDifference;

  private:

    mitkIpPicDescriptor* SmoothIPPicBinaryImage( mitkIpPicDescriptor* image, int &contourOfs, mitkIpPicDescriptor* dest = NULL );
    void SmoothIPPicBinaryImageHelperForRows( mitkIpPicDescriptor* source, mitkIpPicDescriptor* dest, int &contourOfs, int* maskOffsets, int maskSize, int startOffset, int endOffset );

    mitkIpPicDescriptor* m_OriginalPicSlice;
    int m_SeedPointMemoryOffset;

    ScalarType m_VisibleWindow;
    ScalarType m_DefaultWindow;
    ScalarType m_MouseDistanceScaleFactor;

    int m_PaintingPixelValue;
    int m_LastWorkingSeed;

    bool m_FillFeedbackContour;
};

} // namespace

#endif


