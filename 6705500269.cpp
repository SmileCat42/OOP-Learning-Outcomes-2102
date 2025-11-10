#include <iostream>
using namespace std;

class Order;
class Discount;
class Tea;
class Juice;
class TeaJuice;
class Honey;
class WildHoney;
class FarmedHoney;

class ColdDrink{
    double price;
    bool smoothie;
    int type;
    public :
    virtual double reducePrice()=0;
    ColdDrink(){
        setPrice(20);
        setSmoothie(true);
        setType(1);
    }
    ColdDrink(double a, bool b, int c){
        setPrice(a);
        setSmoothie(b);
        setType(c);
    }
    void setPrice(double a){
        price=a;
    }
    void setSmoothie(bool a){
        smoothie=a;
    }
    void setType(int a){
        type=a;
    }
    double getPrice(){
        return price;
    }
    bool getSmoothie(){
        return smoothie;
    }
    int getType(){
        return type;
    }
    virtual void show(){
        cout << "Price : " << price << " smoothie : " << smoothie << " type : " << type << endl;
    }
    friend ostream& operator << (ostream &os, ColdDrink &a);
};

class Tea:virtual public ColdDrink{
    int type;
    public :
    Tea(){
        setType(1);
    }
    Tea(double a, bool b, int c, int d): ColdDrink(a,b,c){
        setType(d);
    }
    void setType(int a){
        type=a;
    }
    int getType(){
        return type;
    }
    double reducePrice(){
        setPrice(getPrice()-2);
        return getPrice();
    }
    void show(){
        cout << "---Tea---" << endl;
        cout << "Type : " << type << endl;
        ColdDrink::show();
    }
};

class Juice:virtual public ColdDrink{
    int name;
    public :
    Juice(){
        setName(1);
    }
    Juice(double a, bool b, int c, int d):ColdDrink(a,b,c){
        setName(d);
    }
    void setName(int a){
        name=a;
    }
    int getName(){
        return name;
    }
    double reducePrice(){
        setPrice(getPrice()-3);
        return getPrice();
    }
    void show(){
        cout << "---Juice---" << endl;
        cout << "Name juice : " << name << endl;
        ColdDrink::show();
    }
};

class Honey{
    int grade;
    static int count;
    public :
    Honey(){
        setGrade(2);
        count++;
    }
    Honey(int a){
        setGrade(a);
        count++;
    }
    void setGrade(int a){
        grade=a;
    }
    int getGrade(){
        return grade;
    }
    static int getCount(){
        return count;
    }
    virtual string getInfo(){
        switch(grade){
            case 1 : return "grade A";
            case 2 : return "grade B";
            case 3 : return "grade C";
        }
    }
    virtual string operator ++ (){
        return getInfo();
    }
};

int Honey::count;



ostream& operator << (ostream& os, ColdDrink &a){
    a.show();
}



class WildHoney:public Honey{
    int source;
    public :
    WildHoney(){
        setSource(1);
    }
    WildHoney(int a, int b):Honey(a){
        setSource(b);
    }
    void setSource(int a){
        source=a;
    }
    string getSource(){
        switch(source){
            case 1 : return "ChiangRai";
            case 2 : return "ChumPon";
            case 3 : return "SongKla";
            case 4 : return "SriSaKet";
        }
    }
    string getInfo(){
        switch(source){
            case 1 : return "ChiangRai";
            case 2 : return "ChumPon";
            case 3 : return "SongKla";
            case 4 : return "SriSaKet";
        }
    }
    string operator ++ (){
        return getInfo();
    }
};

class FarmedHoney:public Honey{
    int type;
    public :
    FarmedHoney(){
        setType(1);
    }
    FarmedHoney(int a, int b):Honey(a){
        setType(b);
    }
    void setType(int a){
        type=a;
    }
    string getType(){
        switch(type){
            case 1 : return "Ramyai";
            case 2 : return "Linjee";
            case 3 : return "Sadao";
        }
    }
    string getInfo(){
        switch(type){
            case 1 : return "Lamyai";
            case 2 : return "Linjee";
            case 3 : return "Sadao";
        }
    }
    string operator ++(){
        return getInfo();
    }
};

