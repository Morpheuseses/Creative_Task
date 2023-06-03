#include "salesmantraveller.h"


SalesmanTraveller::SalesmanTraveller(int** arr, int size, std::vector<Edge> *&ways) : sizeArr{ size + 1 }, sizeArrSecond{ size + 1 }, firstSizeArr{ size + 1 }, Ways{ ways }
{

    array = new int*[sizeArr];
    arraySecond = new int*[sizeArrSecond];
    for (int i = 0; i < sizeArr; i++)
    {
        array[i] = new int[sizeArr];
        arraySecond[i] = new int[sizeArr];
    }


    for (int i = 0; i < sizeArr; i++)
    {
        for (int j = 0; j < sizeArr; j++)
        {
            if (i == 0)
            {
                array[i][j] = j - 1;
                arraySecond[i][j] = j - 1;
            }
            if (j == 0)
            {
                array[i][j] = i - 1;
                arraySecond[i][j] = i - 1;
            }
            if (i > 0 && j > 0)
            {
                array[i][j] = arr[i - 1][j - 1];
                arraySecond[i][j] = arr[i - 1][j - 1];
            }
        }
    }

    di = new int[sizeArr - 1];
    dj = new int[sizeArr - 1];
    diSecond = new int[sizeArr - 1];
    djSecond = new int[sizeArr - 1];

    for (int i = 0; i < sizeArr - 1; i++)
    {
        di[i] = dj[i] = diSecond[i] = djSecond[i] = 101;
    }


    HWays = 0;

    H_current = 0, H_0 = 0, H_1 = 0;
}

int SalesmanTraveller::findMinElemColumn(int j, int currI)
{
    int min = 101;
    for (int i = 1; i < sizeArr; i++)
    {
        if (array[i][j] != -1)
        {

            if (currI == -1)
            {
                if (array[i][j] < min)
                {
                    min = array[i][j];
                }
            }
            else
            {
                if (i != currI)
                {
                    if (array[i][j] < min)
                    {
                        min = array[i][j];
                    }
                }
            }
        }
    }
    if (currI == -1) { if (min == 101) min = 0; }
    else { if (min == 101) min = 101; }

    return min;
}

int SalesmanTraveller::findMinElemRow(int i, int currJ)
{
    int min = 101;
    for (int j = 1; j < sizeArr; j++)
    {
        if (array[i][j] != -1)
        {

            if (currJ == -1)
            {
                if (array[i][j] < min)
                {
                    min = array[i][j];
                }
            }
            else
            {
                if (j != currJ)
                {
                    if (array[i][j] < min)
                    {
                        min = array[i][j];
                    }
                }
            }
        }
    }

    if (currJ == -1) { if (min == 101) min = 0; }
    else { if (min == 101) min = 101; }

    return min;
}

void SalesmanTraveller::findDi()
{

    for (int i = 0; i < sizeArr - 1; i++)
    {
        di[i] = 101;
    }
    di_sum = 0;

    for (int i = 0; i < sizeArr - 1; i++)
    {
        di[i] = findMinElemRow(i + 1);
        di_sum += di[i];
    }

}

void SalesmanTraveller::findDj()
{

    for (int j = 0; j < sizeArr - 1; j++)
    {
        dj[j] = 101;
    }
    dj_sum = 0;

    for (int j = 0; j < sizeArr - 1; j++)
    {
        dj[j] = findMinElemColumn(j + 1);
        dj_sum += dj[j];
    }
}

void SalesmanTraveller::reduceMatrix()
{
    findDi();

    for (int i = 1; i < sizeArr; i++)
    {
        for (int j = 1; j < sizeArr; j++)
        {
            if (array[i][j] != -1)
            {
                array[i][j] -= di[i - 1];
            }
        }
    }

    findDj();

    for (int j = 1; j < sizeArr; j++)
    {
        for (int i = 1; i < sizeArr; i++)
        {
            if (array[i][j] != -1)
            {
                array[i][j] -= dj[j - 1];
            }
        }
    }
}

void SalesmanTraveller::findZeros()
{
    zerosArray.clear();
    int J = 0;
    for (int i = 1; i < sizeArr; i++)
    {
        J = i;
        for (int j = 1; j < sizeArr; j++)
        {
            if (array[i][j] == 0 )
            {
                zerosArray.push_back(Zero((findMinElemRow(i, j) + findMinElemColumn(j, i)), i, j));
            }
        }
    }

}

