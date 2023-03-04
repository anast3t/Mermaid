#include <iostream>
#include <vector>
using namespace std;

template<class T> class Output;

template<class T> class Input {
    private:
        Output<T> *emmiter;
    public:
        void acceptInput(T data){
            cout<<"Input got data " << this << endl;
        }
    protected:
        void setEmmiter(Output<T> *output){
            emmiter = output;
            cout<<"Emmiter set in Input" << endl;
        }
};

template<class T> class Output {
    private:
        Input<T> *reciever;

    public:
        void send(T data){
            cout<<"Output sent data " << this << endl;
            reciever->acceptInput(data);
        }

    protected:
        void setReciever(Input<T> *input){
            reciever = input;
            cout<<"Reciever set in Output" << endl;
        }
};

template<class DataType> class IOPair: public Output<DataType>, protected Input<DataType> {
    private:
    protected: 
        void bind(IOPair<DataType> *newPair){
            this->setReciever(newPair);
            this->setEmmiter(newPair);
            cout<<"RE set "<< this << endl;
        }
    public:
        static void bind(IOPair<DataType> *pair1, IOPair<DataType> *pair2){
            cout<<"--Starting binding " << endl;
            pair1->bind(pair2);
            pair2->bind(pair1);
            cout<<"--IOPair set" << endl;
        }
};

class Data{
    public:
        int datapack;
};

class DNode {
    public: 
        IOPair<Data> master;
        virtual void pairMaster(DNode &master) = 0;
};

class Master : public DNode{
    public:
        void pairMaster(Master &master){
            cout << "set master in Master, going in slave mode";
        }
};

class Slave : public DNode {
    public:
        void pairMaster(Master &master){
            cout << "set master in Slave";
        }

};

class Carrier : public DNode{
    public:
        void pairMaster(Slave &master){
            cout << "set master in Carrier";
        }
};

int main() {
    // std::cout << "Hello World!" << endl;
    // IOPair<int> pair1, pair2;
    // IOPair<int>::bind(&pair1, &pair2);
    // pair1.send(1);

    Slave slave;
    Carrier carrier;
    Master master;
    Master master2;

    carrier.pairMaster(slave);
    slave.pairMaster(master);
    master.pairMaster(master2);


    return 0;
}