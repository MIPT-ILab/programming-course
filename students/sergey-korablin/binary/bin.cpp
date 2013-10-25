#include <stdio.h>
#include <assert.h>

class Binary {
    bool *data;
    unsigned long len;
    //data[0] - младший бит (порядок обратный)

    long subEqualDiff ( const Binary a,
                        const Binary b ) {
        /*
        Проверить, заполнены ли нулями старшие разряды
        более длинного числа (число старших разрядов - 
        разность длин более длинного и короткого чисел)
        Если нули, вернуть 0
        Если не нули в длинном a, вернуть 1
        Если не нули в длинном b, вернуть -1
        ***
        Более понятно:
        Приложить два числа младшими разрядами
        Проверить выступающий слева "хвост"
        Если он заполнен нулями, вернуть 0
        Если нет, вернуть 1 (если длинное a)
        или -1 (если длинное b)
        */
        unsigned long i;
        if ((a.len) > (b.len)) { // a длиннее b
            for (i=a.len-1; i>=b.len; i--)
            /*

            */
                    if (a.data[i]!=0)
                        return 1;
            return 0; 
        }
        else
            return (-1) * subEqualDiff (b, a);
    }

    unsigned long subMinLen ( const Binary a,
                              const Binary b ) {
        //Вернуть длину меньшего из чисел
        return (a.len < b.len) ? a.len : b.len;
    }

    unsigned long subMaxLen ( const Binary a,
                              const Binary b ) {
        //Вернуть длину большего из чисел
        return (a.len > b.len) ? a.len : b.len;
    }

    int Expand (const long diff) {
        /*
        Изменение длины бинарного числа
        Если больше нуля - то добавить место со стороны
        старшего разряда
        Если меньше нуля - убрать diff старших разрядов
        При расширении занять место нулями
        */
        if (diff==0)
            return 0;
        if ((this->len + diff) < 0)
            return -1;
        if ((this->len + diff) == 0) {
            this->Delete();
            return 0;
        }
        unsigned long to_backup=this->len;
        if (diff < 0)
            to_backup += diff;
        this->len += diff;
        bool *tmp = new bool[to_backup];
        unsigned long i=0;
        for (i=0; i < to_backup; i++) {
            tmp[i]=this->data[i];
        }
        delete []this->data;
        this->data=new bool [this->len];
        for (i=0; i<to_backup; i++) {
            this->data[i]=tmp[i];
        }
        for (i=to_backup; i < this->len; i++) {
            this->data[i]=0;
        }
        return 0;
    }

    bool subSum ( const bool a,
                  const bool b,
                  bool &reg) {
        /*
        Выполнить сложение a и b по модулю 2
        В качестве регистра использовать reg
        */
        if (a!=b) { //1+0 or 0+1
            if (reg==0) {
                return 1;
            }
            else {
                reg=1;
                return 0;
            }
        }
        else {
            if (a==0) { //0+0
                if (reg==0) {
                    return 0;
                }
                else {
                    reg=0;
                    return 1;
                }
            }
            else { // 1+1
                if (reg==0) {
                    reg=1;
                    return 0;
                }
                else
                {
                    return 1;
                }
            }
        }
    }

    bool subDif ( const bool a, 
                  const bool b, 
                  bool &reg) {
        /*
        Выполнить вычитание a-b по модулю 2
        Занятый разряд поместить в reg
        */
        if (a==0 && b==0)  // 0 - 0
            if (reg==0)
                return 0;
            else {
                reg=1;
                return 1;
            }
        else
        if (a==1 && b==0) // 1 - 0
            if (reg==0)
                return 1;
            else {
                reg=0;
                return 0;
            }
        else
        if (a==1 && b==1) //1 - 1
            if (reg==0)
                return 0;
            else {
                reg=1;
                return 1;
            }
        else              // 0 - 1
        if (reg==0) {
            reg=1;
            return 1;
        }
        else
            return 0;
    }

