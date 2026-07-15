#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QThread>
#include <QPixmap>
#include <QImage>
#include <QDir>
#include <QList>
#include <match.h>
#include <QDebug>
#include <QLabel>
#include <QTimer>

class Worker : public QThread
{

    Q_OBJECT

public:
    explicit Worker(QDir memoryDir, QPixmap subjectPixmap, int tolerance, QObject *parent = nullptr) : QThread(parent) {

         QTimer::singleShot(2000, this, [=](){doWork(memoryDir, subjectPixmap, tolerance);});
    }

    void doWork(QDir memoryDir, QPixmap subjectPixmap, int tolerance);


signals:
    void resultReady(QList<QLabel*>);

};

#endif // WORKER_H
