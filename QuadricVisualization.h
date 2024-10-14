#pragma once
#include <vtkActor.h>
#include <vtkAppendFilter.h>
#include <vtkCamera.h>
#include <vtkContourFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkExtractVOI.h>
#include <vtkNamedColors.h>
#include <vtkOutlineFilter.h>
#include <vtkProperty.h>
#include <vtkQuadric.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSampleFunction.h>
#include <vtkPolyDataMapper.h>
class QuadricVisualization
{
public:
	void CreateIsosurface(vtkSampleFunction* function, vtkActor* actor, unsigned int numberOfContours = 5);

	void CreatePlanes(vtkSampleFunction* function, vtkActor* actor, unsigned int numberOfPlanes);

	void CreateContours(vtkSampleFunction* function, vtkActor* actor, unsigned int numberOfPlanes, unsigned int numberOfContours);

	void CreateOutline(vtkSampleFunction* function, vtkActor* actor);
};

