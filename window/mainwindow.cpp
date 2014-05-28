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
    this->inputFileName = QFileDialog::getOpenFileName(this, tr("Seleziona il file"), "", tr("Files (*.*)"));

    if(inputFileName.isNull()) { qDebug("No file selected..."); }
    else {
        qDebug("Selected file: " + inputFileName.toLatin1());
        this->ui_filePathText->setText(inputFileName);

        this->gen_outputFileName();
    }
}

void MainWindow::on_startWorkButton_clicked() {

    qDebug("startWorkButton Clicked");
    qDebug("Instance selected: %d", this->ui->instanceComboBox->currentIndex());
    qDebug("Work Mode selected: %d", this->ui->workModeComboBox->currentIndex());

    this->nB = new NearestNeighbour(this->inputFileName.toStdString(), this->ui->instanceComboBox->currentIndex(),
                                    this->ui->workModeComboBox->currentIndex());

    this->nB->exec();

    this->outputPath = this->gen_outputFileName();
    this->ui->outputText->setText(outputPath);
}

void MainWindow::on_writeOutputButton_clicked() {
    this->nB->write_file(this->outputPath);
}

QString MainWindow::gen_outputFileName() {

    qDebug("->>> Corrent OS: %s", OS);

    QString res;

    QStringList name, pieces;

    if(OS == "win") { pieces = this->inputFileName.split("\\"); }
    if(OS == "unix") { pieces = this->inputFileName.split("/"); }

    name = pieces.takeLast().split(".");

    if(OS == "win") { for(int i = 0; i < pieces.size(); i++) { res.append(pieces.at(i) + "\\"); } }
    if(OS == "unix") { for(int i = 0; i < pieces.size(); i++) { res.append(pieces.at(i) + "/"); } }

    for(int i = 0; i < name.size() - 1; i++) { res.append(name.at(i) + "."); }

    res.append("out." + name.last());

    return res;
}