    void subCopyLostItems ( Binary const &a,  
                            Binary const &b, 
                            Binary &sum, 
                            bool &reg) {
    /*
    Перенести "хвост" старших разрядов более длинного числа
    в итоговое число sum. Учитывать значение регистра,
    переданное после суммирования основной части
    */
        if ((a.len) >= (b.len)) {
            unsigned long i=b.len;
            while (i < a.len) {
                sum.data[i]=subSum(a.data[i], 0, reg);
                i++;
            }
            if (reg==1) {
                sum.Expand(1); //если не влезло, расширить
            }
            if (i < sum.len) {                  //TODO check IF[WHILE]
                sum.data[i]=subSum(0, 0, reg);
                i++;
            }
        }
        else {
            subCopyLostItems (b, a, sum, reg);
        }
    }

    int subDifLostItems ( Binary const &a,
                           Binary const &b,
                           Binary &dif,
                            bool &reg ) {
    /*
    Перенести "хвост" старших разрядов более длинного числа
    в итоговое число dif. Учитывать значение регистра
    (занятый разряд), переданное после вычитания основной части
    Если в результате число отрицательное, вернуть -1
    */
        if ((a.len) >= (b.len)) {
            unsigned long i=b.len;
            while (i < a.len) {
                dif.data[i]=subDif(a.data[i], 0, reg);
                i++;
            }
            while (i < dif.len) {
                dif.data[i]=subDif(0, 0, reg);
                i++;
            }
            if (reg==1)
                return 1;
            return 0;
        }
        else {
            subDifLostItems (b, a, dif, reg);
        }
    }

    unsigned long myPow (const unsigned long x, const unsigned long n) {
    //Возведение x в степень n
        if (n==0)
            return 1;
        if (n==1)
            return x;
        unsigned long i;
        unsigned long ans=x;
        for (i=1; i<n; i++) {
            ans=ans*x;
        }
        return ans;
    }
//----------------------------------------------------------
    public:

    void Init (const unsigned long in_l) {
        unsigned long l=in_l;
//        if (l < 8)
//            l = 8;
//        Это попытка оптимизации по памяти
        this->data = new bool[l];
        this->len = l;
        unsigned long i;
        for (i=0; i<(this->len); i++) {
            this->data[i]=0;
        }
    }
    
    Binary (const unsigned long l) {
        this->Init(l);
    }

    Binary () {
        this->Init(1);
    }

    void Delete () {
        this->len = 0;
        delete []this->data;
    }

    ~Binary() {
      //  this->Delete();
    }

    unsigned long GetLen() {
        return this->len;
    }

    Binary& operator= (Binary &rv) {
        if (this==&rv)
            return *this;
        this->Delete();
        this->Init(rv.len);
        unsigned long i;
        for (i=0; i<this->len; i++) {
            this->data[i]=rv.data[i];
        }
        return *this;
    }

    Binary & operator + ( Binary const &rv ) {
        unsigned long l;
        l=subMaxLen(*this,rv);
        Binary *sum=new Binary;
        sum->Init (l);
        bool registr=0;
        unsigned long i = 0;
        unsigned long minL=subMinLen(*this,rv);
        while (i < minL) {
            sum->data[i]=subSum(this->data[i],rv.data[i],registr);
            i++;
        }
        subCopyLostItems(*this,rv,*sum,registr);
        //расширение при необходимости выполняется строкой выше
//        delete []this->data;
        *this=*sum;
        return *this;
    }

    Binary & operator - ( Binary const &rv ) {
        unsigned long l;
        l=subMaxLen(*this,rv);
        Binary *dif=new Binary;
        dif->Init (l);
        bool registr=0;
        unsigned long i = 0;
        unsigned long minL=subMinLen(*this,rv);
        while (i < minL) {
            dif->data[i]=subDif(this->data[i],rv.data[i],registr);
            i++;
        }
        assert (subDifLostItems(*this,rv,*dif,registr)==0);
        Optimise (*dif); //убрать нули в высших разрядах
//        this->Delete();
        *this=*dif;
        return *this;
    }

    int Equal (const Binary a, const Binary b) {
    /*
    Проверить равенство a и b
    Если a>b, вернуть 1
    Если a<b, вернуть -1
    Если a==b, вернуть 0
    */
        unsigned long i=0;
        int res=subEqualDiff (a, b);
        if (res!=0)
            return res;
        unsigned long MinLen=subMinLen (a, b);
        for (i=0; i<MinLen; i++) {
            if ((int)a.data[i] > (int)b.data[i])
                return 1;
            else
                if ((int)a.data[i] < (int)b.data[i])
                return -1;
        }
        return 0;
    }

