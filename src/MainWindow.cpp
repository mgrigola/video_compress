#include "MainWindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    pCap(new VideoCapturePlusQt),
    currentOpenFile(""),
    readyForNewPixmap(true),
    grabberThreadDone(true),
    convertToBw(false)
{
    ui->setupUi(this);
    ui->fileDetailTable->hide();
    ui->pushButtonPlay->hide();
    ui->pushButtonPause->hide();
    ui->horizontalSlider->hide();
    ui->lcdFrameNumber->hide();

    //Connect shit
    connect(ui->browsePushButton, SIGNAL(clicked(bool)), this, SLOT(Browse_Dir()) );
    connect(ui->dirComboBox, SIGNAL(editTextChanged(QString)), this, SLOT(Get_Files_In_Dir()) );
    connect(ui->dirComboBox, SIGNAL(activated(QString)), this, SLOT(Get_Files_In_Dir()) );
    connect(ui->patternComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT( Get_Files_In_Dir()) );
    connect(ui->pushButtonPlay, SIGNAL(clicked(bool)), this, SLOT(Run_Video()));
    connect(ui->pushButtonPause, SIGNAL(clicked(bool)), this, SLOT(Pause_Video()));
    connect(this, SIGNAL(Send_Pixmap_To_Display(QPixmap*)), this, SLOT(Receive_Pixmap_To_Display(QPixmap*)) );
    connect(ui->filesTable, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(Raise_Compression_Controls(int,int)) );

    playerFps = 60.0;
    //ui->viewerLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    //ui->viewerLabel->setScaledContents(true);

    Get_Files_In_Dir();

    compressionDockCreated = false;
    //trackingDockCreated = false, displayDebug1=false, displayDebug2=false, displayDebug3=false;

    ui->viewerLabel->installEventFilter(this);

    rCollect.Set_Allow_Multiple_Regions(false);
    rCollect.Set_Allow_Nonrectangularity(false);
}



MainWindow::~MainWindow()
{
    delete ui;
    delete pCap;
}

void MainWindow::Browse_Dir(void)
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Select Folder with Video Files"), ui->dirComboBox->currentText() );

    if (!directory.isEmpty())
    {
        if (ui->dirComboBox->findText(directory) == -1)
            ui->dirComboBox->addItem(directory);
        ui->dirComboBox->setCurrentIndex(ui->dirComboBox->findText(directory));
    }
    Get_Files_In_Dir();
}

void MainWindow::Get_Files_In_Dir(void)
{
    ui->filesTable->setRowCount(0);

    currentDirString = ui->dirComboBox->currentText();
    currentDir = QDir(currentDirString);
    currentFilterString = ui->patternComboBox->currentText();
    if (currentFilterString.isEmpty())
        currentFilterString = "*";

    addToComboBoxHistory(ui->patternComboBox, currentFilterString);
    addToComboBoxHistory(ui->dirComboBox, currentDirString);

    QStringList fileList = currentDir.entryList(QStringList(currentFilterString), QDir::Files | QDir::NoSymLinks);
    for (const QString& pFileString : fileList)
    {
        //QFile file(currentDir.absoluteFilePath(pString));
        QTableWidgetItem* pFileNameItem = new QTableWidgetItem(pFileString);
        pFileNameItem->setFlags(pFileNameItem->flags() ^ Qt::ItemIsEditable);
        int row = ui->filesTable->rowCount();
        ui->filesTable->insertRow(row);
        ui->filesTable->setItem(row, 0, pFileNameItem);
    }
}

void MainWindow::addToComboBoxHistory(QComboBox* pComboBox, QString stringToAdd)
{
    if (pComboBox->findText(stringToAdd) == -1)
        pComboBox->addItem(stringToAdd);
}


