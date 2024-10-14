#include "VTK_OCC_Qt.h"
#include <BRepPrimAPI_MakeBox.hxx>
#include <IVtkTools_ShapeDataSource.hxx>
#include <QSurfaceFormat>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNamedColors.h>
#include <vtkProperty.h>
#include <vtkSmartPointer.h>

#include "vtkAutoInit.h"
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

VTK_OCC_Qt::VTK_OCC_Qt(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.display, &QAction::triggered, this, &VTK_OCC_Qt::display);
	connect(ui.play, &QAction::triggered, this, &VTK_OCC_Qt::play);
	connect(ui.HeadSlice, &QAction::triggered, this, &VTK_OCC_Qt::HeadSlice);
	connect(ui.IronIsoSurface, &QAction::triggered, this, &VTK_OCC_Qt::IronIsoSurface);
	connect(ui.ComplexV, &QAction::triggered, this, &VTK_OCC_Qt::ComplexV);
	connect(ui.Kitchen, &QAction::triggered, this, &VTK_OCC_Qt::Kitchen);
	connect(ui.TensorAxes, &QAction::triggered, this, &VTK_OCC_Qt::TensorAxes);
	connect(ui.step, &QAction::triggered, this, &VTK_OCC_Qt::read_step);
	connect(ui.actionreadIGS, &QAction::triggered, this, &VTK_OCC_Qt::read_IGS);

	connect(ui.lorenz, &QAction::triggered, this, &VTK_OCC_Qt::Lorenz);
	connect(ui.makebox, &QAction::triggered, this, &VTK_OCC_Qt::makebox);
	connect(ui.makecone, &QAction::triggered, this, &VTK_OCC_Qt::makecone);
	connect(ui.OnButtonCreatepnt, &QAction::triggered, this, &VTK_OCC_Qt::Createpnt);
	initializeGL();
}


void VTK_OCC_Qt::mousePressEvent(QMouseEvent * event)
{
}

void VTK_OCC_Qt::display()
{

	BRepPrimAPI_MakeBox mkBox(1., 2., 3.);
	const TopoDS_Shape& shape = mkBox.Shape();

	vtkNew<vtkRenderer> ren;

	vtkNew<IVtkTools_ShapeDataSource> occsource;
	occsource->SetShape(new IVtkOCC_Shape(shape));

	vtkNew<vtkPolyDataMapper> mapper;

	mapper->SetInputConnection(occsource->GetOutputPort());

	vtkNew<vtkActor> actor;
	actor->SetMapper(mapper.Get());
	ren->AddActor(actor.Get());

	initializeGL();


}
void VTK_OCC_Qt::initializeGL()
{
	renderers = vtkSmartPointer<vtkRenderer>::New();
	renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
	renderWindow->AddRenderer(renderers);
	renderers->SetBackground(1, 1, 1);
	renderers->SetBackground2(0.529, 0.8078, 0.92157);
	renderers->SetGradientBackground(1);
	ui.openGLWidget->setRenderWindow(renderWindow);//��ʾ��vtk��
}
//�� 4 �� - ���ӻ��ܵ�
void VTK_OCC_Qt::play()
{
	QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
	vtkNew<vtkQuadric> quadric;
	quadric->SetCoefficients(1, 2, 3, 0, 1, 0, 0, 0, 0, 0);
	vtkNew<vtkSampleFunction> sample;
	sample->SetSampleDimensions(25, 25, 25);
	sample->SetImplicitFunction(quadric);

	vtkNew<vtkActor> isoActor;
	quadricVisualization.CreateIsosurface(sample, isoActor);

	vtkNew<vtkActor> outlineIsoActor;
	quadricVisualization.CreateOutline(sample, outlineIsoActor);

	vtkNew<vtkActor> planesActor;
	quadricVisualization.CreatePlanes(sample, planesActor, 3);
	vtkNew<vtkActor> outlinePlanesActor;
	quadricVisualization.CreateOutline(sample, outlinePlanesActor);
	planesActor->AddPosition(isoActor->GetBounds()[0] * 2.0, 0, 0);
	outlinePlanesActor->AddPosition(isoActor->GetBounds()[0] * 2.0, 0, 0);

	vtkNew<vtkActor> contourActor;
	quadricVisualization.CreateContours(sample, contourActor, 3, 15);
	vtkNew<vtkActor> outlineContourActor;
	quadricVisualization.CreateOutline(sample, outlineContourActor);
	contourActor->AddPosition(isoActor->GetBounds()[0] * 4.0, 0, 0);
	outlineContourActor->AddPosition(isoActor->GetBounds()[0] * 4.0, 0, 0);

	vtkNew<vtkRenderer> renderer;
	renderer->AddActor(planesActor);
	renderer->AddActor(outlinePlanesActor);
	renderer->AddActor(contourActor);
	renderer->AddActor(outlineContourActor);
	renderer->AddActor(isoActor);
	renderer->AddActor(outlineIsoActor);
	renderer->TwoSidedLightingOn();

	// Try to set camera to match figure on book.
	renderer->GetActiveCamera()->SetPosition(0, -1, 0);
	renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
	renderer->GetActiveCamera()->SetViewUp(0, 0, -1);
	renderer->ResetCamera();
	renderer->GetActiveCamera()->Elevation(20);
	renderer->GetActiveCamera()->Azimuth(10);
	renderer->GetActiveCamera()->Dolly(1.2);
	renderer->ResetCameraClippingRange();
	//���ñ���Ϊ����ɫ
	renderer->SetBackground(1, 1, 1);
	renderer->SetBackground2(0.529, 0.8078, 0.92157);
	renderer->SetGradientBackground(1);
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;//����һ��vtk����
	renderWindow->AddRenderer(renderer);//�ڴ����м�����Ⱦ��
	renderWindow->SetWindowName("RenderWindowNoUIFile");//���ڱ���
	ui.openGLWidget->setRenderWindow(renderWindow);//��ʾ��vtk��
}

