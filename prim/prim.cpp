//采用邻接矩阵的方法
#include <iostream>
#include <fstream>
using namespace std;
class Graph
{
public:
    int n;          //图的顶点个数
    int m;          //已建树的结点数
    int **edges;    //邻接矩阵
    int **rs_edges; //记录结果矩阵
    int *add;       //已经建树的结点
    bool *c_add;    //判断是否已经成为树结点

public:
    Graph()
    {
        infile();
        Prim();
        outfile();
    }
    ~Graph() //析构函数
    {
        delete[] add;
        delete[] c_add;
        for (int i = 0; i < n; i++)
            delete[] edges[i];
        delete[] edges;
        for (int i = 0; i < n; i++)
            delete[] rs_edges[i];
        delete[] rs_edges;
    }
    void infile();  //读取文件
    void outfile(); //输出结果
    void Prim();    //Prim算法
};
void Graph::infile()
{
    ifstream infile;
    infile.open("Prim_text.txt");
    infile >> n;
    edges = new int *[n];
    for (int i = 0; i < n; i++)
        edges[i] = new int[n];
    rs_edges = new int *[n];
    for (int i = 0; i < n; i++)
        rs_edges[i] = new int[n];
    add = new int[n];
    c_add = new bool[n];
    m = 1;
    add[0] = 0;
    c_add[0] = true;
    for (int i = 1; i < n; i++)
        c_add[i] = false;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            infile >> edges[i][j];
            rs_edges[i][j] = -1;
        }
    infile.close();
}
void Graph::Prim()
{
    int min = INT_MAX;
    int temp1, temp2; //记录距离最小的两个结点
    while (m != n)
    {
        for (int j = 0; j < m; j++)
            for (int i = 0; i < n; i++)
                if ((!c_add[i]) && edges[add[j]][i] != 0 && edges[add[j]][i] != -1 && edges[add[j]][i] < min)
                {
                    min = edges[add[j]][i];
                    temp1 = add[j];
                    temp2 = i;
                }
        c_add[temp2] = 1;
        add[m] = temp2;
        m++;
        rs_edges[temp1][temp2] = min;
        min = INT_MAX;
    }
}
void Graph::outfile()
{
    ofstream outfile;
    outfile.open("Prim_re.txt");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            if (j < i)
                outfile << rs_edges[j][i] << '\t';
            else if (j == i)
                outfile << 0 << '\t';
            else
                outfile << rs_edges[i][j] << '\t';
        outfile << endl;
    }
    outfile.close();
}

int main()
{
    Graph G;
    system("pause");
    return 0;
}
