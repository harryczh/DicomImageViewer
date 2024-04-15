#include "HW3Finish_version2.h"

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

#include <QVTKWidget.h> 
#include <qstring.h>
#include <qpalette.h>
#include <qcolordialog.h>
#include <qcolor.h>
#include <qfiledialog.h>
#include <qfile.h>
#include <qlayout.h>
#include "qsettings.h"
#include <qstringlist.h>
#include <qdebug.h>
#include <qmouseeventtransition.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkTextSource.h>
#include <vtkTextMapper.h>
#include <string.h>
#include <sstream>

using namespace std;


HW3Finish_version2::HW3Finish_version2(QWidget *parent, Qt::WFlags flags)	: QWidget(parent, flags)
{
	ui.setupUi(this);
	
	//建立繪製者
	Renderer_3D = vtkSmartPointer<vtkRenderer>::New();  
	Renderer_sagittal_LT = vtkSmartPointer<vtkRenderer>::New();
	Renderer_coronal_AP = vtkSmartPointer<vtkRenderer>::New();
	Renderer_axial = vtkSmartPointer<vtkRenderer>::New();
	
	//讀檔
	v16_openfile = vtkSmartPointer<vtkVolume16Reader>::New();  //讀入的是二維圖像


	//抽取皮膚
	skinFilter = vtkSmartPointer<vtkContourFilter>::New();  //定義輪廓(參考5-1)
	//渲染程序
	skinNormals = vtkSmartPointer<vtkPolyDataNormals>::New();  //繪製法線(計算網格頂點法向量)(參考5-3)
	skinStripper = vtkSmartPointer<vtkStripper>::New();  //三角帶連接
	skinMapper = vtkSmartPointer<vtkPolyDataMapper>::New();  //定義映射器(幾何)
	skin_Actor = vtkSmartPointer<vtkActor>::New();  //參考4-4


	//抽取骨頭
	boneFilter = vtkSmartPointer<vtkContourFilter>::New();
	//渲染程序
	boneNormals = vtkSmartPointer<vtkPolyDataNormals>::New();
	boneStripper = vtkSmartPointer<vtkStripper>::New();
	boneMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	bone_Actor = vtkSmartPointer<vtkActor>::New();


	//定義外框
	outlineFilter = vtkSmartPointer<vtkOutlineFilter>::New();
	//渲染程序
	outlineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	outlineActor = vtkSmartPointer<vtkActor>::New();


	//定義剖面
	sagittal_table = vtkSmartPointer<vtkLookupTable>::New();
	axial_table = vtkSmartPointer<vtkLookupTable>::New();
	coronal_table = vtkSmartPointer<vtkLookupTable>::New();
	//LT view 渲染程序
	sagittalColors_3D = vtkSmartPointer<vtkImageMapToColors>::New();
	sagittalColors_2D = vtkSmartPointer<vtkImageMapToColors>::New();	
	sagittal_ImageActor_3D = vtkSmartPointer<vtkImageActor>::New();  //想在3D渲染窗口中顯示圖像時，需要使用的是vtkImageActor(是一個包含Actor和Mapper對象的合成類)
	//vtkImageActor是一個三維圖像渲染Actor，通過紋理映射將圖像映射到一個多邊形上進行顯示。(參考2_5-1)
	//使用vtkImageActor較vtkImageViewer2要復雜一些，需要建立完整的渲染管線：包括vtkImageActor，vtkRender，vtkRenderWindow，vtkRenderWindowInteractor管線。
	//另外，作為圖像二維瀏覽器，不需要在三維空間中進行旋轉操作，因此還需要為vtkRenderWindow定義一個vtkInteractorStyleImage對象。
	sagittal_ImageActor_2D = vtkSmartPointer<vtkImageActor>::New(); 
	//axial view 渲染程序
	axialColors_3D = vtkSmartPointer<vtkImageMapToColors>::New();
	axialColors_2D = vtkSmartPointer<vtkImageMapToColors>::New();
	axial_ImageActor_3D = vtkSmartPointer<vtkImageActor>::New();
	axial_ImageActor_2D = vtkSmartPointer<vtkImageActor>::New();
	//AP view 渲染程序
	coronalColors_3D = vtkSmartPointer<vtkImageMapToColors>::New();
	coronalColors_2D = vtkSmartPointer<vtkImageMapToColors>::New();
	coronal_ImageActor_3D = vtkSmartPointer<vtkImageActor>::New();
	coronal_ImageActor_2D = vtkSmartPointer<vtkImageActor>::New();


	//定義相機
	Camera_3D = vtkSmartPointer<vtkCamera>::New();
	Camera_LT = vtkSmartPointer<vtkCamera>::New();  //定義攝像機
	Camera_AP = vtkSmartPointer<vtkCamera>::New();  //定義攝像機
	Camera_axil = vtkSmartPointer<vtkCamera>::New();  //定義攝像機
	

	//設置畫面數據textactor
	//slicename
	slicename_textactor = vtkSmartPointer<vtkTextActor> ::New();	
	//LT slice value
	LT_slicevalue_textactor = vtkSmartPointer<vtkTextActor> ::New();
	//AP slice value
	AP_slicevalue_textactor = vtkSmartPointer<vtkTextActor> ::New();
	//axial slice value
	axial_slicevalue_textactor = vtkSmartPointer<vtkTextActor> ::New();
	//window
	windowname_textactor = vtkSmartPointer<vtkTextActor> ::New();
	windowvalue_textactor = vtkSmartPointer<vtkTextActor> ::New();
	//level
	levelname_textactor = vtkSmartPointer<vtkTextActor> ::New();
	levelvalue_textactor = vtkSmartPointer<vtkTextActor> ::New();


	//設置view位置
	Renderer_3D ->SetViewport(0.0, 0.5, 0.5, 1.0);  //(xmin,ymin,xmax,ymax)
	Renderer_sagittal_LT ->SetViewport(0.5, 0.5, 1.0, 1.0);
	Renderer_coronal_AP ->SetViewport(0.0, 0.0, 0.5, 0.5);
	Renderer_axial ->SetViewport(0.5, 0.0, 1.0, 0.5);
	

	//將繪製者(器)加入窗口，QT有內鍵窗口(qvtkWidget)
	ui.qvtkWidget ->GetRenderWindow() ->AddRenderer(Renderer_3D);
	ui.qvtkWidget ->GetRenderWindow() ->AddRenderer(Renderer_sagittal_LT);
	ui.qvtkWidget ->GetRenderWindow() ->AddRenderer(Renderer_coronal_AP);
	ui.qvtkWidget ->GetRenderWindow() ->AddRenderer(Renderer_axial);

	
	//關閉view互動
	Renderer_sagittal_LT ->SetInteractive(false);
	Renderer_coronal_AP ->SetInteractive(false);
	Renderer_axial ->SetInteractive(false);
	//Renderer_sagittal_LT ->InteractiveOff();

	Update();
	ui.qvtkWidget ->update();	
}

HW3Finish_version2::~HW3Finish_version2()
{

}

