#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTableWidget>


#include "paintscene.h"
#include "vertex.h"
#include "adjmatrix.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;

    PaintScene* scene = nullptr;
    AdjMatrix* Matrix = nullptr;
    QTableWidget* adjMatrix;


private slots:
    void sendPtrMatrix(AdjMatrix*& out_ptrMatrix);
    void slotGetMatrixSize(int size);

    // to do buttons and ui slots
    void on_comboBox_2_currentIndexChanged(int index);
    void on_comboBox_3_currentIndexChanged(const QString& argl);
    void on_comboBox_4_currentIndexChanged(int index);


    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();

    void updateLabelText(const QString& argl);
    void updateComboBox_3(int indexOfComBox_2);
    void updateComboBox_5(int indexOfComboBox_4);
    void on_lineEdit_textChanged(const QString &arg1);
    void on_comboBox_currentIndexChanged(int index);

};

#endif // MAINWINDOW_H
