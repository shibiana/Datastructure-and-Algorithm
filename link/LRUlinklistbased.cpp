typedef int DataType;

class SNode
{
public:
    DataType data;
    SNode* next;
}; //定义结点数据类型

class SList
{
public:
    SList();                             //默认构造函数
    SList(int MaxSize);                  //构造函数
    ~SList();
    void intsertElemAtBegin(DataType x); //从链表到头部插入节点
    bool findElem(DataType x);           //查找x，存在则返回1，不存在返回0
    void deleteElemAtEnd();              //删除尾结点         
    bool deleteElem(DataType x);         //删除指定的结点,如果存在则删除，返回1，如果不存在，则删除失败，返回0
    bool isfull();                       //查看链表是否以及满了，1表示满，0表示不满
    bool isempty();
    void printAll();
    void* findElemOptim(DataType x);     //针对此应用的优化，查找,返回指定元素的前一个节点的指针
    void deleteElemOptim(void* snode);  //针对此应用的优化，删除

private:
    int MaxSize;                         //链表可以存储的最大数据量
    int length;                          //链表的长度
    SNode* head;                         //指向头结点的指针
};//定义链表数据类型

/*（1）链表的插入、删除、查找操作
  （2）假设存储的全是int类型的数据*/

#include <iostream>
using namespace std;

SList::SList()
{
    head = new SNode;                    //申请头结点
    head->next = NULL;
    this->MaxSize = 0;
    this->length = 0;
}

SList::SList(int MaxSize)
{
    head = new SNode;                    //申请头结点
    head->next = NULL;
    this->MaxSize = MaxSize;
    this->length = 0;
}

//销毁单链表，要把开辟的空间都释放，然后再销毁
SList::~SList()
{
    SNode* ptr,*temp;
    ptr = head;
    while(ptr->next != NULL)
    {
        temp = ptr->next;
        ptr->next = ptr->next->next;
        delete temp;
    }
    delete head;
    this->head = NULL;
    this->length = 0;
}

//链表头部插入结点
void SList::intsertElemAtBegin(DataType x)
{
    SNode* ptr = new SNode;
    ptr->data = x;

    ptr->next = head->next;
    head->next = ptr;

    this->length++;
}

//查找值为x的结点
bool SList::findElem(DataType x)
{
    SNode* ptr = head;
    while(ptr->next != NULL)
    {
        if(ptr->next->data == x)
        {
            return 1;
        }
        ptr = ptr->next;
    }
    return 0;
}

//删除尾结点
void SList::deleteElemAtEnd()
{
    SNode* ptr, *temp;
    ptr = head;

    //找到倒数第二个结点
    while(ptr->next != NULL && ptr->next->next != NULL)
    {
        ptr = ptr->next;
    }
    temp = ptr->next;
    ptr->next = temp->next;

    delete temp;
    this->length--;
}

//删除指定结点
bool SList::deleteElem(DataType x)
{
    SNode* ptr, *temp;
    ptr = head;

    while(ptr->next != NULL){
        if(ptr->next->data == x)
        {
            temp = ptr->next;
            ptr->next = temp->next;
            delete temp;
            this->length--;
            return 1;
        }
        ptr = ptr->next;
    }
    return 0;
}

//查看链表是否为空
bool SList::isempty()
{
    if(this->length == 0)
    {
        return 0;
    }
    else{
        return 1;
    }
}

//查看链表是否满
bool SList::isfull()
{
    if(this->length == this->MaxSize)
    {
        return 0;
    }
    else{
        return 1;
    }
}

//打印
void SList::printAll()
{
    SNode* ptr;
    ptr = head;
    while(ptr -> next != NULL){
        ptr = ptr -> next;
        cout << ptr-> data <<"   ";
    }
    cout << endl;
}   

//返回值为x的前一个结点
void* SList::findElemOptim(DataType x)
{
    SNode* ptr;
    ptr = head;

    while(ptr->next != NULL)
    {
        if(ptr->next->data == x)
        {
            return (void*)ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

//删除snode结点的下一个结点
void SList::deleteElemOptim(void* snode)
{
    SNode* ptr, *temp;
    ptr = (SNode *)snode;
    temp =  ptr -> next;
    ptr -> next = temp -> next;
    this -> length --;
    delete temp;
}

int main(int argc, char const *argv[])
{
    cout << "test "<< endl;   
    SList slist(10);     //缓存最大10个。
    int num = 0;
    while(1)
    {
        cout << "please enter a number,99999== exit" << endl;
        cin >> num;
        if(num == 99999)
            break;
        /* 未优化
        if(slist.findElem(num)){    //存在
            slist.deleteElem(num);     //把原来的位置删除
            slist.intsertElemAtBegin(num); //在链表头插入
        }
        */
       //优化
       SNode * prePtr = (SNode *)slist.findElemOptim(num);
       if(prePtr != NULL){    //存在
            slist.deleteElemOptim(prePtr);     //把原来的位置删除
            slist.intsertElemAtBegin(num); //在链表头插入
        }
        else{      //不存在
            if(slist.isfull()){    //不满
                slist.intsertElemAtBegin(num);
            }
            else{                   //满
                slist.deleteElemAtEnd();
                slist.intsertElemAtBegin(num);
            }
        }
        slist.printAll();
    }
    return 0;
}