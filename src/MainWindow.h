#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QImage>
#include <QPixmap>
#include <QComboBox>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <QDesktopServices>
#include <QByteArray>
#include <QDockWidget>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QTimer>
#include <QDir>
#include <QEvent>
#include <QMouseEvent>

#include <string>

#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"

#include "VideoCapturePlusQt.h"
#include "VideoWriterPlusQt.h"
#include "RegionCollection.h"
#include "Region.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    bool videoIsRunning, readyForNewPixmap;
    Ui::MainWindow *ui;
    QDir currentDir;
    QString currentDirString, currentFilterString, currentOpenFile, currentOpenFileDetail;
    cv::Mat currentImg;
    VideoCapturePlusQt* pCap;
    VideoWriterPlusQt* pWriter;
    double timestampMsec;
    QPixmap pixmap1, pixmap2, *debugPixmap1, *debugPixmap2, *debugPixmap3;
    QDockWidget* dockWidgetCompressionControls;
    QLabel *labelDebug1, *labelDebug2, *labelDebug3;

    void addToComboBoxHistory(QComboBox* pComboBox, QString stringToAdd);
    bool Display_Current_Image(bool advanceFrame=false);
    bool Load_File(QString fileName);
    QString Get_File_Name_At_Row(int row);
    void Grabber_Thread(void);
    void Stop_Running_Grabber(void);
    void Create_Compression_Dock(void);
    void Saver_Thread(void);

    //a bunch of options for how this thing behaves
    bool stepWise, convertToBw;
    int camNo;

    bool compressionDockCreated, grabberThreadDone;
    double playerFps;

    RegionCollection<Region> rCollect;
    cv::Size vImgSize;
    std::string outputDir;
    
    cv::Mat vidImage, annotatedVidImage, grayVidImage;
    QEvent::Type lastType;
    
//    void Set_Tracking_Vars(void);
//    void Initialize_Tracking_Stuff(void);
//    void Process_Tracking(void);
//    void Stop_Running_Grabber(void);

//    void Display_Debug1(void);
//    void Display_Debug2(void);

    QComboBox* comboBoxCodec;
    QComboBox* comboBoxSaveDir;
    QDoubleSpinBox* spinBoxFrameRate;
    QSpinBox* spinBoxStartFrame;
    QSpinBox* spinBoxEndFrame;
    QVBoxLayout* vLayoutCompression;
    QPushButton* pushButtonSave;
    QProgressBar* progressBarSave;
    QLabel* textLabelDoneMessage;

signals:
    void Send_Pixmap_To_Display(QPixmap* pPixmap);
    void Send_Mat_To_Display(cv::Mat* pMat);
    void Send_Update_Progress_Bar(int val);
    void Send_Delete_Done_Message(void);
    //void Send_Pixmap_To_Display_Track(QPixmap* pPixmap);
//    void Send_Pixmap_To_Display_Debug1(QPixmap* pPixmap);
//    void Send_Pixmap_To_Display_Debug2(QPixmap* pPixmap);


private slots:
    void Browse_Dir(void);
    void Get_Files_In_Dir(void);
    //void Show_Files_In_FileList(void);
    void Show_File_Details(int row, int column);
    //void on_filesTable_cellActivated(int row, int column);
    void on_filesTable_cellClicked(int row, int column);
    void Run_Video(void);
    void Pause_Video(void);

    void Receive_Pixmap_To_Display(QPixmap* pPixmap);
    void Receive_Mat_To_Display(cv::Mat* pMat);
    //void Receive_Pixmap_To_Display_Track(QPixmap* pPixmap);
//    void Receive_Pixmap_To_Display_Debug1(QPixmap* pPixmap);
//    void Receive_Pixmap_To_Display_Debug2(QPixmap* pPixmap);

//    void on_checkBox_debug1_toggled(bool checked);
//    void on_checkBox_debug2_toggled(bool checked);
//    void on_checkBox_debug3_toggled(bool checked);
    void on_horizontalSlider_sliderMoved(int position);
    void on_Browse_Save_Dir_Clicked(void);
    void on_Set_Start_Frame_Clicked(void);
    void on_Set_End_Frame_Clicked(void);
    void Start_Save(void);
    void Receive_Update_Progress_bar(int val);
    void Delete_Done_Message(void);

    void Update_Compression_For_Video(bool something);
    void Raise_Compression_Controls(int row, int column);

    void resizeEvent(QResizeEvent* event);

    bool eventFilter(QObject* target, QEvent* event);  //do i need this?
    //void mouseMoveEvent();
};

#endif // MAINWINDOW_H

