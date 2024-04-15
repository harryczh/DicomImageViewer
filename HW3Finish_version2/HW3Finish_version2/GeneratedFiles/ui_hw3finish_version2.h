/********************************************************************************
** Form generated from reading UI file 'hw3finish_version2.ui'
**
** Created: Tue Dec 5 11:41:19 2017
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HW3FINISH_VERSION2_H
#define UI_HW3FINISH_VERSION2_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_HW3Finish_version2Class
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVTKWidget *qvtkWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_3;
    QPushButton *Skin_accept_button;
    QSlider *Skin_opacity_slider;
    QLabel *Skin_opacity_value;
    QLabel *Skin_isovalue_name;
    QLabel *Skin_isovalue_value;
    QSlider *Skin_isovalue_slider;
    QPushButton *Skin_color_button;
    QLabel *Skin_opacity_name;
    QLabel *Skin_title;
    QLabel *Skin_color_show;
    QWidget *widget_2;
    QSlider *Skull_opacity_slider;
    QLabel *Skull_opacity_name;
    QLabel *Skull_title;
    QSlider *Skull_isovalue_slider;
    QLabel *Skull_opacity_value;
    QPushButton *Skull_accept_button;
    QLabel *Skull_isovalue_name;
    QLabel *Skull_isovalue_value;
    QPushButton *Skull_color_button;
    QLabel *Skull_color_show;
    QWidget *widget;
    QLabel *Xslice_name;
    QLabel *Zslice_name;
    QSpinBox *Xslice_position;
    QSpinBox *Yslice_position;
    QLabel *Yslice_name;
    QCheckBox *Orthogonal_planes;
    QSpinBox *Zslice_position;
    QSlider *Window_slider;
    QLabel *Window_name;
    QLabel *Level_name;
    QLabel *Level_value;
    QLabel *Window_value;
    QSlider *Level_slider;
    QLabel *Slice_title;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *Open_File;
    QPushButton *Update;

    void setupUi(QWidget *HW3Finish_version2Class)
    {
        if (HW3Finish_version2Class->objectName().isEmpty())
            HW3Finish_version2Class->setObjectName(QString::fromUtf8("HW3Finish_version2Class"));
        HW3Finish_version2Class->setEnabled(true);
        HW3Finish_version2Class->resize(816, 521);
        HW3Finish_version2Class->setAutoFillBackground(true);
        horizontalLayout_3 = new QHBoxLayout(HW3Finish_version2Class);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        qvtkWidget = new QVTKWidget(HW3Finish_version2Class);
        qvtkWidget->setObjectName(QString::fromUtf8("qvtkWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(qvtkWidget->sizePolicy().hasHeightForWidth());
        qvtkWidget->setSizePolicy(sizePolicy);
        qvtkWidget->setMinimumSize(QSize(500, 500));
        qvtkWidget->setSizeIncrement(QSize(0, 0));
        qvtkWidget->setBaseSize(QSize(0, 0));

        horizontalLayout_3->addWidget(qvtkWidget);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget_3 = new QWidget(HW3Finish_version2Class);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setMinimumSize(QSize(140, 230));
        widget_3->setMaximumSize(QSize(140, 230));
        Skin_accept_button = new QPushButton(widget_3);
        Skin_accept_button->setObjectName(QString::fromUtf8("Skin_accept_button"));
        Skin_accept_button->setEnabled(false);
        Skin_accept_button->setGeometry(QRect(78, 200, 51, 23));
        Skin_opacity_slider = new QSlider(widget_3);
        Skin_opacity_slider->setObjectName(QString::fromUtf8("Skin_opacity_slider"));
        Skin_opacity_slider->setEnabled(false);
        Skin_opacity_slider->setGeometry(QRect(8, 150, 121, 22));
        Skin_opacity_slider->setMaximum(10);
        Skin_opacity_slider->setSingleStep(1);
        Skin_opacity_slider->setPageStep(1);
        Skin_opacity_slider->setValue(0);
        Skin_opacity_slider->setOrientation(Qt::Horizontal);
        Skin_opacity_value = new QLabel(widget_3);
        Skin_opacity_value->setObjectName(QString::fromUtf8("Skin_opacity_value"));
        Skin_opacity_value->setGeometry(QRect(72, 121, 31, 20));
        QFont font;
        font.setPointSize(12);
        Skin_opacity_value->setFont(font);
        Skin_isovalue_name = new QLabel(widget_3);
        Skin_isovalue_name->setObjectName(QString::fromUtf8("Skin_isovalue_name"));
        Skin_isovalue_name->setGeometry(QRect(8, 51, 81, 20));
        QFont font1;
        font1.setPointSize(9);
        Skin_isovalue_name->setFont(font1);
        Skin_isovalue_value = new QLabel(widget_3);
        Skin_isovalue_value->setObjectName(QString::fromUtf8("Skin_isovalue_value"));
        Skin_isovalue_value->setGeometry(QRect(90, 51, 31, 20));
        Skin_isovalue_value->setFont(font);
        Skin_isovalue_slider = new QSlider(widget_3);
        Skin_isovalue_slider->setObjectName(QString::fromUtf8("Skin_isovalue_slider"));
        Skin_isovalue_slider->setEnabled(false);
        Skin_isovalue_slider->setGeometry(QRect(8, 80, 121, 22));
        Skin_isovalue_slider->setMaximum(1000);
        Skin_isovalue_slider->setSingleStep(100);
        Skin_isovalue_slider->setPageStep(100);
        Skin_isovalue_slider->setValue(0);
        Skin_isovalue_slider->setOrientation(Qt::Horizontal);
        Skin_color_button = new QPushButton(widget_3);
        Skin_color_button->setObjectName(QString::fromUtf8("Skin_color_button"));
        Skin_color_button->setEnabled(false);
        Skin_color_button->setGeometry(QRect(8, 200, 61, 23));
        Skin_opacity_name = new QLabel(widget_3);
        Skin_opacity_name->setObjectName(QString::fromUtf8("Skin_opacity_name"));
        Skin_opacity_name->setGeometry(QRect(8, 121, 61, 20));
        Skin_title = new QLabel(widget_3);
        Skin_title->setObjectName(QString::fromUtf8("Skin_title"));
        Skin_title->setGeometry(QRect(40, 11, 51, 31));
        Skin_color_show = new QLabel(widget_3);
        Skin_color_show->setObjectName(QString::fromUtf8("Skin_color_show"));
        Skin_color_show->setGeometry(QRect(13, 203, 16, 16));
        Skin_color_show->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(widget_3);

        widget_2 = new QWidget(HW3Finish_version2Class);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(140, 230));
        widget_2->setMaximumSize(QSize(140, 230));
        Skull_opacity_slider = new QSlider(widget_2);
        Skull_opacity_slider->setObjectName(QString::fromUtf8("Skull_opacity_slider"));
        Skull_opacity_slider->setEnabled(false);
        Skull_opacity_slider->setGeometry(QRect(5, 150, 121, 22));
        Skull_opacity_slider->setMaximum(10);
        Skull_opacity_slider->setPageStep(1);
        Skull_opacity_slider->setValue(0);
        Skull_opacity_slider->setOrientation(Qt::Horizontal);
        Skull_opacity_name = new QLabel(widget_2);
        Skull_opacity_name->setObjectName(QString::fromUtf8("Skull_opacity_name"));
        Skull_opacity_name->setGeometry(QRect(5, 121, 61, 20));
        Skull_title = new QLabel(widget_2);
        Skull_title->setObjectName(QString::fromUtf8("Skull_title"));
        Skull_title->setGeometry(QRect(35, 10, 51, 31));
        Skull_isovalue_slider = new QSlider(widget_2);
        Skull_isovalue_slider->setObjectName(QString::fromUtf8("Skull_isovalue_slider"));
        Skull_isovalue_slider->setEnabled(false);
        Skull_isovalue_slider->setGeometry(QRect(5, 80, 121, 22));
        Skull_isovalue_slider->setMaximum(3000);
        Skull_isovalue_slider->setSingleStep(100);
        Skull_isovalue_slider->setPageStep(100);
        Skull_isovalue_slider->setValue(0);
        Skull_isovalue_slider->setOrientation(Qt::Horizontal);
        Skull_opacity_value = new QLabel(widget_2);
        Skull_opacity_value->setObjectName(QString::fromUtf8("Skull_opacity_value"));
        Skull_opacity_value->setGeometry(QRect(69, 121, 31, 20));
        Skull_opacity_value->setFont(font);
        Skull_accept_button = new QPushButton(widget_2);
        Skull_accept_button->setObjectName(QString::fromUtf8("Skull_accept_button"));
        Skull_accept_button->setEnabled(false);
        Skull_accept_button->setGeometry(QRect(75, 200, 51, 23));
        Skull_isovalue_name = new QLabel(widget_2);
        Skull_isovalue_name->setObjectName(QString::fromUtf8("Skull_isovalue_name"));
        Skull_isovalue_name->setGeometry(QRect(5, 51, 81, 20));
        Skull_isovalue_value = new QLabel(widget_2);
        Skull_isovalue_value->setObjectName(QString::fromUtf8("Skull_isovalue_value"));
        Skull_isovalue_value->setGeometry(QRect(87, 51, 31, 20));
        Skull_isovalue_value->setFont(font);
        Skull_color_button = new QPushButton(widget_2);
        Skull_color_button->setObjectName(QString::fromUtf8("Skull_color_button"));
        Skull_color_button->setEnabled(false);
        Skull_color_button->setGeometry(QRect(5, 200, 61, 23));
        Skull_color_show = new QLabel(widget_2);
        Skull_color_show->setObjectName(QString::fromUtf8("Skull_color_show"));
        Skull_color_show->setGeometry(QRect(10, 203, 16, 16));

        horizontalLayout->addWidget(widget_2);


        verticalLayout->addLayout(horizontalLayout);

        widget = new QWidget(HW3Finish_version2Class);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(150, 190));
        widget->setMaximumSize(QSize(292, 190));
        Xslice_name = new QLabel(widget);
        Xslice_name->setObjectName(QString::fromUtf8("Xslice_name"));
        Xslice_name->setGeometry(QRect(10, 60, 31, 21));
        Zslice_name = new QLabel(widget);
        Zslice_name->setObjectName(QString::fromUtf8("Zslice_name"));
        Zslice_name->setGeometry(QRect(10, 120, 31, 21));
        Xslice_position = new QSpinBox(widget);
        Xslice_position->setObjectName(QString::fromUtf8("Xslice_position"));
        Xslice_position->setEnabled(false);
        Xslice_position->setGeometry(QRect(40, 60, 81, 22));
        Xslice_position->setMaximum(63);
        Xslice_position->setValue(0);
        Yslice_position = new QSpinBox(widget);
        Yslice_position->setObjectName(QString::fromUtf8("Yslice_position"));
        Yslice_position->setEnabled(false);
        Yslice_position->setGeometry(QRect(40, 90, 81, 22));
        Yslice_position->setMaximum(63);
        Yslice_position->setValue(0);
        Yslice_name = new QLabel(widget);
        Yslice_name->setObjectName(QString::fromUtf8("Yslice_name"));
        Yslice_name->setGeometry(QRect(10, 90, 31, 21));
        Orthogonal_planes = new QCheckBox(widget);
        Orthogonal_planes->setObjectName(QString::fromUtf8("Orthogonal_planes"));
        Orthogonal_planes->setEnabled(false);
        Orthogonal_planes->setGeometry(QRect(10, 160, 141, 16));
        Orthogonal_planes->setCheckable(true);
        Orthogonal_planes->setChecked(false);
        Orthogonal_planes->setAutoRepeat(true);
        Orthogonal_planes->setAutoExclusive(false);
        Zslice_position = new QSpinBox(widget);
        Zslice_position->setObjectName(QString::fromUtf8("Zslice_position"));
        Zslice_position->setEnabled(false);
        Zslice_position->setGeometry(QRect(40, 120, 81, 22));
        Zslice_position->setMaximum(92);
        Zslice_position->setValue(0);
        Window_slider = new QSlider(widget);
        Window_slider->setObjectName(QString::fromUtf8("Window_slider"));
        Window_slider->setEnabled(false);
        Window_slider->setGeometry(QRect(158, 150, 121, 22));
        Window_slider->setMaximum(3926);
        Window_slider->setSingleStep(100);
        Window_slider->setPageStep(100);
        Window_slider->setValue(0);
        Window_slider->setOrientation(Qt::Horizontal);
        Window_name = new QLabel(widget);
        Window_name->setObjectName(QString::fromUtf8("Window_name"));
        Window_name->setGeometry(QRect(158, 121, 71, 20));
        Level_name = new QLabel(widget);
        Level_name->setObjectName(QString::fromUtf8("Level_name"));
        Level_name->setGeometry(QRect(158, 50, 51, 20));
        Level_value = new QLabel(widget);
        Level_value->setObjectName(QString::fromUtf8("Level_value"));
        Level_value->setGeometry(QRect(210, 50, 41, 20));
        Level_value->setFont(font);
        Window_value = new QLabel(widget);
        Window_value->setObjectName(QString::fromUtf8("Window_value"));
        Window_value->setGeometry(QRect(230, 120, 41, 20));
        Window_value->setFont(font);
        Level_slider = new QSlider(widget);
        Level_slider->setObjectName(QString::fromUtf8("Level_slider"));
        Level_slider->setEnabled(false);
        Level_slider->setGeometry(QRect(158, 79, 121, 22));
        Level_slider->setMaximum(1963);
        Level_slider->setSingleStep(100);
        Level_slider->setPageStep(100);
        Level_slider->setValue(0);
        Level_slider->setOrientation(Qt::Horizontal);
        Slice_title = new QLabel(widget);
        Slice_title->setObjectName(QString::fromUtf8("Slice_title"));
        Slice_title->setGeometry(QRect(110, 10, 51, 31));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 170, 271, 16));

        verticalLayout->addWidget(widget);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        Open_File = new QPushButton(HW3Finish_version2Class);
        Open_File->setObjectName(QString::fromUtf8("Open_File"));
        Open_File->setMinimumSize(QSize(75, 23));
        Open_File->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_2->addWidget(Open_File);

        Update = new QPushButton(HW3Finish_version2Class);
        Update->setObjectName(QString::fromUtf8("Update"));
        Update->setMinimumSize(QSize(75, 23));
        Update->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_2->addWidget(Update);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(HW3Finish_version2Class);
        QObject::connect(Open_File, SIGNAL(clicked()), HW3Finish_version2Class, SLOT(Open_File()));
        QObject::connect(Update, SIGNAL(clicked()), HW3Finish_version2Class, SLOT(Update()));
        QObject::connect(Level_slider, SIGNAL(valueChanged(int)), HW3Finish_version2Class, SLOT(Level()));
        QObject::connect(Yslice_position, SIGNAL(valueChanged(int)), HW3Finish_version2Class, SLOT(Yslice()));
        QObject::connect(Skull_opacity_slider, SIGNAL(valueChanged(int)), HW3Finish_version2Class, SLOT(Skull_opacity()));
        QObject::connect(Zslice_position, SIGNAL(valueChanged(int)), HW3Finish_version2Class, SLOT(Zslice()));
        QObject::connect(Skin_isovalue_slider, SIGNAL(valueChanged(int)), HW3Finish_version2Class, SLOT(Skin_isovalue()));
        QObject::connect(Xslice_position, SIGNAL(valueChanged(int)), HW3Finish_version2Class, SLOT(Xslice()));
        QObject::connect(Skull_isovalue_slider, SIGNAL(valueChanged(int)), HW3Finish_version2Class, SLOT(Skull_isovalue()));
        QObject::connect(Skin_color_button, SIGNAL(clicked()), HW3Finish_version2Class, SLOT(Skin_color()));
        QObject::connect(Skin_opacity_slider, SIGNAL(valueChanged(int)), HW3Finish_version2Class, SLOT(Skin_opacity()));
        QObject::connect(Skull_color_button, SIGNAL(clicked()), HW3Finish_version2Class, SLOT(Skull_color()));
        QObject::connect(Orthogonal_planes, SIGNAL(clicked()), HW3Finish_version2Class, SLOT(Orthogonal_planes()));
        QObject::connect(Window_slider, SIGNAL(valueChanged(int)), HW3Finish_version2Class, SLOT(Window()));
        QObject::connect(Skin_accept_button, SIGNAL(clicked()), HW3Finish_version2Class, SLOT(Skin_accept()));
        QObject::connect(Skull_accept_button, SIGNAL(clicked()), HW3Finish_version2Class, SLOT(Skull_accept()));

        QMetaObject::connectSlotsByName(HW3Finish_version2Class);
    } // setupUi

    void retranslateUi(QWidget *HW3Finish_version2Class)
    {
        HW3Finish_version2Class->setWindowTitle(QApplication::translate("HW3Finish_version2Class", "HW3Finish_version2", 0, QApplication::UnicodeUTF8));
        Skin_accept_button->setText(QApplication::translate("HW3Finish_version2Class", "Accept", 0, QApplication::UnicodeUTF8));
        Skin_opacity_value->setText(QString());
        Skin_isovalue_name->setText(QApplication::translate("HW3Finish_version2Class", "<html><head/><body><p><span style=\" font-size:12pt;\">ISO-Value =</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        Skin_isovalue_value->setText(QString());
        Skin_color_button->setText(QApplication::translate("HW3Finish_version2Class", "    Color", 0, QApplication::UnicodeUTF8));
        Skin_opacity_name->setText(QApplication::translate("HW3Finish_version2Class", "<html><head/><body><p><span style=\" font-size:12pt;\">Opacity =</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        Skin_title->setText(QApplication::translate("HW3Finish_version2Class", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600;\">Skin</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        Skin_color_show->setText(QString());
        Skull_opacity_name->setText(QApplication::translate("HW3Finish_version2Class", "<html><head/><body><p><span style=\" font-size:12pt;\">Opacity =</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        Skull_title->setText(QApplication::translate("HW3Finish_version2Class", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600;\">Skull</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        Skull_opacity_value->setText(QString());
        Skull_accept_button->setText(QApplication::translate("HW3Finish_version2Class", "Accept", 0, QApplication::UnicodeUTF8));
        Skull_isovalue_name->setText(QApplication::translate("HW3Finish_version2Class", "<html><head/><body><p><span style=\" font-size:12pt;\">ISO-Value =</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        Skull_isovalue_value->setText(QString());
        Skull_color_button->setText(QApplication::translate("HW3Finish_version2Class", "    Color", 0, QApplication::UnicodeUTF8));
        Skull_color_show->setText(QString());
        Xslice_name->setText(QApplication::translate("HW3Finish_version2Class", "<html><head/><body><p><span style=\" font-size:12pt;\">X =</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        Zslice_name->setText(QApplication::translate("HW3Finish_version2Class", "<html><head/><body><p><span style=\" font-size:12pt;\">Z =</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        Yslice_name->setText(QApplication::translate("HW3Finish_version2Class", "<html><head/><body><p><span style=\" font-size:12pt;\">Y =</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        Orthogonal_planes->setText(QApplication::translate("HW3Finish_version2Class", "Show Orthogonal Planes", 0, QApplication::UnicodeUTF8));
        Window_name->setText(QApplication::translate("HW3Finish_version2Class", "<html><head/><body><p><span style=\" font-size:12pt;\">Window =</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        Level_name->setText(QApplication::translate("HW3Finish_version2Class", "<html><head/><body><p><span style=\" font-size:12pt;\">Level =</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        Level_value->setText(QString());
        Window_value->setText(QString());
        Slice_title->setText(QApplication::translate("HW3Finish_version2Class", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600;\">Slice</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("HW3Finish_version2Class", "TextLabel", 0, QApplication::UnicodeUTF8));
        Open_File->setText(QApplication::translate("HW3Finish_version2Class", "Open File", 0, QApplication::UnicodeUTF8));
        Update->setText(QApplication::translate("HW3Finish_version2Class", "Update", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class HW3Finish_version2Class: public Ui_HW3Finish_version2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HW3FINISH_VERSION2_H