void MainWindow::on_filesTable_cellClicked(int row, int column)
{
    QString fileName = Get_File_Name_At_Row(row);
    if (Load_File(fileName))
    {
        currentOpenFile = fileName;

        Show_File_Details(row, column);
        if (Display_Current_Image())
            std::cout << "Showing first frame" << std::endl;

        ui->pushButtonPlay->show();
        ui->pushButtonPause->show();
        ui->lcdFrameNumber->show();
        ui->horizontalSlider->show();
        ui->horizontalSlider->setMaximum(pCap->frameCount-1);
        ui->horizontalSlider->setValue(pCap->frameNo);
    }
}

void MainWindow::Show_File_Details(int row, int column)
{
    QTableWidget* pDTable = ui->fileDetailTable;

    pDTable->setRowCount(6);
    pDTable->clear();
    pDTable->setSortingEnabled(false);
    pDTable->setDisabled(true);
    pDTable->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));
    pDTable->show();

    pDTable->setItem(0, 0, new QTableWidgetItem("Codec:") );
    pDTable->setItem(0, 1, new QTableWidgetItem(pCap->codec.c_str()) );

    //playerFps = pCap->fps;
    std::string fps = std::to_string(static_cast<int>(pCap->fps)) + "." + std::to_string(static_cast<int>(100.0 * pCap->fps) % 100);
    pDTable->setItem(1, 0, new QTableWidgetItem("Framerate:") );
    pDTable->setItem(1, 1, new QTableWidgetItem(fps.c_str()) );

    std::string frameCount = std::to_string(pCap->frameCount);
    pDTable->setItem(2, 0, new QTableWidgetItem("Frames:") );
    pDTable->setItem(2, 1, new QTableWidgetItem(frameCount.c_str()) );

    double vidTime = pCap->frameCount / pCap->fps;
    int vidMinutes = static_cast<int>(vidTime) / 60;
    std::string vidMinutesStr = std::to_string(vidMinutes);
    int vidSeconds = static_cast<int>(vidTime) % 60;
    std::string vidSecondsStr = (vidSeconds<10 ? "0" : "") + std::to_string(vidSeconds);
    std::string vidLengthStr = vidMinutesStr + ":" + vidSecondsStr;
    pDTable->setItem(3, 0, new QTableWidgetItem("Length:") );
    pDTable->setItem(3, 1, new QTableWidgetItem(vidLengthStr.c_str()) );

    std::string vidSizeStr = std::to_string(pCap->size.width) + "x" + std::to_string(pCap->size.height);
    pDTable->setItem(4, 0, new QTableWidgetItem("Resolution:") );
    pDTable->setItem(4, 1, new QTableWidgetItem(vidSizeStr.c_str()) );

    QFile openFile(currentOpenFile);
    long fSz = static_cast<int64>(openFile.size());
    int fileSizeMB = (fSz+51200)/1024000;
    int fileSizeKB = (fSz - (1024000*fileSizeMB) + 51200)/100000;
    //int fileSizeKB = std::floor( std::max(fSz - (1024000*fileSizeMB), long(0))/100000);
    std::string fileSizeStr = std::to_string(fileSizeMB) + "." + std::to_string(fileSizeKB) +  "MB";
    pDTable->setItem(5, 0, new QTableWidgetItem("File Size:") );
    pDTable->setItem(5, 1, new QTableWidgetItem(fileSizeStr.c_str()) );


    std::cout << "fileDetails: " << ui->filesTable->item(row, column)->text().toStdString() << std::endl;
}