void VTK_OCC_Qt::HeadSlice()//������Ƭ
{
	vtkNew<vtkNamedColors> colors;

	vtkNew<vtkRenderer> ren1;

	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("MetaImage Files (*.mhd)"));
	if (fileName.isEmpty())
	{
		return;
	}
	// ���� vtkMetaImageReader ���������ļ���,�������ܵ�
	vtkSmartPointer<vtkMetaImageReader> reader = vtkSmartPointer<vtkMetaImageReader>::New();
	reader->SetFileName(fileName.toStdString().c_str());
	reader->Update();
	
	

	vtkNew<vtkExtractVOI> extractVOI;
	extractVOI->SetInputConnection(reader->GetOutputPort());
	extractVOI->SetVOI(0, 50, 0, 50, 0, 50);
	extractVOI->Update();

	vtkNew<vtkContourFilter> iso;
	iso->SetInputConnection(extractVOI->GetOutputPort());
	iso->GenerateValues(12, 500, 1150);

	vtkNew<vtkPolyDataMapper> isoMapper;
	isoMapper->SetInputConnection(iso->GetOutputPort());
	isoMapper->ScalarVisibilityOff();

	vtkNew<vtkActor> isoActor;
	isoActor->SetMapper(isoMapper);
	isoActor->GetProperty()->SetColor(colors->GetColor3d("Wheat").GetData());

	vtkNew<vtkOutlineFilter> outline;
	outline->SetInputConnection(extractVOI->GetOutputPort());

	vtkNew<vtkPolyDataMapper> outlineMapper;
	outlineMapper->SetInputConnection(outline->GetOutputPort());

	vtkNew<vtkActor> outlineActor;
	outlineActor->SetMapper(outlineMapper);

	ren1->AddActor(outlineActor);
	ren1->AddActor(isoActor);
	ren1->SetBackground(colors->GetColor3d("SlateGray").GetData());
	ren1->ResetCamera();
	ren1->GetActiveCamera()->Dolly(1.5);
	ren1->ResetCameraClippingRange();


	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;//����һ��vtk����
	renderWindow->AddRenderer(ren1);//�ڴ����м�����Ⱦ��
	ui.openGLWidget->setRenderWindow(renderWindow);//��ʾ��vtk��
}

void VTK_OCC_Qt::IronIsoSurface()//�����ױ���
{
	vtkNew<vtkNamedColors>colors;
	vtkNew<vtkRenderer>ren1;
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("VTK Files (*.vtk)"));
	if (fileName.isEmpty())
	{
		return;
	}
	vtkNew<vtkStructuredPointsReader>render;
	render->SetFileName(fileName.toStdString().c_str());
	render->Update();
	vtkNew<vtkContourFilter> iso;
	iso->SetInputConnection(render->GetOutputPort());
	iso->SetValue(0, 128);

	vtkNew<vtkPolyDataMapper> isoMapper;
	isoMapper->SetInputConnection(iso->GetOutputPort());
	isoMapper->ScalarVisibilityOff();

	vtkNew<vtkActor> isoActor;
	isoActor->SetMapper(isoMapper);
	isoActor->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());

	vtkNew<vtkOutlineFilter> outline;
	outline->SetInputConnection(render->GetOutputPort());

	vtkNew<vtkPolyDataMapper> outlineMapper;
	outlineMapper->SetInputConnection(outline->GetOutputPort());

	vtkNew<vtkActor> outlineActor;
	outlineActor->SetMapper(outlineMapper);

	ren1->AddActor(outlineActor);
	ren1->AddActor(isoActor);

	ren1->SetBackground(1, 1, 1);
	ren1->SetBackground2(0.529, 0.8078, 0.92157);
	ren1->SetGradientBackground(1);
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;//����һ��vtk����
	renderWindow->AddRenderer(ren1);//�ڴ����м�����Ⱦ��
	ui.openGLWidget->setRenderWindow(renderWindow);//��ʾ��vtk��


	// render the image
	//
	ren1->ResetCamera();
	ren1->GetActiveCamera()->Azimuth(30);
	ren1->GetActiveCamera()->Elevation(30);
}

