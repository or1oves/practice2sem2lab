#include <iostream>
#include <chrono>
#include <ctime>
#include <limits>
using namespace std;
using namespace chrono;

void menu() {
    cout << "0) exit program\n" <<
            "1) fill out de list\n" <<
            "2) actions with de list\n" <<
            "3) show de list\n" <<
            "4) fill out de array\n" <<
            "5) action with de array\n" <<
            "6) show de array\n" <<
            "7) time\n";
}

void menu2() {
    cout << "1) insert de element\n" <<
            "2) delete de element (index)\n" <<
            "3) delete de element (value)\n" <<
            "4) swap de element\n" <<
            "5) show de element (index)\n" <<
            "6) show de element (value)\n" <<
            "7) IDZ\n";
}



void clearStream() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.sync();
}

int inputInt(){
    int number;
    while(!(cin >> number)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "wrong input! \n";
    }
    return number;
}

int inputRandomInt(){
    return rand()%100;
}

struct Node {   //узел (звено) списка
    int data;
    Node *  prev;
    Node *  next;
    Node(int x) : data(x), prev(nullptr), next(nullptr) {}
};

struct List {
    Node * head;
    Node * tail;

    void createList(){
        head = nullptr;
        tail = nullptr;
    }


    void addHead(int x){
        Node *temp = new Node(x);
        temp->next = head;
        if(head != nullptr){
            head->prev = temp;
        }
        if(tail == nullptr){
            tail = temp;
        }
        head = temp;
    }

    void addTail(int x){
        Node *temp = new Node(x);
        temp->prev = tail;
        if(tail != nullptr){
            tail->next = temp;
        }
        if(head == nullptr){
            head = temp;
        }
        tail = temp;
    }

    void moveHead(){
        if(head == nullptr)
            return;
        Node *temp = head->next;
        if(temp != nullptr){
            temp->prev = nullptr;
        }
        else{
            tail = nullptr;
        }
        delete head;
        head = temp;
    }

    void moveTail(){
        if(tail == nullptr)
            return;
        Node *temp = tail->next;
        if(temp != nullptr){
            temp->next = nullptr;
        }
        else{
            head = nullptr;
        }
        delete tail;
        tail = temp;
    }

    void clearList(){
        while(head != nullptr){
            moveTail();
        }
    }

    void randList(int &len){
        for(int i = 0; i < len; i++){
            addTail(inputRandomInt());
        }
    }

    Node *getId(int id){
        Node *temp = head;
        int a = 0;
        while(a != id && temp != nullptr){
            temp = temp->next;
            a++;
        }
        if(temp == nullptr) // элементов нет
            return nullptr;
        else
            return temp;
    }

    int getValue(int value){
        int id = 0;
        for(Node *temp = head; temp != nullptr; temp = temp->next){
            if(temp->data == value){
                return id;
            }
            id++;
        }
        return -1; // если нет нужного числа
    }

    void Insert(int id, int x){
        Node *Ins = getId(id);
        if(Ins == nullptr){
            addTail(x);
            return;
        }
        Node *prevIns = Ins->prev;
        if(prevIns == nullptr){
            addHead(x);
            return;
        }
        Node *temp = new Node(x);
        temp->prev = prevIns;
        temp->next = Ins;
        prevIns->next = temp;
        Ins->prev = temp;
    }

    void deleteByValue(int value){
        Node *temp = head;
        if(temp == nullptr){
            cout << "there is no such element";
            return;
        }
        while(temp){ //проходимся по элементам
            if(temp->data == value){
                break;
            }
            temp = temp->next;
        }
        if(temp->prev == nullptr){
            moveHead(); //если нужно удалить первый элемент
            return;
        }
        if(temp->next == nullptr){
            moveTail(); //если нужно удалить последний элемент
            return;
        }
        else {
            Node *prevDel = temp->prev;
            Node *Del = temp->next;
            prevDel->next = Del; //если удаляем не head
            Del->prev = prevDel; //если удаляем не tail
        }
        delete temp;
    }

    void deleteByIndex(int index){
        Node *temp = getId(index);
        if(temp == nullptr){
            cout << "there is no such element";
            return;
        }
        if(temp->prev == nullptr){
            moveHead(); //если нужно удалить первый элемент
            return;
        }
        if(temp->next == nullptr){
            moveTail(); //если нужно удалить последний элемент
            return;
        }
        else {
            Node *prevDel = temp->prev;
            Node *Del = temp->next;
            prevDel->next = Del; //если удаляем не head
            Del->prev = prevDel; //если удаляем не tail}
        }
        delete temp;
    }

    void print(){
        for(Node *temp = head; temp != nullptr; temp = temp->next){
            cout << temp->data << " ";
        }
        cout << '\n';
    }

