#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QDebug>
#include <QLabel>
#include <QPixmap>
#include <QScreen>
#include <QTimer>
#include <QPushButton>
#include <QThread>
#include <match.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QPixmap("://icon.png"));

    /// Load Memory //
    memoryDrive.setPath("memory");

    QWidget *scrollAreaContent = new QWidget();

    QHBoxLayout *hLayout = new QHBoxLayout(scrollAreaContent);

    hLayout->setSpacing(4);
    hLayout->setContentsMargins(QMargins(2,2,2,2));
    ui->scrollArea->setWidget(scrollAreaContent);

    QSpacerItem *horizontalSpacer = new QSpacerItem(1000,1, QSizePolicy::Expanding, QSizePolicy::Expanding);

    //qInfo() << memoryDrive.entryList();

    for(int i =0; i< memoryDrive.entryList({"*.png"}).size(); i++){

        QPushButton  *icon = new QPushButton();

        icon->setIcon(QPixmap("memory/" + memoryDrive.entryList({"*.png"}).at(i)));
        icon->setToolTip(memoryDrive.entryList({"*.png"}).at(i));
        //icon->setText(memoryDrive.entryList().at(i));
        //icon->setGeometry(0,0,34,34);
        icon->setFixedHeight(34);
        icon->setFixedWidth(34);
        icon->setIconSize(QSize(34,34));
        //qInfo() << memoryDrive.entryList().at(i);
        //icon->setScaledContents(true);
        hLayout->addWidget(icon);

        connect(icon, &QPushButton::clicked, this, [=]{ selectMemory(memoryDrive.entryList({"*.png"}).at(i)); });

    }

    hLayout->addItem(horizontalSpacer);

    ui->selectedMemory->setPixmap(QPixmap("memory/" + memoryDrive.entryList({"*.png"}).at(0)));

    ui->iconsCounter->setText("Icons: " + QString::number(memoryDrive.entryList({"*.png"}).count()));
    //qInfo() << memoryDrive.entryList().at(2);

    /// Menus

    QMenu *MemoryMenu = ui->menuEdit->addMenu("Memory");
    MemoryMenu->setFont(QFont ("Ubuntu", 10));
    QAction *ConvertToShapesAction = new QAction();
    ConvertToShapesAction->setText("Convert to Shapes");
    MemoryMenu->addAction(ConvertToShapesAction);

    QAction *initialiseDatabaseAction = new QAction();
    initialiseDatabaseAction->setText("Initialise Database");
    MemoryMenu->addAction(initialiseDatabaseAction);



    /// Connect Slots

    connect(ui->loadImageButton, SIGNAL(clicked()), this, SLOT(loadImage()));
    connect(ui->identifyImageButton, SIGNAL(clicked()), this, SLOT(identify()));
    connect(ConvertToShapesAction, SIGNAL(triggered()), this, SLOT(convertToShapes()));

    ///


    /// hides

    ui->progressBar->hide();


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::loadImage(){

    QString imagePath = QFileDialog::getOpenFileName(nullptr,
       tr("Open Image"), "/home/rgb_trouw", tr("Image Files (*.png *.jpg *.bmp)"));

    subjectPath = imagePath;

    ui->imageSubject->setPixmap(QPixmap(imagePath));
    ui->lowRes->setPixmap(QPixmap(imagePath));
    ui->subjectLabel->setPixmap(QPixmap(imagePath));
    ui->identifyImageButton->setEnabled(true);
    ui->functionBox->setEnabled(true);

}