void VTK_OCC_Qt::ComplexV()
{
	vtkNew<vtkNamedColors>colors;
	vtkNew<vtkRenderer>ren1;
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("VTK Files (*.vtk)"));
	if (fileName.isEmpty())
	{
		return;
	}
	vtkNew<vtkStructuredPointsReader>render;
	render->SetFileName(fileName.toStdString().c_str());
	render->Update();


	vtkNew<vtkHedgeHog> hhog;
	hhog->SetInputConnection(render->GetOutputPort());
	hhog->SetScaleFactor(0.3);

	vtkNew<vtkLookupTable> lut;
	//  lut->SetHueRange(.667, 0.0);
	lut->Build();

	vtkNew<vtkPolyDataMapper> hhogMapper;
	hhogMapper->SetInputConnection(hhog->GetOutputPort());
	hhogMapper->SetScalarRange(50, 550);
	hhogMapper->SetLookupTable(lut);

	vtkNew<vtkActor> hhogActor;
	hhogActor->SetMapper(hhogMapper);

	vtkNew<vtkOutlineFilter> outline;
	outline->SetInputConnection(render->GetOutputPort());

	vtkNew<vtkPolyDataMapper> outlineMapper;
	outlineMapper->SetInputConnection(outline->GetOutputPort());

	vtkNew<vtkActor> outlineActor;
	outlineActor->SetMapper(outlineMapper);
	outlineActor->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());

	ren1->AddActor(outlineActor);
	ren1->AddActor(hhogActor);

	ren1->GetActiveCamera()->SetFocalPoint(0, 0, 0);
	ren1->GetActiveCamera()->SetPosition(1,0,0);
	ren1->GetActiveCamera()->SetViewUp(0, 0, 1);
	ren1->ResetCamera();
	ren1->GetActiveCamera()->Azimuth(60);
	ren1->GetActiveCamera()->Elevation(30);
	ren1->GetActiveCamera()->Dolly(1.1);
	ren1->ResetCameraClippingRange();

	ren1->SetBackground(1, 1, 1);
	ren1->SetBackground2(0.529, 0.8078, 0.92157);
	ren1->SetGradientBackground(1);
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;//����һ��vtk����
	renderWindow->AddRenderer(ren1);//�ڴ����м�����Ⱦ��
	ui.openGLWidget->setRenderWindow(renderWindow);//��ʾ��vtk��


}

