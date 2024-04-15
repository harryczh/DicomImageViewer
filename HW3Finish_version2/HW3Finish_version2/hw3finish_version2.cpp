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
	
	//�إ�ø�s��
	Renderer_3D = vtkSmartPointer<vtkRenderer>::New();  
	Renderer_sagittal_LT = vtkSmartPointer<vtkRenderer>::New();
	Renderer_coronal_AP = vtkSmartPointer<vtkRenderer>::New();
	Renderer_axial = vtkSmartPointer<vtkRenderer>::New();
	
	//Ū��
	v16_openfile = vtkSmartPointer<vtkVolume16Reader>::New();  //Ū�J���O�G���Ϲ�


	//����ֽ�
	skinFilter = vtkSmartPointer<vtkContourFilter>::New();  //�w�q����(�Ѧ�5-1)
	//��V�{��
	skinNormals = vtkSmartPointer<vtkPolyDataNormals>::New();  //ø�s�k�u(�p����泻�I�k�V�q)(�Ѧ�5-3)
	skinStripper = vtkSmartPointer<vtkStripper>::New();  //�T���a�s��
	skinMapper = vtkSmartPointer<vtkPolyDataMapper>::New();  //�w�q�M�g��(�X��)
	skin_Actor = vtkSmartPointer<vtkActor>::New();  //�Ѧ�4-4


	//������Y
	boneFilter = vtkSmartPointer<vtkContourFilter>::New();
	//��V�{��
	boneNormals = vtkSmartPointer<vtkPolyDataNormals>::New();
	boneStripper = vtkSmartPointer<vtkStripper>::New();
	boneMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	bone_Actor = vtkSmartPointer<vtkActor>::New();


	//�w�q�~��
	outlineFilter = vtkSmartPointer<vtkOutlineFilter>::New();
	//��V�{��
	outlineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	outlineActor = vtkSmartPointer<vtkActor>::New();


	//�w�q�孱
	sagittal_table = vtkSmartPointer<vtkLookupTable>::New();
	axial_table = vtkSmartPointer<vtkLookupTable>::New();
	coronal_table = vtkSmartPointer<vtkLookupTable>::New();
	//LT view ��V�{��
	sagittalColors_3D = vtkSmartPointer<vtkImageMapToColors>::New();
	sagittalColors_2D = vtkSmartPointer<vtkImageMapToColors>::New();	
	sagittal_ImageActor_3D = vtkSmartPointer<vtkImageActor>::New();  //�Q�b3D��V���f����ܹϹ��ɡA�ݭn�ϥΪ��OvtkImageActor(�O�@�ӥ]�tActor�MMapper��H���X����)
	//vtkImageActor�O�@�ӤT���Ϲ���VActor�A�q�L���z�M�g�N�Ϲ��M�g��@�Ӧh��ΤW�i����ܡC(�Ѧ�2_5-1)
	//�ϥ�vtkImageActor��vtkImageViewer2�n�_���@�ǡA�ݭn�إߧ��㪺��V�޽u�G�]�AvtkImageActor�AvtkRender�AvtkRenderWindow�AvtkRenderWindowInteractor�޽u�C
	//�t�~�A�@���Ϲ��G���s�����A���ݭn�b�T���Ŷ����i�����ާ@�A�]���ٻݭn��vtkRenderWindow�w�q�@��vtkInteractorStyleImage��H�C
	sagittal_ImageActor_2D = vtkSmartPointer<vtkImageActor>::New(); 
	//axial view ��V�{��
	axialColors_3D = vtkSmartPointer<vtkImageMapToColors>::New();
	axialColors_2D = vtkSmartPointer<vtkImageMapToColors>::New();
	axial_ImageActor_3D = vtkSmartPointer<vtkImageActor>::New();
	axial_ImageActor_2D = vtkSmartPointer<vtkImageActor>::New();
	//AP view ��V�{��
	coronalColors_3D = vtkSmartPointer<vtkImageMapToColors>::New();
	coronalColors_2D = vtkSmartPointer<vtkImageMapToColors>::New();
	coronal_ImageActor_3D = vtkSmartPointer<vtkImageActor>::New();
	coronal_ImageActor_2D = vtkSmartPointer<vtkImageActor>::New();


	//�w�q�۾�
	Camera_3D = vtkSmartPointer<vtkCamera>::New();
	Camera_LT = vtkSmartPointer<vtkCamera>::New();  //�w�q�ṳ��
	Camera_AP = vtkSmartPointer<vtkCamera>::New();  //�w�q�ṳ��
	Camera_axil = vtkSmartPointer<vtkCamera>::New();  //�w�q�ṳ��
	

	//�]�m�e���ƾ�textactor
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


	//�]�mview��m
	Renderer_3D ->SetViewport(0.0, 0.5, 0.5, 1.0);  //(xmin,ymin,xmax,ymax)
	Renderer_sagittal_LT ->SetViewport(0.5, 0.5, 1.0, 1.0);
	Renderer_coronal_AP ->SetViewport(0.0, 0.0, 0.5, 0.5);
	Renderer_axial ->SetViewport(0.5, 0.0, 1.0, 0.5);
	

	//�Nø�s��(��)�[�J���f�AQT�����䵡�f(qvtkWidget)
	ui.qvtkWidget ->GetRenderWindow() ->AddRenderer(Renderer_3D);
	ui.qvtkWidget ->GetRenderWindow() ->AddRenderer(Renderer_sagittal_LT);
	ui.qvtkWidget ->GetRenderWindow() ->AddRenderer(Renderer_coronal_AP);
	ui.qvtkWidget ->GetRenderWindow() ->AddRenderer(Renderer_axial);

	
	//����view����
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

