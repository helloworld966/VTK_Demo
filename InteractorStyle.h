#ifndef INTERACTORSTYLE_H
#define INTERACTORSTYLE_H

#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkLine.h>
#include <vtkPolygon.h>
#include <vtkPropPicker.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkPolyData.h>

class InteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
	static InteractorStyle* New();
	vtkTypeMacro(InteractorStyle, vtkInteractorStyleTrackballCamera);

	virtual void OnLeftButtonDown() override;

	void SetDefaultRenderer(vtkSmartPointer<vtkRenderer> renderer)
	{
		this->DefaultRenderer = renderer;
	}

private:
	void DrawGeometry(double* pos);

	vtkSmartPointer<vtkRenderer> DefaultRenderer;
};

#endif // INTERACTORSTYLE_H