void VTK_OCC_Qt::Kitchen()
{
	double range[2];
	double maxTime = 0.0;
	vtkNew<vtkNamedColors> colors;
	vtkNew<vtkRenderer>aren;
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("VTK Files (*.vtk)"));
	if (fileName.isEmpty())
	{
		return;
	}
	//��ȡ����
	vtkNew<vtkStructuredGridReader>render;
	render->SetFileName(fileName.toStdString().c_str());
	render->Update();
	render->GetOutput()->GetLength();

	if (render->GetOutput()->GetPointData()->GetScalars())
	{
		render->GetOutput()->GetPointData()->GetScalars()->GetRange(range);
	}
	if (render->GetOutput()->GetPointData()->GetVectors())
	{
		auto maxVelocity =
			render->GetOutput()->GetPointData()->GetVectors()->GetMaxNorm();
		maxTime = 4.0 * render->GetOutput()->GetLength() / maxVelocity;
	}

	//Χ�����ݽ��и���
	vtkNew<vtkStructuredGridOutlineFilter> outlineF;
	outlineF->SetInputConnection(render->GetOutputPort());
	vtkNew<vtkPolyDataMapper> outlineMapper;
	outlineMapper->SetInputConnection(outlineF->GetOutputPort());
	vtkNew<vtkActor> outline;
	outline->SetMapper(outlineMapper);
	outline->GetProperty()->SetColor(colors->GetColor3d("LampBlack").GetData());

	//������Ӱ��
	vtkNew<vtkStructuredGridGeometryFilter> doorGeom;
	doorGeom->SetInputConnection(render->GetOutputPort());
	doorGeom->SetExtent(27, 27, 14, 18, 0, 11);
	vtkNew<vtkPolyDataMapper> mapDoor;
	mapDoor->SetInputConnection(doorGeom->GetOutputPort());
	mapDoor->ScalarVisibilityOff();
	vtkNew<vtkActor> door;
	door->SetMapper(mapDoor);
	door->GetProperty()->SetColor(colors->GetColor3d("Burlywood").GetData());

	vtkNew<vtkStructuredGridGeometryFilter> window1Geom;
	window1Geom->SetInputConnection(render->GetOutputPort());
	window1Geom->SetExtent(0, 0, 9, 18, 6, 12);
	vtkNew<vtkPolyDataMapper> mapWindow1;
	mapWindow1->SetInputConnection(window1Geom->GetOutputPort());
	mapWindow1->ScalarVisibilityOff();
	vtkNew<vtkActor> window1;
	window1->SetMapper(mapWindow1);
	window1->GetProperty()->SetColor(colors->GetColor3d("SkyBlue").GetData());
	window1->GetProperty()->SetOpacity(.6);

	vtkNew<vtkStructuredGridGeometryFilter> window2Geom;
	window2Geom->SetInputConnection(render->GetOutputPort());
	window2Geom->SetExtent(5, 12, 23, 23, 6, 12);
	vtkNew<vtkPolyDataMapper> mapWindow2;
	mapWindow2->SetInputConnection(window2Geom->GetOutputPort());
	mapWindow2->ScalarVisibilityOff();
	vtkNew<vtkActor> window2;
	window2->SetMapper(mapWindow2);
	window2->GetProperty()->SetColor(colors->GetColor3d("SkyBlue").GetData());
	window2->GetProperty()->SetOpacity(.6);

	vtkNew<vtkStructuredGridGeometryFilter> klower1Geom;
	klower1Geom->SetInputConnection(render->GetOutputPort());
	klower1Geom->SetExtent(17, 17, 0, 11, 0, 6);
	vtkNew<vtkPolyDataMapper> mapKlower1;
	mapKlower1->SetInputConnection(klower1Geom->GetOutputPort());
	mapKlower1->ScalarVisibilityOff();
	vtkNew<vtkActor> klower1;
	klower1->SetMapper(mapKlower1);
	klower1->GetProperty()->SetColor(colors->GetColor3d("EggShell").GetData());

	vtkNew<vtkStructuredGridGeometryFilter> klower2Geom;
	klower2Geom->SetInputConnection(render->GetOutputPort());
	klower2Geom->SetExtent(19, 19, 0, 11, 0, 6);
	vtkNew<vtkPolyDataMapper> mapKlower2;
	mapKlower2->SetInputConnection(klower2Geom->GetOutputPort());
	mapKlower2->ScalarVisibilityOff();
	vtkNew<vtkActor> klower2;
	klower2->SetMapper(mapKlower2);
	klower2->GetProperty()->SetColor(colors->GetColor3d("EggShell").GetData());

	vtkNew<vtkStructuredGridGeometryFilter> klower3Geom;
	klower3Geom->SetInputConnection(render->GetOutputPort());
	klower3Geom->SetExtent(17, 19, 0, 0, 0, 6);
	vtkNew<vtkPolyDataMapper> mapKlower3;
	mapKlower3->SetInputConnection(klower3Geom->GetOutputPort());
	mapKlower3->ScalarVisibilityOff();
	vtkNew<vtkActor> klower3;
	klower3->SetMapper(mapKlower3);
	klower3->GetProperty()->SetColor(colors->GetColor3d("EggShell").GetData());

	vtkNew<vtkStructuredGridGeometryFilter> klower4Geom;
	klower4Geom->SetInputConnection(render->GetOutputPort());
	klower4Geom->SetExtent(17, 19, 11, 11, 0, 6);
	vtkNew<vtkPolyDataMapper> mapKlower4;
	mapKlower4->SetInputConnection(klower4Geom->GetOutputPort());
	mapKlower4->ScalarVisibilityOff();
	vtkNew<vtkActor> klower4;
	klower4->SetMapper(mapKlower4);
	klower4->GetProperty()->SetColor(colors->GetColor3d("EggShell").GetData());

	vtkNew<vtkStructuredGridGeometryFilter> klower5Geom;
	klower5Geom->SetInputConnection(render->GetOutputPort());
	klower5Geom->SetExtent(17, 19, 0, 11, 0, 0);
	vtkNew<vtkPolyDataMapper> mapKlower5;
	mapKlower5->SetInputConnection(klower5Geom->GetOutputPort());
	mapKlower5->ScalarVisibilityOff();
	vtkNew<vtkActor> klower5;
	klower5->SetMapper(mapKlower5);
	klower5->GetProperty()->SetColor(colors->GetColor3d("EggShell").GetData());

	vtkNew<vtkStructuredGridGeometryFilter> klower6Geom;
	klower6Geom->SetInputConnection(render->GetOutputPort());
	klower6Geom->SetExtent(17, 19, 0, 7, 6, 6);
	vtkNew<vtkPolyDataMapper> mapKlower6;
	mapKlower6->SetInputConnection(klower6Geom->GetOutputPort());
	mapKlower6->ScalarVisibilityOff();
	vtkNew<vtkActor> klower6;
	klower6->SetMapper(mapKlower6);
	klower6->GetProperty()->SetColor(colors->GetColor3d("EggShell").GetData());

	vtkNew<vtkStructuredGridGeometryFilter> klower7Geom;
	klower7Geom->SetInputConnection(render->GetOutputPort());
	klower7Geom->SetExtent(17, 19, 9, 11, 6, 6);
	vtkNew<vtkPolyDataMapper> mapKlower7;
	mapKlower7->SetInputConnection(klower7Geom->GetOutputPort());
	mapKlower7->ScalarVisibilityOff();
	vtkNew<vtkActor> klower7;
	klower7->SetMapper(mapKlower7);
	klower7->GetProperty()->SetColor(colors->GetColor3d("EggShell").GetData());

	vtkNew<vtkStructuredGridGeometryFilter> hood1Geom;
	hood1Geom->SetInputConnection(render->GetOutputPort());
	hood1Geom->SetExtent(17, 17, 0, 11, 11, 16);
	vtkNew<vtkPolyDataMapper> mapHood1;
	mapHood1->SetInputConnection(hood1Geom->GetOutputPort());
	mapHood1->ScalarVisibilityOff();
	vtkNew<vtkActor> hood1;
	hood1->SetMapper(mapHood1);
	hood1->GetProperty()->SetColor(colors->GetColor3d("Silver").GetData());

	vtkNew<vtkStructuredGridGeometryFilter> hood2Geom;
	hood2Geom->SetInputConnection(render->GetOutputPort());
	hood2Geom->SetExtent(19, 19, 0, 11, 11, 16);
	vtkNew<vtkPolyDataMapper> mapHood2;
	mapHood2->SetInputConnection(hood2Geom->GetOutputPort());
	mapHood2->ScalarVisibilityOff();
	vtkNew<vtkActor> hood2;
	hood2->SetMapper(mapHood2);
	hood2->GetProperty()->SetColor(colors->GetColor3d("Furniture").GetData());

	vtkNew<vtkStructuredGridGeometryFilter> hood3Geom;
	hood3Geom->SetInputConnection(render->GetOutputPort());
	hood3Geom->SetExtent(17, 19, 0, 0, 11, 16);
	vtkNew<vtkPolyDataMapper> mapHood3;
	mapHood3->SetInputConnection(hood3Geom->GetOutputPort());
	mapHood3->ScalarVisibilityOff();
	vtkNew<vtkActor> hood3;
	hood3->SetMapper(mapHood3);
	hood3->GetProperty()->SetColor(colors->GetColor3d("Furniture").GetData());

	vtkNew<vtkStructuredGridGeometryFilter> hood4Geom;
	hood4Geom->SetInputConnection(render->GetOutputPort());
	hood4Geom->SetExtent(17, 19, 11, 11, 11, 16);
	vtkNew<vtkPolyDataMapper> mapHood4;
	mapHood4->SetInputConnection(hood4Geom->GetOutputPort());
	mapHood4->ScalarVisibilityOff();
	vtkNew<vtkActor> hood4;
	hood4->SetMapper(mapHood4);
	hood4->GetProperty()->SetColor(colors->GetColor3d("Furniture").GetData());

	vtkNew<vtkStructuredGridGeometryFilter> hood6Geom;
	hood6Geom->SetInputConnection(render->GetOutputPort());
	hood6Geom->SetExtent(17, 19, 0, 11, 16, 16);
	vtkNew<vtkPolyDataMapper> mapHood6;
	mapHood6->SetInputConnection(hood6Geom->GetOutputPort());
	mapHood6->ScalarVisibilityOff();
	vtkNew<vtkActor> hood6;
	hood6->SetMapper(mapHood6);
	hood6->GetProperty()->SetColor(colors->GetColor3d("Furniture").GetData());

	vtkNew<vtkStructuredGridGeometryFilter> cookingPlateGeom;
	cookingPlateGeom->SetInputConnection(render->GetOutputPort());
	cookingPlateGeom->SetExtent(17, 19, 7, 9, 6, 6);
	vtkNew<vtkPolyDataMapper> mapCookingPlate;
	mapCookingPlate->SetInputConnection(cookingPlateGeom->GetOutputPort());
	mapCookingPlate->ScalarVisibilityOff();
	vtkNew<vtkActor> cookingPlate;
	cookingPlate->SetMapper(mapCookingPlate);
	cookingPlate->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());

	vtkNew<vtkStructuredGridGeometryFilter> filterGeom;
	filterGeom->SetInputConnection(render->GetOutputPort());
	filterGeom->SetExtent(17, 19, 7, 9, 11, 11);
	vtkNew<vtkPolyDataMapper> mapFilter;
	mapFilter->SetInputConnection(filterGeom->GetOutputPort());
	mapFilter->ScalarVisibilityOff();
	vtkNew<vtkActor> filter;
	filter->SetMapper(mapFilter);
	filter->GetProperty()->SetColor(colors->GetColor3d("Furniture").GetData());

	//��������
	vtkNew<vtkLineSource> line;
	line->SetResolution(39);
	line->SetPoint1(0.08, 2.50, 0.71);
	line->SetPoint2(0.08, 4.50, 0.71);
	vtkNew<vtkPolyDataMapper> rakeMapper;
	rakeMapper->SetInputConnection(line->GetOutputPort());
	vtkNew<vtkActor> rake;
	rake->SetMapper(rakeMapper);
	vtkNew<vtkStreamTracer> streamers;
	streamers->SetInputConnection(render->GetOutputPort());
	streamers->SetSourceConnection(line->GetOutputPort());
	streamers->SetMaximumPropagation(maxTime);
	streamers->SetInitialIntegrationStep(.5);
	streamers->SetMinimumIntegrationStep(.1);
	streamers->SetIntegratorType(2);
	streamers->Update();

	vtkNew<vtkPolyDataMapper> streamersMapper;
	streamersMapper->SetInputConnection(streamers->GetOutputPort());
	streamersMapper->SetScalarRange(range);

	vtkNew<vtkActor> lines;
	lines->SetMapper(streamersMapper);
	lines->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());

	aren->TwoSidedLightingOn();

	aren->AddActor(outline);
	aren->AddActor(door);
	aren->AddActor(window1);
	aren->AddActor(window2);
	aren->AddActor(klower1);
	aren->AddActor(klower2);
	aren->AddActor(klower3);
	aren->AddActor(klower4);
	aren->AddActor(klower5);
	aren->AddActor(klower6);
	aren->AddActor(klower7);
	aren->AddActor(hood1);
	aren->AddActor(hood2);
	aren->AddActor(hood3);
	aren->AddActor(hood4);
	aren->AddActor(hood6);
	aren->AddActor(cookingPlate);
	aren->AddActor(filter);
	aren->AddActor(lines);
	aren->AddActor(rake);

	aren->SetBackground(colors->GetColor3d("SlateGray").GetData());

	vtkNew<vtkCamera> aCamera;
	aren->SetActiveCamera(aCamera);
	aren->ResetCamera();

	aCamera->SetFocalPoint(3.505, 2.505, 1.255);
	aCamera->SetPosition(3.505, 24.6196, 1.255);
	aCamera->SetViewUp(0, 0, 1);
	aCamera->Azimuth(60);
	aCamera->Elevation(30);
	aCamera->Dolly(1.4);
	aren->ResetCameraClippingRange();

	aren->SetBackground(1, 1, 1);
	aren->SetBackground2(0.529, 0.8078, 0.92157);
	aren->SetGradientBackground(1);
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;//����һ��vtk����
	renderWindow->AddRenderer(aren);//�ڴ����м�����Ⱦ��
	ui.openGLWidget->setRenderWindow(renderWindow);//��ʾ��vtk��
}

