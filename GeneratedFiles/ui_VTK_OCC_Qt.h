/********************************************************************************
** Form generated from reading UI file 'VTK_OCC_Qt.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VTK_OCC_QT_H
#define UI_VTK_OCC_QT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <qvtkopenglnativewidget.h>

QT_BEGIN_NAMESPACE

class Ui_VTK_OCC_QtClass
{
public:
    QAction *display;
    QAction *play;
    QAction *HeadSlice;
    QAction *IronIsoSurface;
    QAction *ComplexV;
    QAction *Kitchen;
    QAction *TensorAxes;
    QAction *step;
    QAction *point;
    QAction *lorenz;
    QAction *actionreadIGS;
    QAction *makebox;
    QAction *makecone;
    QAction *OnButtonCreatepnt;
    QAction *OnButtonCereatlin;
    QAction *OnButtonCereatface;
    QWidget *centralWidget;
    QVTKOpenGLNativeWidget *openGLWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menuOCC;
    QMenu *menu_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *VTK_OCC_QtClass)
    {
        if (VTK_OCC_QtClass->objectName().isEmpty())
            VTK_OCC_QtClass->setObjectName(QString::fromUtf8("VTK_OCC_QtClass"));
        VTK_OCC_QtClass->resize(1345, 822);
        display = new QAction(VTK_OCC_QtClass);
        display->setObjectName(QString::fromUtf8("display"));
        play = new QAction(VTK_OCC_QtClass);
        play->setObjectName(QString::fromUtf8("play"));
        HeadSlice = new QAction(VTK_OCC_QtClass);
        HeadSlice->setObjectName(QString::fromUtf8("HeadSlice"));
        IronIsoSurface = new QAction(VTK_OCC_QtClass);
        IronIsoSurface->setObjectName(QString::fromUtf8("IronIsoSurface"));
        ComplexV = new QAction(VTK_OCC_QtClass);
        ComplexV->setObjectName(QString::fromUtf8("ComplexV"));
        Kitchen = new QAction(VTK_OCC_QtClass);
        Kitchen->setObjectName(QString::fromUtf8("Kitchen"));
        TensorAxes = new QAction(VTK_OCC_QtClass);
        TensorAxes->setObjectName(QString::fromUtf8("TensorAxes"));
        step = new QAction(VTK_OCC_QtClass);
        step->setObjectName(QString::fromUtf8("step"));
        point = new QAction(VTK_OCC_QtClass);
        point->setObjectName(QString::fromUtf8("point"));
        lorenz = new QAction(VTK_OCC_QtClass);
        lorenz->setObjectName(QString::fromUtf8("lorenz"));
        actionreadIGS = new QAction(VTK_OCC_QtClass);
        actionreadIGS->setObjectName(QString::fromUtf8("actionreadIGS"));
        makebox = new QAction(VTK_OCC_QtClass);
        makebox->setObjectName(QString::fromUtf8("makebox"));
        makecone = new QAction(VTK_OCC_QtClass);
        makecone->setObjectName(QString::fromUtf8("makecone"));
        OnButtonCreatepnt = new QAction(VTK_OCC_QtClass);
        OnButtonCreatepnt->setObjectName(QString::fromUtf8("OnButtonCreatepnt"));
        OnButtonCereatlin = new QAction(VTK_OCC_QtClass);
        OnButtonCereatlin->setObjectName(QString::fromUtf8("OnButtonCereatlin"));
        OnButtonCereatface = new QAction(VTK_OCC_QtClass);
        OnButtonCereatface->setObjectName(QString::fromUtf8("OnButtonCereatface"));
        centralWidget = new QWidget(VTK_OCC_QtClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        openGLWidget = new QVTKOpenGLNativeWidget(centralWidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(0, 0, 1351, 771));
        VTK_OCC_QtClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(VTK_OCC_QtClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1345, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menuOCC = new QMenu(menuBar);
        menuOCC->setObjectName(QString::fromUtf8("menuOCC"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        VTK_OCC_QtClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(VTK_OCC_QtClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        VTK_OCC_QtClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(VTK_OCC_QtClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        VTK_OCC_QtClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menuOCC->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(display);
        menu->addAction(play);
        menu->addAction(HeadSlice);
        menu->addAction(IronIsoSurface);
        menu->addAction(ComplexV);
        menu->addAction(Kitchen);
        menu->addAction(TensorAxes);
        menuOCC->addAction(step);
        menuOCC->addAction(point);
        menuOCC->addAction(lorenz);
        menu_2->addAction(actionreadIGS);
        menu_2->addAction(makebox);
        menu_2->addAction(makecone);
        menu_2->addAction(OnButtonCreatepnt);
        menu_2->addAction(OnButtonCereatlin);
        menu_2->addAction(OnButtonCereatface);

        retranslateUi(VTK_OCC_QtClass);

        QMetaObject::connectSlotsByName(VTK_OCC_QtClass);
    } // setupUi

    void retranslateUi(QMainWindow *VTK_OCC_QtClass)
    {
        VTK_OCC_QtClass->setWindowTitle(QApplication::translate("VTK_OCC_QtClass", "VTK_OCC_Qt", nullptr));
        display->setText(QApplication::translate("VTK_OCC_QtClass", "\346\230\276\347\244\272", nullptr));
        play->setText(QApplication::translate("VTK_OCC_QtClass", "\345\244\232\351\207\215\346\230\276\347\244\272", nullptr));
        HeadSlice->setText(QApplication::translate("VTK_OCC_QtClass", "\344\272\272\350\204\221\345\210\207\347\211\207", nullptr));
        IronIsoSurface->setText(QApplication::translate("VTK_OCC_QtClass", "\351\223\201\350\233\213\347\231\275\350\241\250\351\235\242", nullptr));
        ComplexV->setText(QApplication::translate("VTK_OCC_QtClass", "\347\273\204\345\220\210\345\261\225\347\244\272", nullptr));
        Kitchen->setText(QApplication::translate("VTK_OCC_QtClass", "\345\216\250\346\210\277", nullptr));
        TensorAxes->setText(QApplication::translate("VTK_OCC_QtClass", "\345\274\240\351\207\217\350\275\264", nullptr));
        step->setText(QApplication::translate("VTK_OCC_QtClass", "\346\211\223\345\274\200step\346\226\207\344\273\266", nullptr));
        point->setText(QApplication::translate("VTK_OCC_QtClass", "\347\202\271\345\207\273", nullptr));
        lorenz->setText(QApplication::translate("VTK_OCC_QtClass", "Lorenz", nullptr));
        actionreadIGS->setText(QApplication::translate("VTK_OCC_QtClass", "\350\257\273\345\217\226IGS", nullptr));
        makebox->setText(QApplication::translate("VTK_OCC_QtClass", "\347\233\222\345\255\220", nullptr));
        makecone->setText(QApplication::translate("VTK_OCC_QtClass", "\346\233\262\351\235\242", nullptr));
        OnButtonCreatepnt->setText(QApplication::translate("VTK_OCC_QtClass", "\345\210\233\345\273\272\347\202\271", nullptr));
        OnButtonCereatlin->setText(QApplication::translate("VTK_OCC_QtClass", "\345\210\233\345\273\272\347\272\277", nullptr));
        OnButtonCereatface->setText(QApplication::translate("VTK_OCC_QtClass", "\345\210\233\345\273\272\351\235\242", nullptr));
        menu->setTitle(QApplication::translate("VTK_OCC_QtClass", "\346\226\207\344\273\266", nullptr));
        menuOCC->setTitle(QApplication::translate("VTK_OCC_QtClass", "OCC\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QApplication::translate("VTK_OCC_QtClass", "\346\226\207\344\273\266\350\257\273\345\217\226", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VTK_OCC_QtClass: public Ui_VTK_OCC_QtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VTK_OCC_QT_H
