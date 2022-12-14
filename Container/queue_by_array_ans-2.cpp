#include <iostream>
#include <string>


template <class T>
class Queue{
private:
    // array 기반이기 때문에 linked-list에 비해 value에 대한 접근, push, pop 모두 더 작은 오버헤드로 push pop을 할 수 있습니다.
    T *node;
    // front, rear의 index를 나타냅니다.
    int FR, RE;
    // size는 현재 queue에 들어있는 원소 수입니다.
    int _size;
    // capacity는 queue에 할당된 메모리의 크기입니다.
    int capacity;

    // MEMORY_BORDER는 class Queue에 종속적인 resize_half의 border line입니다.
    // program과 processor에 따라 이 border line은 달라질 수 있습니다.
    // 기준은 border line 보다 메모리가 작을 때도 resize_half를 하면 오버헤드가 커지는 것과, boreder line 아래로 내려가서 쓰이지 않는 메모리 누수로 인한 불이익을, 시간적인 측면과 공간적인 측면에서 종합적으로 고려한 평균적인 profit 지점입니다.
    static const int MEMORY_BORDER = 1024;

    // resize_double은 capacity가 부족할 때, capacity를 두 배로 늘리는 함수입니다.
    // resize_half는 메모리 누수를 방지하기 위해 MEMORY_BORDER까지는 쓰지 않는 영역이 쓰는 영역보다 많을 경우 capacity를 1/2하는 함수입니다. 
    // 매 pop push 연산마다 allocation and free를 해야 하는 linked_list 대비 이 부분에 대한 오버헤드가 훨씬 적으면서 메모리 누수는 방지할 수 있는 array 기반의 핵심적 함수입니다.
    void resize(int sz);
    void resize_double();
    void resize_half();

public:
    // queue의 생성자와 소멸자입니다.
    Queue();
    ~Queue();
    // empty 함수는 비어 있으면 true, else false를 return합니다.
    bool empty();
    // size 함수는 들어 있는 자료의 개수를 리턴합니다.
    int size();
    // push 함수는 value를 queue에 push하는 함수입니다.
    // rear index만 옮기면 되어 linked-list 대비 효율적입니다.
    void push(T val);
    // pop 함수는 front()에 있는 value를 return하고, queue에서 빼내는 함수입니다.
    // front index만 옮기면 되어 linked-list 대비 효율적입니다.
    T pop();
    // front 또한
    T front();
    T back();
    // clear 연산도 한번에 연속적인 배열을 해제할 수 있는 array와 달리, linked list는 비효율적입니다.
    void clear();

////////////////////////////////////
    // fuction for debug

    // 디버그를 위한 print 함수입니다.
    // void print();    
    void print_values();
    // void print_container();

    // 디버그를 위한 capacity return 함수입니다.
    int return_capacity(){
       return capacity; 
    }
};


template <class T>
Queue<T>::Queue(){
    _size = FR = RE = 0;
    capacity = 32;
    node = new T[capacity];
}
template <class T>
Queue<T>::~Queue(){
    delete[] node;
}

template <class T>
bool Queue<T>::empty(){
    return FR == RE;
}
template <class T>
int Queue<T>::size(){
    return _size;
}
template <class T>
void Queue<T>::clear(){
    delete[] node;
    _size = 0, capacity = 32;
    node = new T[capacity];
}

template <class T>
void Queue<T>::resize(int cp){
    T *tmp;
    tmp = new T[cp];
    register int idx =0;
    if(FR<RE){
        for(register int i=FR;i<RE;++i)
            tmp[idx++]=node[i];
    }
    else if(FR>=RE){
        for(register int i=FR;i<capacity;++i)
            tmp[idx++]=node[i];
        for(register int i=0;i<RE;++i)
            tmp[idx++]=node[i];
    }
    node = tmp;
    FR = 0;
    _size = RE = idx;
    capacity = cp;
}
template <class T>
void Queue<T>::resize_double(){
    resize(capacity*2);
}
template <class T>
void Queue<T>::resize_half(){
    resize(capacity/2);
}
template <class T>
void Queue<T>::push(T val){
    // exponential해서 드문 연산이기에, 따라서 이 함수는 평균적으로 O(1), constant amortized time입니다.
    if (_size == capacity){
        resize_double();
    }
    node[RE++]=val;
    RE = RE>=capacity ? 0 : RE;
    ++_size;
}