bool MainWindow::Load_File(QString fileName)
{
    Stop_Running_Grabber();

    if (fileName == currentOpenFile)
    {
        std::cout << "load is same file - " << fileName.toStdString() << std::endl;
        return false;
    }

    std::cout << "Before stop read" << std::endl;
    pCap->Stop_Read();
    std::cout << "After stop read" << std::endl;

    //std::this_thread::sleep_for(std::chrono::milliseconds(10));
    if (!pCap->Start_Read(fileName.toStdString().c_str(), fileName.toStdString().c_str()))
    {
        std::cout << "failed to start read" << std::endl;
        return false;
    }

//    if (!trackingDockCreated)
//    {
//        Create_Tracking_Dock();
//        trackingDockCreated = true;
//    }

    if  (!compressionDockCreated)
    {
        Create_Compression_Dock();
        compressionDockCreated = true;
    }

    rCollect.Set_Image_Size(pCap->size);

    //std::this_thread::sleep_for(std::chrono::milliseconds(10));  //***THIS IS APPARENTLY NECESSARY TO BE ABLE TO DISPLAY THE FIRST FRAME AFTERWARD?!!?***
    std::cout << "Loaded: " << fileName.toStdString() << std::endl;
    return true;
}

QString MainWindow::Get_File_Name_At_Row(int row)
{
    return currentDirString + "/" + ui->filesTable->item(row, 0)->text();
}

bool MainWindow::Display_Current_Image(bool advanceFrame)
{
    bool jobsDone = false;
    int failCount = -1;

    cv::Mat vImg, gvImg, gRgbImg;

    while (!jobsDone && ++failCount<50)
    {
        pCap->Get_Frame(vImg, gvImg, gRgbImg, timestampMsec, false);
        if (vImg.empty())
            std::this_thread::sleep_for(std::chrono::milliseconds(20));  //***THIS IS APPARENTLY NECESSARY TO BE ABLE TO DISPLAY THE FIRST FRAME AFTERWARD?!!?***
        else
            jobsDone = true;
    }
    if (failCount == 50)
    {
        std::cout << "Failed to load video / retrieve image?" << std::endl;
        return false;
    }

    std::cout << "Displaying Current Image" << std::endl;

    if (rCollect.size() > 0)  rCollect.Draw_Regions(vImg, false, true, true);

    QImage::Format fmt = (vImg.channels()==1) ? QImage::Format_Grayscale8 : QImage::Format_RGB888;
    QImage qImage((uchar*)vImg.data, vImg.cols, vImg.rows, vImg.step, fmt);
    pixmap1 = QPixmap::fromImage(qImage);

    if (!pixmap1.isNull())  { emit( Send_Pixmap_To_Display(&pixmap1) ); }
    else  { return false; }

    return true;
}




void MainWindow::Run_Video(void)
{
    std::thread grabberThread = std::thread(&MainWindow::Grabber_Thread, this);
    grabberThread.detach();
}


void MainWindow::Pause_Video()
{
    videoIsRunning = false;
}

void MainWindow::Receive_Pixmap_To_Display(QPixmap* pPixmap)
{
    std::cout << "Receiving Pixmap" << std::endl;
    ui->viewerLabel->setPixmap(pPixmap->scaled(ui->viewerLabel->width(), ui->viewerLabel->height(), Qt::KeepAspectRatio) );
    //ui->viewerLabel->setPixmap( *pPixmap );
    ui->viewerLabel->repaint();
    ui->horizontalSlider->setValue(pCap->frameNo);
    ui->lcdFrameNumber->display(int(pCap->frameNo));
}


void MainWindow::Receive_Mat_To_Display(cv::Mat* pMat)
{
    std::cout << "Receiving Mat" << std::endl;

    QImage::Format frmt = pMat->channels() == 1 ? QImage::Format_Grayscale8 : QImage::Format_RGB888;
    QImage qImg((uchar*)pMat->data, pMat->cols, pMat->rows, pMat->step, frmt);
    QPixmap pxmap = QPixmap::fromImage(qImg);

    ui->viewerLabel->setPixmap(pxmap.scaled(ui->viewerLabel->width(), ui->viewerLabel->height(), Qt::KeepAspectRatio) );
    ui->viewerLabel->repaint();
}