void MainWindow::convertToShapes(){

    ui->progressBar->show();

    if(QDir("memory/shapes").exists()){

    } else {
        QDir().mkdir("memory/shapes");

        }

        //qInfo() << memoryDrive.entryList();

        for(int i=0; i< memoryDrive.entryList({"*.png"}).count(); i++){

            QPixmap memoryPixmap("memory/" + memoryDrive.entryList({"*.png"}).at(i));
            QImage memoryImage(memoryPixmap.toImage());
            QImage *bufferImage= new QImage(34,34, QImage::Format_RGB888);

            //ui->bitwiseResult->setPixmap(memoryPixmap); //

            for(int width=0; width<34; width++){

                for(int height=0; height<34; height++){

                    QRgb rgbColor = memoryImage.pixel(width,height);

                    QColor *color = new QColor();
                    color->setRgb(rgbColor);

                    bool ok = true;

                    int r= QString(color->name()).right(6).left(2).toInt(&ok,16);
                    int g= QString(color->name()).right(4).left(2).toInt(&ok,16);
                    int b= QString(color->name()).right(2).toInt(&ok,16);

                    if(r != 0 && g != 0 && b != 0){
                        bufferImage->setPixel(width,height,qRgb(255,255,255));
                    } else {
                        bufferImage->setPixel(width,height,qRgb(0,0,0));
                    }

                }

             }

            bufferImage->save("memory/shapes/" + memoryDrive.entryList({"*.png"}).at(i),"PNG");

        }

        ui->progressBar->hide();
}

void MainWindow::identify(){

//    qInfo() << ui->lowRes->pos().x();
//    qInfo() << ui->lowRes->pos().y();



    if(QDir("subjects").exists()){

    } else {
        QDir().mkdir("subjects");

    }

    QPixmap *lowResPixmap = new QPixmap();
    *lowResPixmap = QPixmap::grabWindow(this->winId(), ui->lowRes->pos().x(), ui->lowRes->pos().y()+22, 34, 34);

    ui->progressBar->show();

    //qInfo() << ui->lowRes->pos();
    //*lowResPixmap = QScreen::grabWindow(0, ui->lowRes->pos().x(), ui->lowRes->pos().y(), 34, 34);

    QImage *lowResImage = new QImage;
    *lowResImage = lowResPixmap->toImage();

    lowResImage->save("subjects/lowRes" + subjectPath.right(subjectPath.size() - subjectPath.lastIndexOf("/") - 1) ,"PNG");

    //qInfo() << "subjects/lowRes" + subjectPath.right(subjectPath.size() - subjectPath.lastIndexOf("/") - 1);

    QPixmap subjectPixmap = QPixmap("subjects/lowRes" + subjectPath.right(subjectPath.size() - subjectPath.lastIndexOf("/") - 1));
    QImage subjectImage(subjectPixmap.toImage());
    QImage *bufferImage = new QImage(34,34, QImage::Format_RGB888);

    for(int width=0; width<34; width++){

        for(int height=0; height<34; height++){

            QRgb rgbColor = subjectImage.pixel(width,height);

            QColor *color = new QColor();
            color->setRgb(rgbColor);

            bool ok = true;

            int r= QString(color->name()).right(6).left(2).toInt(&ok,16);
            int g= QString(color->name()).right(4).left(2).toInt(&ok,16);
            int b= QString(color->name()).right(2).toInt(&ok,16);

            //qInfo() << "r:" + QString::number(r) + " g:" + QString::number(g) + " b:" + QString::number(b);

            if(r != 0 && g != 0 && b != 0){
                bufferImage->setPixel(width,height,qRgb(255,255,255));
            } else {
                bufferImage->setPixel(width,height,qRgb(0,0,0));
            }
            //qInfo() << color->name();
            //QThread::usleep(1000);

        }}


        if(QDir("subjects/shapes").exists()){

        } else {
            QDir().mkdir("subjects/shapes");

        }

        bufferImage->save("subjects/shapes/" + subjectPath.right(subjectPath.size() - subjectPath.lastIndexOf("/") - 1), "PNG");

        ui->shapeIcon->setPixmap(QPixmap("subjects/shapes/" + subjectPath.right(subjectPath.size() - subjectPath.lastIndexOf("/") - 1)));



   QTimer::singleShot(1000, this, SLOT(crossCheck()));
}

