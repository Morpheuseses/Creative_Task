#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new PaintScene();
    scene->setSceneRect(0,0, ui->graphicsView->size().width()-15,ui->graphicsView->size().height()-15);
    ui->graphicsView->setScene(scene);

    Matrix = new AdjMatrix();

    connect(scene, &PaintScene::signalGetPtrMatrix, this, &MainWindow::sendPtrMatrix);

    connect(Matrix, &AdjMatrix::signalSendMatrixSize, this, &MainWindow::slotGetMatrixSize);

    this->setFixedSize(1024,600);
}

void MainWindow::sendPtrMatrix(AdjMatrix*& out_ptrMatrix)
{
    out_ptrMatrix = Matrix;
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    Matrix->deleteAll();
}

void MainWindow::slotGetMatrixSize(int size)
{

    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->comboBox_3->clear();
    if(size!=-1)
    {
        for(int i = 0; i < size; i++)
        {
            ui->comboBox->addItem(QString::number(i));
            ui->comboBox_2->addItem(QString::number(i));
            ui->comboBox_3->addItem(QString::number(i));
        }
    }
    adjMatrix = ui->tableWidget;
    adjMatrix->setColumnCount(Matrix->Points.size());
    adjMatrix->setRowCount(Matrix->Points.size());

    QStringList header;

    for (int i = 0; i < Matrix->Points.size(); i++)
    {
        header << QString::number(i);
    }

    adjMatrix->setHorizontalHeaderLabels(header);
    adjMatrix->setVerticalHeaderLabels(header);

    for (int i  = 0; i < ui->tableWidget->rowCount(); i++)
        for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
            QTableWidgetItem * tbl = new QTableWidgetItem(QString::number(Matrix->PathMatrix[i][j].size));
            if (j == i)
                tbl->setBackgroundColor(Qt::gray);
            adjMatrix->setItem(i, j, tbl);
        }
}

void MainWindow::on_pushButton_5_clicked()
{
    Matrix->ActivateSalesmansMethod();
}

void MainWindow::on_pushButton_2_clicked()
{

        if(ui->comboBox->currentIndex() >=0 && Matrix->Points.size() >=2) {
            Matrix->deletePoint(ui->comboBox->currentIndex());
        }

}
void MainWindow::on_pushButton_3_clicked()
{
    int i = ui->comboBox_2->currentText().toInt();
    int j = ui->comboBox_3->currentText().toInt();
    if (Matrix->Points.size() > 0 && i >= 0 && j >= 0)
    {
        Matrix->deleteLine(i,j);
    }
}

void MainWindow::updateComboBox_3(int indexOfComboBox_2)
{
    if (indexOfComboBox_2 >= 0)
    {
        ui->comboBox_3->clear();

        for (int i = 0; i < Matrix->Points.size(); i++)
        {
            if (Matrix->PathMatrix[indexOfComboBox_2][i].size != -1)
                ui->comboBox_3->addItem(QString::number(i));
        }
    }
}

void MainWindow::updateComboBox_5(int indexOfcomboBox_4)
{
    if (indexOfcomboBox_4 >= 0)
    {
        ui->comboBox_5->clear();

        for (int i = 0; i < Matrix->Points.size(); i++)
        {
            if (Matrix->PathMatrix[indexOfcomboBox_4][i].size == -1 && indexOfcomboBox_4 != i)
            {
                ui->comboBox_5->addItem(QString::number(i));
            }
        }
    }
}
void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    int i = ui->comboBox_2->currentIndex();
    int j = ui->comboBox_3->currentText().toInt();
    if(arg1.toInt() > 0 && arg1.toInt() < 101 && i >= 0 && j >= 0)
    {
        Matrix->setPathSize(i, j, arg1.toInt());
    }

}


void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    updateComboBox_3(index);
}

void MainWindow::on_comboBox_3_currentIndexChanged(const QString &arg1)
{
    ui->lineEdit->clear();

    int i = ui->comboBox_2->currentIndex();
    int j = arg1.toInt();

    if(i >= 0 && j >= 0)
    {
        Matrix->setAllLinesOneColor(0);
        Matrix->setLineColor(i, j, 1);
        ui->lineEdit->setText(QString::number(Matrix->PathMatrix[i][j].size));
    }

}
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(index >=0)
    {
        ui->label_4->clear();
        ui->label_4->setText(QString::number(Matrix->degreeOfTop(index)));
        Matrix->setAllPointsOneColor(0);
        Matrix->setPointColor(index, 1);
    }
}