void MainWindow::Grabber_Thread(void)
{
    videoIsRunning = true;
    grabberThreadDone = false;
    int startFrame = pCap->frameNo;
    double cpuFreq = cv::getTickFrequency()*1000;
    double zeroTime = cv::getCPUTickCount();

    cv::Mat cvImage;
    bool evenOdd = false;
    std::cout << "starting grabber thread" << std::endl;

    while (pCap->isOkay && videoIsRunning && pCap->frameNo < pCap->frameCount)
    {
        if (!pCap->Get_Frame(vidImage, grayVidImage, annotatedVidImage, timestampMsec, true))
        {
            std::cout << "Failed frame: " << pCap->frameNo << std::endl;
            continue;
        }

        if (rCollect.size() > 0)  rCollect.Draw_Regions(vidImage, false, true, true);

        QImage::Format fmt = (vidImage.channels()==1) ? QImage::Format_Grayscale8 : QImage::Format_RGB888;
        QImage qImage = QImage((uchar*)vidImage.data, vidImage.cols, vidImage.rows, vidImage.step, fmt);

        if (evenOdd)
        {
            pixmap1 = QPixmap::fromImage(qImage);
            while (!readyForNewPixmap || (cv::getCPUTickCount()-zeroTime)/cpuFreq < (static_cast<double>(pCap->frameNo - startFrame)/pCap->fps) )  std::this_thread::sleep_for(std::chrono::milliseconds(10));
            emit( Send_Pixmap_To_Display(&pixmap1) );
        }
        else
        {
            pixmap2 = QPixmap::fromImage(qImage);
            while (!readyForNewPixmap || (cv::getCPUTickCount()-zeroTime)/cpuFreq < (static_cast<double>(pCap->frameNo - startFrame)/pCap->fps) )  std::this_thread::sleep_for(std::chrono::milliseconds(10));
            //std::cout << (cv::getCPUTickCount()-zeroTime)/cpuFreq << " <? " << (static_cast<double>(pCap->frameNo)/pCap->fps) << std::endl;
            emit( Send_Pixmap_To_Display(&pixmap2) );
        }
        evenOdd = !evenOdd;
    }

    grabberThreadDone = true;
    videoIsRunning = false;
    std::cout << "exiting grabber thread" << std::endl;
}


void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    // //    pCap->Set_Pause_Buffering(true);
    pCap->Set_Frame_No(position);
    Display_Current_Image();
    std::cout << "Horizontal slider MOVED: " << position << std::endl;
}


