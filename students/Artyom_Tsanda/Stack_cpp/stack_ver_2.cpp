#include <iostream>
#include <assert.h>
#include <string.h>
using namespace std;
#define _STACKSIZE_ 100

struct stack_t
{
    double data_[_STACKSIZE_];
    int count_;

    stack_t();
   ~stack_t();
    bool push(double value);
    double pop();
    bool OK() const;    //checks if evrth is ok whith stack
    bool dump() const;  //prints all elements of the stack
    int size() const;   //returns a number of elements in the stack
    double get() const; //the same as pop but witout destroing the last element
};

stack_t::stack_t():
    count_(0)
    {
        memset(data_,0,_STACKSIZE_);
        cout<<"Hello. Stack has been already launched."<<endl;
        ;
    }

stack_t::~stack_t()
{
    cout<<"Stack has been already destroyed. Good bye."<<endl;
}

bool stack_t::push(double value)
{
    if(count_>=_STACKSIZE_ || count_<0)
        return false;
    data_[count_]=value;
    count_++;
    return true;
}

double stack_t::pop()
{
    if(count_<1 || count_>_STACKSIZE_){
        cout<<"Error: Impossible usage of pop() function."<<endl;
        assert(0);
    }
    count_--;
    return data_[count_];
}

bool stack_t::OK()const
{
    if(count_<0 || count_>_STACKSIZE_)
        return false;
    else
        return true;
}

bool stack_t::dump() const
{
    if(OK()){
        if(count_>=1){

            cout<<"\nHere is your stack:\n"<<endl;

            for(int i=count_-1;i>=0;i--)
                cout<<count_-i<<" element : "<<data_[i]<<endl;

            cout<<"\n"<<endl;
            return true;
        }
        else{
            cout<<"\nStack is empty."<<endl;
            return true;
        }
    }else
        return false;
}

int stack_t::size()const
{
    if(OK())
        return count_;
    else
        return -1;
}

double stack_t::get()const
{
    if(count_<1 || count_>_STACKSIZE_){
        cout<<"Error: Impossible usage of get() function.\n"<<endl;
        assert(0);
    }
    else
        return data_[count_-1];
}

i/*nt main()
{
    stack_t st;
    st.push(1);
    st.push(2);
    st.push(0.222222);
    st.dump();
    cout<<st.size()<<endl;
    cout<<st.get()<<endl;

}*/
