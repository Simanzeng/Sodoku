//数独求解程序
#include<iostream>
#include<bitset>      //标准库提供的 bitset 类简化了位集的处理
#include<cstdlib>    //exit(0),system

#define N 9
#define M 3

using namespace std;

class Sodoku
{
public:
    Sodoku();
    ~Sodoku() {}
    // 设置点
    void Set();
    // 输入已知位置的数字得到满足规则的一个
    void Solution();
    // 输出
    void Print() const;
private:
    int a[N][N];
    bitset<N> b[N][N];
    bool c[N][N];     //记录已知的数
    // 对数组进行初始化
    void Init();
    // 获得此位置能取的值
    void GetBitset(int x,int y);
    // 判断是否越界，是则返回0，否则返回相应数组a的值
    int IsFull(int x,int y);
    // 返回第一个为1的位置（从1开始）,return 0表示没找到
    int FirstOne(int x,int y);
};

void Sodoku::Init()   // 对数组进行初始化
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            a[i][j]=0;
            c[i][j]=false;
        }
    }
}

void Front(int &x,int &y)//返回上一点的坐标 0开始
{
    if(y-1<0)
    {
        if(x-1<0)
        {
            cout<<"ERROR，无解!"<<endl;
            exit(0);
        }
        x--;
        y=N-1;
    }
    else
        y--;
}

void Next(int &x,int &y)//返回下一点的坐标
{
    if(y+1>N-1)
    {
        y=0;
        x++;
    }
    else
        y++;
}

Sodoku::Sodoku()    //构造函数
{
    Init();
}


void Sodoku::Solution()  // 输入已知位置的数字得到满足规则的一个
{
    int x=0,y=0,pos;
    bool bl=true;
    while(c[x][y])   //已知的数
    {
        if(x==N-1&&y==N-1)
            break;
        Next(x,y);
    }
    while(1)
    {
        if(bl)
        {
            b[x][y].set();     //把b[x][y]中所有二进制位都置为 1
            GetBitset(x,y);
        }
        pos=FirstOne(x,y);
        if(pos==0)
        {
            a[x][y]=0;//不可省
            Front(x,y);
            while(c[x][y])
                Front(x,y);
            bl=false;
        }
        else
        {
            b[x][y].reset(pos-1);
            a[x][y]=pos;
            if(x==N-1&&y==N-1)
                break;
            else
            {
                Next(x,y);
                while(c[x][y])
                {
                    if(x==N-1&&y==N-1)
                        break;
                    Next(x,y);
                }
                bl=true;
            }
        }
    }
}

void Sodoku::Set()  // 设置已知点
{
    int count=0;
    int x,y,temp;
    int i,j,k,l,m;
    cout<<"                        数独计算器 —— Simanzeng"<<endl;
    cout<<"输入规则：先输入方格中共有多少个已知的数，再依次";
    cout<<"输入各个数的坐标和相应值（比如第一个格中的数为a,则输入 1 1 a）。"<<endl;
    cout<<"有多少个已知数；";
    cin>>count;
    cout<<"请输入已知数在方格中的坐标(x,y)和相应值"<<endl;
    for(m=0;m<count;)
    {
        cin>>x>>y>>temp;//从1开始
        x--;
        y--;
        for(i=0;i<N;i++)
        {
            if(temp==IsFull(x,i))
                goto here;
        }
        for(j=0;j<N;j++)
        {
            if(temp==IsFull(j,y))
                goto here;
        }
        for(i=x-x%M,l=0;l<M;i++,l++)
        {
            for(j=y-y%M,k=0;k<M;j++,k++)
            {
                if(i==x||j==y)
                    continue;
                if(temp==IsFull(i,j))
                    goto here;
            }
        }
        goto there;
here:
        cout<<"此点与先前输入的点有冲突，不符合游戏规则！请重新输入！"<<endl;
        continue;
there:
        m++;
        a[x][y]=temp;
        c[x][y]=true;
    }
}

int Sodoku::FirstOne(int x,int y)   // 返回第一个符合规则的数,return 0表示没找到
{
    int i;
    for(i=0;i<N;i++)
    {
        if(b[x][y].test(i)==1)
            return i+1;
    }
    return 0;
}

void Sodoku::GetBitset(int x,int y)   // 获得此位置能取的值i,其中b[x][y].test(i-1)==1
{
    int pos,i,j,k,l;
    for(i=0;i<N;i++)
    {
        pos=IsFull(x,i);
        if(pos!=0)
            b[x][y].reset(pos-1);   //把b[x][y]中在 pos-1处的二进制位置为0
    }
    for(j=0;j<N;j++)
    {
        pos=IsFull(j,y);
        if(pos!=0)
            b[x][y].reset(pos-1);     //把b[x][y]中在 pos-1处的二进制位置为0
    }
    for(i=x-x%M,l=0;l<M;i++,l++)
    {
        for(j=y-y%M,k=0;k<M;j++,k++)
        {
            if(i==x||j==y)    //前面的两种情况
                continue;
            pos=IsFull(i,j);
            if(pos!=0)
                b[x][y].reset(pos-1);      //把b[x][y]中在 pos-1处的二进制位置为0
        }
    }
}

int Sodoku::IsFull(int x,int y)  // 判断是否越界，是则返回0，否则返回相应数组a的值
{
    if(x<0||x>=N||y<0||y>=N)
        return 0;
    else
        return a[x][y];
}

void Sodoku::Print() const
{
    cout<<"得到一个满足数独的9阶方阵："<<endl;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
            cout<<a[i][j]<<"  ";
        cout<<endl;
    }
    cout<<endl;
}

int main()
{
    Sodoku A;
    A.Set();
    cout<<endl;
    A.Solution();
    A.Print();
    system("PAUSE");
    return 0;
}