void MainWindow::Stop_Running_Grabber(void)
{
    if (videoIsRunning)
    {
        videoIsRunning = false;
        while (!grabberThreadDone) std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}





void MainWindow::Create_Compression_Dock(void)
{
    dockWidgetCompressionControls = new QDockWidget(tr("Compress and Save"), this);
    dockWidgetCompressionControls->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::AllDockWidgetFeatures);
    tabifyDockWidget(ui->dockWidget, dockWidgetCompressionControls);
    QWidget* widgetCompressionControlsContent = new QWidget(dockWidgetCompressionControls);
    dockWidgetCompressionControls->setWidget(widgetCompressionControlsContent);

    //Directory & browse  -  hLayoutSaveDir
    comboBoxSaveDir = new QComboBox(dockWidgetCompressionControls);
    for (int idx=0; idx < ui->dirComboBox->count(); idx++)  { comboBoxSaveDir->addItem(ui->dirComboBox->itemText(idx)); }
    comboBoxSaveDir->setCurrentText(ui->dirComboBox->currentText());
    comboBoxSaveDir->setEditable(true);
    comboBoxSaveDir->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));
    comboBoxSaveDir->setToolTip("<html><head/><body><p>Directory to save</p></body></html>");

    QPushButton* pushButtonBrowseSaveDir = new QPushButton("...",dockWidgetCompressionControls);
    pushButtonBrowseSaveDir->setToolTip("<html><head/><body><p>Browse for directory</p></body></html>");
    pushButtonBrowseSaveDir->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    pushButtonBrowseSaveDir->setMaximumWidth(32);
    connect(pushButtonBrowseSaveDir, SIGNAL(clicked(bool)), this, SLOT(on_Browse_Save_Dir_Clicked(void)));

    QHBoxLayout* hLayoutSaveDir = new QHBoxLayout(dockWidgetCompressionControls);
    hLayoutSaveDir->addWidget(comboBoxSaveDir,1);
    hLayoutSaveDir->addWidget(pushButtonBrowseSaveDir,0);


    //Codec & framerate  -  hLayoutSaveParams
    comboBoxCodec = new QComboBox(dockWidgetCompressionControls);
    comboBoxCodec->insertItems(0, QStringList() << "X264" << "H264" << "DIVX" << "XVID" << "FMP4" << "MP4A" << "None");

    spinBoxFrameRate = new QDoubleSpinBox(dockWidgetCompressionControls);
    spinBoxFrameRate->setValue(30.0);

    QHBoxLayout* hLayoutSaveParams = new QHBoxLayout(dockWidgetCompressionControls);
    hLayoutSaveParams->addWidget(comboBoxCodec);
    hLayoutSaveParams->addWidget(spinBoxFrameRate);

    //Start/End frame buttons  -  hLayoutStartEndFrames
    spinBoxStartFrame = new QSpinBox(dockWidgetCompressionControls);
    spinBoxStartFrame->clear();
    spinBoxStartFrame->setMinimum(0);

    QPushButton* pushButtonSetStartFrame = new QPushButton("set", dockWidgetCompressionControls);
    pushButtonSetStartFrame->setMaximumWidth(28);
    connect(pushButtonSetStartFrame, SIGNAL(clicked(bool)), this, SLOT(on_Set_Start_Frame_Clicked()));

    spinBoxEndFrame = new QSpinBox(dockWidgetCompressionControls);
    spinBoxEndFrame->clear();
    spinBoxEndFrame->setMinimum(0);

    QPushButton* pushButtonSetEndFrame = new QPushButton("set", dockWidgetCompressionControls);
    pushButtonSetEndFrame->setMaximumWidth(28);
    connect(pushButtonSetEndFrame, SIGNAL(clicked(bool)), this, SLOT(on_Set_End_Frame_Clicked()));

    QHBoxLayout* hLayoutStartEndFrames = new QHBoxLayout(dockWidgetCompressionControls);
    hLayoutSaveDir->setSpacing(4);
    hLayoutStartEndFrames->addWidget(spinBoxStartFrame);
    hLayoutStartEndFrames->addWidget(pushButtonSetStartFrame);
    hLayoutStartEndFrames->addWidget(spinBoxEndFrame);
    hLayoutStartEndFrames->addWidget(pushButtonSetEndFrame);
    hLayoutStartEndFrames->insertSpacerItem(2, new QSpacerItem(20,1) );

    //The start/save button  -  pushButtonSave
    pushButtonSave = new QPushButton("Save!", dockWidgetCompressionControls);
    connect(pushButtonSave, SIGNAL(clicked(bool)), this, SLOT(Start_Save()));

    //Add it all together in vlayout
    vLayoutCompression = new QVBoxLayout(dockWidgetCompressionControls);
    vLayoutCompression->setSpacing(6);
    vLayoutCompression->addLayout(hLayoutSaveDir);
    //vLayoutCompression->addWidget(comboBoxSaveFile);
    vLayoutCompression->addLayout(hLayoutSaveParams);
    vLayoutCompression->addLayout(hLayoutStartEndFrames);
    vLayoutCompression->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Expanding));
    vLayoutCompression->addWidget(pushButtonSave);

    widgetCompressionControlsContent->setLayout(vLayoutCompression);

    connect(dockWidgetCompressionControls, SIGNAL(visibilityChanged(bool)), this, SLOT(Update_Compression_For_Video(bool)) );
}


void MainWindow::on_Browse_Save_Dir_Clicked(void)
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Select Folder to Save Compressed Output"), comboBoxSaveDir->currentText() );

    if (!directory.isEmpty())
    {
        if (comboBoxSaveDir->findText(directory) == -1)
            comboBoxSaveDir->addItem(directory);
        comboBoxSaveDir->setCurrentIndex(comboBoxSaveDir->count()-1);
    }
}

