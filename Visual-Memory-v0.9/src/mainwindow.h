#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QMenu>
#include <QThread>
#include <worker.h>
#include <QHBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void loadImage();
    void identify();
    void selectMemory(QString fileName);

    void on_pushButton_clicked();
    void results(QList<QLabel*> list);

private:
    Ui::MainWindow *ui;

    QString subjectPath = "";

    QDir memoryDrive;

    void loadMemory();

    int tolerance = 34;

    QThread workerThread;

    QWidget *scrollAreaContent3 = new QWidget();

    QHBoxLayout *hLayout3 = new QHBoxLayout(scrollAreaContent3);
    QPixmap subjectPixmap;
     QSpacerItem *horizontalSpacer3 = new QSpacerItem(1000,1, QSizePolicy::Expanding, QSizePolicy::Expanding);
};
#endif // MAINWINDOW_H
