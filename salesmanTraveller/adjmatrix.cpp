#include "adjmatrix.h"

AdjMatrix::AdjMatrix(QObject *parent) : QObject(parent)
{
    PathMatrix = nullptr;
}

int AdjMatrix::addPoint(int x, int y)
{
    Path** buffWaysMatrix = new Path*[Points.size()+1];
    for (int i = 0; i < Points.size()+1; i++)
    {
        buffWaysMatrix[i] = new Path[Points.size()+1];
    }

    if (PathMatrix == nullptr)
    {
        PathMatrix = buffWaysMatrix;
        buffWaysMatrix = nullptr;
    }
    else
    {
        for (int i = 0; i < Points.size(); i++)
        {
            for (int j = 0; j < Points.size(); j++)
            {
                buffWaysMatrix[i][j] = PathMatrix[i][j];
            }
        }
        for (int i = 0; i < Points.size(); i++)
        {
            delete[] PathMatrix[i];
        }
        delete[] PathMatrix;

        PathMatrix = buffWaysMatrix;
        buffWaysMatrix = nullptr;
    }

    Points.push_back(new Vertex(x,y,Points.size()));

    for (int i = 0; i < Points.size()-1; i++)
    {
        srand(time(NULL) -  i*100); rand();
        int buff = 1 + rand() % 9999;
        buff = 1 + rand() % 9999 + buff;
        srand(time(NULL) - buff); rand();

        int way = 1 + (rand()&0x7FFF) % 24;

        addLine(i, Points.size()-1, way);
    }

    emit signalSendMatrixSize(Points.size());

    return Points.size()-1;
}

void AdjMatrix::addLine(int firstVert, int secondVert, int size)
{
    PathMatrix[firstVert][secondVert].size = size;

    PathMatrix[firstVert][secondVert].line = new QGraphicsLineItem(Points[firstVert]->x,
                                                                 Points[firstVert]->y,
                                                                 Points[secondVert]->x,
                                                                 Points[secondVert]->y);
    PathMatrix[firstVert][secondVert].line->setPen(QPen(Qt::black));
    PathMatrix[firstVert][secondVert].text = new QGraphicsTextItem(QString::number(size));
    PathMatrix[firstVert][secondVert].text->setFont(QFont("", 10, 70, 0));
    int sizeX = 0, sizeY = 0;
    sizeX = Points[firstVert]->x < Points[secondVert]->x ? Points[firstVert]->x : Points[secondVert]->x;
    sizeY = Points[firstVert]->y < Points[secondVert]->y ? Points[firstVert]->y : Points[secondVert]->y;

    PathMatrix[firstVert][secondVert].text->setPos(sizeX + (std::abs(Points[firstVert]->x - Points[secondVert]->x)/2) - 15
                                                 , sizeY + (std::abs(Points[firstVert]->y - Points[secondVert]->y)/2) - 15);

    PathMatrix[secondVert][firstVert].size = PathMatrix[firstVert][secondVert].size;
    PathMatrix[secondVert][firstVert].line = PathMatrix[firstVert][secondVert].line;
    PathMatrix[secondVert][firstVert].text = PathMatrix[firstVert][secondVert].text;

    emit signalSendMatrixSize(Points.size());
}

void AdjMatrix::deleteLine(int index_i, int index_j)
{

    PathMatrix[index_i][index_j].size = -1;
    delete PathMatrix[index_i][index_j].line;
    delete PathMatrix[index_i][index_j].text;
    PathMatrix[index_i][index_j].line = nullptr;
    PathMatrix[index_i][index_j].text = nullptr;

    PathMatrix[index_j][index_i].size = -1;
    PathMatrix[index_j][index_i].line = nullptr;
    PathMatrix[index_j][index_i].text = nullptr;

    emit signalSendMatrixSize(Points.size());
}

int AdjMatrix::deletePoint(int index)
{
    if(Points.size()==0)
    {
        qDebug() << "Points is empty. Element correspond to index " << index << " was not removed";
        return -1;
    }
    if (index >= Points.size())
    {
        qDebug() << "Element correspond to index "<< index << "is not in Points. Element was not removed";
        return -2;
    }

    if (Points.size()==1)
    {
        deleteLine(0,0);

        delete[] PathMatrix[0];
        delete[] PathMatrix;
        PathMatrix = nullptr;
    }
    else
    {
        for (int i = 0; i < Points.size(); i++)
        {
            if (i != index)
            {
                deleteLine(index, i);
                deleteLine(i, index);
            }
        }
        deleteLine(index, index);

    Path** buffWaysMatrix = new Path*[Points.size()-1];

    for (int i = 0; i < Points.size(); i++)
        buffWaysMatrix[i] = new Path[Points.size()-1];

    int I = 0, J = 0;
    for (int i = 0; i < Points.size(); i++)
    {
            I = i;
            if (i!= index)
            {
                if (i > index) {--I;}
                for (int j = 0; j < Points.size(); j++)
                {
                    J = j;
                    if (j!=index)
                    {
                        if (j>index) {--J;}
                        buffWaysMatrix[I][J] = PathMatrix[i][j];
                    }
                }
            }

    }
    for (int i = 0; i < Points.size(); i++)
    {
        delete[] PathMatrix[i];
    }
    delete[] PathMatrix;

    PathMatrix = buffWaysMatrix;
    }



    delete Points[index];

    for (int i = index; i < Points.size()-1; i++)
    {
        Points[i] = Points[i+1];
        Points[i]->Number = i;
        Points[i]->nameOfTop->setPlainText(QString::number(i));
    }

    Points.pop_back();

    emit signalSendMatrixSize(Points.size());

    return 1;
}

