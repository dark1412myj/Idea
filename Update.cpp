#include<iostream>
//#include<thread>
using namespace std;

class Manager
{
private:
    int* inSelect;
    int NumOfThread;
    bool isUpdate;
    //bool hascreate;
    Manager()
    {
        inSelect = NULL;
        isUpdate = 0;
        //hascreate = 0;
        NumOfThread = 0;
    }
    ~Manager() {}
public:
    bool Init(int NumOfThread)
    {
        if(inSelect)
            return false;
        inSelect=new int[NumOfThread];
        this->NumOfThread = NumOfThread;
    }
    static Manager& GetInstance()
    {
        static Manager instance;
        return instance;
    }
    bool Update()     //�豣֤�̰߳�ȫ
    {
        isUpdate = 1;
        for(int i=0; i<NumOfThread; ++i)
        {
            while(inSelect[i]);
        }
        //do some update
        isUpdate = 0;
        return true;
    }
    bool Deal(int threadId)   //���̻߳�����������ʹ��
    {
        bool ret = false;
        inSelect[threadId]=1;
        if(0==isUpdate)
        {
            //do something as usual
            ret = true;
        }else
        {
            //do something to skip this deal
            ret = false;
        }
        inSelect[threadId]=0;
        return ret;
    }

};

int main()
{
    return 0;
}
