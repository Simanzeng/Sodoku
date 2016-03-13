//����������
#include<iostream>
#include<bitset>      //��׼���ṩ�� bitset �����λ���Ĵ���
#include<cstdlib>    //exit(0),system

#define N 9
#define M 3

using namespace std;

class Sodoku
{
public:
    Sodoku();
    ~Sodoku() {}
    // ���õ�
    void Set();
    // ������֪λ�õ����ֵõ���������һ��
    void Solution();
    // ���
    void Print() const;
private:
    int a[N][N];
    bitset<N> b[N][N];
    bool c[N][N];     //��¼��֪����
    // ��������г�ʼ��
    void Init();
    // ��ô�λ����ȡ��ֵ
    void GetBitset(int x,int y);
    // �ж��Ƿ�Խ�磬���򷵻�0�����򷵻���Ӧ����a��ֵ
    int IsFull(int x,int y);
    // ���ص�һ��Ϊ1��λ�ã���1��ʼ��,return 0��ʾû�ҵ�
    int FirstOne(int x,int y);
};

void Sodoku::Init()   // ��������г�ʼ��
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

void Front(int &x,int &y)//������һ������� 0��ʼ
{
    if(y-1<0)
    {
        if(x-1<0)
        {
            cout<<"ERROR���޽�!"<<endl;
            exit(0);
        }
        x--;
        y=N-1;
    }
    else
        y--;
}

void Next(int &x,int &y)//������һ�������
{
    if(y+1>N-1)
    {
        y=0;
        x++;
    }
    else
        y++;
}

Sodoku::Sodoku()    //���캯��
{
    Init();
}


void Sodoku::Solution()  // ������֪λ�õ����ֵõ���������һ��
{
    int x=0,y=0,pos;
    bool bl=true;
    while(c[x][y])   //��֪����
    {
        if(x==N-1&&y==N-1)
            break;
        Next(x,y);
    }
    while(1)
    {
        if(bl)
        {
            b[x][y].set();     //��b[x][y]�����ж�����λ����Ϊ 1
            GetBitset(x,y);
        }
        pos=FirstOne(x,y);
        if(pos==0)
        {
            a[x][y]=0;//����ʡ
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

void Sodoku::Set()  // ������֪��
{
    int count=0;
    int x,y,temp;
    int i,j,k,l,m;
    cout<<"                        ���������� ���� Simanzeng"<<endl;
    cout<<"������������뷽���й��ж��ٸ���֪������������";
    cout<<"������������������Ӧֵ�������һ�����е���Ϊa,������ 1 1 a����"<<endl;
    cout<<"�ж��ٸ���֪����";
    cin>>count;
    cout<<"��������֪���ڷ����е�����(x,y)����Ӧֵ"<<endl;
    for(m=0;m<count;)
    {
        cin>>x>>y>>temp;//��1��ʼ
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
        cout<<"�˵�����ǰ����ĵ��г�ͻ����������Ϸ�������������룡"<<endl;
        continue;
there:
        m++;
        a[x][y]=temp;
        c[x][y]=true;
    }
}

int Sodoku::FirstOne(int x,int y)   // ���ص�һ�����Ϲ������,return 0��ʾû�ҵ�
{
    int i;
    for(i=0;i<N;i++)
    {
        if(b[x][y].test(i)==1)
            return i+1;
    }
    return 0;
}

void Sodoku::GetBitset(int x,int y)   // ��ô�λ����ȡ��ֵi,����b[x][y].test(i-1)==1
{
    int pos,i,j,k,l;
    for(i=0;i<N;i++)
    {
        pos=IsFull(x,i);
        if(pos!=0)
            b[x][y].reset(pos-1);   //��b[x][y]���� pos-1���Ķ�����λ��Ϊ0
    }
    for(j=0;j<N;j++)
    {
        pos=IsFull(j,y);
        if(pos!=0)
            b[x][y].reset(pos-1);     //��b[x][y]���� pos-1���Ķ�����λ��Ϊ0
    }
    for(i=x-x%M,l=0;l<M;i++,l++)
    {
        for(j=y-y%M,k=0;k<M;j++,k++)
        {
            if(i==x||j==y)    //ǰ����������
                continue;
            pos=IsFull(i,j);
            if(pos!=0)
                b[x][y].reset(pos-1);      //��b[x][y]���� pos-1���Ķ�����λ��Ϊ0
        }
    }
}

int Sodoku::IsFull(int x,int y)  // �ж��Ƿ�Խ�磬���򷵻�0�����򷵻���Ӧ����a��ֵ
{
    if(x<0||x>=N||y<0||y>=N)
        return 0;
    else
        return a[x][y];
}

void Sodoku::Print() const
{
    cout<<"�õ�һ������������9�׷���"<<endl;
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