//畫面調整
void HW3Finish_version2 :: resizeEvent(QResizeEvent * event)
{
	//ui.label ->setText(QString ::number(slicename_textactor->GetWidth()));
	
	//slice name
	slicename_textactor->SetInput ("Slice : ");
	slicename_textactor->SetPosition ( 0, ui.qvtkWidget ->height() / 2 - 15);
	
	//LT slice value			
	LT_slicevalue_textactor->SetPosition ( 35, ui.qvtkWidget ->height() / 2 - 15);	
	//AP slice value
	AP_slicevalue_textactor->SetPosition ( 35, ui.qvtkWidget ->height() / 2 - 15);	
	//axial slice value
	axial_slicevalue_textactor->SetPosition ( 35, ui.qvtkWidget ->height() / 2 - 15);
	
	//window
	windowname_textactor->SetInput ("Window : ");
	windowname_textactor->SetPosition ( ui.qvtkWidget ->width() / 2 - 85, 15);
	windowvalue_textactor->SetPosition ( ui.qvtkWidget ->width() / 2 - 30, 15);
	//level
	levelname_textactor->SetInput ("Level : ");
	levelname_textactor->SetPosition ( ui.qvtkWidget ->width()/2-85, 0);
	levelvalue_textactor->SetPosition ( ui.qvtkWidget ->width()/2-30, 0);
	
	Update();
}

//跟新
void HW3Finish_version2 :: Update()
{
	//Renderer_3D->SetActiveCamera(Three_D_Camera);
	//Renderer_sagittal_LT->SetActiveCamera(LT_Camera);
	//Renderer_coronal_AP->SetActiveCamera(AP_Camera);
	//Renderer_axial->SetActiveCamera(axial_Camera);

	Renderer_3D ->ResetCamera ();
	Renderer_sagittal_LT ->ResetCamera ();
	Renderer_coronal_AP ->ResetCamera ();
	Renderer_axial ->ResetCamera ();

	//Renderer_3D->ResetCameraClippingRange ();
	//Renderer_sagittal_LT->ResetCameraClippingRange ();
	//Renderer_coronal_AP->ResetCameraClippingRange ();
	//Renderer_axial->ResetCameraClippingRange ();

	ui.qvtkWidget ->GetRenderWindow() ->Render();
	//ui.qvtkWidget_2 ->GetRenderWindow() ->Render();
	//ui.qvtkWidget_3 ->GetRenderWindow() ->Render();
	//ui.qvtkWidget_4 ->GetRenderWindow() ->Render();
}

//調整ISO_Value 調整完要按Accept
void HW3Finish_version2 :: Skin_isovalue()
{
	skinFilter ->SetValue(0, ui.Skin_isovalue_slider ->value());
	//顯示數值
	QString s = QString::number(ui.Skin_isovalue_slider ->value());
	QFont font = ui.Skin_isovalue_value ->font();
	font.setPointSize(12);
	ui.Skin_isovalue_value ->setFont(font);
	ui.Skin_isovalue_value ->setText(s);
	//Update();	
}
void HW3Finish_version2 :: Skull_isovalue()
{
	boneFilter ->SetValue(0, ui.Skull_isovalue_slider ->value());
	//顯示數值
	QString s = QString::number(ui.Skull_isovalue_slider->value());
	QFont font = ui.Skull_isovalue_value ->font();
	font.setPointSize(12);
	ui.Skull_isovalue_value ->setFont(font);
	ui.Skull_isovalue_value ->setText(s);
	//Update();
}

//調整透明度
void HW3Finish_version2 :: Skin_opacity()
{
	double dvalue = ui.Skin_opacity_slider ->value();
	skin_Actor ->GetProperty() ->SetOpacity(dvalue/10);
	//顯示數值
	QString s = QString::number(dvalue/10);
	QFont font = ui.Skin_opacity_value ->font();
	font.setPointSize(12);
	ui.Skin_opacity_value ->setFont(font);
	ui.Skin_opacity_value ->setText(s);
	Update();
}
void HW3Finish_version2 :: Skull_opacity()
{
	double dvalue = ui.Skull_opacity_slider ->value();
	bone_Actor ->GetProperty() ->SetOpacity(dvalue/10);
	//bone_Actor->GetProperty()->SetOpacity((double)ui.Skull_opacity_slider ->value()/100);
	//顯示數值
	QString s = QString::number(dvalue/10);
	QFont font = ui.Skull_opacity_value ->font();
	font.setPointSize(12);
	ui.Skull_opacity_value ->setFont(font);
	ui.Skull_opacity_value ->setText(s);
	Update();
}

//調整顏色
void HW3Finish_version2 :: Skin_color()
{
	QColor color = QColorDialog::getColor(Qt::black, this, "Pick a color",  QColorDialog::DontUseNativeDialog);
	double red = color.red();
	double green = color.green();
	double blue = color.blue();
	//顯示顏色
	QPalette palette = ui.Skin_color_show ->palette();
	palette.setColor(ui.Skin_color_show ->backgroundRole(), color);   
	ui.Skin_color_show ->setAutoFillBackground(true);
	ui.Skin_color_show ->setPalette(palette);

	skin_Actor ->GetProperty() ->SetDiffuseColor(red/255, green/255, blue/255);
	Update();
}
void HW3Finish_version2 :: Skull_color()
{
	QColor color = QColorDialog::getColor(Qt::black, this, "Pick a color",  QColorDialog::DontUseNativeDialog);
	double red = color.red();
	double green = color.green();
	double blue = color.blue();
	//顯示顏色
	QPalette palette = ui.Skull_color_show ->palette();
	palette.setColor(ui.Skull_color_show ->backgroundRole(), color);   
	ui.Skull_color_show ->setAutoFillBackground(true);
	ui.Skull_color_show ->setPalette(palette);

	bone_Actor ->GetProperty() ->SetDiffuseColor(red/255, green/255, blue/255);
	Update();
}
	
//Accept
void HW3Finish_version2 :: Skin_accept()
{
	Renderer_3D ->ResetCamera ();
	Renderer_sagittal_LT ->ResetCamera ();
	Renderer_coronal_AP ->ResetCamera ();
	Renderer_axial ->ResetCamera ();

	//Renderer_3D ->ResetCameraClippingRange ();
	//Renderer_sagittal_LT ->ResetCameraClippingRange ();
	//Renderer_coronal_AP ->ResetCameraClippingRange ();
	//Renderer_axial ->ResetCameraClippingRange ();

	ui.qvtkWidget ->GetRenderWindow() ->Render();
	//ui.qvtkWidget_2 ->GetRenderWindow() ->Render();
	//ui.qvtkWidget_3 ->GetRenderWindow() ->Render();
	//ui.qvtkWidget_4 ->GetRenderWindow() ->Render();
}
void HW3Finish_version2 :: Skull_accept()
{
	Renderer_3D ->ResetCamera ();
	Renderer_sagittal_LT ->ResetCamera ();
	Renderer_coronal_AP ->ResetCamera ();
	Renderer_axial ->ResetCamera ();

	//Renderer_3D->ResetCameraClippingRange ();
	//Renderer_sagittal_LT->ResetCameraClippingRange ();
	//Renderer_coronal_AP->ResetCameraClippingRange ();
	//Renderer_axial->ResetCameraClippingRange ();

	ui.qvtkWidget ->GetRenderWindow() ->Render();
	//ui.qvtkWidget_2 ->GetRenderWindow() ->Render();
	//ui.qvtkWidget_3 ->GetRenderWindow() ->Render();
	//ui.qvtkWidget_4 ->GetRenderWindow() ->Render();
}

