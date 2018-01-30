/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSlider *horizontalSlider;
    QToolButton *pushButtonPause;
    QToolButton *pushButtonPlay;
    QLCDNumber *lcdFrameNumber;
    QLabel *viewerLabel;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents_2;
    QWidget *verticalWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QComboBox *dirComboBox;
    QPushButton *browsePushButton;
    QComboBox *patternComboBox;
    QTableWidget *filesTable;
    QTableWidget *fileDetailTable;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1247, 820);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(2);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setTracking(true);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setInvertedAppearance(false);
        horizontalSlider->setInvertedControls(false);
        horizontalSlider->setTickPosition(QSlider::TicksBelow);
        horizontalSlider->setTickInterval(5);

        gridLayout->addWidget(horizontalSlider, 1, 2, 1, 2);

        pushButtonPause = new QToolButton(centralWidget);
        pushButtonPause->setObjectName(QStringLiteral("pushButtonPause"));
        pushButtonPause->setEnabled(true);
        pushButtonPause->setMinimumSize(QSize(48, 24));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        pushButtonPause->setFont(font);
        pushButtonPause->setAutoFillBackground(true);
        pushButtonPause->setArrowType(Qt::NoArrow);

        gridLayout->addWidget(pushButtonPause, 1, 1, 1, 1);

        pushButtonPlay = new QToolButton(centralWidget);
        pushButtonPlay->setObjectName(QStringLiteral("pushButtonPlay"));
        pushButtonPlay->setEnabled(true);
        pushButtonPlay->setMinimumSize(QSize(48, 24));
        pushButtonPlay->setArrowType(Qt::RightArrow);

        gridLayout->addWidget(pushButtonPlay, 1, 0, 1, 1);

        lcdFrameNumber = new QLCDNumber(centralWidget);
        lcdFrameNumber->setObjectName(QStringLiteral("lcdFrameNumber"));
        lcdFrameNumber->setEnabled(true);
        lcdFrameNumber->setMaximumSize(QSize(40, 16777215));
        QFont font1;
        font1.setPointSize(6);
        font1.setBold(true);
        font1.setWeight(75);
        lcdFrameNumber->setFont(font1);
        lcdFrameNumber->setFrameShape(QFrame::StyledPanel);
        lcdFrameNumber->setFrameShadow(QFrame::Plain);
        lcdFrameNumber->setLineWidth(1);
        lcdFrameNumber->setMidLineWidth(0);
        lcdFrameNumber->setSmallDecimalPoint(false);
        lcdFrameNumber->setSegmentStyle(QLCDNumber::Flat);

        gridLayout->addWidget(lcdFrameNumber, 1, 4, 1, 1);

        viewerLabel = new QLabel(centralWidget);
        viewerLabel->setObjectName(QStringLiteral("viewerLabel"));
        sizePolicy.setHeightForWidth(viewerLabel->sizePolicy().hasHeightForWidth());
        viewerLabel->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setKerning(true);
        viewerLabel->setFont(font2);
        viewerLabel->setCursor(QCursor(Qt::CrossCursor));
        viewerLabel->setMouseTracking(true);
        viewerLabel->setScaledContents(true);
        viewerLabel->setAlignment(Qt::AlignCenter);
        viewerLabel->setTextInteractionFlags(Qt::LinksAccessibleByKeyboard|Qt::LinksAccessibleByMouse);

        gridLayout->addWidget(viewerLabel, 0, 0, 1, 5);

        MainWindow->setCentralWidget(centralWidget);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        sizePolicy.setHeightForWidth(dockWidget->sizePolicy().hasHeightForWidth());
        dockWidget->setSizePolicy(sizePolicy);
        dockWidget->setMinimumSize(QSize(258, 322));
        dockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(dockWidgetContents_2->sizePolicy().hasHeightForWidth());
        dockWidgetContents_2->setSizePolicy(sizePolicy1);
        dockWidgetContents_2->setMinimumSize(QSize(258, 300));
        dockWidgetContents_2->setSizeIncrement(QSize(2, 2));
        dockWidgetContents_2->setAutoFillBackground(false);
        verticalWidget = new QWidget(dockWidgetContents_2);
        verticalWidget->setObjectName(QStringLiteral("verticalWidget"));
        verticalWidget->setGeometry(QRect(10, -10, 258, 800));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(verticalWidget->sizePolicy().hasHeightForWidth());
        verticalWidget->setSizePolicy(sizePolicy2);
        verticalWidget->setMinimumSize(QSize(258, 300));
        verticalWidget->setBaseSize(QSize(0, 0));
        verticalWidget->setAcceptDrops(true);
        verticalWidget->setAutoFillBackground(false);
        verticalLayout = new QVBoxLayout(verticalWidget);
        verticalLayout->setSpacing(4);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout->setContentsMargins(1, 9, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        dirComboBox = new QComboBox(verticalWidget);
        dirComboBox->setObjectName(QStringLiteral("dirComboBox"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(dirComboBox->sizePolicy().hasHeightForWidth());
        dirComboBox->setSizePolicy(sizePolicy3);
        dirComboBox->setMinimumSize(QSize(0, 0));
        dirComboBox->setEditable(true);

        horizontalLayout->addWidget(dirComboBox);

        browsePushButton = new QPushButton(verticalWidget);
        browsePushButton->setObjectName(QStringLiteral("browsePushButton"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(9);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(browsePushButton->sizePolicy().hasHeightForWidth());
        browsePushButton->setSizePolicy(sizePolicy4);
        browsePushButton->setMaximumSize(QSize(40, 16777215));

        horizontalLayout->addWidget(browsePushButton);


        verticalLayout->addLayout(horizontalLayout);

        patternComboBox = new QComboBox(verticalWidget);
        patternComboBox->setObjectName(QStringLiteral("patternComboBox"));
        sizePolicy3.setHeightForWidth(patternComboBox->sizePolicy().hasHeightForWidth());
        patternComboBox->setSizePolicy(sizePolicy3);
        patternComboBox->setMinimumSize(QSize(255, 0));
        patternComboBox->setToolTipDuration(-1);
        patternComboBox->setEditable(true);

        verticalLayout->addWidget(patternComboBox);

        filesTable = new QTableWidget(verticalWidget);
        if (filesTable->columnCount() < 1)
            filesTable->setColumnCount(1);
        filesTable->setObjectName(QStringLiteral("filesTable"));
        filesTable->setEnabled(true);
        sizePolicy.setHeightForWidth(filesTable->sizePolicy().hasHeightForWidth());
        filesTable->setSizePolicy(sizePolicy);
        filesTable->setMinimumSize(QSize(255, 0));
        filesTable->setAcceptDrops(true);
        filesTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        filesTable->setDragEnabled(true);
        filesTable->setDragDropMode(QAbstractItemView::DropOnly);
        filesTable->setAlternatingRowColors(true);
        filesTable->setShowGrid(true);
        filesTable->setSortingEnabled(true);
        filesTable->setWordWrap(false);
        filesTable->setCornerButtonEnabled(true);
        filesTable->setColumnCount(1);
        filesTable->horizontalHeader()->setVisible(false);
        filesTable->horizontalHeader()->setCascadingSectionResizes(true);
        filesTable->horizontalHeader()->setDefaultSectionSize(108);
        filesTable->horizontalHeader()->setStretchLastSection(true);
        filesTable->verticalHeader()->setVisible(false);
        filesTable->verticalHeader()->setDefaultSectionSize(18);
        filesTable->verticalHeader()->setProperty("showSortIndicator", QVariant(true));
        filesTable->verticalHeader()->setStretchLastSection(false);

        verticalLayout->addWidget(filesTable);

        fileDetailTable = new QTableWidget(verticalWidget);
        if (fileDetailTable->columnCount() < 2)
            fileDetailTable->setColumnCount(2);
        fileDetailTable->setObjectName(QStringLiteral("fileDetailTable"));
        fileDetailTable->setEnabled(false);
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(fileDetailTable->sizePolicy().hasHeightForWidth());
        fileDetailTable->setSizePolicy(sizePolicy5);
        fileDetailTable->setMinimumSize(QSize(255, 0));
        fileDetailTable->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));
        fileDetailTable->setFocusPolicy(Qt::WheelFocus);
        fileDetailTable->setAcceptDrops(true);
        fileDetailTable->setToolTipDuration(9999);
        fileDetailTable->setAutoFillBackground(true);
        fileDetailTable->setDefaultDropAction(Qt::ActionMask);
        fileDetailTable->setShowGrid(false);
        fileDetailTable->setWordWrap(false);
        fileDetailTable->setColumnCount(2);
        fileDetailTable->horizontalHeader()->setVisible(false);
        fileDetailTable->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(fileDetailTable);

        dockWidget->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Video Compress", Q_NULLPTR));
        pushButtonPause->setText(QApplication::translate("MainWindow", "||", Q_NULLPTR));
        pushButtonPlay->setText(QApplication::translate("MainWindow", "Go!", Q_NULLPTR));
        viewerLabel->setText(QString());
        dockWidget->setWindowTitle(QApplication::translate("MainWindow", "File Selection", Q_NULLPTR));
        dirComboBox->clear();
        dirComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "C:/Users/m/Desktop/rbc_track", Q_NULLPTR)
         << QApplication::translate("MainWindow", "C:/", Q_NULLPTR)
        );
#ifndef QT_NO_TOOLTIP
        dirComboBox->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Directory to search</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        browsePushButton->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Browse for directory</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        browsePushButton->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        patternComboBox->clear();
        patternComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "*.avi", Q_NULLPTR)
         << QApplication::translate("MainWindow", "*.mov", Q_NULLPTR)
         << QApplication::translate("MainWindow", "*.mp4", Q_NULLPTR)
         << QApplication::translate("MainWindow", "*.mkv", Q_NULLPTR)
         << QApplication::translate("MainWindow", "*", Q_NULLPTR)
        );
#ifndef QT_NO_TOOLTIP
        patternComboBox->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Pattern to match.  * is a wildcard or 'anything'.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        patternComboBox->setStatusTip(QApplication::translate("MainWindow", "this is a stastus tip?", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_TOOLTIP
        filesTable->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>List of all files in the chosen directory matching the specifed pattern.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        filesTable->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_TOOLTIP
        fileDetailTable->setToolTip(QApplication::translate("MainWindow", "Some video file metadata", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        fileDetailTable->setWhatsThis(QApplication::translate("MainWindow", "Some video file metadata", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
