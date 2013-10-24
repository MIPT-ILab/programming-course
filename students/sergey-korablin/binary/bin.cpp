#include <stdio.h>

//Sorry for code formatting
//I'm now interested in correct work
//But it works.. hm.. strange
//I'll do refactoring later

class Binary {
    bool *data;
    unsigned long len;
    //data[0] - младший бит (порядок обратный)

    long subEqualDiff (const Binary a, const Binary b) {
        unsigned long i;
        if ((a.len) > (b.len)) {
            for (i=a.len-1; i>=b.len; i--)
                    if (a.data[i]!=0)
                        return 1;
            return 0;
        }
        else
            return (-1) * subEqualDiff (b, a);
    }

    unsigned long subMinLen (const Binary a, const Binary b) {
        if (a.len < b.len)
            return a.len;
        return b.len;
    }

    unsigned long subMaxLen (const Binary a, const Binary b) {
        if (a.len > b.len)
            return a.len;
        return b.len;
    }

    int Expand (long diff) {
        if (diff==0)
            return 0;
        if ((this->len + diff) < 0)
            return -1;
        if ((this->len + diff) == 0) {
            this->Delete();
            return 0;
        }
        this->len += diff;
        bool *tmp;
        tmp = new bool[this->len];
        unsigned long i=0;
        for (i=0; i<this->len; i++) {
            tmp[i]=this->data[i];
        }
        delete []this->data;
        this->data=new bool [this->len];
        for (i=0; i<this->len; i++) {
            this->data[i]=tmp[i];
        }
        return 0;
    }

    bool subSum (const bool a, const bool b, bool &reg) {
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

    bool subDif (const bool a, const bool b, bool &reg) {
        if (a==0 && b==0)
            if (reg==0)
                return 0;
            else {
                reg=1;
                return 1;
            }
        else
        if (a==1 && b==0)
            if (reg==0)
                return 1;
            else {
                reg=0;
                return 0;
            }
        else
        if (a==1 && b==1)
            if (reg==0)
                return 0;
            else {
                reg=1;
                return 1;
            }
        else
        if (reg==0) {
            reg=1;
            return 1;
        }
        else
            return 0;
    }

    void subCopyLostItems ( Binary const &a,  Binary const &b, Binary &sum, bool &reg) {
        if ((a.len) >= (b.len)) {
            unsigned long i=b.len;
            while (i < a.len) {
                sum.data[i]=subSum(a.data[i], 0, reg);
                i++;
            }
            if (reg==1) {
                sum.Expand(1);
            }
            while (i < sum.len) {
                sum.data[i]=subSum(0, 0, reg);
                i++;
            }
        }
        else {
            subCopyLostItems (b, a, sum, reg);
        }
    }

    void subDifLostItems ( Binary const &a,  Binary const &b, Binary &dif, bool &reg) {
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
        }
        else {
            subDifLostItems (b, a, dif, reg);
        }
    }

    unsigned long myPow (const unsigned long x, const unsigned long n) {
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
        //this->Delete();
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
        subDifLostItems(*this,rv,*dif,registr);
        Optimise (*dif);
        *this=*dif;
        return *this;
    }

    int Equal (const Binary a, const Binary b) {
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
        unsigned long i=0;
        unsigned long t=x;
        while (t>0) {
            t=t/2;
            i++;
        }
        this->Delete();
        this->Init(i+1);
        t=x;
        i=0;
        while (t>0) {
            this->data[i]=t%2;
            t=t/2;
            i++;
        }
    }

    unsigned long ConvertToDecimal () {
        unsigned long ans=0;
        unsigned long i=0;
        for (i=0; i<this->len; i++) {
            ans+=((int)this->data[i])*myPow(2,i);
        }
        return ans;
    }
    friend Binary & And ( Binary const &, Binary const & );
    friend Binary & Or ( Binary const &, Binary const & );
};

    Binary & And ( Binary const &lv, Binary const &rv ) {
        unsigned long minL=(lv.len>rv.len)?lv.len:rv.len;
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

/*
    int m[8], o[4]; //char is better, but it makes type warnings
    scanf ("%d.%d.%d.%d",&m[0],&m[1],&m[2],&m[3]);
    scanf ("%d.%d.%d.%d",&m[4],&m[5],&m[6],&m[7]);
    Binary M[8], O[4];
    int i=0;
    for (i=0; i<8; i++) {
        M[i].ConvertToBinary(m[i]);
    }
    for (i=0; i<3; i++) {
        O[i]=And(M[i],M[i+4]);
        o[i]=O[i].ConvertToDecimal();
    }
    printf("%d.%d.%d.%d\n", m[4]==255?o[0]:255,
                            m[5]==255?o[1]:255,
                            m[6]==255?o[2]:255,
                            m[7]==255?o[3]:255);

*/

    Binary x,y,z;
    unsigned long a=0,b=0;
//    scanf("%ld %ld",&a, &b);
    x.ConvertToBinary(a);
    y.ConvertToBinary(b);
    unsigned long i;
    for (i=0;i<1000000000;i++) {
        x.Increment();
        z=And(x,y);
        if (z.ConvertToDecimal()!=0)
            printf("PWND z.ConvertToDecimal()=%d; i=%d\n",z.ConvertToDecimal(),i);
    }
    printf("FIN\n");
    
    scanf("%ld %ld",&a, &b);
    x.ConvertToBinary(a);
    y.ConvertToBinary(b);
        
//    x.Print();
//    y.Print();
    z=And(x,y);
    z.Print();
/*    z=Or(x,y);
    z.Print();
    z.Delete();
    z.Init(1);
    z=x+y;
    z.Print();
*/

    return 0;
}