    void inputList(){
        int number;
        while(cin >> number){
            addTail(number);
            if(cin.peek() == '\n'){
                break;
            }
        }
        clearStream();
    }


    void swapInList(int index, int index2){
        Node *temp = getId(index);
        Node *temp2 = getId(index2);
        Node *prevElement = getId(index - 1);
        Node *prevElement2 = getId(index2 - 1);
        Node *Element = getId(index + 1);
        Node *Element2 = getId(index2 + 1);
        if(temp == nullptr){
            return;
        }
        if(temp2 == nullptr){
            return;
        }
        if(index == index2){
            return;
        }
        if(prevElement == nullptr){
            head = temp2;
        }
        else{
            prevElement->next = temp2;
        }
        if(prevElement2 == nullptr){
            head = temp;
        }
        else{
            prevElement2->next = temp;
        }
        if(Element == nullptr){
            tail = temp2;
        }
        else{
            Element->prev = temp2;
        }
        if(Element2 == nullptr){
            tail = temp;
        }
        else{
            Element2->prev = temp;
        }
        Node *temp3 = temp->next;
        temp->next = temp2->next;
        temp2->next = temp3;
        temp3 = temp->prev;
        temp->prev = temp2->prev;
        temp2->prev = temp3;
    }

    int countInList(){
        int count = 0;
        for(Node *temp = head; temp != nullptr; temp = temp->next){
            count++;
        }
        return count;
    }

    void shakerInList(int &countOfElements){
        int startShake = 0;
        int endShake = countOfElements - 1;
        bool isSwapped = true;
        while(isSwapped){
            isSwapped = false;
            for(int i = startShake; i < endShake; ++i){
                if(getId(i) -> data > getId(i + 1) -> data){
                    swapInList(i, i + 1);
                    isSwapped = true;
                }
            }
            if(!isSwapped){
                break;
            }
            isSwapped = false;
            --endShake;
            for(int i = endShake - 1; i >= startShake; --i){
                if(getId(i) -> data > getId(i + 1) -> data){
                    swapInList(i, i + 1);
                    isSwapped = true;
                }
            }
            ++startShake;
        }
    }

};

struct spendTime{
    long unsigned int createTime = 0; // шоб без е было
    long unsigned int inputTime = 0;
    unsigned int insertTime = 0;
    unsigned int deleteByIdTime = 0;
    unsigned int deleteByValueTime = 0;
    unsigned int getIdTime = 0;
    unsigned int getValueTime = 0;
    unsigned int idzTime = 0;

    void timeMenu(){
        cout << "\ncreate time: " << createTime <<
             "\nfill time: " << inputTime <<
             "\ninsert time: " << insertTime <<
             "\ndelete by index time: " << deleteByIdTime <<
             "\ndelete by value time: " << deleteByValueTime <<
             "\ngetting by id time: " << getIdTime <<
             "\ngetting by value time: " << getValueTime <<
             "\nIDZ time: " << idzTime <<
             "\n";
    }
};

void randomArray(int &SIZE, int* &arr){ //массивчики
    int *ind = new int[SIZE];
    for(int i = 0; i < SIZE; i++){
        *(ind + i) = inputRandomInt();
    }
    delete[] arr;
    arr = ind;
}

void clearArray(int &SIZE, int* &arr){
    SIZE = 0;
    int *ind = new int[0];
    delete[] arr;
    arr = ind;
}

void showArray(int &SIZE, int* &arr){
    for(int i = 0; i < SIZE; i++){
        cout << arr[i] << " ";
    }
    cout << '\n';
}

void inputToArray(int &SIZE, int* &arr, int &id, int &value){
    int *ind = new int[SIZE + 1];
    if(id > SIZE || id < 0){
        return;
    }
    for(int i = 0; i < SIZE; i++){
        ind[i] = arr[i];
    }
    ind[id] = value;
    for(int i = 0; i < SIZE; i++){
        ind[i + 1] = arr[i];
    }
    SIZE++;
    delete [] arr;
    arr = ind;
}

void inputArray(int &SIZE, int* &arr, int &value){
    while(cin >> value){
        int *ind = new int[SIZE + 1];
        for(int i = 0; i < SIZE; i++){
            ind[i] = arr[i];
        }
        ind[SIZE] = value;
        SIZE++;
        delete [] arr;
        arr = ind;
    }
    clearStream();
}


void deleteByIndexArray(int &SIZE, int* &arr, int &id){
    int *ind = new int[SIZE - 1];
    int a = 0;
    for(int i = 0; i < SIZE; i++){
        if(i != id){
            *(ind + a) = *(arr + i);
            a++;
        }
    }
    if(a < SIZE){
        SIZE--;
        delete [] arr;
        arr = ind;
    }
    else{
        cout << "no elements found\n";
    }
}