template <class T>
T Queue<T>::pop(){
    // exponential해서 드문 연산이기에, 따라서 이 함수는 평균적으로 O(1), constant amortized time입니다.
    // 메모리 누수를 방지합니다.
    if(capacity > MEMORY_BORDER && _size*2 < capacity){
        resize_half();
    }
    if(empty())throw std::out_of_range("empty queue");
    T ret = node[FR++];
    FR = FR>=capacity ? 0 : FR;
    --_size;
    return ret;
}
template <class T>
T Queue<T>::front(){
    if(empty())throw std::out_of_range("empty queue");
    return node[FR];
}
template <class T>
T Queue<T>::back(){
    if(empty())throw std::out_of_range("empty queue");
    else return node[RE!=0 ? RE-1 : capacity-1];
}

template <class T>
void Queue<T>::print_values(){
    if(empty());
    else if(size()<10){
        if(FR<RE){
            for(int i=FR;i<RE;++i)
                std::cout<<node[i]<<' ';
        }
        else if(FR>=RE){
            for(int i=FR;i<capacity;++i)
                std::cout<<node[i]<<' ';
            for(int i=0;i<RE;++i)
                std::cout<<node[i]<<' ';
        }
    }else{
        int cnt = 0;
        if(FR<RE){
            for(int i=FR;i<RE;++i){
                std::cout<<node[i]<<' ';
                ++cnt;
                if(cnt>=10){
                    std::cout<<" ...";
                    break;
                }
            }
        }
        else if(FR>=RE){
            for(int i=FR;i<capacity;++i){
                std::cout<<node[i]<<' ';
                ++cnt;
                if(cnt>=10){
                    std::cout<<" ...";
                    break;
                }
            }
            for(int i=0;i<RE;++i){
                std::cout<<node[i]<<' ';
                ++cnt;
                if(cnt>=10){
                    std::cout<<" ...";
                    break;
                }
            }
        }
    }
    std::cout<<'\n';
}

int main(){
    // template로 queue를 정의했기에, using으로 Queue<C>에서 C에 정의하는 class만 int에서 바꾸면 float, double, 심지어 std::string이 가능합니다.
    // 이 코드에서는 std::string을 Queue에 들어가는 원소의 종류로 사용했습니다.
    using C = std::string;
    Queue<C> qu;
    /*
public:
    Queue();
    ~Queue();
    bool empty();
    int size();
    void push(T val);
    T pop();
    T front();
    T back();
    void clear();
    void print_values();
    int return_capacity()
    */

    // while문을 돌면서 기본적으로 함수명에 대한 command를 받고, 필요하다면 후속 값도 받는 형식입니다.
    // push_zeros는 C의 매개변수가 없을 때의 생성자를 이후 입력한 값의 횟수만큼 queue에 넣는 command입니다.
    // pop_cnt는 이후 입력한 값의 횟수만큼 pop 연산을 해서 queue에서 자료를 반복적으로 빼는 command입니다.

    // size와 capacity의 변화를 추적하며, 메모리 누수가 방지됨을 확인할 수 있습니다.
    while(true){
        std::string cmd;
        std::cin>>cmd;
        if(cmd == "push"){
            C x;std::cin>>x;
            qu.push(x);
        }else if(cmd == "pop"){
            std::cout<<qu.pop()<<'\n';
        }else if(cmd == "empty"){
            std::cout<<qu.empty()<<'\n';
        }
        else if(cmd == "size"){
            std::cout<<qu.size()<<'\n';
        }else if(cmd=="front"){
            std::cout<<qu.front()<<'\n';
        }else if(cmd=="back"){
            std::cout<<qu.back()<<'\n';
        }else if(cmd=="clear"){
            qu.clear();
        }else if(cmd=="push_zeros"){
            int times;std::cin>>times;
            for(int i=0;i<times;++i){
                qu.push(C());
            }
        }else if(cmd=="pop_cnt"){
            int times;std::cin>>times;
            for(int i=0;i<times;++i){
                qu.pop();
            }
        }
        std::cout<<"Queue status: ";
        qu.print_values();
        std::cout<<"size: "<<qu.size()<<", capacity: "<<qu.return_capacity()<<"\n\n";
    }
    return 0;
}