void VTK_OCC_Qt::TensorAxes()
{
	vtkNew<vtkNamedColors>colors;
	vtkNew<vtkRenderer>ren;

	//��������
	vtkNew<vtkPointLoad>ptLoad;
	ptLoad->SetLoadValue(100.0);//���ø���ֵΪ 100.0����ʾʩ����ģ���ϵ�����ѹ��
	ptLoad->SetSampleDimensions(6, 6, 6); //����������ά��Ϊ 6x6x6������ģ����ÿ�������ϵķֱ��ʻ��������
	ptLoad->ComputeEffectiveStressOn();//������ЧӦ�����㡣������ѧģ���У��Լ�������ڸ����µ�Ӧ���ֲ���
	ptLoad->SetModelBounds(-10, 10, -10, 10, -10, 10); //����ģ�͵ı߽緶ΧΪ x ���� - 10 �� 10��y ���� - 10 �� 10��z ���� - 10 �� 10
	
	//��ȡ���ݱ���
	vtkNew<vtkImageDataGeometryFilter> plane;//��ͼ������ת��Ϊ��������
	plane->SetInputConnection(ptLoad->GetOutputPort());//�� ptLoad �����������ӵ� plane ������������
	plane->SetExtent(2, 2, 0, 99, 0, 99);//���ù������Ĵ���Χ

	//����������
	vtkNew<vtkAxes> axes;
	axes->SetScaleFactor(0.5);

	vtkNew<vtkTubeFilter> tubeAxes;//vtkTubeFilter���߶�ת��ΪԲ����
	tubeAxes->SetInputConnection(axes->GetOutputPort());//�� axes �����������ӵ� tubeAxes ������������
	tubeAxes->SetRadius(0.1);//�������ɵĹܵ��İ뾶Ϊ 0.1
	tubeAxes->SetNumberOfSides(4);//�������ɵĹܵ��ı���Ϊ 6������ζ�Źܵ����� 6 ������ɣ��γ�һ�������εĽ���

	vtkNew<vtkTensorGlyph> tensorAxes;//vtkTensorGlyph���ڸ��������������ɼ���ͼ�Ρ�
	tensorAxes->SetInputConnection(ptLoad->GetOutputPort());
	tensorAxes->SetSourceConnection(axes->GetOutputPort());
	tensorAxes->SetScaleFactor(10);//������������Ϊ 10������������ɵļ���ͼ�εĴ�С
	tensorAxes->ClampScalingOn();// �����������ơ�


	vtkNew<vtkLookupTable> lut;
	MakeLogLUT(lut);

	vtkNew<vtkPolyDataMapper> tensorAxesMapper;
	tensorAxesMapper->SetInputConnection(tensorAxes->GetOutputPort());
	tensorAxesMapper->SetLookupTable(lut);
	plane->Update(); // ǿ�Ƹ��±�����Χ

	tensorAxesMapper->SetScalarRange(plane->GetOutput()->GetScalarRange());

	vtkNew<vtkActor> tensorActor;
	tensorActor->SetMapper(tensorAxesMapper);

	//��������Χ����һ������
	vtkNew<vtkOutlineFilter> outline;
	outline->SetInputConnection(ptLoad->GetOutputPort());

	vtkNew<vtkPolyDataMapper> outlineMapper;
	outlineMapper->SetInputConnection(outline->GetOutputPort());

	vtkNew<vtkActor> outlineActor;
	outlineActor->SetMapper(outlineMapper);
	outlineActor->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());

	//
	// ����һ��Բ׶�壬�䶥���ʾʩ�ӵ��غɡ�
	//
	vtkNew<vtkConeSource> coneSrc;
	coneSrc->SetRadius(0.5);
	coneSrc->SetHeight(2);
	vtkNew<vtkPolyDataMapper> coneMap;
	coneMap->SetInputConnection(coneSrc->GetOutputPort());
	vtkNew<vtkActor> coneActor;
	coneActor->SetMapper(coneMap);
	coneActor->SetPosition(0, 0, 11);
	coneActor->RotateY(90);
	coneActor->GetProperty()->SetColor(colors->GetColor3d("BurlyWood").GetData());

	vtkNew<vtkCamera> camera;
	camera->SetFocalPoint(0.113766, -1.13665, -1.01919);
	camera->SetPosition(-29.4886, -63.1488, 26.5807);
	camera->SetViewAngle(24.4617);
	camera->SetViewUp(0.17138, 0.331163, 0.927879);
	camera->SetClippingRange(1, 100);

	ren->AddActor(tensorActor);
	ren->AddActor(outlineActor);
	ren->AddActor(coneActor);
	ren->SetActiveCamera(camera);

	ren->SetBackground(1, 1, 1);
	ren->SetBackground2(0.529, 0.8078, 0.92157);
	ren->SetGradientBackground(1);
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;//����һ��vtk����
	renderWindow->AddRenderer(ren);//�ڴ����м�����Ⱦ��
	ui.openGLWidget->setRenderWindow(renderWindow);//��ʾ��vtk��

}