void deleteByValueArray(int &SIZE, int* &arr, int &value){
    int *ind = new int[SIZE - 1];
    int a = 0;
    for(int i = 0; i < SIZE; i++){
        if(*(arr + i) != value){
            *(ind + a) = *(arr + i);
            a++;
        }
    }
    if(a < SIZE){
        SIZE--;
        delete [] arr;
        arr = ind;
    }
    else{
        cout << "no elements found\n";
    }
}

void getValueArray(int &SIZE, int* &arr, int &value){
    for(int i = 0; i < SIZE; i++){
        if(*(arr + i) == value){
            cout << "index: " << i << '\n';
            return;
        }
    }
    cout << "no elements found";
}


void swapArray(int &SIZE, int* &arr, int index, int index2){
    if(index < 0 || index2 < 0){
        return;
    }
    if(index >= SIZE || index2 >= SIZE){
        return;
    }
    swap(*(index + arr), *(index2 + arr));
}

void shakerInArray(int* &arr, int &SIZE){
    int startShake = 0;
    int endShake = SIZE - 1;
    bool isSwapped = true;
    while(isSwapped){
        isSwapped = false;
        for(int i = startShake; i < endShake; ++i){
            if(arr[i] > arr[i + 1]){
                swap(arr[i], arr[i + 1]);
                isSwapped = true;
            }
        }
        if(!isSwapped){
            break;
        }
        isSwapped = false;
        --endShake;
        for(int i = endShake - 1; i >= startShake; --i){
            if(arr[i] > arr[i + 1]){
                swap(arr[i], arr[i + 1]);
                isSwapped = true;
            }
        }
        ++startShake;
    }
}

