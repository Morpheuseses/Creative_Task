#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QGridLayout>
#include <QPushButton>
#include <QTimer>
#include <QVector>
#include <QLabel>
#include <QLineEdit>
#include <QRandomGenerator>
#include <QProgressBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Робот шахтер");
    this->setWindowIcon(QIcon("WALLC2B7E_28character29.png"));
    ui->centralwidget->setStyleSheet("QWidget {background-color: rgb(41,71,87)}");

    QTimer *timer = new QTimer(this);
    QTimer *timer_rock = new QTimer(this);
    QTimer *timer_charge = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &MainWindow::execute);
    connect(this, &MainWindow::destReached, this, &MainWindow::makeNewDest);
    connect(timer_rock, &QTimer::timeout, this, &MainWindow::rockFell);
    connect(timer_charge, &QTimer::timeout, this, &MainWindow::robotChargeChanged);
    timer->start(150);
    timer_rock->start(10000);
    timer_charge->start(300);

    openGlW = new myGLWidget(&mypainter, this);
    openGlW->setFixedHeight(840); // 30 x 30 клеток
    openGlW->setFixedWidth(900);


    map = new Map;

    openGlW->map = map;

    list = new QListWidget(this);
    list->setStyleSheet("QListWidget {background: rgb(100,100,100);}");
    list->setStyleSheet("QHeaderView::section {background: rgb(150,150,150)}");

    // initializing all robots
    init();

    QGridLayout *grid = new QGridLayout();

    QPushButton *btn = new QPushButton();
    btn->setStyleSheet("QPushButton {background: rgb(170,176,56); color: white; font: bold; font-size: 20px}" );
    QPushButton *btn2 = new QPushButton();
    btn2->setStyleSheet("QPushButton {background: rgb(30,89,69); color: white; font: bold; font-size: 20px}" );
    QPushButton *btn3 = new QPushButton();
    btn3->setStyleSheet("QPushButton {background: rgb(170,20,0); color: white; font: bold; font-size: 20px}" );


    btn->setText("Return to base");
    btn2->setText("Go to Explore");
    btn3->setText("Stop the robots");

    connect(btn, &QPushButton::clicked, this, &MainWindow::returnToBase);
    connect(btn2, &QPushButton::clicked, this, &MainWindow::goToExplore);
    connect(btn3, &QPushButton::clicked, this, &MainWindow::stopRobot);
    connect(this, &MainWindow::on_stopRobot, this, &MainWindow::stopRobot);



    grid->addWidget(openGlW, 0, 0);
    grid->addWidget(btn, 1, 0);
    grid->addWidget(btn2, 2, 0);
    grid->addWidget(btn3, 3, 0);
    grid->addWidget(list, 0, 1);

    ui->centralwidget->setLayout(grid);

    connect(timer, &QTimer::timeout, openGlW, &myGLWidget::redraw);
}

void MainWindow::init()
{
    int quantity = 1;
    // creating a robot array
    robotVec.resize(quantity);
    for (auto& robot : robotVec)
    {
        robot = new Robot;
        robot->map = map;
    }

    std::pair<int, int> sp(0, 0); // start point
    std::pair<int, int> ep(map->width-1, map->height-1); // end point

    robotVec[0]->setMoveTo(std::make_pair(sp.first, sp.second), std::make_pair(ep.first, ep.second));
    robotVec[0]->base = sp;
    //robotVec[1]->setMoveTo(std::make_pair(sp.first + 1, sp.second), std::make_pair(ep.first - 1, ep.second));
    //robotVec[1]->base = std::make_pair(sp.first+1, sp.second);
    //robotVec[2]->setMoveTo(std::make_pair(sp.first + 2, sp.second), std::make_pair(ep.first - 2, ep.second));
    for (int i = 0; i < robotVec.size(); i++)
    {
        makeListItem();
    }

    for (auto& robot : robotVec)
    {
        robot->map->placeRobot(robot);
        emit on_robotMadestep();
    }
    // set start and end points of robots

}
void MainWindow::makeListItem()
{
    QWidget* wgt = new QWidget;
    QLayout* l = new QHBoxLayout;
    QLabel* label = new QLabel;
    label->setStyleSheet("QLabel {color: white}");
    l->addWidget(label);
    labels.push_back(label);
    connect(this, &MainWindow::on_robotMadestep, this, &MainWindow::robotMadestep);

    wgt->setLayout(l);

    QListWidgetItem* item = new QListWidgetItem(list);
    wgt->setStyleSheet("QWidget {background: rgb(100, 100, 100)}");
    item->setSizeHint(wgt->sizeHint());
    list->setItemWidget(item, wgt);

}
void MainWindow::execute()
{
    for (int i = 0; i < robotVec.size(); i++)
    {
        robotVec[i]->make_step();
        emit on_robotMadestep();
    }
    for (auto& robot : robotVec)
    {
        if (*robot->start_point == *robot->end_point)
            emit destReached(robot);
    }

}
void MainWindow::makeNewDest(Robot* robot)
{
    robot->makeNewDest();
}
void MainWindow::robotMadestep()
{
    for (int i = 0; i < labels.size(); i++)
    {
        QString state = "";
        switch (robotVec[i]->state) {
            case 0:
                state = "Waiting";
                break;

            case 1:
                state = "Moving";
                break;
            case 2:
                state = "Dead";
               break;
            case 3:
                state = "Return to base";
                break;
        }

        labels[i]->setText( "Robot " + QString::number(i) + ": x: " + QString::number(robotVec[i]->x) + " y: " + QString::number(robotVec[i]->y)
                            + " charge: " + QString::number(robotVec[i]->charge) + " % state: " +  state);
    }
}

void MainWindow::returnToBase()
{
    for (auto& robot : robotVec)
    {
        robot->setMoveTo(std::make_pair(robot->x, robot->y), robot->base);
        robot->state = 3;
    }
}
void MainWindow::robotChargeChanged()
{
    for (auto& robot : robotVec)
    {
        if (robot->charge > 0 && !(robot->x == robot->base.first && robot->y == robot->base.second))
            robot->charge--;
        if (robot->x == robot->base.first && robot->y == robot->base.second && robot->charge < 100)
            robot->charge++;
        if (robot->charge == 0)
            robot->state = 2;
    }
}

void MainWindow::goToExplore()
{
    for (auto& robot : robotVec)
    {
        robot->state = 1;
    }
}
void MainWindow::stopRobot()
{
    for (auto& robot : robotVec)
    {
        robot->state = 0;
    }
}
void MainWindow::rockFell()
{
    bool flag = true;
    int dx, dy;
    while (flag)
    {
        dx = QRandomGenerator::global()->bounded(0, map->width-1);
        dy = QRandomGenerator::global()->bounded(0, map->height-1);
        if (map->prohibited.find(map->map_table[dx][dy]) > map->prohibited.length())
            flag = false;
    }
    for (auto& r : robotVec)
    {
        if (r->x == dx  && r->y == dy)
        {
             r->state = 2;
             map->map_table[dy][dx] = "R";
             break;
        }
        else
        {
            map->map_table[dy][dx] = "R";
            break;
        }
    }

}
MainWindow::~MainWindow()
{
    delete ui;
}
