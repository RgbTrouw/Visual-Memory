#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QMenu>

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
    void convertToShapes();
    void identify();
    void crossCheck();

    void selectMemory(QString fileName);

private:
    Ui::MainWindow *ui;

    QString subjectPath = "";

    QDir memoryDrive;

    void loadMemory();
};
#endif // MAINWINDOW_H