//調整剖面位置
void HW3Finish_version2 :: Xslice()
{
	sagittal_ImageActor_3D ->SetDisplayExtent(ui.Xslice_position ->value(),ui.Xslice_position ->value(), 0,63, 0,92);
	sagittal_ImageActor_2D ->SetDisplayExtent(ui.Xslice_position ->value(),ui.Xslice_position ->value(), 0,63, 0,92);		
	
	//view數據
	int ixslice = ui.Xslice_position ->value();
	stringstream ssxslice;	
	ssxslice << ixslice; //把int型態變數寫入到stringstream
	string sxslice;
	ssxslice >>  sxslice;  //透過串流運算子寫到string類別即可
	const char * ccxslice = sxslice.c_str();
	LT_slicevalue_textactor->SetInput (ccxslice);

	Update();	
}
void HW3Finish_version2 :: Yslice()
{
	coronal_ImageActor_3D ->SetDisplayExtent(0,63, ui.Yslice_position ->value(),ui.Yslice_position ->value(), 0,92);
	coronal_ImageActor_2D ->SetDisplayExtent(0,63, ui.Yslice_position ->value(),ui.Yslice_position ->value(), 0,92);
	//view數據
	int iyslice = ui.Yslice_position ->value();
	stringstream ssyslice;	
	ssyslice << iyslice; //把int型態變數寫入到stringstream
	string syslice;
	ssyslice >>  syslice;  //透過串流運算子寫到string類別即可
	const char * ccyslice = syslice.c_str();
	AP_slicevalue_textactor->SetInput (ccyslice);
	Update();
}
void HW3Finish_version2 :: Zslice()
{
	axial_ImageActor_3D ->SetDisplayExtent(0,63, 0,63, ui.Zslice_position ->value(), ui.Zslice_position ->value());
	axial_ImageActor_2D ->SetDisplayExtent(0,63, 0,63, ui.Zslice_position ->value(), ui.Zslice_position ->value());
	//view數據
	int izslice = ui.Zslice_position ->value();
	stringstream sszslice;	
	sszslice << izslice; //把int型態變數寫入到stringstream
	string szslice;
	sszslice >>  szslice;  //透過串流運算子寫到string類別即可
	const char * cczslice = szslice.c_str();
	axial_slicevalue_textactor->SetInput (cczslice);
	Update();
}

//調整Window_Level
void HW3Finish_version2 :: Level()
{
	if(ui.Level_slider ->value() >= (ui.Window_slider ->value()) / 2)
	{
		double min = (ui.Level_slider ->value()) - (ui.Window_slider ->value()) / 2;
		double max = (ui.Level_slider ->value()) + (ui.Window_slider ->value()) / 2;
		sagittal_table ->SetTableRange (min, max);
		axial_table ->SetTableRange (min, max);
		coronal_table ->SetTableRange (min, max);
		//顯示數值
		QString QSlevel = QString::number(ui.Level_slider ->value());
		QFont font = ui.Level_value ->font();
		font.setPointSize(12);
		ui.Level_value ->setFont(font);
		ui.Level_value ->setText(QSlevel);
		//顯示數值(view)
		int ilevelvalue = ui.Level_slider ->value();		
		stringstream sstrlevelvalue;	
		sstrlevelvalue << ilevelvalue; //把int型態變數寫入到stringstream
		string slevelvalue;
		sstrlevelvalue >>  slevelvalue;  //透過串流運算子寫到string類別即可
		const char * cclevel = slevelvalue.c_str();
		levelvalue_textactor->SetInput (cclevel);
	}
		Update();
}
void HW3Finish_version2 :: Window()
{
	if(ui.Level_slider ->value() >= (ui.Window_slider ->value()) / 2)
	{
		double min = (ui.Level_slider ->value()) - (ui.Window_slider ->value()) / 2;
		double max = (ui.Level_slider ->value()) + (ui.Window_slider ->value()) / 2;
		sagittal_table->SetTableRange (min, max);
		axial_table->SetTableRange (min, max);
		coronal_table->SetTableRange (min, max);
		//顯示數值(控制欄)
		QString QSwindow = QString::number(ui.Window_slider ->value());
		QFont font = ui.Window_value ->font();
		font.setPointSize(12);		
		ui.Window_value ->setFont(font);
		ui.Window_value ->setText(QSwindow);
		//顯示數值(view)
		int iwinvalue = ui.Window_slider ->value();		
		stringstream sstrwinvalue;	
		sstrwinvalue << iwinvalue; //把int型態變數寫入到stringstream
		string swinvalue;
		sstrwinvalue >>  swinvalue;  //透過串流運算子寫到string類別即可
		const char * ccwindow = swinvalue.c_str();
		windowvalue_textactor->SetInput (ccwindow);
	}
	Update();
}

//正交剖面開關
void HW3Finish_version2 :: Orthogonal_planes()
{
	if(ui.Orthogonal_planes ->checkState())
	{
		//Renderer_3D ->AddActor(sagittal_ImageActor_3D);
		//Renderer_3D ->AddActor(axial_ImageActor_3D);
		//Renderer_3D ->AddActor(coronal_ImageActor_3D);
		sagittal_ImageActor_3D ->VisibilityOn();
		axial_ImageActor_3D ->VisibilityOn();
		coronal_ImageActor_3D ->VisibilityOn();
	}
	else
	{
		//Renderer_3D ->RemoveActor(sagittal_ImageActor_3D);
		//Renderer_3D ->RemoveActor(axial_ImageActor_3D);
		//Renderer_3D ->RemoveActor(coronal_ImageActor_3D);
		sagittal_ImageActor_3D ->VisibilityOff();
		axial_ImageActor_3D ->VisibilityOff();
		coronal_ImageActor_3D ->VisibilityOff();
	}
	Update();
}

//讀檔後才可動作
void HW3Finish_version2 :: Action()
{
	ui.Skin_isovalue_slider ->setEnabled(true);
	ui.Skin_opacity_slider ->setEnabled(true);

	ui.Skull_isovalue_slider ->setEnabled(true);
	ui.Skull_opacity_slider ->setEnabled(true);

	ui.Skin_color_button ->setEnabled(true);
	ui.Skin_accept_button ->setEnabled(true);

	ui.Skull_color_button ->setEnabled(true);
	ui.Skull_accept_button ->setEnabled(true);

	ui.Xslice_position ->setEnabled(true);
	ui.Yslice_position ->setEnabled(true);
	ui.Zslice_position ->setEnabled(true);

	ui.Orthogonal_planes ->setEnabled(true);
	ui.Level_slider ->setEnabled(true);
	ui.Window_slider ->setEnabled(true);

	Update();
}

