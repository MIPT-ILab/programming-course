#include <stdio.h>
#include <assert.h>
#include <string.h>

#define _STACKSIZE_ 100

struct stack_t
{
    double data_[_STACKSIZE_];
    int count_;

    stack_t();
   ~stack_t();
    bool push(double value);
    double pop();
    // FIXME It should be better to read with space between () and const;
    // bool OK() const;
    bool OK()const;    //checks if evrth is ok whith stack
    bool dump()const;  //prints all elements of the stack
    int size()const;   //returns a number of elements in the stack
    double get()const; //the same as pop but witout destroing the last element
};

stack_t::stack_t():
    count_(0)
    {
    // FIXME In C++ we use commands 'new' and 'delete' to deal with
    // dynamic memory
        memset(data_,0,_STACKSIZE_);
        // FIXME In C++ we input or output text with std::cout and std::cin.
        printf("Hello. Stack has been already launched.\n");
    }

stack_t::~stack_t()
{
// FIXME It is useless to assign value to counter here.
    count_=-1;
    // FIXME In C++ we input or output text with std::cout and std::cin.
    printf("Stack has been already destroyed. Good bye.\n");
}

bool stack_t::push(double value)
{
    if(count_>=_STACKSIZE_ || count_<0)
        return false;
    // FIXME I prefer to split this. It is pretty difficult to understand
    // all effects of this code.
    // count_++;
    // data_[count] = valeu;
    data_[count_++]=value;
    return true;
}

double stack_t::pop()
{
    if(count_<1 || count_>_STACKSIZE_){
    // FIXME In C++ we input or output text with std::cout and std::cin.
        printf("Error: Impossible usage of pop() function.\n");
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
            int i=count_;
            printf("\nHere is your stack:\n");
            // FIXME THis is very complicated loop. Rewrite it.
            // In C++ you can 'for (int i = 0; i <....; i++) {...}'
            for(i--;i>=0;i--)
                printf("%03d element : %f\n",count_-i,data_[i]);
            printf("\n");
            return true;
        }
        else{}  // FIXME What is it?) {} THis code is very unclear.
            printf("\nStack is empty.\n");
            return true;
        }
    else
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
        printf("Error: Impossible usage of get() function.\n");
        assert(0);
    }
    else
        return data_[count_-1];
}

/*int main()
{
    stack_t st;
    st.push(1);
    st.push(2);
    st.push(0.222222);
    st.dump();
    printf("%d\n",st.size());
    printf("%fl\n",st.get());

}*/


// FIXME Add list-based version!
