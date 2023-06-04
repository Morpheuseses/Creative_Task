#ifndef SALESMANTRAVELLER_H
#define SALESMANTRAVELLER_H

#include <vector>

class SalesmanTraveller
{

public:
    struct Edge
    {
        int firstTop;
        int secondTop;

        Edge(int I, int J) : firstTop(I), secondTop(J)
        {

        }
        bool operator==(Edge e)
        {
            return e.firstTop ==  firstTop && e.secondTop == secondTop;
        }
    };

private:

    class Zero
    {
    public:
        int quantity;
        int i;
        int j;

        Zero(int Q, int I, int J) : quantity{ Q }, i{ I }, j{ J }
        {
        }
        ~Zero()
        {
        }
    };
private:

    int **array = nullptr;
    int **arraySecond = nullptr;


    const int firstSizeArr;
    int sizeArr;
    int sizeArrSecond;
    int *di = nullptr, *dj = nullptr;
    int *diSecond = nullptr, *djSecond = nullptr;

    int di_sum, dj_sum;


    std::vector<Edge> *Ways = nullptr;
    int HWays;

    int H_current, H_0, H_1;

    std::vector<Zero> zerosArray;
public:
    SalesmanTraveller(int** arr, int size, std::vector<Edge> *&ways);

    int findMinElemColumn(int j, int currI = -1);
    int findMinElemRow(int i, int currJ = -1);
    void findDi();
    void findDj();
    void reduceMatrix();
    void findZeros();
    void findZeros1();
    int findBiggerZero();
    void exclusionSimilarEdge(int indexI, int indexJ, bool choseArr);
    void edgesExclusion(int indexI, int indexJ);
    void chooseMatrix(int chose);
    void mainFunction();

    ~SalesmanTraveller();
};


#endif // SALESMANTRAVELLER_H