//顯示初始數值
void HW3Finish_version2 :: Initial_value()
{	
	//skin iso value
	QString QSskin_isovalue = QString::number(500);
	ui.Skin_isovalue_value ->setText(QSskin_isovalue);
	//拉桿位置
	double dskin_isovalue = 500;
	ui.Skin_isovalue_slider ->setValue(dskin_isovalue);

	//skull iso value
	QString QSskull_isovalue = QString::number(1150);
	ui.Skull_isovalue_value ->setText(QSskull_isovalue);
	//拉桿位置
	double dskull_isovalue = 1150;
	ui.Skull_isovalue_slider ->setValue(dskull_isovalue);

	//skin opacity
	QString skin_opacity_value = QString::number(0.5);
	ui.Skin_opacity_value ->setText(skin_opacity_value);
	//拉桿位置
	double dskin_opacity_value = 5;
	ui.Skin_opacity_slider ->setValue(dskin_opacity_value);

	//skull opacity
	QString skull_opacity_value = QString::number(0.5);
	ui.Skull_opacity_value ->setText(skull_opacity_value);
	//拉桿位置
	double dskull_opacity_value = 5;
	ui.Skull_opacity_slider ->setValue(dskull_opacity_value);
		
	//skin顏色	
	double dskincolor[3];
 	dskincolor[0] = skin_Actor ->GetProperty() ->GetDiffuseColor()[0];
	dskincolor[1] = skin_Actor ->GetProperty() ->GetDiffuseColor()[1];
	dskincolor[2] = skin_Actor ->GetProperty() ->GetDiffuseColor()[2];
	QPalette QPskincolor = ui.Skin_color_show ->palette();
	QPskincolor.setColor(ui.Skin_color_show ->backgroundRole(), QColor(dskincolor[0]*255,dskincolor[1]*255,dskincolor[2]*255)); 
	ui.Skin_color_show ->setAutoFillBackground(true);
	ui.Skin_color_show ->setPalette(QPskincolor);
	
	//bone顏色	
	double dskullcolor[3];
 	dskullcolor[0] = bone_Actor ->GetProperty() ->GetDiffuseColor()[0];
	dskullcolor[1] = bone_Actor ->GetProperty() ->GetDiffuseColor()[1];
	dskullcolor[2] = bone_Actor ->GetProperty() ->GetDiffuseColor()[2];
	QPalette QPskullcolor = ui.Skull_color_show ->palette();
	QPskullcolor.setColor(ui.Skull_color_show ->backgroundRole(), QColor(dskullcolor[0]*255,dskullcolor[1]*255,dskullcolor[2]*255)); 
	ui.Skull_color_show ->setAutoFillBackground(true);
	ui.Skull_color_show ->setPalette(QPskullcolor);
	
	//xslice position value
	double dxslice_position = 32;
	ui.Xslice_position ->setValue(dxslice_position);
			
	//yslice position value
	double dyslice_position = 32;
	ui.Yslice_position ->setValue(dyslice_position);	
	
	//zslice position value
	double dzslice_position = 46;
	ui.Zslice_position ->setValue(dzslice_position);
	
	//level value
	QString QSlevel_value = QString::number(1000);
	ui.Level_value ->setText(QSlevel_value);
	//拉桿位置
	double dlevel_value = 1000;
	ui.Level_slider ->setValue(dlevel_value);
	
	//window value
	QString QSwindow_value = QString::number(2000);
	ui.Window_value ->setText(QSwindow_value);
	//拉桿位置
	double dwindow_value = 2000;
	ui.Window_slider ->setValue(dwindow_value);
		
	//正交平面勾選
	ui.Orthogonal_planes ->setChecked(true);

	Update();
}