    void Optimise (Binary &x) {
    //Убирает нулевые старшие разряды
        if (x.len==1) {
            return;
        }
        unsigned long i=0;
        while (x.data[x.len-1-i]==0 && i<x.len) {
            i++;
        }
        if (i==x.len)
            i--;
        x.Expand(-i);
    }

    void Print () {
    //Выводит число, если оно существует
        if (this->len==0)
            return;
        unsigned long i=(this->len)-1;
        while (i>0) {
            printf("%d",(int)this->data[i]);
            i--;
        }
        printf("%d\n",(int)this->data[i]);;
    }

    void Increment () {
        //Увеличивает значение на 1
        unsigned long i = 0;
        if (this->data[i]==0) {
            this->data[i]=1; return;
        }
        else {
            this->data[i]=0;
            i++;
            if (i == this->len) {
                this->Expand (1);
            }
            while (this->data[i]==1) {
                this->data[i]=0;
                i++;
            }
            if (i == this->len) {
                this->Expand (1);                
            }
            this->data[i]=1;
        }
    }
    
    void Decrement () {
        //Уменьшает значение на 1
        unsigned long i = 0;
        if (this->data[i]==1) {
            this->data[i]=0; return;
        }
        else {
            if (this->len==1)
                return;
            this->data[i]=1;
            i++;
            while (this->data[i]==0) {
                this->data[i]=1;
                i++;
            }
            this->data[i]=0;
        }
        Optimise (*this);
    }

    void ConvertToBinary (const unsigned long x) {
        //Переводит положительное число x в двоичный вид
        //Заменяет текущее значение переменной
        unsigned long i=0;
        unsigned long t=x;
        if (x==0) {
            this->Delete();
            this->Init(1);
            return;
        }
        while (t>0) {
            t=t/2;
            i++;
        }
        this->Delete();
        this->Init(i);
        t=x;
        i=0;
        while (t>0) {
            this->data[i]=t%2;
            t=t/2;
            i++;
        }
    }

    unsigned long ConvertToDecimal () {
        //Возвращает десятичное значение числа
        unsigned long ans=0;
        unsigned long i=0;
        for (i=0; i<this->len; i++) {
            ans+=((int)this->data[i])*myPow(2,i);
        }
        return ans;
    }
    friend Binary & And ( Binary const &, Binary const & );
    //Побитовое И

    friend Binary & Or ( Binary const &, Binary const & );
    //Побитовое ИЛИ
};

    Binary & And ( Binary const &lv, Binary const &rv ) {
        unsigned long minL=(lv.len<rv.len)?lv.len:rv.len;
        Binary *bAnd=new Binary;
        bAnd->Init (minL);
        unsigned long i = 0;
        while (i < minL) {
            bAnd->data[i]=lv.data[i] && rv.data[i];
            i++;
        }
        bAnd->Optimise(*bAnd);
        return *bAnd;
    }

    Binary & Or ( Binary const &lv, Binary const &rv ) {
        unsigned long minL=(lv.len<rv.len)?lv.len:rv.len;
        unsigned long maxL=(lv.len>rv.len)?lv.len:rv.len;
        Binary *bOr=new Binary;
        bOr->Init (maxL);
        unsigned long i = 0;
        while (i < minL) {
            bOr->data[i]=lv.data[i] || rv.data[i];
            i++;
        }
        if (lv.len>rv.len)
            while (i<maxL) {
                bOr->data[i]=lv.data[i];
                i++;
            }
        else
            while (i<maxL) {
                bOr->data[i]=rv.data[i];
                i++;
            }
        bOr->Optimise(*bOr);
        return *bOr;
    }

int main () {
    Binary x,y,z;
    unsigned long a=1,b=3;
    //scanf("%lu %lu",&a, &b);
    x.ConvertToBinary(a);
    y.ConvertToBinary(b);
    printf("x in bin: ");    
    x.Print();
    printf("y in bin: ");
    y.Print();
    z=And(x,y);
    printf("x and y in bin: ");
    z.Print();
    z=Or(x,y);
    printf("x or y in bin: ");
    z.Print();
    z.Delete();
    z.Init(1);
    printf("x + y in bin: ");
    z=x+y;
    z.Print();
    x.Delete();
    z.Delete();
    y.Delete();
    return 0;
}
