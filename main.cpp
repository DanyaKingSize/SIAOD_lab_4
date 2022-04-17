#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

class Tree {
private:
    int size;
    int height;


    class Element {
    public:
        int data;
        Element *levo = nullptr;
        Element *pravo = nullptr;
    };

    Element *root;

    void _add(Element *branch, int value) {

        if (root == nullptr) {
            Element *temp = new Element;
            temp->data = value;
            root = temp;
            return;
        }
        if (value >= branch->data) {
            if (branch->pravo == nullptr) {
                Element *temp = new Element;
                temp->data = value;
                branch->pravo = temp;
            } else {
                _add(branch->pravo, value);
            }
        } else {
            if (branch->levo == nullptr) {
                Element *temp = new Element;
                temp->data = value;
                branch->levo = temp;
            } else {
                _add(branch->levo, value);
            }
        }

        size++;
    }

    void _pPrintTree(Element *branch) {
        if (branch == nullptr) return;
        cout << branch->data << " ";
        _pPrintTree(branch->levo);
        _pPrintTree(branch->pravo);

    }

    void _sPrintTree(Element *branch) {
        if (branch == nullptr) return;
        _sPrintTree(branch->levo);
        cout << branch->data << " ";
        _sPrintTree(branch->pravo);
    }

    void _oPrintTree(Element *branch) {
        if (branch == nullptr)   // Базовый случай
        {
            return;
        }
        _oPrintTree(branch->levo);   //рекурсивный вызов левого поддерева
        _oPrintTree(branch->pravo);  //рекурсивный вызов правого поддерева
        cout << branch->data << " ";
    }

    void _print(Element *branch, int space) {
        if (branch == nullptr) {
            return;
        }
        _print(branch->pravo, space + 1);

        for (int i = 0; i < space; ++i) {
            cout << "    ";
        }
        cout << branch->data << endl;

        _print(branch->levo, space + 1);
    }

    // какой тип????
    Element *_search(Element *branch, int value) { // Доделать
        if (branch == nullptr) return nullptr;
            height++;
        if (branch->data == value) {
            return branch;
        }
            //height++
        if (value >= branch->data) {
            return _search(branch->pravo, value);
        } else {
            return _search(branch->levo, value);
        }
    }

    Element *_min(Element *branch) {
        if (branch->levo == nullptr) {
            return branch;
        }
        return _min(branch->levo);

    }

    Element  *foundPapa(Element *branch) {
        Element *temp = root;
        Element *parent = nullptr;

        while (temp != branch) {
            parent = temp;
            if (temp->data > branch->data) {
                temp = temp->levo;
            } else {
                temp = temp->pravo;
            }
        }

        return parent;
    }


    void _delete(Element *branch) {
        if (branch->levo != nullptr && branch->pravo != nullptr) {

            Element *temp = _min(branch->pravo);
            branch->data = temp->data;
            _delete(temp);

        } else if (branch->levo == nullptr && branch->pravo == nullptr) {
            Element *temp = foundPapa(branch);
            if (branch->data >= temp->data) {
                temp->pravo = nullptr;
            } else {
                temp->levo = nullptr;

            }
            temp->data = branch->data;

            delete branch;
        } else if (branch->levo == nullptr && branch->pravo != nullptr) {
            Element *temp = foundPapa(branch);
            if (branch->data >= temp->data) {
                temp->pravo = branch->pravo;
            } else {
                temp->levo = branch->pravo;
            }
            delete branch;


        } else if (branch->levo != nullptr && branch->pravo == nullptr) {
            Element *temp = foundPapa(branch);
            if (branch->data >= temp->data) {
                temp->pravo = branch->levo;
            } else {
                temp->levo = branch->levo;
            }
            delete branch;
        }
    }

    void _destroy(Element *branch){
        if(branch== nullptr) return;
        _destroy(branch->levo);
        _destroy(branch->pravo);
        delete branch;
    }

public:

    // Описание методов

//Констркутор лего
    Tree() {
        size = 0;
        root = nullptr;


    }

    ~Tree(){
        _destroy(root);

    }

    void print() {
        _print(root, 0);
        cout << endl;
    }

    bool isEmpty() const {
        return size == 0;
    }

    void add(int value) {
        _add(root, value);
    }

// Прямой вывод
    void pPrintTree() {
        _pPrintTree(root);
    }

// Симметричный вывод
    void sPrintTree() {
        _sPrintTree(root);
    }

//Обратный вывод
    void oPrintTree() {
        _oPrintTree(root);

    }

    Element *search(int val) {
        height = 0;
        return _search(root, val);
    }

    void deleteEl(int val) {

        _delete(search(val));
    }

    int zadacha(int value){
        if (search(value) == nullptr){
            return -1;
        }
        return height;
    }
};


int randomNum() {

    return rand() % 15;
}


int main() {
    srand(time(NULL));
    Tree derevo = Tree();
    cout << "How do you want to put the values into the tree?" << endl << "Enter 1 to write by hand " << endl
         << "Enter 2 to generate random " << endl << "Enter 3 to take from txt file" << endl;
    int q;
    cin >> q;
    if (q == 1) {
        int h, x;
        cout << "How much number you wont to write?  " << endl;
        cin >> h;
        for (int i = 0; i < h; i++) {
            cin >> x;
            derevo.add(x);
        }
    }
    if (q == 2) {
        int h;
        cout << "How much number you wont to write?  " << endl;
        cin >> h;
        for (int i = 0; i < h; i++) {
            derevo.add(randomNum());
        }
    }
    if (q == 3) {
        ifstream FileIn("../FileIn.txt");
        if (!FileIn.is_open()) {
            cout << "Error opening file!!!" << endl;
        } else {
            cout << "File open successfully" << endl;
        }
        int val;
        while (FileIn >> val) {
            derevo.add(val);
        }
    }

    derevo.pPrintTree();
    cout << endl;
    derevo.sPrintTree();
    cout << endl;
    derevo.oPrintTree();
    cout << endl<<endl<<endl;
    derevo.print();
    derevo.deleteEl(2);
    derevo.print();
    //cout<<"What element you wont to found theit height?"<<endl;
   // int o;
   // cin>>o;
  //  cout<<"Otvet: "<<derevo.zadacha(o)<<endl;
  //  cout<<"What element you wont to delete?"<<endl;
  //  cin>>o;
    //derevo.deleteEl(o);
  //  derevo.print();

    return 0;

}