int main(){
    srand(time(nullptr)); // NULL
    time_point<steady_clock, duration<__int64_t, ratio<1, 1000000000>>> start, end;
    nanoseconds result;
    spendTime listTime, arrayTime;
    int task, id, value, count;
    int SIZE = 0;
    int *arr = new int [SIZE];
    List list;
    list.createList();
    while(true){
        menu();
        cout << "enter task: ";
        cin >> task;
        switch(task){

            case 1:
                cout << "1) random list\n" <<
                        "2) own list\n";
                cin >> task;
                if(task == 1){
                    list.clearList();
                    int len = 0;
                    cout << "enter length of list: ";
                    cin >> len;
                    clearStream();
                    start = steady_clock::now();
                    list.randList(len);
                    end = steady_clock::now();
                    result = duration_cast<nanoseconds>(end - start);
                    listTime.createTime = result.count();
                    list.print();
                }
                if(task == 2){
                    list.clearList();
                    cout << "enter de list: ";
                    start = steady_clock::now();
                    list.inputList();
                    end = steady_clock::now();
                    result = duration_cast<nanoseconds>(end - start);
                    listTime.inputTime = result.count();
                    list.print();
                }
                break;

            case 2:
                menu2();
                cout << "enter task: ";
                cin >> task;
                switch(task) {

                    case 1:
                        cout << "enter id: ";
                        cin >> id;
                        cout << "enter value: ";
                        cin >> value;
                        start = steady_clock::now();
                        list.Insert(id, value);
                        end = steady_clock::now();
                        result = duration_cast<nanoseconds>(end - start);
                        listTime.insertTime = result.count();
                        list.print();
                        break;

                    case 2:
                        cout << "enter id: ";
                        cin >> id;
                        start = steady_clock::now();
                        list.deleteByIndex(id);
                        end = steady_clock::now();
                        result = duration_cast<nanoseconds>(end - start);
                        listTime.deleteByIdTime = result.count();
                        list.print();
                        break;

                    case 3:
                        cout << "enter value: ";
                        cin >> value;
                        start = steady_clock::now();
                        list.deleteByValue(value);
                        end = steady_clock::now();
                        result = duration_cast<nanoseconds>(end - start);
                        listTime.deleteByValueTime = result.count();
                        list.print();
                        break;

                    case 4:
                        cout << "first index: ";
                        cin >> id;
                        cout << "second index: ";
                        cin >> value;
                        list.swapInList(id, value);
                        list.print();
                        break;

                    case 5:
                        Node *value2;
                        cout << "enter id: ";
                        cin >> id;
                        start = steady_clock::now();
                        value2 = list.getId(id);
                        end = steady_clock::now();
                        result = duration_cast<nanoseconds>(end - start);
                        if(value2 != nullptr){
                            cout << value2->data << '\n';
                            listTime.getIdTime = result.count();
                        }
                        else{
                            cout << "wrong id";
                        }
                        break;

                    case 6:
                        cout << "enter value: ";
                        cin >> value;
                        start = steady_clock::now();
                        id = list.getValue(value);
                        end = steady_clock::now();
                        if(id == -1){
                            cout << "no value\n";
                        }
                        else{
                            cout << "id: " << id << '\n';
                            result = duration_cast<nanoseconds>(end - start);
                            listTime.getValueTime = result.count();
                        }
                        break;

                    case 7:
                        count = list.countInList();
                        start = steady_clock::now();
                        list.shakerInList(count);
                        end = steady_clock::now();
                        result = duration_cast<nanoseconds>(end - start);
                        listTime.idzTime = result.count();
                        list.print();
                        break;

                    default:
                        cout << "wrong task!\n";
                        break;
                }
                break;

            case 3:
                list.print();
                break;

            case 4:
                clearArray(SIZE, arr);
                cout << "1) random array\n" <<
                     "2) own array\n";
                cin >> task;
                if(task == 1){
                    cout << "enter size of array: ";
                    cin >> SIZE;
                    clearStream();
                    start = steady_clock::now();
                    randomArray(SIZE, arr);
                    end = steady_clock::now();
                    result = duration_cast<nanoseconds>(end - start);
                    showArray(SIZE, arr);
                    arrayTime.createTime = result.count();
                }
                if(task == 2){
                    cout << "enter array: ";
                    start = steady_clock::now();
                    inputArray(SIZE, arr, value);
                    end = steady_clock::now();
                    result = duration_cast<nanoseconds>(end - start);
                    arrayTime.inputTime = result.count();
                }
                break;

            case 5:
                menu2();
                cout << "enter task: ";
                cin >> task;
                switch(task){

                    case 1:
                        cout << "enter id: ";
                        cin >> id;
                        cout << "enter value: ";
                        cin >> value;
                        start = steady_clock::now();
                        inputToArray(SIZE, arr, id, value);
                        end = steady_clock::now();
                        result = duration_cast<nanoseconds>(end - start);
                        arrayTime.insertTime = result.count();
                        showArray(SIZE, arr);
                        break;

                    case 2:
                        cout << "enter id: ";
                        cin >> id;
                        start = steady_clock::now();
                        deleteByIndexArray(SIZE, arr, id);
                        end = steady_clock::now();
                        result = duration_cast<nanoseconds>(end - start);
                        arrayTime.deleteByIdTime = result.count();
                        showArray(SIZE, arr);
                        break;

                    case 3:
                        if(SIZE == 0){
                            cout << "array is empty\n";
                            break;
                        }
                        cout << "enter value: ";
                        cin >> value;
                        start = steady_clock::now();
                        deleteByValueArray(SIZE, arr,value);
                        end = steady_clock::now();
                        result = duration_cast<nanoseconds>(end - start);
                        arrayTime.deleteByValueTime = result.count();
                        showArray(SIZE, arr);
                        break;

                    case 4:
                        cout << "enter first index: ";
                        cin >> id;
                        cout << "enter second index: ";
                        cin >> value;
                        swapArray(SIZE, arr, id, value);
                        break;

                    case 5:
                        cout << "enter id: ";
                        cin >> id;
                        if(id >= SIZE || id < 0){
                            cout << "\nwrond id!\n";
                        }
                        else{
                            start = steady_clock::now();
                            value = arr[id];
                            end = steady_clock::now();
                            cout << "number: " << value << '\n';
                            result = duration_cast<nanoseconds>(end - start);
                            arrayTime.getIdTime = result.count();
                        }
                        break;

                    case 6:
                        cout << "enter value: ";
                        cin >> value;
                        start = steady_clock::now();
                        getValueArray(SIZE, arr,value);
                        end = steady_clock::now();
                        result = duration_cast<nanoseconds>(end - start);
                        arrayTime.getValueTime = result.count();
                        break;

                    case 7:
                        start = steady_clock::now();
                        shakerInArray(arr, SIZE);
                        end = steady_clock::now();
                        result = duration_cast<nanoseconds>(end - start);
                        arrayTime.idzTime = result.count();
                        showArray(SIZE, arr);
                        break;

                    default:
                        cout << "wrong task!\n";
                        break;
                }

            case 6:
                showArray(SIZE, arr);
                break;

            case 7:
                cout << "list: ";
                listTime.timeMenu();
                cout << "array: ";
                arrayTime.timeMenu();
                break;

            case 0:
                list.clearList();
                delete [] arr;
                arr = nullptr;
                exit(0);

            default:
                cout << "wrong task!";
                break;
        }
    }
}