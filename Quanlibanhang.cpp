
#include<iostream>
#include<string>
#include<fstream>
#include<map>
using namespace std;
const int N = 100000;
map<int, int> mp;


//Hàm cập nhập câp nhật vào linklist
//Từ linklist câpj nhật lại vào bảng
//MÃ CODE ĐƯỢC QUY ĐỊNH LÀ XXXX

struct Product{
    int code;
    string name;
    float price;
    int number;
};
template<class T>
struct Prd{
    T s;
    Prd *next;
};


template <class T>
int getCode(Product a) {
    return a.code;
}
template <class T>
string getName(Product a) {
    return a.name;
}
template <class T>
float getPrice(Product a) {
    return a.price;
}

float getNumber(Product a) {
    return a.number;
}

typedef struct Prd<Product>* prd;

int updateProduct(prd &a, char product[]) {
    ifstream prds(product);
    if (!prds.is_open()) {
        return 1; 
    } else {
        char ignore[N];
        prds.getline(ignore, N);
        prds.getline(ignore, N);
        while (prds.getline(ignore, N, '|')) {
            Product s;
            prds >> s.code;
            prds.ignore(); 
            getline(prds, s.name, '|');
            prds >> s.price;
            prds.ignore(); 
            prds >> s.number;
            prds.ignore(); 


            prd newNode = new Prd<Product>();
            newNode->s = s;
            newNode->next = nullptr;
            if (a == nullptr) {
                a = newNode;
            } else {
                prd temp = a;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
        }
        prds.close();
    }
    return 0; 
}
template <class T>
prd makeNode() {
    T s;
    cout << "Nhập thông tin sản phẩm: " << endl;
    cout << "Nhập mã sản phẩm: " << endl; cin >> s.code;
    cin.ignore();
    cout << "Nhập tên sản phẩm: " << endl; getline(cin, s.name);
    cout << "Nhập giá sản phẩm: " << endl; cin >> s.price;
    cout << "Nhập số lượng sản phẩm: " << endl; cin >> s.number;
    prd tmp = new Prd<Product>();
    tmp->s = s;
    tmp->next = NULL;
    return tmp;
}

bool empty(prd a) {
    return a == NULL;
}

int Size(prd a) {
    int cnt = 0;
    while(a != NULL) {
        a = a->next;
        cnt++;
    }
    return cnt;
}
template<class T>
void insertFirst(prd &a) {
    prd tmp = makeNode();
    if(a == NULL) {
        a = tmp;
    } else {
        tmp->next = a;
        a = tmp;
    }
}
template <class T>
void insertLast(prd &a) {
    prd tmp = makeNode<T>();
    if(a == NULL) {
        a = tmp;
    } else {
        prd p = a;
        while(p->next != NULL) {
            p = p->next;
        }
        p->next = tmp;
    }
}
template <class T>
void insertMiddle(prd &a, int pos) {
    int n = Size(a);
    if( pos <= 0 || pos > n + 1) {
        cout << "Vị trí cần chèn không hợp lệ!";
    }
    if( pos == 1 ) {
        insertFirst<T>(a);
    }
    else if (pos + 1 == n) {
        insertLast<T>(a);
    }
    else{ 
        prd tmp = makeNode<T>();
        prd p = a;
        for(int i = 0; i < pos; i++) {
            p = p->next;
        }
        tmp->next = p->next;
        p->next = tmp;
    }
}

void deleteFirst(prd &a){
    if(a == NULL) return;
    a = a->next;
}

void deleteLast(prd &a) {
    if(a == NULL) {
        return;
    } else {
        prd truoc = NULL, sau = a;
        while(sau->next != NULL) {
            truoc = sau;
            sau = sau->next;
        }
        if(truoc == NULL) {
            a = NULL;
        } else {
            truoc->next = NULL;
        }
    }
}
// pos nằm ở bảng product.txt
void deleteMiddle(prd &a, int pos) {
    if(pos <= 0 || pos > Size(a)) return;
    if(a == NULL) {
        return;
    }
    prd truoc = NULL, sau = a;
    for(int i = 0; i < pos; i++) {
        truoc = sau;
        sau = sau->next;
    }
    if(truoc == NULL) {
        a = NULL;
    } else {
        truoc = truoc->next;
    }
}

template <class T>
int updateBoard(char product[], prd a) { 
    ofstream prds(product);
    if(!prds.is_open()) {
        cout << "Không mở được bảng!";
        return 1;
    } else {
        prds << "THIẾT BỊ THÔNG MINH CÔNG TY TIẾN LUẬT CUTE PHÔ MAI QUE" << endl;
        prds << "STT | CODE | NAME | PRICE | NUMBER" << endl;
        prd p = a;
        int k = 1;
        while(p != NULL) {
            prds << k << "|" << getCode<T>(p->s) << "|" << getName<T>(p->s) << "|" << getPrice<T>(p->s) << "|" << getNumber<T>(p->s) << endl;
            k++;
            p = p->next;
        }
        prds.close();
    }
    return 0;
}
template <class T>
void in(T s) {
    int k = 1;
    cout << getCode(s) << "|" << getName(s) << "|" << getPrice(s) << "|" << getNumber(s) << endl;
}

template <class T>
void inds(prd a) {
    cout << "THIẾT BỊ THÔNG MINH CÔNG TY TIẾN LUẬT CUTE PHÔ MAI QUE" << endl;
    while(a != NULL) {
        in<T>(a->s);
        a = a->next;
    }
    cout << "....................THANK YOU...................";
}

void sortNumber(prd &a) {
    int n = Size(a);
    for(prd p = a; p->next != NULL; p = p->next) {
        prd min = p;
        for(prd k = p; k->next !=NULL; k = k->next) {
            if(getNumber(p->s) > getNumber(k->s)){
                min = k;
            }
        }
        Product tmp = min->s;
        min->s = p->s;
        p->s = tmp;
    }
}
template<class T>
void sortPrice(prd &a) {
    int n = Size(a);
    for(prd p = a; p->next != NULL; p = p->next) {
        prd min = p;
        for(prd k = p; k->next !=NULL; k = k->next) {
            if(p->s.price > k->s.price){
                min = k;
            }
        }
        T tmp = min->s;
        min->s = p->s;
        p->s = tmp;
    }
}

int updatesFreqToBoard(map<int, int> a, char Fre[]) {
    ofstream freq(Fre);
    if(!freq.is_open()){
        return 1;
    } else {
        cout << "SỐ LƯỢNG SẢN PHẨM ĐÃ BÁN" << endl;
        cout << "stt | Code | Numbers" << endl;
        int k = 1;
        for(auto it : a) {
            freq << k << it.first << "|" << it.second << endl;
            k++;
        }
    }
    freq.close();
    return 0;
}

int updatesFreqByBoard(map<int, int> a, char Fre[]) {
    ifstream freq(Fre);
    if(!freq.is_open()) {
        return 1;
    } else {
        int x, y;
        char ignore[N];
        freq.getline(ignore, N);
        freq.getline(ignore, N);
        while(!freq.eof()) {
            freq.getline(ignore, N, '|');
            freq >> x;
            freq.ignore();
            freq >> y;
            freq.ignore();
            a[x] = y;
        }
    }
    freq.close();
    return 0;
}

void buyProduct(map<int, int> a, prd &n){
    int Total = 0;
    while(1) { 
        cout << "1. Mua san pham" << endl;
        cout << "2. Thoat" << endl;
        cout << "-----------------------------" << endl;
        cout << "Chọn sự lựa chọn của bạn" << endl;
        int k; cin >> k;
        if(k == 1) {
            cout << "Nhập mã sản phẩm bạn muốn mua" << endl;
            int codeBought; cin >> codeBought;
            cout << "Nhập số lượng sản phẩm: " << endl;
            int numberBought; cin >> numberBought;
            for(prd p = n; p != NULL; p = p->next) {
                if(p->s.code == codeBought) {
                    p->s.number -= numberBought;
                    Total = Total + p->s.price*numberBought;
                    break;
                }
            }
            a[codeBought] += numberBought;
        }
        if(k == 2) {
            break;
        }
    }
    cout << "Số tiền bạn cần thanh toán là: " << Total << endl;
}
template<typename T>
prd Products = new Prd<T>();

template <class T>
void managerSelect(char product[], char frequency[]){
    while(1) {
        cout << "-----QUẢN LÝ------" << endl;
        cout << "1. Cap nhat san pham" << endl;
        cout << "2. Kiem tra san pham" << endl;
        cout << "3. Them một sản phẩm vào đầu" << endl;
        cout << "4. Thêm mot san pham vao cuoi" << endl;
        cout << "5. Them mot phan tu tai vi tri k" << endl;
        cout << "6. Xoa mot phan tu tai vi tri dau tien" << endl;
        cout << "7. Xoa mot phan tu tai vi tri cuoi" << endl;
        cout << "8. Xoa mot phan tu tai vi tri k" << endl;
        cout << "9. Xem tan suat ban hang" << endl;
        cout << "10. Cap nhat tan suat len bang" << endl;
        cout << "11. Cap nhat tan suat tu bang" << endl;
        cout << "12. So luong san pham" << endl;
        cout << "13. In Bang san pham" << endl;
        cout << "14. Cap nhat san pham len ban len bang" << endl;
        cout << "15. Ket thuc lua chon Quan li" << endl; 
        cout << "-----------------------00------------------" << endl;
        int k; 
        cout << "Nhap su lua chon cua ban" << endl; cin >> k;
        if(k == 1) {
            if(updateProduct(Products, product) == 1) {
                cout << "Update khong thanh cong" << endl;
            } else {
                cout << "Update thanh cong" << endl;
            }
        }
        else if(k == 2) {
            empty(Products);
        }
        else if(k == 3) {
            insertFirst<T>(Products);
        }
        else if(k == 4) {
            insertLast<T>(Products);
        }
        else if(k == 5) {
            int resInsert;
            cout << "Nhap vi tri k can them" << endl; cin >> resInsert;
            insertMiddle(Products, resInsert);
        }
        else if(k == 6) {
            deleteFirst(Products);
        }
        else if(k == 7) {
            deleteLast(Products);
        }
        else if(k == 8) {
            int resDelete;
            cout << "Nhap vi tri ban muon xoa" << endl; cin >> resDelete;
            deleteMiddle(Products, resDelete); 
        }
        else if(k == 12) {
            cout << "So luong san pham la" << Size(Products) << endl;
        }
        else if(k == 11) {
            updatesFreqByBoard(mp, frequency);
        }
        else if(k == 10) {
            updatesFreqToBoard(mp, frequency);
        } 
        else if(k == 13) {
            inds(Products);
        }
        else if(k == 14) {
            if(updateBoard(product, Products) == 1) {
                cout << "Updates khong thanh cong" << endl;
            } else { 
                cout << "Updates thanh cong" << endl;
            }
        }
        else if(k == 15) {
            break;
        }
    }
}
template<class T>
void customSelect(char product[], char frequency[]) {
    while(1) {
        cout << "----------KHACH HANG---------" << endl;
        cout << "1. In ra luong san pham" << endl;
        cout << "2. Mua san pham" << endl;
        cout << "3. Thoat" << endl;
        cout << "------------00---------------" << endl;
        cout << "Nhap lua chon cua ban" << endl;
        int customSelect; cin >> customSelect;
        if(customSelect == 1) {
            inds<T>(Products);
        }
        else if(customSelect == 2) {
            buyProduct(mp, Products);
        }
        else {
            break;
        }
    }
}


int main() {
    char product[] = "product.txt";
    char frequency[] = "frequency.txt";
    while(1) {
        cout << "CÔNG TY TRÁCH NHIỆM HỮU HẠN MỘT THÀNH VIÊN TIẾN LUẬT CUTE" << endl;
        cout << "--------------^/--------------" << endl;
        cout << "1. QUẢN LÝ" << endl;
        cout << "2. KHÁCH HÀNG" << endl;
        cout << "3. THOAT" << endl;
        cout << "-----------00----------" << endl;
        cout << "Nhập lựa chọn của bạn" << endl;
        int k; cin >> k;
        if(k == 1) {
            managerSelect<Product>(product, frequency);
        } 
        else if(k == 2) {
            customSelect<Product>(product, frequency);
        }
        else if(k == 3) {
            break;
        }
    }
    delete Products<Product>;
    return 0;
}



