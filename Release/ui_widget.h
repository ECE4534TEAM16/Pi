/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLabel *label;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QLabel *label_9;
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QVBoxLayout *verticalLayout;
    QPushButton *mapperStart_button;
    QPushButton *userStart_button;
    QPushButton *mazeSolve_button;
    QSpacerItem *verticalSpacer_2;
    QPushButton *constraints_button;
    QPushButton *exit_button;
    QHBoxLayout *horizontalLayout;
    QListWidget *mapperList;
    QListWidget *userList;
    QSpacerItem *verticalSpacer_3;
    QWidget *tab_2;
    QGridLayout *gridLayout_3;
    QGraphicsView *mazeView;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(1000, 1000);
        gridLayout = new QGridLayout(Widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(Widget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_2);

        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QStringLiteral("label_4"));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout_2->addWidget(label_4);

        label_9 = new QLabel(tab);
        label_9->setObjectName(QStringLiteral("label_9"));
        QFont font1;
        font1.setFamily(QStringLiteral("Ubuntu"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setItalic(true);
        font1.setWeight(75);
        label_9->setFont(font1);
        label_9->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_9);

        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font2;
        font2.setPointSize(11);
        font2.setBold(true);
        font2.setItalic(false);
        font2.setUnderline(false);
        font2.setWeight(75);
        label_3->setFont(font2);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_3);

        label_5 = new QLabel(tab);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_5);

        label_6 = new QLabel(tab);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_6);

        label_7 = new QLabel(tab);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_2->addWidget(label_7);

        label_8 = new QLabel(tab);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_2->addWidget(label_8);


        gridLayout_2->addLayout(verticalLayout_2, 3, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        mapperStart_button = new QPushButton(tab);
        mapperStart_button->setObjectName(QStringLiteral("mapperStart_button"));

        verticalLayout->addWidget(mapperStart_button);

        userStart_button = new QPushButton(tab);
        userStart_button->setObjectName(QStringLiteral("userStart_button"));

        verticalLayout->addWidget(userStart_button);

        mazeSolve_button = new QPushButton(tab);
        mazeSolve_button->setObjectName(QStringLiteral("mazeSolve_button"));

        verticalLayout->addWidget(mazeSolve_button);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        constraints_button = new QPushButton(tab);
        constraints_button->setObjectName(QStringLiteral("constraints_button"));

        verticalLayout->addWidget(constraints_button);

        exit_button = new QPushButton(tab);
        exit_button->setObjectName(QStringLiteral("exit_button"));

        verticalLayout->addWidget(exit_button);


        gridLayout_2->addLayout(verticalLayout, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        mapperList = new QListWidget(tab);
        mapperList->setObjectName(QStringLiteral("mapperList"));
        mapperList->setProperty("isWrapping", QVariant(false));
        mapperList->setWordWrap(false);

        horizontalLayout->addWidget(mapperList);

        userList = new QListWidget(tab);
        userList->setObjectName(QStringLiteral("userList"));

        horizontalLayout->addWidget(userList);


        gridLayout_2->addLayout(horizontalLayout, 1, 1, 3, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 2, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_3 = new QGridLayout(tab_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        mazeView = new QGraphicsView(tab_2);
        mazeView->setObjectName(QStringLiteral("mazeView"));
        mazeView->setMouseTracking(false);

        gridLayout_3->addWidget(mazeView, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(Widget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Mapping Rovers", 0));
        label_2->setText(QApplication::translate("Widget", "Mapper Operation Log", 0));
        label->setText(QApplication::translate("Widget", "User Operation Log", 0));
        label_4->setText(QApplication::translate("Widget", "ECE 4534 Team 16", 0));
        label_9->setText(QApplication::translate("Widget", "Map Solving Robots", 0));
        label_3->setText(QApplication::translate("Widget", "Created by:", 0));
        label_5->setText(QApplication::translate("Widget", "Michael Chuber", 0));
        label_6->setText(QApplication::translate("Widget", "Austin Lamicella", 0));
        label_7->setText(QApplication::translate("Widget", "Owen Nugent", 0));
        label_8->setText(QApplication::translate("Widget", "Tyler Olson", 0));
        mapperStart_button->setText(QApplication::translate("Widget", "Start Mapper Rover", 0));
        userStart_button->setText(QApplication::translate("Widget", "Start User Rover", 0));
        mazeSolve_button->setText(QApplication::translate("Widget", "Solve Map", 0));
        constraints_button->setText(QApplication::translate("Widget", "Application Constraints", 0));
        exit_button->setText(QApplication::translate("Widget", "Exit Application", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Widget", "Control and Logs", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Widget", "Graphical Maze", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