void VTK_OCC_Qt::MakeLogLUT(vtkLookupTable * lut)
{
	// Original
	lut->SetScaleToLog10();
	lut->SetHueRange(.6667, 0.0);
	lut->Build();
}

void VTK_OCC_Qt::read_step()
{
	//�ļ���ȡ
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open STEP File"), "", tr("STEP Files (*.stp *.step)"));
	if (fileName.isEmpty())
	{
		return;
	}
	STEPControl_Reader reader;
	IFSelect_ReturnStatus status = reader.ReadFile(fileName.toStdString().c_str());

	// ת�� STEP �ļ��е���״
	reader.TransferRoots();
	TopoDS_Shape shape = reader.OneShape();

	Handle_IVtkOCC_Shape aShapeImpl = new IVtkOCC_Shape(shape);//Handle_IVtkOCC_Shape����ָ�룬��OCC����shape���ݸ�IVtkOCC_Shape
	Handle_IVtkVTK_ShapeData aDataImpl = new IVtkVTK_ShapeData();//Handle_IVtkVTK_ShapeData����ָ�룬�洢ת�����vtk����
	Handle_IVtk_IShapeMesher aMesher = new IVtkOCC_ShapeMesher();//������������
	aMesher->Build(aShapeImpl, aDataImpl);//�����������񻯣��洢��aDataImpl��
	vtkPolyData* aPolyData = aDataImpl->getVtkPolyData();//��ȡת����� VTK ���������

	vtkNew<vtkPolyDataMapper> mapper;//��������mapper�Զ������ڴ档vtkPolyDataMapper���ڽ���������ݣ�vtkPolyData��ӳ�䵽ͼ�ι��ߣ��Ա������Ⱦ
	mapper->SetInputData(aPolyData);//��aPolyData��������Ϊmapper���������ݡ�aPolyData��һ�������������ݵ�vtkPolyData����

	//����һ��actor
	vtkNew<vtkActor> actor;
	actor->SetMapper(mapper);

	//����һ��vtk��Ⱦ��
	vtkNew<vtkRenderer> ren;
	ren->AddActor(actor);

	//��ӱ�����ɫ
	ren->SetBackground(1, 1, 1);
	ren->SetBackground2(0.529, 0.8078, 0.92157);
	ren->SetGradientBackground(1);
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;//����һ��vtk����
	renderWindow->AddRenderer(ren);//�ڴ����м�����Ⱦ��
	ui.openGLWidget->setRenderWindow(renderWindow);//��ʾ��vtk��
}