void SalesmanTraveller::findZeros1()
{
    zerosArray.clear();
        int J = 0;
        for (int i = 1; i < sizeArr; i++)
        {
            J = i;
            for (int j = 1; j < sizeArr; j++)
            {
                if (array[i][j] == 0)
                {
                    zerosArray.push_back(Zero((findMinElemRow(i, j) + findMinElemColumn(j, i)), i, j));
                }
            }
        }
}

int SalesmanTraveller::findBiggerZero()
{
    int numb = 0;
    for (int i = 0; i < zerosArray.size(); i++)
    {
        if (zerosArray[i].quantity > zerosArray[numb].quantity)
        {
            numb = i;
        }
    }

    return numb;
}

void SalesmanTraveller::exclusionSimilarEdge(int indexI, int indexJ, bool choseArr)
{
    int I = -1;
    int J = -1;

    if (choseArr == 1)
    {
        for (int i = 1; i < sizeArr; i++)
        {
            if (arraySecond[indexI][0] == array[0][i])
            {
                J = i;
            }
            if (arraySecond[0][indexJ] == array[i][0])
            {
                I = i;
            }
        }
        if (I != -1 && J != -1) { array[I][J] = -1; }
    }
    else
    {
        arraySecond[indexI][indexJ] = -1;
    }
}

void SalesmanTraveller::edgesExclusion(int indexI, int indexJ)
{

    for (int i = 0; i < sizeArr; i++)
    {
        for (int j = 0; j < sizeArr; j++)
        {
            arraySecond[i][j] = array[i][j];
        }
    }

    sizeArrSecond = sizeArr;

    for (int i = 0; i < sizeArrSecond - 1; i++)
    {
        diSecond[i] = di[i];
        djSecond[i] = dj[i];
    }


    int I = 0, J = 0;
    for (int i = 1; i < sizeArr; i++)
    {
        I = i;
        if (i != indexI)
        {
            if (i > indexI) { --I; }
            for (int j = 1; j < sizeArr; j++)
            {
                J = j;
                if (j != indexJ)
                {
                    if (j > indexJ) { --J; }
                    array[I][J] = arraySecond[i][j];
                }
            }
        }
    }


    --sizeArr;


    for (int i = indexI; i < sizeArr; i++)
    {
        array[i][0] = array[i + 1][0];
    }

    for (int j = indexJ; j < sizeArr; j++)
    {
        array[0][j] = array[0][j + 1];
    }


    for (int i = indexI - 1; i < sizeArr - 1; i++)
    {
        di[i] = di[i + 1];
    }

    for (int j = indexJ - 1; j < sizeArr - 1; j++)
    {
        dj[j] = dj[j + 1];
    }

}

void SalesmanTraveller::chooseMatrix(int chose)
{
    if (chose == 1)
    {
        H_current = H_1;
    }
    else
    {
        sizeArr = sizeArrSecond;
        for (int i = 0; i < sizeArrSecond; i++)
        {
            for (int j = 0; j < sizeArrSecond; j++)
            {
                array[i][j] = arraySecond[i][j];
            }
        }

        for (int i = 0; i < sizeArr - 1; i++)
        {
            di[i] = diSecond[i];
            dj[i] = djSecond[i];
        }

        H_current = H_0;
    }
}

void SalesmanTraveller::mainFunction()
{
    reduceMatrix();

    H_current = di_sum + dj_sum;

    int numbOfZeroMax = 0;
    bool isH_0 = false;
    bool flag = true;
    while (flag)
    {
        if (isH_0 == false)
        {

            findZeros();
        }
        else
        {
            zerosArray.erase(zerosArray.begin() + numbOfZeroMax);

        }

        numbOfZeroMax = findBiggerZero();
        Zero zeroMax = zerosArray[numbOfZeroMax];


        H_0 = H_current + zeroMax.quantity;

        edgesExclusion(zeroMax.i, zeroMax.j);
        exclusionSimilarEdge(zeroMax.i, zeroMax.j, 1);


        reduceMatrix();

        H_1 = H_current + di_sum + dj_sum;

        if (H_1 <= H_0)
        {
            isH_0 = false;
            (*Ways).push_back(Edge(arraySecond[zeroMax.i][0], arraySecond[0][zeroMax.j]));
            chooseMatrix(1);

        }
        else
        {
            isH_0 = true;
            chooseMatrix(0);
            H_current -= zeroMax.quantity;
        }


        if (sizeArr == 1)
        {
            flag = false;
        }

    }

}

SalesmanTraveller::~SalesmanTraveller()
{
        for (int i = 0; i < sizeArr; i++)
        {
            delete[] array[i];
            delete[] arraySecond[i];
        }

        delete[] array;
        delete[] arraySecond;

        delete[] di;
        delete[] dj;
        delete[] diSecond;
        delete[] djSecond;
}






