/*
//開啟Dicom檔案
void HW3Finish_version2 :: Open_Dicom_File()
{
	//重複開檔
	Renderer_3D ->RemoveAllViewProps();
	Renderer_sagittal_LT ->RemoveAllViewProps();
	Renderer_coronal_AP ->RemoveAllViewProps();
	Renderer_axial ->RemoveAllViewProps();

	//file dialog
	char *ch;

	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"E:\\VTK_Toolkits\\VTKData5.10.1\\Data\\SawbonHeadCTDCM");
	int a = fileName.length();
	//char *ch;
	QByteArray ba = fileName.toLatin1();    
	ch=ba.data();
	if(!fileName.isEmpty())
	{		
		for(int i=0; i<=48 ; i++)
		{
			ch[i] = ch[i];
			if (i==48)
			{
				for(int i=49; i<=a; i++)
				{
					ch[i]='\0';
				}
			}
		}
		//ui.label ->setText(ch);

		//vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();  //建立繪製窗口
		//renWin->AddRenderer(Renderer_3D);  //將繪製者加入窗口

		//設置窗口的交互器(與窗口的互動模式)(參考下圓柱範例)
		//vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();  
		//iren->SetRenderWindow(renWin);  //設置窗口為reWin(與reWin連接)

		//設定窗口背景(.2, .3, .4)
		Renderer_3D ->SetBackground(0,0,0);  
		Renderer_sagittal_LT ->SetBackground(0,0,0); 
		Renderer_coronal_AP ->SetBackground(0,0,0); 
		Renderer_axial ->SetBackground(0,0,0); 

		//設置窗口打小
		//ui.qvtkWidget ->GetRenderWindow() ->SetSize(250,250);  
		//ui.qvtkWidget_2 ->GetRenderWindow() ->SetSize(250,250);
		//ui.qvtkWidget_3 ->GetRenderWindow() ->SetSize(250,250);
		//ui.qvtkWidget_4 ->GetRenderWindow() ->SetSize(250,250);

		//數據讀入
		v16_openfile ->SetDataDimensions(64,64);  //設置圖像像素值
		v16_openfile ->SetImageRange(1, 93);  //設置圖片數量(第1~93張)
		v16_openfile ->SetDataByteOrderToLittleEndian();
		//v16_openfile ->SetFilePrefix ("E:\\VTK_Tool\\vtkdata-5.10.1\\Data\\headsq\\quarter");  //圖檔位置
		v16_openfile ->SetFilePrefix(ch);	
		//v16_openfile->SetFilePrefix (argv[1]);
		v16_openfile ->SetDataSpacing (3.2, 3.2, 1.5);  //設置像素間距
		v16_openfile ->Update();


		vtkSmartPointer<vtkDICOMImageReader> DicomImageReader = vtkSmartPointer<vtkDICOMImageReader>::New();
		DicomImageReader->SetFileName(inputFilename.c_str());
		DicomImageReader->Update();

		vtkSmartPointer<vtkImageViewer2> imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
		imageViewer->SetInputConnection(reader->GetOutputPort());
		vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
		imageViewer->SetupInteractor(renderWindowInteractor);
		imageViewer->Render();
		imageViewer->GetRenderer()->ResetCamera();
		imageViewer->Render();



		//抽取皮膚
		//vtkContourFilter
		skinFilter ->SetInputConnection(DicomImageReader ->GetOutputPort());  //Filter輸入輸出的連接匹配(參考4-3) //設置讀入數據源
		skinFilter ->SetValue(0, 500);  //設置閥值(二維圖像重建)(輪廓數和輪廓值)(參考5-1)
		skinFilter ->Update();

		//vtkPolyDataNormals	
		skinNormals ->SetInputConnection(skinFilter ->GetOutputPort());
		skinNormals ->SetFeatureAngle(60.0);
		skinNormals ->Update();

		//vtkStripper	
		skinStripper ->SetInputConnection(skinNormals ->GetOutputPort());
		skinStripper ->Update();

		//vtkPolyDataMapper
		skinMapper ->SetInputConnection(skinStripper ->GetOutputPort());
		skinMapper ->ScalarVisibilityOff();  //參考4-4
		//Actor的屬性中關於顏色的設置只有當Actor的Mapper沒有標量數據(ScalarData)時才起作用。
		//缺省情況下，Mapper輸入的標量數據會對Actor進行著色，而Actor的顏色設置會被忽略。
		//如果要忽略這些標量數據，可以使用方法ScalarVisibilityOff()

		//vtkActor
		skin_Actor ->SetMapper(skinMapper);  //設置皮膚幾何數據屬性(一個Actor的幾何是通過SetMapper()方法指定的)
		skin_Actor ->GetProperty() ->SetDiffuseColor(1, .49, .25);  //設置皮膚顏色屬性
		skin_Actor ->GetProperty() ->SetSpecular(.3);  //設置反射率
		skin_Actor ->GetProperty() ->SetSpecularPower(20);  //設置反射光強度
		//Actor裡有一個類型為vtkProperty的實例，主要是用來控制Actor的顯示屬性
		//我們通過方法GetProperty()間接引用Actor的屬性。或者，我們也可以先實例化一個vtkProperty對象，然後把它設置到Actor中



		//抽取骨骼
		//vtkContourFilter
		boneFilter ->SetInputConnection(DicomImageReader ->GetOutputPort());
		boneFilter ->SetValue(0, 1150);
		boneFilter ->Update();

		//vtkPolyDataNormals
		boneNormals ->SetInputConnection(boneFilter ->GetOutputPort());
		boneNormals ->SetFeatureAngle(60.0);
		boneNormals ->Update();

		//vtkStripper
		boneStripper ->SetInputConnection(boneNormals ->GetOutputPort());
		boneStripper ->Update();

		//vtkPolyDataMapper
		boneMapper ->SetInputConnection(boneStripper ->GetOutputPort());
		boneMapper ->ScalarVisibilityOff();

		//vtkActor
		bone_Actor->SetMapper(boneMapper);
		bone_Actor->GetProperty() ->SetDiffuseColor(1, 1, .9412);



		//設置外框
		//vtkOutlineFilter
		outlineFilter ->SetInputConnection(DicomImageReader ->GetOutputPort());
		outlineFilter ->Update();

		//外框Mapper	
		outlineMapper ->SetInputConnection(outlineFilter ->GetOutputPort());

		//外框Actor	
		outlineActor ->SetMapper(outlineMapper);
		outlineActor ->GetProperty() ->SetColor(0,0,0);



		//設置剖面
		//設置LT剖面(矢)(sagittal)vtkLookupTable	
		sagittal_table ->SetTableRange (0, 2000);
		sagittal_table ->SetSaturationRange (0, 0);  //設置切面顏色
		sagittal_table ->SetHueRange (0, 0);
		sagittal_table ->SetValueRange (0, 1);
		sagittal_table ->Build(); //effective built

		//設置軸剖面(axial)vtkLookupTable	
		axial_table ->SetTableRange (0, 2000);
		axial_table ->SetHueRange (0, 1);
		axial_table ->SetSaturationRange (1, 1);
		axial_table ->SetValueRange (1, 1);
		axial_table ->Build(); //effective built

		//設置AP剖面(冠)(coronal)vtkLookupTable	
		coronal_table ->SetTableRange (0, 2000);
		coronal_table ->SetHueRange (.6, .6);
		coronal_table ->SetSaturationRange (0, 1);
		coronal_table ->SetValueRange (1, 1);
		coronal_table ->Build(); //effective built


		//LT view(3D)vtkImageMapToColors	
		sagittalColors_3D->SetInputConnection(DicomImageReader ->GetOutputPort());
		sagittalColors_3D->SetLookupTable(sagittal_table);
		sagittalColors_3D->Update();	
		//LT view(2D)	
		sagittalColors_2D ->SetInputConnection(DicomImageReader ->GetOutputPort());
		sagittalColors_2D ->SetLookupTable(sagittal_table);
		sagittalColors_2D ->Update();
		//LT view actor(3D)
		sagittal_ImageActor_3D ->SetInput(sagittalColors_3D ->GetOutput());
		sagittal_ImageActor_3D ->SetDisplayExtent(32,32, 0,63, 0,92);  //設置切面位置，顯示範圍(xmin,xmax,ymin,ymax,zmin,zmax)	
		//LT view actor(2D)	 
		sagittal_ImageActor_2D ->SetInput(sagittalColors_2D ->GetOutput());
		sagittal_ImageActor_2D ->SetDisplayExtent(32,32, 0,63, 0,92);  

		//axial view(3D)	
		axialColors_3D ->SetInputConnection(DicomImageReader ->GetOutputPort());
		axialColors_3D ->SetLookupTable(axial_table);
		axialColors_3D ->Update();	
		//axial view(2D)
		axialColors_2D ->SetInputConnection(DicomImageReader ->GetOutputPort());
		axialColors_2D ->SetLookupTable(axial_table);
		axialColors_2D ->Update();
		//axial view actor(3D)	
		axial_ImageActor_3D ->SetInput(axialColors_3D ->GetOutput());
		axial_ImageActor_3D ->SetDisplayExtent(0,63, 0,63, 46,46);	
		//axial view actor(2D)	
		axial_ImageActor_2D ->SetInput(axialColors_2D ->GetOutput());
		axial_ImageActor_2D ->SetDisplayExtent(0,63, 0,63, 46,46);

		//AP view(3D)	
		coronalColors_3D ->SetInputConnection(DicomImageReader ->GetOutputPort());
		coronalColors_3D ->SetLookupTable(coronal_table);
		coronalColors_3D ->Update();	
		//AP view(2D)	
		coronalColors_2D ->SetInputConnection(DicomImageReader ->GetOutputPort());
		coronalColors_2D ->SetLookupTable(coronal_table);
		coronalColors_2D ->Update();
		//AP view actor(3D)	
		coronal_ImageActor_3D ->SetInput(coronalColors_3D ->GetOutput());
		coronal_ImageActor_3D ->SetDisplayExtent(0,63, 32,32, 0,92);	
		//AP view actor(2D)	
		coronal_ImageActor_2D ->SetInput(coronalColors_2D ->GetOutput());
		coronal_ImageActor_2D ->SetDisplayExtent(0,63, 32,32, 0,92);



		//設置攝像機
		//3D  
		Camera_3D ->SetViewUp (0, 0, -1);  //設置攝像機方向(控置相機"向上"的方向)
		Camera_3D ->SetPosition (0, 1, 0);  //光源位置(世界座系定義)
		Camera_3D ->SetFocalPoint (0, 0, 0);  //設置焦點座標(光照方向)(世界座系定義)
		Camera_3D ->ComputeViewPlaneNormal();  //以當前設置的相機位置和焦點重置視平面的法向量
		//以下兩個方法都不會改變相機的View-up向量(參考4-3)
		Camera_3D ->Azimuth(30.0);  //會在球坐標下以焦點為中心沿著經度方向(Longitude Direction)旋轉指定的角度
		Camera_3D ->Elevation(30.0);  //是沿著緯度方向(LatitudeDirection)旋轉

		//LT	
		Camera_LT ->SetViewUp (0, 0, -1);  //設置攝像機方向
		Camera_LT ->SetPosition (1, 0, 0);  //光源位置 物體看相機
		Camera_LT ->SetFocalPoint (0, 0, 0);  //設置焦點座標
		Camera_LT ->ComputeViewPlaneNormal();
		Camera_LT ->Azimuth(0.0);
		Camera_LT ->Elevation(0.0);

		//AP	
		Camera_AP ->SetViewUp (0, 0, -1);  //設置攝像機方向
		Camera_AP ->SetPosition (0, 1, 0);  //光源位置 物體看相機
		Camera_AP ->SetFocalPoint (0, 0, 0);  //設置焦點座標
		Camera_AP ->ComputeViewPlaneNormal();
		Camera_AP ->Azimuth(0.0);
		Camera_AP ->Elevation(0.0);

		//axial	
		Camera_axil ->SetViewUp (0, -1, 0);  //設置攝像機方向
		Camera_axil ->SetPosition (0, 0, -1);  //光源位置 物體看相機
		Camera_axil ->SetFocalPoint (0, 0, 0);  //設置焦點座標
		Camera_axil ->ComputeViewPlaneNormal();
		Camera_axil ->Azimuth(0.0);
		Camera_axil ->Elevation(0.0);



		//添加演員開始繪製
		//3D
		Renderer_3D ->AddActor(outlineActor);
		Renderer_3D ->AddActor(sagittal_ImageActor_3D);
		Renderer_3D ->AddActor(axial_ImageActor_3D);
		Renderer_3D ->AddActor(coronal_ImageActor_3D);
		Renderer_3D ->AddActor(skin_Actor);
		Renderer_3D ->AddActor(bone_Actor);
		//2D
		Renderer_sagittal_LT ->AddActor(sagittal_ImageActor_2D);
		Renderer_axial ->AddActor(axial_ImageActor_2D);
		Renderer_coronal_AP ->AddActor(coronal_ImageActor_2D);



		//畫面數據
		//LT slice
		Renderer_sagittal_LT->AddActor2D ( slicename_textactor );
		Renderer_sagittal_LT->AddActor2D ( LT_slicevalue_textactor );
		//AP slice
		Renderer_coronal_AP->AddActor2D ( slicename_textactor );
		Renderer_coronal_AP->AddActor2D ( AP_slicevalue_textactor );
		//axial slice
		Renderer_axial->AddActor2D ( slicename_textactor );
		Renderer_axial->AddActor2D ( axial_slicevalue_textactor );	

		//LT window
		Renderer_sagittal_LT->AddActor2D ( windowname_textactor );
		Renderer_sagittal_LT->AddActor2D ( windowvalue_textactor );
		//AP window
		Renderer_coronal_AP->AddActor2D ( windowname_textactor );
		Renderer_coronal_AP->AddActor2D ( windowvalue_textactor );
		//axial window
		Renderer_axial->AddActor2D ( windowname_textactor );
		Renderer_axial->AddActor2D ( windowvalue_textactor );

		//LT level
		Renderer_sagittal_LT->AddActor2D ( levelname_textactor );
		Renderer_sagittal_LT->AddActor2D ( levelvalue_textactor );
		//AP level
		Renderer_coronal_AP->AddActor2D ( levelname_textactor );
		Renderer_coronal_AP->AddActor2D ( levelvalue_textactor );
		//axial level
		Renderer_axial->AddActor2D ( levelname_textactor );
		Renderer_axial->AddActor2D ( levelvalue_textactor );



		//骨頭可視化關閉
		//bone ->VisibilityOff();

		//設置透明度(Actor的透明度)
		skin_Actor ->GetProperty() ->SetOpacity(0.5);
		bone_Actor ->GetProperty() ->SetOpacity(0.5);


		//繪製者設置攝像機
		Renderer_3D ->SetActiveCamera(Camera_3D);  //保存和恢復相機狀態(也就是重置視圖)(參考4-3)
		Renderer_sagittal_LT ->SetActiveCamera(Camera_LT);
		Renderer_coronal_AP ->SetActiveCamera(Camera_AP);
		Renderer_axial ->SetActiveCamera(Camera_axil);


		//用渲染器的ResetCamera()方法把該相機設置到渲染器中，ResetCamera()方法可以沿著視向量移動相機，這樣，渲染器裡所有的Actor都會可見
		Renderer_3D ->ResetCamera();
		Renderer_sagittal_LT ->ResetCamera();
		Renderer_coronal_AP ->ResetCamera();
		Renderer_axial ->ResetCamera();


		//aCamera->Dolly(1.5);  //沿著視平面的法向方向移動相機，或者放大、收縮渲染場景中可見的actor
		//另外有Zoom()方法是通過改變視角(ViewAngle)(即SetViewAngle()方法)使得物體放大顯示


		Renderer_3D ->ResetCameraClippingRange();
		Renderer_sagittal_LT ->ResetCameraClippingRange();
		Renderer_coronal_AP ->ResetCameraClippingRange();
		Renderer_axial ->ResetCameraClippingRange();


		//實現渲染
		ui.qvtkWidget ->GetRenderWindow() ->Render();
		//ui.qvtkWidget_2 ->GetRenderWindow() ->Render();
		//ui.qvtkWidget_3 ->GetRenderWindow() ->Render();
		//ui.qvtkWidget_4 ->GetRenderWindow() ->Render();
	}	
	Action();  //開啟動作
	Initial_value();  //顯示初值

	Update();

	//interact with data
	//iren->Initialize();
	//iren->Start(); 
	//system("pause");
	//return EXIT_SUCCESS;
}
*/

