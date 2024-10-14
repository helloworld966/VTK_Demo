#include "QuadricVisualization.h"

void QuadricVisualization::CreateIsosurface(vtkSampleFunction * function, vtkActor * actor, unsigned int numberOfContours)
{
	double range[2];
	// Generate the implicit surface.
	vtkNew<vtkContourFilter> contour;
	contour->SetInputConnection(function->GetOutputPort());
	range[0] = 1.0;
	range[1] = 6.0;
	contour->GenerateValues(numberOfContours, range);

	// Map contour
	vtkNew<vtkPolyDataMapper> isosurfaceMapper;
	isosurfaceMapper->SetInputConnection(contour->GetOutputPort());
	isosurfaceMapper->SetScalarRange(0, 7);

	actor->SetMapper(isosurfaceMapper);
	return;
}

void QuadricVisualization::CreatePlanes(vtkSampleFunction * function, vtkActor * actor, unsigned int numberOfPlanes)
{
	vtkNew<vtkAppendFilter> append;
	int dims[3];
	function->GetSampleDimensions(dims);
	int sliceIncr = (dims[2] - 1) / (numberOfPlanes + 1);
	int slice = -4;
	for (unsigned int i = 0; i < numberOfPlanes; ++i)
	{
		vtkNew<vtkExtractVOI> extract;
		extract->SetInputConnection(function->GetOutputPort());
		extract->SetVOI(0, dims[0] - 1, 0, dims[1] - 1, slice + sliceIncr,
			slice + sliceIncr);
		append->AddInputConnection(extract->GetOutputPort());
		slice += sliceIncr;
	}
	append->Update();

	// Map planes.
	vtkNew<vtkDataSetMapper> planesMapper;
	planesMapper->SetInputConnection(append->GetOutputPort());
	planesMapper->SetScalarRange(0, 7);

	actor->SetMapper(planesMapper);
	actor->GetProperty()->SetAmbient(1.);
	return;
}

void QuadricVisualization::CreateContours(vtkSampleFunction * function, vtkActor * actor, unsigned int numberOfPlanes, unsigned int numberOfContours)
{
	vtkNew<vtkAppendFilter> append;

	int dims[3];
	function->GetSampleDimensions(dims);
	int sliceIncr = (dims[2] - 1) / (numberOfPlanes + 1);

	int slice = -4;
	for (unsigned int i = 0; i < numberOfPlanes; ++i)
	{
		vtkNew<vtkExtractVOI> extract;
		extract->SetInputConnection(function->GetOutputPort());
		extract->SetVOI(0, dims[0] - 1, 0, dims[1] - 1, slice + sliceIncr,
			slice + sliceIncr);
		double range[2];
		range[0] = 1.0;
		range[1] = 6.0;
		vtkNew<vtkContourFilter> contour;
		contour->SetInputConnection(extract->GetOutputPort());
		contour->GenerateValues(numberOfContours, range);
		append->AddInputConnection(contour->GetOutputPort());
		slice += sliceIncr;
	}
	append->Update();

	// Map contours.
	vtkNew<vtkDataSetMapper> contoursMapper;
	contoursMapper->SetInputConnection(append->GetOutputPort());
	contoursMapper->SetScalarRange(0, 7);

	actor->SetMapper(contoursMapper);
	actor->GetProperty()->SetAmbient(1.);
	return;
}

void QuadricVisualization::CreateOutline(vtkSampleFunction * source, vtkActor * actor)
{
	vtkNew<vtkOutlineFilter> outline;
	outline->SetInputConnection(source->GetOutputPort());

	vtkNew<vtkPolyDataMapper> outlineMapper;
	outlineMapper->SetInputConnection(outline->GetOutputPort());
	actor->SetMapper(outlineMapper);
	return;
}