void MainWindow::on_Set_Start_Frame_Clicked(void)
{
    spinBoxStartFrame->setValue(pCap->frameNo);
}

void MainWindow::on_Set_End_Frame_Clicked(void)
{
    spinBoxEndFrame->setValue(pCap->frameNo);
}


void MainWindow::Start_Save(void)
{
    progressBarSave = new QProgressBar(dockWidgetCompressionControls);
    progressBarSave->setValue(0);
    vLayoutCompression->insertWidget(4, progressBarSave);
    connect( this, SIGNAL(Send_Update_Progress_Bar(int)), this, SLOT(Receive_Update_Progress_bar(int)) );
    //connect( this, SIGNAL(Send_Delete_Done_Message()), this, SLOT(Delete_Done_Message()) );
    pushButtonSave->hide();

    std::thread saverThread = std::thread(&MainWindow::Saver_Thread, this);
    saverThread.detach();
    std::cout << "Successfully detached thread" << std::endl;
    return;
}


void MainWindow::Saver_Thread(void)
{
    cv::Mat imgToUse;
    std::cout << "starting saver thread" << std::endl;

    videoIsRunning = true;
    grabberThreadDone = false;
    size_t maxAcceptableBufferSize = 16;
    int waitTime = 10;

    int endFrame = pCap->frameCount;
    if (spinBoxEndFrame->value() > 0 && spinBoxEndFrame->value()<pCap->frameCount)  { endFrame = spinBoxEndFrame->value(); }

    int startFrame = 0;
    if (spinBoxStartFrame->value() > 0 && spinBoxStartFrame->value() < endFrame)  { startFrame = spinBoxStartFrame->value(); }

    std::string sCodec = comboBoxCodec->currentText().toStdString();
    int codec = (sCodec.compare("None")==0) ? 0 : cv::VideoWriter::fourcc(sCodec[0],sCodec[1],sCodec[2],sCodec[3]);

    double frameRate = spinBoxFrameRate->value();
    double quality = 100.0;

    if ( !QDir( comboBoxSaveDir->currentText() ).exists() )
        QDir().mkdir( comboBoxSaveDir->currentText() );

    pWriter = new VideoWriterPlusQt(codec, frameRate, quality);
    std::string saveDir = comboBoxSaveDir->currentText().toStdString();
    std::string saveFile = pCap->openFileName + "_" + sCodec;

    pWriter->Add_Stream( saveDir + "/" + saveFile + ".avi");
    pWriter->Start_Save();

    pCap->Set_Frame_No(startFrame);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));


    while (pCap->isOkay && videoIsRunning && pCap->frameNo < endFrame)
    {
        //if read is faster than write, buffer will otherwise grow to consume all system ram, so we sleep if buffer is too large and keep doubling sleep time every successive wait
        if (pWriter->writeBuffer.size() > maxAcceptableBufferSize)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
            waitTime = waitTime*2;
        }
        else
        {
            waitTime = std::max(waitTime/2, 10);
        }

        if (!pCap->Get_Frame(vidImage, grayVidImage, annotatedVidImage, timestampMsec, true))
        {
            std::cout << "Failed frame: " << pCap->frameNo << std::endl;
            continue;
        }


        if (rCollect.size() > 0)
        {
            cv::Rect boundedRect(rCollect[0]->bRect);
            boundedRect.width = std::max(1,boundedRect.width);
            boundedRect.height = std::max(1,boundedRect.height);
            //imgToUse = vidImage(sRegions[0].bRect);
            if (convertToBw)  imgToUse = grayVidImage(boundedRect);
            else imgToUse = vidImage(boundedRect);
        }
        else
        {
            if (convertToBw)  imgToUse = grayVidImage;
            else  imgToUse = vidImage;
        }

        //Add here stuff like bound box, convert to BW, etc (need checkboxes or something).
        //if wanna display the frames as processed here too
        pWriter->Write_Frame(vidImage);
        int progressVal = (100*(pCap->frameNo-startFrame))/(endFrame - startFrame + 1);
        emit( Send_Update_Progress_Bar(progressVal) );
    }

    pWriter->Stop_Save(true);

    int endVal = (pCap->frameNo == endFrame && pCap->isOkay) ? -1 : -2;
    emit(Send_Update_Progress_Bar( endVal ));
    grabberThreadDone = true;
}

