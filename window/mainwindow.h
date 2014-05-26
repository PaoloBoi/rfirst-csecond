#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private:
    Ui::MainWindow *ui;

    QTextBrowser *ui_filePathText;

    NearestNeighbour *nB;

    QString fileName;

};

#endif // MAINWINDOW_H
