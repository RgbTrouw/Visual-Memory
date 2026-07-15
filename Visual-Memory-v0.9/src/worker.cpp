#include "worker.h"

void Worker::doWork(QDir memoryDir, QPixmap subjectPixmap, int tolerance){

    QList<int> score;

    QImage subjectImg(subjectPixmap.toImage());


    for(int i=0; i< memoryDir.entryList({"*.png"}).size(); i++){

        QPixmap memoryPixmap = QPixmap("memory/" + memoryDir.entryList({"*.png"}).at(i));
        QImage memoryPixmapImg(memoryPixmap.toImage());

        int scoreValue = 0;

        for(int width=0; width<34; width++){

            for(int height=0; height<34; height++){


                QRgb rgbColorSubject = subjectImg.pixel(width,height);

                QColor *colorSubject = new QColor();
                colorSubject->setRgb(rgbColorSubject);

                bool ok = true;

                int rSubject= QString(colorSubject->name()).right(6).left(2).toInt(&ok,16);
                int gSubject= QString(colorSubject->name()).right(4).left(2).toInt(&ok,16);
                int bSubject= QString(colorSubject->name()).right(2).toInt(&ok,16);

                // b

                QRgb rgbColorCross = memoryPixmapImg.pixel(width,height);

                QColor *colorCross = new QColor();
                colorCross->setRgb(rgbColorCross);


                int rCross= QString(colorCross->name()).right(6).left(2).toInt(&ok,16);
                int gCross= QString(colorCross->name()).right(4).left(2).toInt(&ok,16);
                int bCross= QString(colorCross->name()).right(2).toInt(&ok,16);


                // c

                if( (rCross >= (rSubject - tolerance)  && rCross <= (rSubject + tolerance) )  && ( gCross >= (gSubject - tolerance)  && gCross <= (gSubject + tolerance) )  && ( bCross >= (bSubject - tolerance)  && bCross <= (bSubject + tolerance)) ){
                    scoreValue += 1;
                }



                          //colorSubject->name() << " " << colorCross->name();


         }}

        score.append(scoreValue);

    }


    QList<match*> matchesList;

    for(int i=0; i< memoryDir.entryList({"*.png"}).size(); i++){

        matchesList.append(new match(memoryDir.entryList({"*.png"}).at(i), score.at(i)));
    }


    for(int redundancy = 0; redundancy < matchesList.count(); redundancy++){

    for(int i=1; i<matchesList.count(); i++){

        if(matchesList.at(i)->score > matchesList.at(i-1)->score){

            matchesList.swap(i, i-1);

        }

    }



    }

    QList<QLabel * > labels;

    for(int i=0; i< matchesList.count(); i++){

        qInfo() << matchesList.at(i)->filePath + " : " + QString::number(matchesList.at(i)->score);

        QLabel *matchLabel = new QLabel();
        matchLabel->setToolTip("score: " + QString::number(matchesList.at(i)->score));

        matchLabel->setFixedHeight(34);
        matchLabel->setFixedWidth(34);
        matchLabel->setScaledContents(true);
        matchLabel->setPixmap(QPixmap("memory/" + matchesList.at(i)->filePath));

        labels.append(matchLabel);
    }


    qInfo() << labels.size();

    emit resultReady(labels);


}