void MainWindow::Raise_Compression_Controls(int row, int column)
{
    dockWidgetCompressionControls->raise();
}

void MainWindow::Receive_Update_Progress_bar(int val)
{
    if (val < 0 )
    {
        delete progressBarSave;
        pushButtonSave->show();
        QString displayText = val == -1 ? "Done!" : "Failed?";
        textLabelDoneMessage = new QLabel(displayText, dockWidgetCompressionControls);
        vLayoutCompression->insertWidget(4, textLabelDoneMessage);
        QTimer::singleShot(4000, this, SLOT(Delete_Done_Message()) );
    }
    else  progressBarSave->setValue( val );
}

void MainWindow::Delete_Done_Message(void)
{
    //delete progressBarSave;
    delete textLabelDoneMessage;
}

void MainWindow::Update_Compression_For_Video(bool something)
{
    spinBoxStartFrame->setValue(0);
    spinBoxEndFrame->setMaximum(pCap->frameCount);
    spinBoxEndFrame->setValue(pCap->frameCount);
    spinBoxFrameRate->setValue(pCap->fps);
    addToComboBoxHistory(comboBoxSaveDir, QString::fromStdString(pCap->openFileDir) );
    addToComboBoxHistory(comboBoxSaveDir, QString::fromStdString(pCap->openFileDir + "out") );
    comboBoxSaveDir->setCurrentText(QString::fromStdString(pCap->openFileDir + "out") );
}


void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   Display_Current_Image();
}


bool MainWindow::eventFilter(QObject* target, QEvent* event)
{
    if (target == ui->viewerLabel)
    {
        QEvent::Type type = event->type();
        QMouseEvent* mEvent = (QMouseEvent *)event;
      //  if (type != lastType) std::cout << type;
       // lastType = type;

        if (type==QEvent::MouseButtonPress || type==QEvent::MouseButtonRelease || type==QEvent::MouseMove)
        {
            //bool hereFirst = false;
            //Qt::MouseButtons mb = QApplication::mouseButtons();
            Qt::MouseButton button = mEvent->button();
            int myX = mEvent->x();
            int myY = mEvent->y();

            if (button != Qt::MouseButton::NoButton)
                std::cout << "Button pressed " << button << std::endl;

            std::cout << "  Boop - (" << myX << "," << myY << ")" << std::endl;

            int cvEvent;

            if (type == QEvent::MouseMove)
                cvEvent = CV_EVENT_MOUSEMOVE;

            else if (type == QEvent::MouseButtonPress)
            {
                if (button == Qt::MouseButton::LeftButton)  cvEvent = CV_EVENT_LBUTTONDOWN;
                if (button == Qt::MouseButton::RightButton)  cvEvent = CV_EVENT_RBUTTONDOWN;
            }
            else if (type == QEvent::MouseButtonRelease)
            {
                if (button == Qt::MouseButton::LeftButton)  cvEvent = CV_EVENT_LBUTTONUP;
                if (button == Qt::MouseButton::RightButton)  cvEvent = CV_EVENT_RBUTTONUP;
            }


            //rCollect.Callback(cv;:Point2f(myX,myY), );

            return true;
        }
        else if (type==QEvent::KeyPress)
        {

        }


    //std::cout << std::endl;
    }

    //return QMainWindow::eventFilter(target, event);
    return false;
}
