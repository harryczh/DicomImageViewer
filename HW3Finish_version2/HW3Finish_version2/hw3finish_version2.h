#ifndef HW3FINISH_VERSION2_H
#define HW3FINISH_VERSION2_H

#include <QtGui/QWidget>
#include "ui_HW3Finish_version2.h"

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVolume16Reader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkOutlineFilter.h>
#include <vtkCamera.h>
#include <vtkStripper.h>
#include <vtkLookupTable.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkProperty.h>
#include <vtkPolyDataNormals.h>
#include <vtkContourFilter.h>
#include <vtkImageData.h>
#include <vtkImageMapToColors.h>
#include <vtkImageActor.h>
#include <vtkSmartPointer.h>

#include <vtkTextActor.h>
#include <qlineedit.h>
#include <qmessagebox.h>

class HW3Finish_version2 : public QWidget
{
	Q_OBJECT

public:
	HW3Finish_version2(QWidget *parent = 0, Qt::WFlags flags = 0);
	~HW3Finish_version2();

private:
	Ui::HW3Finish_version2Class ui;
	
	//畫面調整
	void resizeEvent(QResizeEvent * event);

private:

	//設置渲染者
	vtkSmartPointer<vtkRenderer> Renderer_3D;
	vtkSmartPointer<vtkRenderer> Renderer_sagittal_LT;
	vtkSmartPointer<vtkRenderer> Renderer_coronal_AP;
	vtkSmartPointer<vtkRenderer> Renderer_axial;
	vtkSmartPointer<vtkVolume16Reader> v16_openfile;

	//設置畫面數據textactor
	//slicename
	vtkSmartPointer<vtkTextActor> slicename_textactor;
	
	//LT slice
	vtkSmartPointer<vtkTextActor> LT_slicevalue_textactor;
	//AP slice
	vtkSmartPointer<vtkTextActor> AP_slicevalue_textactor;
	//axial slice
	vtkSmartPointer<vtkTextActor> axial_slicevalue_textactor;

	//window
	vtkSmartPointer<vtkTextActor> windowname_textactor;
	vtkSmartPointer<vtkTextActor> windowvalue_textactor;
	//level
	vtkSmartPointer<vtkTextActor> levelname_textactor;
	vtkSmartPointer<vtkTextActor> levelvalue_textactor;
	

	//抽取皮膚
	vtkSmartPointer<vtkContourFilter> skinFilter;
	vtkSmartPointer<vtkPolyDataNormals> skinNormals;
	vtkSmartPointer<vtkStripper> skinStripper;
	vtkSmartPointer<vtkPolyDataMapper> skinMapper;
	vtkSmartPointer<vtkActor> skin_Actor;

	//抽取骨骼
	vtkSmartPointer<vtkContourFilter> boneFilter;
	vtkSmartPointer<vtkPolyDataNormals> boneNormals;
	vtkSmartPointer<vtkStripper> boneStripper;
	vtkSmartPointer<vtkPolyDataMapper> boneMapper;
	vtkSmartPointer<vtkActor> bone_Actor;
	
	//建構三個正交面
	//3D圖外框
	vtkSmartPointer<vtkOutlineFilter> outlineFilter;
	vtkSmartPointer<vtkPolyDataMapper> outlineMapper;
	vtkSmartPointer<vtkActor> outlineActor;

	//設置剖面
	vtkSmartPointer<vtkLookupTable> sagittal_table;
	vtkSmartPointer<vtkLookupTable> axial_table;
	vtkSmartPointer<vtkLookupTable> coronal_table;

	vtkSmartPointer<vtkImageMapToColors> sagittalColors_3D;
	vtkSmartPointer<vtkImageMapToColors> sagittalColors_2D;
	vtkSmartPointer<vtkImageActor> sagittal_ImageActor_3D;
	vtkSmartPointer<vtkImageActor> sagittal_ImageActor_2D;
	
	vtkSmartPointer<vtkImageMapToColors> axialColors_3D;
	vtkSmartPointer<vtkImageMapToColors> axialColors_2D;
	vtkSmartPointer<vtkImageActor> axial_ImageActor_3D;
	vtkSmartPointer<vtkImageActor> axial_ImageActor_2D;
	
	vtkSmartPointer<vtkImageMapToColors> coronalColors_3D;
	vtkSmartPointer<vtkImageMapToColors> coronalColors_2D;
	vtkSmartPointer<vtkImageActor> coronal_ImageActor_3D;
	vtkSmartPointer<vtkImageActor> coronal_ImageActor_2D;

	//設置相機
	vtkSmartPointer<vtkCamera> Camera_3D;
	vtkSmartPointer<vtkCamera> Camera_LT;
	vtkSmartPointer<vtkCamera> Camera_AP;
	vtkSmartPointer<vtkCamera> Camera_axil;

private slots:	
	//開啟檔案
	void Open_File(); 
	//void Open_Dicom_File();

	//跟新
	void Update();
	
	//調整ISO_Value
	void Skin_isovalue();
	void Skull_isovalue();
	
	//調整透明度
	void Skin_opacity();
	void Skull_opacity();

	//調整Skin顏色
	void Skin_color();
	void Skull_color();

	//Accept
	void Skin_accept();
	void Skull_accept();
	
	//調整剖面位置
	void Xslice(); 
	void Yslice();
	void Zslice();

	//Window_Level
	void Level();
	void Window();

	//正交剖面開關
	void Orthogonal_planes();

	//讀檔前關閉動作
	void Action();

	//顯示初始數值
	void Initial_value();
};

#endif // HW3Finish_version2_H