void VTK_OCC_Qt::read_IGS()
{
	//�ļ���ȡ
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open IGES File"), "", tr("IGES Files (*.igs *.iges)"));
	if (fileName.isEmpty())
	{
		return;
	}

	//IGES Import
	IGESControl_Reader ReaderIGES;
	IFSelect_ReturnStatus status = ReaderIGES.ReadFile(fileName.toStdString().c_str());

	IFSelect_PrintCount modeIGES = IFSelect_ListByItem;
	ReaderIGES.PrintCheckLoad(Standard_True, modeIGES);

	// ת�� STEP �ļ��е���״
	ReaderIGES.TransferRoots();
	TopoDS_Shape TopoDS_ShapeIGES = ReaderIGES.OneShape();

	gp_Trsf igesTM;
	igesTM.SetScaleFactor(2);
	igesTM.SetTranslationPart(gp_Vec(0, 3, 0));
	BRepBuilderAPI_Transform stepBRepTransformationIGES(TopoDS_ShapeIGES, igesTM, Standard_True);
	TopoDS_ShapeIGES = stepBRepTransformationIGES.Shape();

	Handle_IVtkOCC_Shape aShapeImpl = new IVtkOCC_Shape(TopoDS_ShapeIGES);//Handle_IVtkOCC_Shape����ָ�룬��OCC����shape���ݸ�IVtkOCC_Shape
	Handle_IVtkVTK_ShapeData aDataImpl = new IVtkVTK_ShapeData();//Handle_IVtkVTK_ShapeData����ָ�룬�洢ת�����vtk����
	Handle_IVtk_IShapeMesher aMesher = new IVtkOCC_ShapeMesher();//������������
	aMesher->Build(aShapeImpl, aDataImpl);//�����������񻯣��洢��aDataImpl��
	vtkPolyData* aPolyData = aDataImpl->getVtkPolyData();//��ȡת����� VTK ���������

	vtkNew<vtkPolyDataMapper> mapper;//��������mapper�Զ������ڴ档vtkPolyDataMapper���ڽ���������ݣ�vtkPolyData��ӳ�䵽ͼ�ι��ߣ��Ա������Ⱦ
	mapper->SetInputData(aPolyData);//��aPolyData��������Ϊmapper���������ݡ�aPolyData��һ�������������ݵ�vtkPolyData����

	//����һ��actor
	vtkNew<vtkActor> actor;
	actor->SetMapper(mapper);

	//����һ��vtk��Ⱦ��
	vtkNew<vtkRenderer> ren;
	ren->AddActor(actor);

	//��ӱ�����ɫ
	ren->SetBackground(1, 1, 1);
	ren->SetBackground2(0.529, 0.8078, 0.92157);
	ren->SetGradientBackground(1);
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;//����һ��vtk����
	renderWindow->AddRenderer(ren);//�ڴ����м�����Ⱦ��
	ui.openGLWidget->setRenderWindow(renderWindow);//��ʾ��vtk��

}

void VTK_OCC_Qt::makebox()
{
	TopoDS_Shape aTopoBox = BRepPrimAPI_MakeBox(3.0, 4.0, 5.0).Shape();
	vtkPolyData* polyData = convertShapeToVTK(aTopoBox);
	displayShape(polyData);
}

void VTK_OCC_Qt::makecone()
{
	gp_Ax2 anAxis;
	anAxis.SetLocation(gp_Pnt(0.0, 10.0, 0.0));
	TopoDS_Shape aTopoReducer = BRepPrimAPI_MakeCone(anAxis, 3.0, 1.5, 5.0).Shape();

	vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
	reader->SetFileName("1.jpg");
	reader->Update();

	vtkNew<vtkTexture> texture;
	texture->SetInputConnection(reader->GetOutputPort());

	vtkPolyData* polyData = convertShapeToVTK(aTopoReducer);
	displayShape(polyData, texture);
}