//�e���վ�
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

//��s
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

//�վ�ISO_Value �վ㧹�n��Accept
void HW3Finish_version2 :: Skin_isovalue()
{
	skinFilter ->SetValue(0, ui.Skin_isovalue_slider ->value());
	//��ܼƭ�
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
	//��ܼƭ�
	QString s = QString::number(ui.Skull_isovalue_slider->value());
	QFont font = ui.Skull_isovalue_value ->font();
	font.setPointSize(12);
	ui.Skull_isovalue_value ->setFont(font);
	ui.Skull_isovalue_value ->setText(s);
	//Update();
}

//�վ�z����
void HW3Finish_version2 :: Skin_opacity()
{
	double dvalue = ui.Skin_opacity_slider ->value();
	skin_Actor ->GetProperty() ->SetOpacity(dvalue/10);
	//��ܼƭ�
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
	//��ܼƭ�
	QString s = QString::number(dvalue/10);
	QFont font = ui.Skull_opacity_value ->font();
	font.setPointSize(12);
	ui.Skull_opacity_value ->setFont(font);
	ui.Skull_opacity_value ->setText(s);
	Update();
}

//�վ��C��
void HW3Finish_version2 :: Skin_color()
{
	QColor color = QColorDialog::getColor(Qt::black, this, "Pick a color",  QColorDialog::DontUseNativeDialog);
	double red = color.red();
	double green = color.green();
	double blue = color.blue();
	//����C��
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
	//����C��
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

//�վ�孱��m
void HW3Finish_version2 :: Xslice()
{
	sagittal_ImageActor_3D ->SetDisplayExtent(ui.Xslice_position ->value(),ui.Xslice_position ->value(), 0,63, 0,92);
	sagittal_ImageActor_2D ->SetDisplayExtent(ui.Xslice_position ->value(),ui.Xslice_position ->value(), 0,63, 0,92);		
	
	//view�ƾ�
	int ixslice = ui.Xslice_position ->value();
	stringstream ssxslice;	
	ssxslice << ixslice; //��int���A�ܼƼg�J��stringstream
	string sxslice;
	ssxslice >>  sxslice;  //�z�L��y�B��l�g��string���O�Y�i
	const char * ccxslice = sxslice.c_str();
	LT_slicevalue_textactor->SetInput (ccxslice);

	Update();	
}
void HW3Finish_version2 :: Yslice()
{
	coronal_ImageActor_3D ->SetDisplayExtent(0,63, ui.Yslice_position ->value(),ui.Yslice_position ->value(), 0,92);
	coronal_ImageActor_2D ->SetDisplayExtent(0,63, ui.Yslice_position ->value(),ui.Yslice_position ->value(), 0,92);
	//view�ƾ�
	int iyslice = ui.Yslice_position ->value();
	stringstream ssyslice;	
	ssyslice << iyslice; //��int���A�ܼƼg�J��stringstream
	string syslice;
	ssyslice >>  syslice;  //�z�L��y�B��l�g��string���O�Y�i
	const char * ccyslice = syslice.c_str();
	AP_slicevalue_textactor->SetInput (ccyslice);
	Update();
}
void HW3Finish_version2 :: Zslice()
{
	axial_ImageActor_3D ->SetDisplayExtent(0,63, 0,63, ui.Zslice_position ->value(), ui.Zslice_position ->value());
	axial_ImageActor_2D ->SetDisplayExtent(0,63, 0,63, ui.Zslice_position ->value(), ui.Zslice_position ->value());
	//view�ƾ�
	int izslice = ui.Zslice_position ->value();
	stringstream sszslice;	
	sszslice << izslice; //��int���A�ܼƼg�J��stringstream
	string szslice;
	sszslice >>  szslice;  //�z�L��y�B��l�g��string���O�Y�i
	const char * cczslice = szslice.c_str();
	axial_slicevalue_textactor->SetInput (cczslice);
	Update();
}

//�վ�Window_Level
void HW3Finish_version2 :: Level()
{
	if(ui.Level_slider ->value() >= (ui.Window_slider ->value()) / 2)
	{
		double min = (ui.Level_slider ->value()) - (ui.Window_slider ->value()) / 2;
		double max = (ui.Level_slider ->value()) + (ui.Window_slider ->value()) / 2;
		sagittal_table ->SetTableRange (min, max);
		axial_table ->SetTableRange (min, max);
		coronal_table ->SetTableRange (min, max);
		//��ܼƭ�
		QString QSlevel = QString::number(ui.Level_slider ->value());
		QFont font = ui.Level_value ->font();
		font.setPointSize(12);
		ui.Level_value ->setFont(font);
		ui.Level_value ->setText(QSlevel);
		//��ܼƭ�(view)
		int ilevelvalue = ui.Level_slider ->value();		
		stringstream sstrlevelvalue;	
		sstrlevelvalue << ilevelvalue; //��int���A�ܼƼg�J��stringstream
		string slevelvalue;
		sstrlevelvalue >>  slevelvalue;  //�z�L��y�B��l�g��string���O�Y�i
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
		//��ܼƭ�(������)
		QString QSwindow = QString::number(ui.Window_slider ->value());
		QFont font = ui.Window_value ->font();
		font.setPointSize(12);		
		ui.Window_value ->setFont(font);
		ui.Window_value ->setText(QSwindow);
		//��ܼƭ�(view)
		int iwinvalue = ui.Window_slider ->value();		
		stringstream sstrwinvalue;	
		sstrwinvalue << iwinvalue; //��int���A�ܼƼg�J��stringstream
		string swinvalue;
		sstrwinvalue >>  swinvalue;  //�z�L��y�B��l�g��string���O�Y�i
		const char * ccwindow = swinvalue.c_str();
		windowvalue_textactor->SetInput (ccwindow);
	}
	Update();
}

//����孱�}��
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

//Ū�ɫ�~�i�ʧ@
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

//��ܪ�l�ƭ�
void HW3Finish_version2 :: Initial_value()
{	
	//skin iso value
	QString QSskin_isovalue = QString::number(500);
	ui.Skin_isovalue_value ->setText(QSskin_isovalue);
	//�Ա��m
	double dskin_isovalue = 500;
	ui.Skin_isovalue_slider ->setValue(dskin_isovalue);

	//skull iso value
	QString QSskull_isovalue = QString::number(1150);
	ui.Skull_isovalue_value ->setText(QSskull_isovalue);
	//�Ա��m
	double dskull_isovalue = 1150;
	ui.Skull_isovalue_slider ->setValue(dskull_isovalue);

	//skin opacity
	QString skin_opacity_value = QString::number(0.5);
	ui.Skin_opacity_value ->setText(skin_opacity_value);
	//�Ա��m
	double dskin_opacity_value = 5;
	ui.Skin_opacity_slider ->setValue(dskin_opacity_value);

	//skull opacity
	QString skull_opacity_value = QString::number(0.5);
	ui.Skull_opacity_value ->setText(skull_opacity_value);
	//�Ա��m
	double dskull_opacity_value = 5;
	ui.Skull_opacity_slider ->setValue(dskull_opacity_value);
		
	//skin�C��	
	double dskincolor[3];
 	dskincolor[0] = skin_Actor ->GetProperty() ->GetDiffuseColor()[0];
	dskincolor[1] = skin_Actor ->GetProperty() ->GetDiffuseColor()[1];
	dskincolor[2] = skin_Actor ->GetProperty() ->GetDiffuseColor()[2];
	QPalette QPskincolor = ui.Skin_color_show ->palette();
	QPskincolor.setColor(ui.Skin_color_show ->backgroundRole(), QColor(dskincolor[0]*255,dskincolor[1]*255,dskincolor[2]*255)); 
	ui.Skin_color_show ->setAutoFillBackground(true);
	ui.Skin_color_show ->setPalette(QPskincolor);
	
	//bone�C��	
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
	//�Ա��m
	double dlevel_value = 1000;
	ui.Level_slider ->setValue(dlevel_value);
	
	//window value
	QString QSwindow_value = QString::number(2000);
	ui.Window_value ->setText(QSwindow_value);
	//�Ա��m
	double dwindow_value = 2000;
	ui.Window_slider ->setValue(dwindow_value);
		
	//���業���Ŀ�
	ui.Orthogonal_planes ->setChecked(true);

	Update();
}

/*
//�}��Dicom�ɮ�
void HW3Finish_version2 :: Open_Dicom_File()
{
	//���ƶ}��
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

		//vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();  //�إ�ø�s���f
		//renWin->AddRenderer(Renderer_3D);  //�Nø�s�̥[�J���f

		//�]�m���f���椬��(�P���f�����ʼҦ�)(�ѦҤU��W�d��)
		//vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();  
		//iren->SetRenderWindow(renWin);  //�]�m���f��reWin(�PreWin�s��)

		//�]�w���f�I��(.2, .3, .4)
		Renderer_3D ->SetBackground(0,0,0);  
		Renderer_sagittal_LT ->SetBackground(0,0,0); 
		Renderer_coronal_AP ->SetBackground(0,0,0); 
		Renderer_axial ->SetBackground(0,0,0); 

		//�]�m���f���p
		//ui.qvtkWidget ->GetRenderWindow() ->SetSize(250,250);  
		//ui.qvtkWidget_2 ->GetRenderWindow() ->SetSize(250,250);
		//ui.qvtkWidget_3 ->GetRenderWindow() ->SetSize(250,250);
		//ui.qvtkWidget_4 ->GetRenderWindow() ->SetSize(250,250);

		//�ƾ�Ū�J
		v16_openfile ->SetDataDimensions(64,64);  //�]�m�Ϲ�������
		v16_openfile ->SetImageRange(1, 93);  //�]�m�Ϥ��ƶq(��1~93�i)
		v16_openfile ->SetDataByteOrderToLittleEndian();
		//v16_openfile ->SetFilePrefix ("E:\\VTK_Tool\\vtkdata-5.10.1\\Data\\headsq\\quarter");  //���ɦ�m
		v16_openfile ->SetFilePrefix(ch);	
		//v16_openfile->SetFilePrefix (argv[1]);
		v16_openfile ->SetDataSpacing (3.2, 3.2, 1.5);  //�]�m�������Z
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



		//����ֽ�
		//vtkContourFilter
		skinFilter ->SetInputConnection(DicomImageReader ->GetOutputPort());  //Filter��J��X���s���ǰt(�Ѧ�4-3) //�]�mŪ�J�ƾڷ�
		skinFilter ->SetValue(0, 500);  //�]�m�֭�(�G���Ϲ�����)(�����ƩM������)(�Ѧ�5-1)
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
		skinMapper ->ScalarVisibilityOff();  //�Ѧ�4-4
		//Actor���ݩʤ������C�⪺�]�m�u����Actor��Mapper�S���жq�ƾ�(ScalarData)�ɤ~�_�@�ΡC
		//�ʬٱ��p�U�AMapper��J���жq�ƾڷ|��Actor�i��ۦ�A��Actor���C��]�m�|�Q�����C
		//�p�G�n�����o�Ǽжq�ƾڡA�i�H�ϥΤ�kScalarVisibilityOff()

		//vtkActor
		skin_Actor ->SetMapper(skinMapper);  //�]�m�ֽ��X��ƾ��ݩ�(�@��Actor���X��O�q�LSetMapper()��k���w��)
		skin_Actor ->GetProperty() ->SetDiffuseColor(1, .49, .25);  //�]�m�ֽ��C���ݩ�
		skin_Actor ->GetProperty() ->SetSpecular(.3);  //�]�m�Ϯg�v
		skin_Actor ->GetProperty() ->SetSpecularPower(20);  //�]�m�Ϯg���j��
		//Actor�̦��@��������vtkProperty����ҡA�D�n�O�Ψӱ���Actor������ݩ�
		//�ڭ̳q�L��kGetProperty()�����ޥ�Actor���ݩʡC�Ϊ̡A�ڭ̤]�i�H����ҤƤ@��vtkProperty��H�A�M��⥦�]�m��Actor��



		//������f
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



		//�]�m�~��
		//vtkOutlineFilter
		outlineFilter ->SetInputConnection(DicomImageReader ->GetOutputPort());
		outlineFilter ->Update();

		//�~��Mapper	
		outlineMapper ->SetInputConnection(outlineFilter ->GetOutputPort());

		//�~��Actor	
		outlineActor ->SetMapper(outlineMapper);
		outlineActor ->GetProperty() ->SetColor(0,0,0);



		//�]�m�孱
		//�]�mLT�孱(��)(sagittal)vtkLookupTable	
		sagittal_table ->SetTableRange (0, 2000);
		sagittal_table ->SetSaturationRange (0, 0);  //�]�m�����C��
		sagittal_table ->SetHueRange (0, 0);
		sagittal_table ->SetValueRange (0, 1);
		sagittal_table ->Build(); //effective built

		//�]�m�b�孱(axial)vtkLookupTable	
		axial_table ->SetTableRange (0, 2000);
		axial_table ->SetHueRange (0, 1);
		axial_table ->SetSaturationRange (1, 1);
		axial_table ->SetValueRange (1, 1);
		axial_table ->Build(); //effective built

		//�]�mAP�孱(�a)(coronal)vtkLookupTable	
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
		sagittal_ImageActor_3D ->SetDisplayExtent(32,32, 0,63, 0,92);  //�]�m������m�A��ܽd��(xmin,xmax,ymin,ymax,zmin,zmax)	
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



		//�]�m�ṳ��
		//3D  
		Camera_3D ->SetViewUp (0, 0, -1);  //�]�m�ṳ����V(���m�۾�"�V�W"����V)
		Camera_3D ->SetPosition (0, 1, 0);  //������m(�@�ɮy�t�w�q)
		Camera_3D ->SetFocalPoint (0, 0, 0);  //�]�m�J�I�y��(���Ӥ�V)(�@�ɮy�t�w�q)
		Camera_3D ->ComputeViewPlaneNormal();  //�H��e�]�m���۾���m�M�J�I���m���������k�V�q
		//�H�U��Ӥ�k�����|���ܬ۾���View-up�V�q(�Ѧ�4-3)
		Camera_3D ->Azimuth(30.0);  //�|�b�y���ФU�H�J�I�����ߪu�۸g�פ�V(Longitude Direction)������w������
		Camera_3D ->Elevation(30.0);  //�O�u�۽n�פ�V(LatitudeDirection)����

		//LT	
		Camera_LT ->SetViewUp (0, 0, -1);  //�]�m�ṳ����V
		Camera_LT ->SetPosition (1, 0, 0);  //������m ����ݬ۾�
		Camera_LT ->SetFocalPoint (0, 0, 0);  //�]�m�J�I�y��
		Camera_LT ->ComputeViewPlaneNormal();
		Camera_LT ->Azimuth(0.0);
		Camera_LT ->Elevation(0.0);

		//AP	
		Camera_AP ->SetViewUp (0, 0, -1);  //�]�m�ṳ����V
		Camera_AP ->SetPosition (0, 1, 0);  //������m ����ݬ۾�
		Camera_AP ->SetFocalPoint (0, 0, 0);  //�]�m�J�I�y��
		Camera_AP ->ComputeViewPlaneNormal();
		Camera_AP ->Azimuth(0.0);
		Camera_AP ->Elevation(0.0);

		//axial	
		Camera_axil ->SetViewUp (0, -1, 0);  //�]�m�ṳ����V
		Camera_axil ->SetPosition (0, 0, -1);  //������m ����ݬ۾�
		Camera_axil ->SetFocalPoint (0, 0, 0);  //�]�m�J�I�y��
		Camera_axil ->ComputeViewPlaneNormal();
		Camera_axil ->Azimuth(0.0);
		Camera_axil ->Elevation(0.0);



		//�K�[�t���}�lø�s
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



		//�e���ƾ�
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



		//���Y�i��������
		//bone ->VisibilityOff();

		//�]�m�z����(Actor���z����)
		skin_Actor ->GetProperty() ->SetOpacity(0.5);
		bone_Actor ->GetProperty() ->SetOpacity(0.5);


		//ø�s�̳]�m�ṳ��
		Renderer_3D ->SetActiveCamera(Camera_3D);  //�O�s�M��_�۾����A(�]�N�O���m����)(�Ѧ�4-3)
		Renderer_sagittal_LT ->SetActiveCamera(Camera_LT);
		Renderer_coronal_AP ->SetActiveCamera(Camera_AP);
		Renderer_axial ->SetActiveCamera(Camera_axil);


		//�δ�V����ResetCamera()��k��Ӭ۾��]�m���V�����AResetCamera()��k�i�H�u�۵��V�q���ʬ۾��A�o�ˡA��V���̩Ҧ���Actor���|�i��
		Renderer_3D ->ResetCamera();
		Renderer_sagittal_LT ->ResetCamera();
		Renderer_coronal_AP ->ResetCamera();
		Renderer_axial ->ResetCamera();


		//aCamera->Dolly(1.5);  //�u�۵��������k�V��V���ʬ۾��A�Ϊ̩�j�B���Y��V�������i����actor
		//�t�~��Zoom()��k�O�q�L���ܵ���(ViewAngle)(�YSetViewAngle()��k)�ϱo�����j���


		Renderer_3D ->ResetCameraClippingRange();
		Renderer_sagittal_LT ->ResetCameraClippingRange();
		Renderer_coronal_AP ->ResetCameraClippingRange();
		Renderer_axial ->ResetCameraClippingRange();


		//��{��V
		ui.qvtkWidget ->GetRenderWindow() ->Render();
		//ui.qvtkWidget_2 ->GetRenderWindow() ->Render();
		//ui.qvtkWidget_3 ->GetRenderWindow() ->Render();
		//ui.qvtkWidget_4 ->GetRenderWindow() ->Render();
	}	
	Action();  //�}�Ұʧ@
	Initial_value();  //��ܪ��

	Update();

	//interact with data
	//iren->Initialize();
	//iren->Start(); 
	//system("pause");
	//return EXIT_SUCCESS;
}
*/

//�}��V16�ɮ�


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
		//���ƶ}��
		Renderer_3D ->RemoveAllViewProps();
		Renderer_sagittal_LT ->RemoveAllViewProps();
		Renderer_coronal_AP ->RemoveAllViewProps();
		Renderer_axial ->RemoveAllViewProps();

		//�^���ɮצ�m
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

		//vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();  //�إ�ø�s���f
		//renWin->AddRenderer(Renderer_3D);  //�Nø�s�̥[�J���f

		//�]�m���f���椬��(�P���f�����ʼҦ�)(�ѦҤU��W�d��)
		//vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();  
		//iren->SetRenderWindow(renWin);  //�]�m���f��reWin(�PreWin�s��)

		//�]�w���f�I��(.2, .3, .4)
		Renderer_3D ->SetBackground(0,0,0);  
		Renderer_sagittal_LT ->SetBackground(0,0,0); 
		Renderer_coronal_AP ->SetBackground(0,0,0); 
		Renderer_axial ->SetBackground(0,0,0); 

		//�]�m���f���p
		//ui.qvtkWidget ->GetRenderWindow() ->SetSize(250,250);  
		//ui.qvtkWidget_2 ->GetRenderWindow() ->SetSize(250,250);
		//ui.qvtkWidget_3 ->GetRenderWindow() ->SetSize(250,250);
		//ui.qvtkWidget_4 ->GetRenderWindow() ->SetSize(250,250);

		//�ƾ�Ū�J
		v16_openfile ->SetDataDimensions(64,64);  //�]�m�Ϲ�������
		v16_openfile ->SetImageRange(1, 93);  //�]�m�Ϥ��ƶq(��1~93�i)
		v16_openfile ->SetDataByteOrderToLittleEndian();
		//v16_openfile ->SetFilePrefix ("E:\\VTK_Tool\\vtkdata-5.10.1\\Data\\headsq\\quarter");  //���ɦ�m
		v16_openfile ->SetFilePrefix(ch);	
		//v16_openfile->SetFilePrefix (argv[1]);
		v16_openfile ->SetDataSpacing (3.2, 3.2, 1.5);  //�]�m�������Z
		v16_openfile ->Update();



		//����ֽ�
		//vtkContourFilter
		skinFilter ->SetInputConnection(v16_openfile ->GetOutputPort());  //Filter��J��X���s���ǰt(�Ѧ�4-3) //�]�mŪ�J�ƾڷ�
		skinFilter ->SetValue(0, 500);  //�]�m�֭�(�G���Ϲ�����)(�����ƩM������)(�Ѧ�5-1)
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
		skinMapper ->ScalarVisibilityOff();  //�Ѧ�4-4
		//Actor���ݩʤ������C�⪺�]�m�u����Actor��Mapper�S���жq�ƾ�(ScalarData)�ɤ~�_�@�ΡC
		//�ʬٱ��p�U�AMapper��J���жq�ƾڷ|��Actor�i��ۦ�A��Actor���C��]�m�|�Q�����C
		//�p�G�n�����o�Ǽжq�ƾڡA�i�H�ϥΤ�kScalarVisibilityOff()

		//vtkActor
		skin_Actor ->SetMapper(skinMapper);  //�]�m�ֽ��X��ƾ��ݩ�(�@��Actor���X��O�q�LSetMapper()��k���w��)
		skin_Actor ->GetProperty() ->SetDiffuseColor(1, .49, .25);  //�]�m�ֽ��C���ݩ�
		skin_Actor ->GetProperty() ->SetSpecular(.3);  //�]�m�Ϯg�v
		skin_Actor ->GetProperty() ->SetSpecularPower(20);  //�]�m�Ϯg���j��
		//Actor�̦��@��������vtkProperty����ҡA�D�n�O�Ψӱ���Actor������ݩ�
		//�ڭ̳q�L��kGetProperty()�����ޥ�Actor���ݩʡC�Ϊ̡A�ڭ̤]�i�H����ҤƤ@��vtkProperty��H�A�M��⥦�]�m��Actor��



		//������f
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



		//�]�m�~��
		//vtkOutlineFilter
		outlineFilter ->SetInputConnection(v16_openfile ->GetOutputPort());
		outlineFilter ->Update();

		//�~��Mapper	
		outlineMapper ->SetInputConnection(outlineFilter ->GetOutputPort());

		//�~��Actor	
		outlineActor ->SetMapper(outlineMapper);
		outlineActor ->GetProperty() ->SetColor(0,0,0);



		//�]�m�孱
		//�]�mLT�孱(��)(sagittal)vtkLookupTable	
		sagittal_table ->SetTableRange (0, 2000);
		sagittal_table ->SetSaturationRange (0, 0);  //�]�m�����C��
		sagittal_table ->SetHueRange (0, 0);
		sagittal_table ->SetValueRange (0, 1);
		sagittal_table ->Build(); //effective built

		//�]�m�b�孱(axial)vtkLookupTable	
		axial_table ->SetTableRange (0, 2000);
		axial_table ->SetHueRange (0, 1);
		axial_table ->SetSaturationRange (1, 1);
		axial_table ->SetValueRange (1, 1);
		axial_table ->Build(); //effective built

		//�]�mAP�孱(�a)(coronal)vtkLookupTable	
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
		sagittal_ImageActor_3D ->SetDisplayExtent(32,32, 0,63, 0,92);  //�]�m������m�A��ܽd��(xmin,xmax,ymin,ymax,zmin,zmax)	
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



		//�]�m�ṳ��
		//3D  
		Camera_3D ->SetViewUp (0, 0, -1);  //�]�m�ṳ����V(���m�۾�"�V�W"����V)
		Camera_3D ->SetPosition (0, 1, 0);  //������m(�@�ɮy�t�w�q)
		Camera_3D ->SetFocalPoint (0, 0, 0);  //�]�m�J�I�y��(���Ӥ�V)(�@�ɮy�t�w�q)
		Camera_3D ->ComputeViewPlaneNormal();  //�H��e�]�m���۾���m�M�J�I���m���������k�V�q
		//�H�U��Ӥ�k�����|���ܬ۾���View-up�V�q(�Ѧ�4-3)
		Camera_3D ->Azimuth(30.0);  //�|�b�y���ФU�H�J�I�����ߪu�۸g�פ�V(Longitude Direction)������w������
		Camera_3D ->Elevation(30.0);  //�O�u�۽n�פ�V(LatitudeDirection)����

		//LT	
		Camera_LT ->SetViewUp (0, 0, -1);  //�]�m�ṳ����V
		Camera_LT ->SetPosition (1, 0, 0);  //������m ����ݬ۾�
		Camera_LT ->SetFocalPoint (0, 0, 0);  //�]�m�J�I�y��
		Camera_LT ->ComputeViewPlaneNormal();
		Camera_LT ->Azimuth(0.0);
		Camera_LT ->Elevation(0.0);

		//AP	
		Camera_AP ->SetViewUp (0, 0, -1);  //�]�m�ṳ����V
		Camera_AP ->SetPosition (0, 1, 0);  //������m ����ݬ۾�
		Camera_AP ->SetFocalPoint (0, 0, 0);  //�]�m�J�I�y��
		Camera_AP ->ComputeViewPlaneNormal();
		Camera_AP ->Azimuth(0.0);
		Camera_AP ->Elevation(0.0);

		//axial	
		Camera_axil ->SetViewUp (0, -1, 0);  //�]�m�ṳ����V
		Camera_axil ->SetPosition (0, 0, -1);  //������m ����ݬ۾�
		Camera_axil ->SetFocalPoint (0, 0, 0);  //�]�m�J�I�y��
		Camera_axil ->ComputeViewPlaneNormal();
		Camera_axil ->Azimuth(0.0);
		Camera_axil ->Elevation(0.0);



		//�K�[�t���}�lø�s
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



		//�e���ƾ�
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



		//���Y�i��������
		//bone ->VisibilityOff();

		//�]�m�z����(Actor���z����)
		skin_Actor ->GetProperty() ->SetOpacity(0.5);
		bone_Actor ->GetProperty() ->SetOpacity(0.5);


		//ø�s�̳]�m�ṳ��
		Renderer_3D ->SetActiveCamera(Camera_3D);  //�O�s�M��_�۾����A(�]�N�O���m����)(�Ѧ�4-3)
		Renderer_sagittal_LT ->SetActiveCamera(Camera_LT);
		Renderer_coronal_AP ->SetActiveCamera(Camera_AP);
		Renderer_axial ->SetActiveCamera(Camera_axil);


		//�δ�V����ResetCamera()��k��Ӭ۾��]�m���V�����AResetCamera()��k�i�H�u�۵��V�q���ʬ۾��A�o�ˡA��V���̩Ҧ���Actor���|�i��
		Renderer_3D ->ResetCamera();
		Renderer_sagittal_LT ->ResetCamera();
		Renderer_coronal_AP ->ResetCamera();
		Renderer_axial ->ResetCamera();


		//aCamera->Dolly(1.5);  //�u�۵��������k�V��V���ʬ۾��A�Ϊ̩�j�B���Y��V�������i����actor
		//�t�~��Zoom()��k�O�q�L���ܵ���(ViewAngle)(�YSetViewAngle()��k)�ϱo�����j���


		Renderer_3D ->ResetCameraClippingRange();
		Renderer_sagittal_LT ->ResetCameraClippingRange();
		Renderer_coronal_AP ->ResetCameraClippingRange();
		Renderer_axial ->ResetCameraClippingRange();


		//��{��V
		ui.qvtkWidget ->GetRenderWindow() ->Render();
		//ui.qvtkWidget_2 ->GetRenderWindow() ->Render();
		//ui.qvtkWidget_3 ->GetRenderWindow() ->Render();
		//ui.qvtkWidget_4 ->GetRenderWindow() ->Render();
	}	
	Action();  //�}�Ұʧ@
	Initial_value();  //��ܪ��

	Update();

	//interact with data
	//iren->Initialize();
	//iren->Start(); 
	//system("pause");
	//return EXIT_SUCCESS;
}