void MainWindow::crossCheck(){

    QList<int> score;

    QPixmap subjectShapePixmap = *ui->shapeIcon->pixmap();
    QImage subjectShapeImage(subjectShapePixmap.toImage());

    for(int i=0; i< memoryDrive.entryList({"*.png"}).size(); i++){

        QPixmap crossShapePixmap = QPixmap("memory/shapes/" + memoryDrive.entryList({"*.png"}).at(i));
        QImage crossShapeImage(crossShapePixmap.toImage());

        //qInfo() << "memory/shapes/" + memoryDrive.entryList().at(i);
        int scoreValue = 0;

        for(int width=0; width<34; width++){

            for(int height=0; height<34; height++){

                // a

                QRgb rgbColorSubject = subjectShapeImage.pixel(width,height);

                QColor *colorSubject = new QColor();
                colorSubject->setRgb(rgbColorSubject);

                bool ok = true;

                int rSubject= QString(colorSubject->name()).right(6).left(2).toInt(&ok,16);
                int gSubject= QString(colorSubject->name()).right(4).left(2).toInt(&ok,16);
                int bSubject= QString(colorSubject->name()).right(2).toInt(&ok,16);

                // b

                QRgb rgbColorCross = crossShapeImage.pixel(width,height);

                QColor *colorCross = new QColor();
                colorCross->setRgb(rgbColorCross);


                int rCross= QString(colorCross->name()).right(6).left(2).toInt(&ok,16);
                int gCross= QString(colorCross->name()).right(4).left(2).toInt(&ok,16);
                int bCross= QString(colorCross->name()).right(2).toInt(&ok,16);


                // c

                if(rSubject != rCross && gSubject != gCross && bSubject != bCross){
                    scoreValue += 1;
                }

                //qInfo()<< colorSubject->name() << " " << colorCross->name();


         }}

        score.append(scoreValue);

    }

    QWidget *scrollAreaContent3 = new QWidget();

    QHBoxLayout *hLayout3 = new QHBoxLayout(scrollAreaContent3);

    hLayout3->setSpacing(4);
    hLayout3->setContentsMargins(QMargins(2,2,2,2));
    ui->scrollArea3->setWidget(scrollAreaContent3);

    QSpacerItem *horizontalSpacer3 = new QSpacerItem(1000,1, QSizePolicy::Expanding, QSizePolicy::Expanding);

    QList<match*> matchesList;

    for(int i=0; i< memoryDrive.entryList({"*.png"}).size(); i++){

        matchesList.append(new match(memoryDrive.entryList({"*.png"}).at(i), score.at(i)));
    }


    for(int redundancy = 0; redundancy < matchesList.count(); redundancy++){

    for(int i=1; i<matchesList.count(); i++){

        if(matchesList.at(i)->score < matchesList.at(i-1)->score){

            matchesList.swap(i, i-1);

        }

    }

//       if(score.at(i) < score.at(i-1)){

//           QLabel *match = new QLabel();
//           match->setToolTip(memoryDrive.entryList({"*.png"}).at(i));

//           //qInfo() << memoryDrive.entryList({"*.png"});
//           //QVariant pcnt = ((1024 - score.at(i)) / 1024) * 100;
//           //qInfo() << pcnt;
//           //match->setToolTip(pcnt.String + " \%");

//           match->setFixedHeight(34);
//           match->setFixedWidth(34);
//           match->setScaledContents(true);
//           match->setPixmap(QPixmap("memory/" + memoryDrive.entryList({"*.png"}).at(i)));

//           hLayout3->addWidget(match);

//           //qInfo() << score.at(i) << " at " << i;
//           //qInfo() << memoryDrive.entryList().at(i+2);
//            matches +=1;
//       }


    }

    for(int i=0; i< matchesList.count(); i++){

        qInfo() << matchesList.at(i)->filePath + " : " + QString::number(matchesList.at(i)->score);

        QLabel *matchLabel = new QLabel();
        matchLabel->setToolTip("score: " + QString::number(matchesList.at(i)->score));

        matchLabel->setFixedHeight(34);
        matchLabel->setFixedWidth(34);
        matchLabel->setScaledContents(true);
        matchLabel->setPixmap(QPixmap("memory/" + matchesList.at(i)->filePath));

         hLayout3->addWidget(matchLabel);
    }


    hLayout3->addItem(horizontalSpacer3);

    ui->progressBar->hide();

}

void MainWindow::selectMemory(QString fileName){

   // qInfo() << fileName;

    ui->selectedMemory->setPixmap(QPixmap("memory/" + fileName));
}