void VTK_OCC_Qt::Lorenz()
{
	double Pr = 10.0; // The Lorenz parameters.
	double b = 2.667;
	double r = 28.0;
	double x, y, z;       // starting (and current) x, y, z
	double h = 0.01;      // integration step size
	int resolution = 200; // slice resolution
	int iter = 10000000;  // number of iterations
	double xmin = -30.0;  // x, y, z range for voxels
	double xmax = 30.0;
	double ymin = -30.0;
	double ymax = 30.0;
	double zmin = -10.0;
	double zmax = 60.0;

	//������ֲ���
	auto xIncr = resolution / (xmax - xmin);
	auto yIncr = resolution / (ymax - ymin);
	auto zIncr = resolution / (zmax - zmin);

	vtkNew<vtkMinimalStandardRandomSequence> randomSequence;
	randomSequence->SetSeed(8775070);
	x = randomSequence->GetRangeValue(xmin, xmax);
	randomSequence->Next();
	y = randomSequence->GetRangeValue(ymin, ymax);
	randomSequence->Next();
	z = randomSequence->GetRangeValue(zmin, zmax);
	randomSequence->Next();

	// ����Ƭ�ڴ�.
	auto sliceSize = resolution * resolution;
	auto numPts = sliceSize * resolution;
	vtkNew<vtkShortArray> scalars;
	auto s = scalars->WritePointer(0, numPts);
	for (auto i = 0; i < numPts; i++)
	{
		s[i] = 0;
	}
	for (auto j = 0; j < iter; j++)
	{
		// ��һ������.
		auto xx = x + h * Pr * (y - x);
		auto yy = y + h * (x * (r - z) - y);
		auto zz = z + h * (x * y - (b * z));

		x = xx;
		y = yy;
		z = zz;

		// ��������ָ��.
		if (x < xmax && x > xmin && y < ymax && y > ymin && z < zmax && z > zmin)
		{
			auto xxx = static_cast<short>(static_cast<double>(xx - xmin) * xIncr);
			auto yyy = static_cast<short>(static_cast<double>(yy - ymin) * yIncr);
			auto zzz = static_cast<short>(static_cast<double>(zz - zmin) * zIncr);
			auto index = xxx + yyy * resolution + zzz * sliceSize;
			s[index] += 1;
		}
	}
	vtkNew<vtkNamedColors> colors;

	vtkNew<vtkStructuredPoints> volume;
	volume->GetPointData()->SetScalars(scalars);
	volume->SetDimensions(resolution, resolution, resolution);
	volume->SetOrigin(xmin, ymin, zmin);
	volume->SetSpacing((xmax - xmin) / resolution, (ymax - ymin) / resolution,(zmax - zmin) / resolution);

	//��ͼ
	vtkNew<vtkRenderer> renderer;
	// Create iso-surface.
	vtkNew<vtkContourFilter> contour;
	contour->SetInputData(volume);
	contour->SetValue(0, 50);

	// Create mapper.
	vtkNew<vtkPolyDataMapper> mapper;
	mapper->SetInputConnection(contour->GetOutputPort());
	mapper->ScalarVisibilityOff();

	// Create actor.
	vtkNew<vtkActor> actor;
	actor->SetMapper(mapper);
	actor->GetProperty()->SetColor(colors->GetColor3d("DodgerBlue").GetData());

	renderer->AddActor(actor);
	renderer->SetBackground(colors->GetColor3d("PaleGoldenrod").GetData());


	auto camera = renderer->GetActiveCamera();
	camera->SetPosition(-67.645167, -25.714343, 63.483516);
	camera->SetFocalPoint(3.224902, -4.398594, 29.552112);
	camera->SetViewUp(-0.232264, 0.965078, 0.121151);
	camera->SetDistance(81.414176);
	camera->SetClippingRange(18.428905, 160.896031);

	//��ӱ�����ɫ
	renderer->SetBackground(1, 1, 1);
	renderer->SetBackground2(0.529, 0.8078, 0.92157);
	renderer->SetGradientBackground(1);
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;//����һ��vtk����
	renderWindow->AddRenderer(renderer);//�ڴ����м�����Ⱦ��
	ui.openGLWidget->setRenderWindow(renderWindow);//��ʾ��vtk��
}

void VTK_OCC_Qt::Createpnt()
{
	//�����㲢��ʾ
	gp_Pnt aPnt(10, 10, 10);
	TopoDS_Shape aShape = BRepBuilderAPI_MakeVertex(aPnt);
	//Handle(AIS_Shape) aisShpae = new AIS_Shape(aShape);
	Handle(IVtkOCC_Shape) occShape = new IVtkOCC_Shape(aShape);
	vtkSmartPointer<IVtkTools_ShapeDataSource> occSource = vtkSmartPointer<IVtkTools_ShapeDataSource>::New();
	occSource->SetShape(occShape);

	mapper->SetInputConnection(occSource->GetOutputPort());

	actor->SetMapper(mapper);

	renderers->AddActor(actor);
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
	renderWindow->AddRenderer(renderers);//�ڴ����м�����Ⱦ��
	ui.openGLWidget->setRenderWindow(renderWindow);//��ʾ��vtk��
}

void VTK_OCC_Qt::Cereatlin()
{
}

void VTK_OCC_Qt::Cereatface()
{
}



vtkPolyData * VTK_OCC_Qt::convertShapeToVTK(const TopoDS_Shape & shape)
{
	Handle_IVtkOCC_Shape aShapeImpl = new IVtkOCC_Shape(shape);
	Handle_IVtkVTK_ShapeData aDataImpl = new IVtkVTK_ShapeData();
	Handle_IVtk_IShapeMesher aMesher = new IVtkOCC_ShapeMesher();
	aMesher->Build(aShapeImpl, aDataImpl);
	return aDataImpl->getVtkPolyData();
}

void VTK_OCC_Qt::displayShape(vtkPolyData * polyData, vtkSmartPointer<vtkTexture> texture)
{
	vtkNew<vtkPolyDataMapper> mapper;
	mapper->SetInputData(polyData);

	vtkNew<vtkActor> actor;
	actor->SetMapper(mapper);
	if (texture) {
		actor->SetTexture(texture);
	}

	renderers->AddActor(actor);
	renderers->SetBackground(1, 1, 1);
	renderers->SetBackground2(0.529, 0.8078, 0.92157);
	renderers->SetGradientBackground(1);
	renderWindow->Render();
}