class TeaJuice:public Tea, public Juice{
    Honey *honey;
    public :
    TeaJuice(){
        honey=0;
    }
    TeaJuice(double a, bool b, int c, int d, int e, Honey &f):Tea(a,b,c,d){
        setName(e);
        setHoney(f);
    }
    ~TeaJuice(){
        cout << "delete TeaJuice  ";
        cout << honey->getInfo() << "  grade : " << honey->getGrade() << endl;
    }
    void setHoney(Honey &a){
        honey=&a;
    }
    void set(Honey *a){
        honey=a;
    }
    void set(int a){
        honey->setGrade(a);
    }
    void set(FarmedHoney *a){
        honey=a;
    }
    void set(WildHoney *a){
        honey=a;
    }
    Honey* getHoney(){
        return honey;
    }
    double reducePrice(){
        setPrice(getPrice()-4);
        return getPrice();
    }
    void show(){
        cout << "---TeaJuice---" << endl;
        cout << "Name juice : " << getName() << endl;
        Tea::show();
    }
    bool checkHoney(string s){
        if(honey->getInfo()==s){
            return true;
        }else{
            return false;
        }
    }
};

class Discount{
    int code;
    double value;
    public :
    Discount(){
        setCode(1);
        setValue(50);
    }
    void setCode(int a){
        code=a;
    }
    void setValue(double a){
        value=a;
    }
    int getCode(){
        return code;
    }
    double getValue(){
        return value;
    }
};

class Order{
    string orderName;
    ColdDrink **coldDrink;
    int num;
    Discount *discount;
    public :
    Order(){
        setOrdername("PP");
        coldDrink=0;
        num=0;
        discount=0;
    }
    Order(Order &a){
        setOrdername(a.orderName);
        setDiscount(a.discount);
        if(a.coldDrink==coldDrink){
            return;
        }
        setNum(a.num);
        for(int i=0;i<a.num;i++){
            coldDrink[i]=a.coldDrink[i];
        }
    }
    ~Order(){
        delete[] coldDrink;
    }
    void setOrdername(string a){
        orderName=a;
    }
    void setNum(int a){
        if(a<0){return;}
        delete[] coldDrink;
        coldDrink=new ColdDrink*[a];
        num=a;
    }
    void setColdDrink(int a,ColdDrink* b){
        coldDrink[a]=b;
    }
    void setDiscount(Discount* a){
        discount=a;
    }
    string getOrdername(){
        return orderName;
    }
    int getNum(){
        return num;
    }
    ColdDrink* getColddrink(int a){
        return coldDrink[a];
    }
    Discount getDiscount(){
        return *discount;
    }
    void show(){
        cout << "--- Order " << orderName << endl;
        cout << "Discount code : " << discount->getCode() << " value : " << discount->getValue() << endl;
        cout << "Teajuice  " << num << " ea." << endl;
        for(int i=0;i<num;i++){
            coldDrink[i]->show();
        }
    }
    double operator ! (){
        double total;
        for(int i=0;i<num;i++){
            total+=coldDrink[i]->getPrice();
        }
        return total-discount->getValue();
    }
    double getPrice(string orderName){
        if(getOrdername()==orderName){
            return !(*this);
        }else{
            return 0;
        }
    }
};



