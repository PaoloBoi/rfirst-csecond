#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifdef _WIN64
#define OS "win"
#elif _WIN32
#define OS "win"
#elif __APPLE__
#define OS "unix"
#elif __linux
#define OS "unix"
#elif __unix // all unices not caught above
#define OS "unix"
#elif __posix
#define OS "unix"
#endif

#include <stdio.h>
#include <QDebug>
#include <QFileDialog>
#include <QTextBrowser>
#include <QMainWindow>
#include <QtGui>

#include "nearestneighbour.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    /* Viene connesso in automatico all'oggetto openFileButton. */
    void on_selectInputButton_clicked();

    void on_startWorkButton_clicked();

    void on_writeOutputButton_clicked();

private:
    Ui::MainWindow *ui;

    QTextBrowser *ui_filePathText;

    NearestNeighbour *nB;

    QString inputFileName;
    QString outputPath;

    QString gen_outputFileName (void);

};

#endif // MAINWINDOW_H
