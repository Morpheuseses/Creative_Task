#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTimer>
#include <QListWidget>
#include <QLabel>

#include "mypainter.h"
#include "map.h"
#include "robot.h"
#include "myglwidget.h"



class myGLWidget;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init();
    void makeListItem();
private:
    QVector<QLabel*> labels;
    QListWidget* list;
    Map* map;
    myGLWidget *openGlW;
    QVector<Robot*> robotVec;
    myPainter mypainter;

    Ui::MainWindow *ui;

signals:
    void on_robotMadestep();
    void destReached(Robot*);
    void on_stopRobot();

private slots:
    void robotMadestep();
    void execute();
    void makeNewDest(Robot*);
    void returnToBase();
    void goToExplore();
    void stopRobot();
    void rockFell();
    void robotChargeChanged();
};
#endif // MAINWINDOW_H
