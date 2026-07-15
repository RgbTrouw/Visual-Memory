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
#include <QBuffer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QPixmap("://icon.png"));

    ui->pushButton->setIcon(QPixmap("addDir.png"));
    /// Load Memory //
    memoryDrive.setPath("memory");

    QWidget *scrollAreaContent = new QWidget();

    QHBoxLayout *hLayout = new QHBoxLayout(scrollAreaContent);

    hLayout->setSpacing(4);
    hLayout->setContentsMargins(QMargins(2,2,2,2));
    ui->scrollArea->setWidget(scrollAreaContent);

    hLayout3->setSpacing(4);
    hLayout3->setContentsMargins(QMargins(2,2,2,2));
    ui->scrollArea3->setWidget(scrollAreaContent3);


    QSpacerItem *horizontalSpacer = new QSpacerItem(1000,1, QSizePolicy::Expanding, QSizePolicy::Expanding);

    qInfo() << memoryDrive.entryList();

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

        connect(icon, &QPushButton::clicked, this, [=](){ selectMemory(memoryDrive.entryList({"*.png"}).at(i)); });

    }

    hLayout->addItem(horizontalSpacer);


    ui->iconsCounter->setText("Icons: " + QString::number(memoryDrive.entryList({"*.png"}).count()));


    connect(ui->loadImageButton, SIGNAL(clicked()), this, SLOT(loadImage()));
    connect(ui->identifyImageButton, SIGNAL(clicked()), this, SLOT(identify()));

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
    //ui->functionBox->setEnabled(true);

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

    subjectPixmap = QPixmap("subjects/lowRes" + subjectPath.right(subjectPath.size() - subjectPath.lastIndexOf("/") - 1));
    QImage subjectImage(subjectPixmap.toImage());


        subjectImage.save("subjects/" + subjectPath.right(subjectPath.size() - subjectPath.lastIndexOf("/") - 1), "PNG");

        //ui->shapeIcon->setPixmap(QPixmap("subjects/" + subjectPath.right(subjectPath.size() - subjectPath.lastIndexOf("/") - 1)));




        Worker *worker = new Worker(memoryDrive, subjectPixmap, ui->toleranceValue->value());
        connect(worker, SIGNAL(resultReady(QList<QLabel*>)), this, SLOT(results(QList<QLabel*>)));

}


void MainWindow::results(QList<QLabel*> list){


    while (hLayout3->takeAt(0) != 0) {
    delete hLayout3->takeAt(0);
    }

    for(int i=0; i<120 && i<list.size(); i++){

        hLayout3->addWidget(list.at(i));

    }

    hLayout3->addItem(horizontalSpacer3);

    ui->progressBar->hide();


}
void MainWindow::selectMemory(QString fileName){

   // qInfo() << fileName;

    ui->selectedMemory->setPixmap(QPixmap("memory/" + fileName));
}

void MainWindow::on_pushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"));


    QDir addDir;
    addDir.setPath(dir);

    QByteArray *ba;
      for(int i =0; i< addDir.entryList({"*.png"}).size(); i++){



      QByteArray bytes;
      QBuffer buffer(&bytes);
      buffer.open(QIODevice::WriteOnly);
      QPixmap(addDir.entryList().at(i)).save(&buffer, "PNG");

      qInfo() << bytes;
      }
}