int main(){
    FarmedHoney lamyai;
    FarmedHoney lingee(2,2);
    FarmedHoney sadao(3,3);

    WildHoney *wildHoney=new WildHoney[3];
    wildHoney[0].setGrade(1);
    wildHoney[0].setSource(2);

    wildHoney[1].setGrade(2);
    wildHoney[1].setSource(3);

    wildHoney[2].setGrade(3);
    wildHoney[2].setSource(4);

    Honey *h=new Honey(2);

    Honey *honey[7];
    honey[0]=&lamyai;
    honey[1]=&lingee;
    honey[2]=&sadao;
    honey[3]=&wildHoney[0];
    honey[4]=&wildHoney[1];
    honey[5]=&wildHoney[2];
    honey[6]=h;
    for(int i=0;i<7;i++){
        cout << i+1 << honey[i]->getInfo() << " grade : " << honey[i]->getGrade() << endl;;
    }

    int nn=0;
    int ss=0;
    for(int i=0;i<7;i++){
        if(honey[i]->getGrade()==1){
            nn++;
        }
        if(honey[i]->getInfo()=="SongKla"){
            ss++;
        }
    }
    cout << "grade A = " << nn << " ea. From SongKla = " << ss << " ea." << endl;

    Tea tea1(60,true,2,1);
    Tea tea2(60,false,1,2);
    Juice juice1(70,true,1,1);
    Juice juice2(75,false,2,4);
    TeaJuice teaJuice1(80,true,1,3,3,*honey[0]);
    TeaJuice teaJuice2(85,true,2,1,2,*honey[6]);

    TeaJuice *teaJuice3=new TeaJuice();
    teaJuice3->setPrice(80);
    teaJuice3->setSmoothie(true);
    teaJuice3->ColdDrink::setType(2);
    teaJuice3->Tea::setType(2);
    teaJuice3->setName(6);
    teaJuice3->setHoney(*honey[1]);
    TeaJuice *teaJuice4=new TeaJuice(85,true,2,1,2,*honey[2]);
    TeaJuice *teaJuice5=new TeaJuice(85,false,2,2,5,*honey[3]);

    TeaJuice *teaJuice[5];
    teaJuice[0]=&teaJuice1;
    teaJuice[1]=&teaJuice2;
    teaJuice[2]=teaJuice3;
    teaJuice[3]=teaJuice4;
    teaJuice[4]=teaJuice5;
    for(int i=0;i<5;i++){
        cout << *teaJuice[i] << endl;
    }
    
    Discount discount[3];
    discount[0].setCode(1);
    discount[0].setValue(10);
    discount[1].setCode(2);
    discount[1].setValue(15);
    discount[2].setCode(3);
    discount[2].setValue(20);

    Order order1,order2,order3;
    order1.setOrdername("AA");
    order1.setNum(2);
    order1.setColdDrink(0,&tea1);
    order1.setColdDrink(1,&juice2);

    order2.setOrdername("BB");
    order2.setDiscount(&discount[0]);
    order2.setNum(4);
    order2.setColdDrink(0,&juice1);
    order2.setColdDrink(1,&tea2);
    order2.setColdDrink(2,teaJuice[3]);
    order2.setColdDrink(3,teaJuice3);

    order3.setOrdername("CC");
    order3.setDiscount(&discount[2]);
    order3.setNum(4);
    order3.setColdDrink(0,&juice1);
    order3.setColdDrink(1,&juice2);
    order3.setColdDrink(2,teaJuice[3]);
    order3.setColdDrink(3,teaJuice3);
    order1.show();
    order2.show();
    order3.show();

    Order *copyOrder3=new Order(order3);
    copyOrder3->show();
    copyOrder3->setColdDrink(0,teaJuice[1]);
    copyOrder3->setColdDrink(1,teaJuice[2]);
    copyOrder3->setDiscount(&discount[1]);
    copyOrder3->show();

    Order *todayOrder[4];
    todayOrder[0]=&order1;
    todayOrder[1]=&order2;
    todayOrder[2]=&order3;
    todayOrder[3]=copyOrder3;

    double sum;
    for(int i=0;i<4;i++){
        sum+=!todayOrder[i];
    }
    cout << "total price of 4 todayOrder = " << sum << endl;

    double dis;
    for(int i=0;i<4;i++){
        dis+=order3.getColddrink(i)->reducePrice();
    }
    cout << "reduce total = " << dis << " baht and Discount : " << order3.getDiscount().getValue() << " baht" << endl;
    
    TeaJuice overload;
    overload.set(honey[1]);
    overload.show();
    overload.set(1);
    overload.show();
    overload.set(&lamyai);
    overload.show();
    overload.set(&wildHoney[1]);
    overload.show();

    delete copyOrder3;
    delete teaJuice3;
    delete teaJuice4;
    delete teaJuice5;
    delete h;
    delete[] wildHoney;
}