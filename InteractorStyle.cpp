#include "InteractorStyle.h"

vtkStandardNewMacro(InteractorStyle);

void InteractorStyle::OnLeftButtonDown()
{
	int* clickPos = this->GetInteractor()->GetEventPosition();

	// 使用拾取器来选择点击位置的对象
	vtkSmartPointer<vtkPropPicker> picker = vtkSmartPointer<vtkPropPicker>::New();
	picker->Pick(clickPos[0], clickPos[1], 0, this->DefaultRenderer);

	double* pos = picker->GetPickPosition();
	std::cout << "Pick position (world coordinates) is: " << pos[0] << " " << pos[1] << " " << pos[2] << std::endl;

	// 在选择的面上绘制点、线和面
	DrawGeometry(pos);

	// 调用父类的左键按下事件处理
	vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}

void InteractorStyle::DrawGeometry(double* pos)
{
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
	vtkSmartPointer<vtkCellArray> polygons = vtkSmartPointer<vtkCellArray>::New();

	points->InsertNextPoint(pos[0], pos[1], pos[2]);
	points->InsertNextPoint(pos[0] + 1, pos[1] + 1, pos[2]);
	points->InsertNextPoint(pos[0] + 1, pos[1], pos[2]);
	points->InsertNextPoint(pos[0], pos[1] + 1, pos[2]);

	vtkSmartPointer<vtkLine> line = vtkSmartPointer<vtkLine>::New();
	line->GetPointIds()->SetId(0, 0);
	line->GetPointIds()->SetId(1, 1);
	lines->InsertNextCell(line);

	vtkSmartPointer<vtkPolygon> polygon = vtkSmartPointer<vtkPolygon>::New();
	polygon->GetPointIds()->SetNumberOfIds(4);
	polygon->GetPointIds()->SetId(0, 0);
	polygon->GetPointIds()->SetId(1, 2);
	polygon->GetPointIds()->SetId(2, 1);
	polygon->GetPointIds()->SetId(3, 3);
	polygons->InsertNextCell(polygon);

	vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
	polyData->SetPoints(points);
	polyData->SetLines(lines);
	polyData->SetPolys(polygons);

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(polyData);

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetColor(1.0, 0.0, 0.0); // 设置颜色为红色

	this->DefaultRenderer->AddActor(actor);
	this->GetInteractor()->GetRenderWindow()->Render();
}
