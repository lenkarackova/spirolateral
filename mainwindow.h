#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QRegExpValidator>
#include <QSvgGenerator>
#include <QRandomGenerator>
#include "about.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void saveSVG();
    void savePNG();
    void random();
    void setLineColor(QColor color);
    void setBackgroundColor(QColor color);
    void setFillColor(QColor color);
    void setReverseTurns();
    void useFillToggle(int state);

private slots:
    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    About *about;
    QString path;

};

#endif // MAINWINDOW_H
