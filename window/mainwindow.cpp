#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);

    /* Traccia l'elemento openFileButton */
    this->ui_filePathText = ui->filePathText;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_selectInputButton_clicked() {
    qDebug("openFileButton Clicked");
    this->fileName = QFileDialog::getOpenFileName(this, tr("Seleziona il file"), "", tr("Files (*.*)"));

    if(fileName.isNull()) { qDebug("No file selected..."); }
    else {
        qDebug("Selected file: " + fileName.toLatin1());
        this->ui_filePathText->setText(fileName);
    }
}

void MainWindow::on_startWorkButton_clicked() {

    qDebug("startWorkButton Clicked");
    qDebug("Instance selected: %d", this->ui->instanceComboBox->currentIndex());
    qDebug("Work Mode selected: %d", this->ui->workModeComboBox->currentIndex());

    this->nB = new NearestNeighbour(this->fileName.toStdString(), this->ui->instanceComboBox->currentIndex(),
                                    this->ui->workModeComboBox->currentIndex());

    this->nB->exec();
}