//開啟V16檔案


void HW3Finish_version2 :: Open_File()
{ 	


	//file dialog
	char *ch;

	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"C:\\Users\\czh\\Desktop\\headsq");
	int a = fileName.length();
	//char *ch;
	QByteArray ba = fileName.toLatin1();    
	ch=ba.data();
	if(!fileName.isEmpty())
	{		
		//重複開檔
		Renderer_3D ->RemoveAllViewProps();
		Renderer_sagittal_LT ->RemoveAllViewProps();
		Renderer_coronal_AP ->RemoveAllViewProps();
		Renderer_axial ->RemoveAllViewProps();

		//擷取檔案位置
		for(int i=0; i<=34 ; i++)
		{
			ch[i] = ch[i];
			if (i==34)
			{
				for(int i=35; i<=a; i++)
				{
					ch[i]='\0';
				}
			}
		}
		ui.label ->setText(ch);

		//vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();  //建立繪製窗口
		//renWin->AddRenderer(Renderer_3D);  //將繪製者加入窗口

		//設置窗口的交互器(與窗口的互動模式)(參考下圓柱範例)
		//vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();  
		//iren->SetRenderWindow(renWin);  //設置窗口為reWin(與reWin連接)

		//設定窗口背景(.2, .3, .4)
		Renderer_3D ->SetBackground(0,0,0);  
		Renderer_sagittal_LT ->SetBackground(0,0,0); 
		Renderer_coronal_AP ->SetBackground(0,0,0); 
		Renderer_axial ->SetBackground(0,0,0); 

		//設置窗口打小
		//ui.qvtkWidget ->GetRenderWindow() ->SetSize(250,250);  
		//ui.qvtkWidget_2 ->GetRenderWindow() ->SetSize(250,250);
		//ui.qvtkWidget_3 ->GetRenderWindow() ->SetSize(250,250);
		//ui.qvtkWidget_4 ->GetRenderWindow() ->SetSize(250,250);

		//數據讀入
		v16_openfile ->SetDataDimensions(64,64);  //設置圖像像素值
		v16_openfile ->SetImageRange(1, 93);  //設置圖片數量(第1~93張)
		v16_openfile ->SetDataByteOrderToLittleEndian();
		//v16_openfile ->SetFilePrefix ("E:\\VTK_Tool\\vtkdata-5.10.1\\Data\\headsq\\quarter");  //圖檔位置
		v16_openfile ->SetFilePrefix(ch);	
		//v16_openfile->SetFilePrefix (argv[1]);
		v16_openfile ->SetDataSpacing (3.2, 3.2, 1.5);  //設置像素間距
		v16_openfile ->Update();



		//抽取皮膚
		//vtkContourFilter
		skinFilter ->SetInputConnection(v16_openfile ->GetOutputPort());  //Filter輸入輸出的連接匹配(參考4-3) //設置讀入數據源
		skinFilter ->SetValue(0, 500);  //設置閥值(二維圖像重建)(輪廓數和輪廓值)(參考5-1)
		skinFilter ->Update();

		//vtkPolyDataNormals	
		skinNormals ->SetInputConnection(skinFilter ->GetOutputPort());
		skinNormals ->SetFeatureAngle(60.0);
		skinNormals ->Update();

		//vtkStripper	
		skinStripper ->SetInputConnection(skinNormals ->GetOutputPort());
		skinStripper ->Update();

		//vtkPolyDataMapper
		skinMapper ->SetInputConnection(skinStripper ->GetOutputPort());
		skinMapper ->ScalarVisibilityOff();  //參考4-4
		//Actor的屬性中關於顏色的設置只有當Actor的Mapper沒有標量數據(ScalarData)時才起作用。
		//缺省情況下，Mapper輸入的標量數據會對Actor進行著色，而Actor的顏色設置會被忽略。
		//如果要忽略這些標量數據，可以使用方法ScalarVisibilityOff()

		//vtkActor
		skin_Actor ->SetMapper(skinMapper);  //設置皮膚幾何數據屬性(一個Actor的幾何是通過SetMapper()方法指定的)
		skin_Actor ->GetProperty() ->SetDiffuseColor(1, .49, .25);  //設置皮膚顏色屬性
		skin_Actor ->GetProperty() ->SetSpecular(.3);  //設置反射率
		skin_Actor ->GetProperty() ->SetSpecularPower(20);  //設置反射光強度
		//Actor裡有一個類型為vtkProperty的實例，主要是用來控制Actor的顯示屬性
		//我們通過方法GetProperty()間接引用Actor的屬性。或者，我們也可以先實例化一個vtkProperty對象，然後把它設置到Actor中



		//抽取骨骼
		//vtkContourFilter
		boneFilter ->SetInputConnection(v16_openfile ->GetOutputPort());
		boneFilter ->SetValue(0, 1150);
		boneFilter ->Update();

		//vtkPolyDataNormals
		boneNormals ->SetInputConnection(boneFilter ->GetOutputPort());
		boneNormals ->SetFeatureAngle(60.0);
		boneNormals ->Update();

		//vtkStripper
		boneStripper ->SetInputConnection(boneNormals ->GetOutputPort());
		boneStripper ->Update();

		//vtkPolyDataMapper
		boneMapper ->SetInputConnection(boneStripper ->GetOutputPort());
		boneMapper ->ScalarVisibilityOff();

		//vtkActor
		bone_Actor->SetMapper(boneMapper);
		bone_Actor->GetProperty() ->SetDiffuseColor(1, 1, .9412);



		//設置外框
		//vtkOutlineFilter
		outlineFilter ->SetInputConnection(v16_openfile ->GetOutputPort());
		outlineFilter ->Update();

		//外框Mapper	
		outlineMapper ->SetInputConnection(outlineFilter ->GetOutputPort());

		//外框Actor	
		outlineActor ->SetMapper(outlineMapper);
		outlineActor ->GetProperty() ->SetColor(0,0,0);



		//設置剖面
		//設置LT剖面(矢)(sagittal)vtkLookupTable	
		sagittal_table ->SetTableRange (0, 2000);
		sagittal_table ->SetSaturationRange (0, 0);  //設置切面顏色
		sagittal_table ->SetHueRange (0, 0);
		sagittal_table ->SetValueRange (0, 1);
		sagittal_table ->Build(); //effective built

		//設置軸剖面(axial)vtkLookupTable	
		axial_table ->SetTableRange (0, 2000);
		axial_table ->SetHueRange (0, 1);
		axial_table ->SetSaturationRange (1, 1);
		axial_table ->SetValueRange (1, 1);
		axial_table ->Build(); //effective built

		//設置AP剖面(冠)(coronal)vtkLookupTable	
		coronal_table ->SetTableRange (0, 2000);
		coronal_table ->SetHueRange (.6, .6);
		coronal_table ->SetSaturationRange (0, 1);
		coronal_table ->SetValueRange (1, 1);
		coronal_table ->Build(); //effective built


		//LT view(3D)vtkImageMapToColors	
		sagittalColors_3D->SetInputConnection(v16_openfile ->GetOutputPort());
		sagittalColors_3D->SetLookupTable(sagittal_table);
		sagittalColors_3D->Update();	
		//LT view(2D)	
		sagittalColors_2D ->SetInputConnection(v16_openfile ->GetOutputPort());
		sagittalColors_2D ->SetLookupTable(sagittal_table);
		sagittalColors_2D ->Update();
		//LT view actor(3D)
		sagittal_ImageActor_3D ->SetInput(sagittalColors_3D ->GetOutput());
		sagittal_ImageActor_3D ->SetDisplayExtent(32,32, 0,63, 0,92);  //設置切面位置，顯示範圍(xmin,xmax,ymin,ymax,zmin,zmax)	
		//LT view actor(2D)	 
		sagittal_ImageActor_2D ->SetInput(sagittalColors_2D ->GetOutput());
		sagittal_ImageActor_2D ->SetDisplayExtent(32,32, 0,63, 0,92);  

		//axial view(3D)	
		axialColors_3D ->SetInputConnection(v16_openfile ->GetOutputPort());
		axialColors_3D ->SetLookupTable(axial_table);
		axialColors_3D ->Update();	
		//axial view(2D)
		axialColors_2D ->SetInputConnection(v16_openfile ->GetOutputPort());
		axialColors_2D ->SetLookupTable(axial_table);
		axialColors_2D ->Update();
		//axial view actor(3D)	
		axial_ImageActor_3D ->SetInput(axialColors_3D ->GetOutput());
		axial_ImageActor_3D ->SetDisplayExtent(0,63, 0,63, 46,46);	
		//axial view actor(2D)	
		axial_ImageActor_2D ->SetInput(axialColors_2D ->GetOutput());
		axial_ImageActor_2D ->SetDisplayExtent(0,63, 0,63, 46,46);

		//AP view(3D)	
		coronalColors_3D ->SetInputConnection(v16_openfile ->GetOutputPort());
		coronalColors_3D ->SetLookupTable(coronal_table);
		coronalColors_3D ->Update();	
		//AP view(2D)	
		coronalColors_2D ->SetInputConnection(v16_openfile ->GetOutputPort());
		coronalColors_2D ->SetLookupTable(coronal_table);
		coronalColors_2D ->Update();
		//AP view actor(3D)	
		coronal_ImageActor_3D ->SetInput(coronalColors_3D ->GetOutput());
		coronal_ImageActor_3D ->SetDisplayExtent(0,63, 32,32, 0,92);	
		//AP view actor(2D)	
		coronal_ImageActor_2D ->SetInput(coronalColors_2D ->GetOutput());
		coronal_ImageActor_2D ->SetDisplayExtent(0,63, 32,32, 0,92);



		//設置攝像機
		//3D  
		Camera_3D ->SetViewUp (0, 0, -1);  //設置攝像機方向(控置相機"向上"的方向)
		Camera_3D ->SetPosition (0, 1, 0);  //光源位置(世界座系定義)
		Camera_3D ->SetFocalPoint (0, 0, 0);  //設置焦點座標(光照方向)(世界座系定義)
		Camera_3D ->ComputeViewPlaneNormal();  //以當前設置的相機位置和焦點重置視平面的法向量
		//以下兩個方法都不會改變相機的View-up向量(參考4-3)
		Camera_3D ->Azimuth(30.0);  //會在球坐標下以焦點為中心沿著經度方向(Longitude Direction)旋轉指定的角度
		Camera_3D ->Elevation(30.0);  //是沿著緯度方向(LatitudeDirection)旋轉

		//LT	
		Camera_LT ->SetViewUp (0, 0, -1);  //設置攝像機方向
		Camera_LT ->SetPosition (1, 0, 0);  //光源位置 物體看相機
		Camera_LT ->SetFocalPoint (0, 0, 0);  //設置焦點座標
		Camera_LT ->ComputeViewPlaneNormal();
		Camera_LT ->Azimuth(0.0);
		Camera_LT ->Elevation(0.0);

		//AP	
		Camera_AP ->SetViewUp (0, 0, -1);  //設置攝像機方向
		Camera_AP ->SetPosition (0, 1, 0);  //光源位置 物體看相機
		Camera_AP ->SetFocalPoint (0, 0, 0);  //設置焦點座標
		Camera_AP ->ComputeViewPlaneNormal();
		Camera_AP ->Azimuth(0.0);
		Camera_AP ->Elevation(0.0);

		//axial	
		Camera_axil ->SetViewUp (0, -1, 0);  //設置攝像機方向
		Camera_axil ->SetPosition (0, 0, -1);  //光源位置 物體看相機
		Camera_axil ->SetFocalPoint (0, 0, 0);  //設置焦點座標
		Camera_axil ->ComputeViewPlaneNormal();
		Camera_axil ->Azimuth(0.0);
		Camera_axil ->Elevation(0.0);



		//添加演員開始繪製
		//3D
		Renderer_3D ->AddActor(outlineActor);
		Renderer_3D ->AddActor(sagittal_ImageActor_3D);
		Renderer_3D ->AddActor(axial_ImageActor_3D);
		Renderer_3D ->AddActor(coronal_ImageActor_3D);
		Renderer_3D ->AddActor(skin_Actor);
		Renderer_3D ->AddActor(bone_Actor);
		//2D
		Renderer_sagittal_LT ->AddActor(sagittal_ImageActor_2D);
		Renderer_axial ->AddActor(axial_ImageActor_2D);
		Renderer_coronal_AP ->AddActor(coronal_ImageActor_2D);



		//畫面數據
		//LT slice
		Renderer_sagittal_LT->AddActor2D ( slicename_textactor );
		Renderer_sagittal_LT->AddActor2D ( LT_slicevalue_textactor );
		//AP slice
		Renderer_coronal_AP->AddActor2D ( slicename_textactor );
		Renderer_coronal_AP->AddActor2D ( AP_slicevalue_textactor );
		//axial slice
		Renderer_axial->AddActor2D ( slicename_textactor );
		Renderer_axial->AddActor2D ( axial_slicevalue_textactor );	

		//LT window
		Renderer_sagittal_LT->AddActor2D ( windowname_textactor );
		Renderer_sagittal_LT->AddActor2D ( windowvalue_textactor );
		//AP window
		Renderer_coronal_AP->AddActor2D ( windowname_textactor );
		Renderer_coronal_AP->AddActor2D ( windowvalue_textactor );
		//axial window
		Renderer_axial->AddActor2D ( windowname_textactor );
		Renderer_axial->AddActor2D ( windowvalue_textactor );

		//LT level
		Renderer_sagittal_LT->AddActor2D ( levelname_textactor );
		Renderer_sagittal_LT->AddActor2D ( levelvalue_textactor );
		//AP level
		Renderer_coronal_AP->AddActor2D ( levelname_textactor );
		Renderer_coronal_AP->AddActor2D ( levelvalue_textactor );
		//axial level
		Renderer_axial->AddActor2D ( levelname_textactor );
		Renderer_axial->AddActor2D ( levelvalue_textactor );



		//骨頭可視化關閉
		//bone ->VisibilityOff();

		//設置透明度(Actor的透明度)
		skin_Actor ->GetProperty() ->SetOpacity(0.5);
		bone_Actor ->GetProperty() ->SetOpacity(0.5);


		//繪製者設置攝像機
		Renderer_3D ->SetActiveCamera(Camera_3D);  //保存和恢復相機狀態(也就是重置視圖)(參考4-3)
		Renderer_sagittal_LT ->SetActiveCamera(Camera_LT);
		Renderer_coronal_AP ->SetActiveCamera(Camera_AP);
		Renderer_axial ->SetActiveCamera(Camera_axil);


		//用渲染器的ResetCamera()方法把該相機設置到渲染器中，ResetCamera()方法可以沿著視向量移動相機，這樣，渲染器裡所有的Actor都會可見
		Renderer_3D ->ResetCamera();
		Renderer_sagittal_LT ->ResetCamera();
		Renderer_coronal_AP ->ResetCamera();
		Renderer_axial ->ResetCamera();


		//aCamera->Dolly(1.5);  //沿著視平面的法向方向移動相機，或者放大、收縮渲染場景中可見的actor
		//另外有Zoom()方法是通過改變視角(ViewAngle)(即SetViewAngle()方法)使得物體放大顯示


		Renderer_3D ->ResetCameraClippingRange();
		Renderer_sagittal_LT ->ResetCameraClippingRange();
		Renderer_coronal_AP ->ResetCameraClippingRange();
		Renderer_axial ->ResetCameraClippingRange();


		//實現渲染
		ui.qvtkWidget ->GetRenderWindow() ->Render();
		//ui.qvtkWidget_2 ->GetRenderWindow() ->Render();
		//ui.qvtkWidget_3 ->GetRenderWindow() ->Render();
		//ui.qvtkWidget_4 ->GetRenderWindow() ->Render();
	}	
	Action();  //開啟動作
	Initial_value();  //顯示初值

	Update();

	//interact with data
	//iren->Initialize();
	//iren->Start(); 
	//system("pause");
	//return EXIT_SUCCESS;
}
