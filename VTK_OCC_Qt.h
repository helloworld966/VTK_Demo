#pragma once

#include <QtWidgets/QMainWindow>
#include"QuadricVisualization.h"
#include "ui_VTK_OCC_Qt.h"
#include<QFileDialog>
#include"InteractorStyle.h"
#include<vtkPlaneSource.h>
//新加入HeadSlice
#include <vtkContourFilter.h>
#include <vtkExtractVOI.h>
#include <vtkMetaImageReader.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkStructuredPointsReader.h>//新加入IronIsoSurface
//新加入ComplexV
#include <vtkHedgeHog.h>
#include <vtkLookupTable.h>

//新加入Kitchen
#include<vtkLineSource.h>
#include <vtkPointData.h>
#include <vtkStreamTracer.h>
#include <vtkStructuredGrid.h>
#include <vtkStructuredGridGeometryFilter.h>
#include <vtkStructuredGridOutlineFilter.h>
#include <vtkStructuredGridReader.h>

//新加入张量轴
#include <vtkAxes.h>
#include <vtkConeSource.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkLookupTable.h>
#include <vtkOutlineFilter.h>
#include <vtkPointLoad.h>
#include <vtkProperty.h>
#include <vtkTensorGlyph.h>
#include <vtkTubeFilter.h>

//opencascade读取step文件,vtk显示，vtk头文件之前已经加过
#include <STEPControl_Reader.hxx>
#include <Standard_Integer.hxx>
#include <TopoDS_Shape.hxx>
#include <IFSelect_ReturnStatus.hxx>
#include <IFSelect_PrintCount.hxx>
#include <IVtkVTK_ShapeData.hxx>
#include <IVtkOCC_ShapeMesher.hxx>
#include <AIS_Shape.hxx>
#include <STEPControl_Reader.hxx>
#include <TopoDS_Shape.hxx>
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>
#include <AIS_InteractiveContext.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <OpenGl_GraphicDriver.hxx>


//新增洛伦兹方程
#include <vtkMinimalStandardRandomSequence.h>
#include <vtkShortArray.h>
#include <vtkStructuredPoints.h>

//新增读取IGES文件头文件
#include <IGESControl_Reader.hxx> 
#include <BRepBuilderAPI_Transform.hxx>
#include <Bnd_Box.hxx>
#include <BRepBndLib.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>

#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepFilletAPI_MakeChamfer.hxx>

#include <BRepOffsetAPI_MakePipe.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>

#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Common.hxx>

#include<vtkJPEGReader.h>
#include<vtkTexture.h>
#include <QMouseEvent>

#include <Aspect_Handle.hxx>
#include <gp_Pnt.hxx>


#include <BRepBuilderAPI_MakeVertex.hxx>//创建点
#include <BRepBuilderAPI_MakeEdge.hxx>//创建线
#include <gce_MakePln.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>//创建面
class VTK_OCC_Qt : public QMainWindow
{
	Q_OBJECT

public:
	VTK_OCC_Qt(QWidget *parent = Q_NULLPTR);

protected:
	void mousePressEvent(QMouseEvent *event) override;
public slots:
	
	void initializeGL();
	void display();
	void play();
	void HeadSlice();
	void IronIsoSurface();
	void ComplexV();
	void Kitchen();
	void TensorAxes();
	void MakeLogLUT(vtkLookupTable* lut);
	void read_step();//读取step文件
	void read_IGS();
	void makebox();
	void makecone();
	void Lorenz();
	void Createpnt();
	void Cereatlin();
	void Cereatface();
	vtkPolyData* convertShapeToVTK(const TopoDS_Shape& shape);
	void displayShape(vtkPolyData* polyData, vtkSmartPointer<vtkTexture> texture = nullptr);
	


private:
	Ui::VTK_OCC_QtClass ui;
	vtkSmartPointer<vtkRenderer> renderers;
	vtkSmartPointer<vtkPolyDataMapper> mapper;
	vtkSmartPointer<vtkActor> actor;
	
	vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;
	QuadricVisualization quadricVisualization;



};