void AdjMatrix::deleteAll()
{
    emit signalSendMatrixSize(-1);

    for (int i = 0; i < Points.size(); i++)
    {
        for (int j = 0; j < Points.size(); j++)
        {
            deleteLine(i,j);
        }
    }

    for (int i = 0; i < Points.size(); i++)
    {
        delete[] PathMatrix[i];
    }
    delete[] PathMatrix;
    PathMatrix = nullptr;

    for (int i = 0; i < Points.size(); i++)
    {
        delete Points[i];
    }

    Points.clear();
}

void AdjMatrix::setLineColor(int firstVert, int secondVert, int chose)
{
    if(PathMatrix[firstVert][secondVert].line != nullptr && firstVert >=0 && secondVert >= 0)
    {
        switch(chose)
        {
        case 0:
        {
            PathMatrix[firstVert][secondVert].line->setPen(QPen(Qt::black));
            break;
        }
        case 1:
        {
            PathMatrix[firstVert][secondVert].line->setPen(QPen(Qt::green));
            break;
        }
        case 2:
        {
            PathMatrix[firstVert][secondVert].line->setPen(QPen(Qt::red));
            break;
        }
        }
    }
}

void AdjMatrix::setPointColor(int firstVert, int chose)
{
    if(Points[firstVert]->circle != nullptr && firstVert >=0)
    {
        switch(chose)
        {
        case 0:
        {
            Points[firstVert]->circle->setBrush(QColor(255,127,39));
            Points[firstVert]->circle->setPen(QPen(QColor(255,127,39)));
            break;
        }
        case 1:
        {
            Points[firstVert]->circle->setBrush(QColor(Qt::green));
            Points[firstVert]->circle->setPen(QPen(Qt::green));
            break;
        }
        case 2:
        {
            Points[firstVert]->circle->setBrush(QColor(Qt::red));
            Points[firstVert]->circle->setPen(QPen(Qt::red));
            break;
        }
        }
    }
}


void AdjMatrix::setAllPointsOneColor(int chose)
{
    for(int i = 0; i < Points.size(); i++)
    {
        setPointColor(i, chose);
    }
}

void AdjMatrix::setPathSize(int firstVert, int secondVert, int size)
{
    PathMatrix[firstVert][secondVert].size = size;
    PathMatrix[secondVert][firstVert].size = size;
    PathMatrix[firstVert][secondVert].text->setHtml(QString::number(size));
}

void AdjMatrix::setAllLinesOneColor(int chose)
{
    for(int i = 0; i < Points.size(); i++)
    {
        for(int j = 0; j < Points.size(); j++)
        {
            setLineColor(i, j, chose);
        }
    }
}

int AdjMatrix::degreeOfTop(int numbOfTop)
{
    int count = 0;
    for(int j = 0; j < Points.size(); j++)
    {
        if(PathMatrix[numbOfTop][j].size != -1) {++count;}
    }

    return count;
}

void AdjMatrix::ActivateSalesmansMethod()
{
    if(Points.size() > 2)
    {
        setAllLinesOneColor(0);

        int **arr = new int*[Points.size()];
        for(int i = 0; i < Points.size(); i++)
        {
            arr[i] = new int[Points.size()];
        }

        for(int i = 0; i < Points.size(); i++)
        {
            for(int j = 0; j < Points.size(); j++)
            {
                arr[i][j] = PathMatrix[i][j].size;
            }
        }


        std::vector<SalesmanTraveller::Edge> *Ways = new std::vector<SalesmanTraveller::Edge>;;

        SalesmanTraveller* Method = new SalesmanTraveller(arr, Points.size(), Ways);

        Method->mainFunction();

        delete Method;

        for(int i = 0; i < (*Ways).size(); i++)
        {
            setLineColor((*Ways)[i].firstTop, (*Ways)[i].secondTop, 2);
        }

        delete Ways;

        for(int i = 0; i < Points.size(); i++)
        {
           delete[] arr[i];
        }
        delete[] arr;
    }
}

QString AdjMatrix::matrixOutput()
{
    QString res;

    res += "     ";
    for (int i  = 0; i < Points.size(); i++)
    {
        res += QString::number(i)+"   ";
    }
    res += "\n";
    for (int i = 0; i < Points.size(); i++)
    {
        res += QString::number(i)+" ";
        for (int j = 0; j < Points.size(); j++)
        {
             res += QString::number(PathMatrix[i][j].size)+" ";

        }
        res += "\n";
    }
    return res;
}

AdjMatrix::~AdjMatrix()
{

}





















