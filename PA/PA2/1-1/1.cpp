#include <cstdio>
const int M = 4000;

struct Node{
    Node *pred, *succ;
    int data[M];
    int _node_size;
    Node() : pred(nullptr), succ(nullptr), _node_size(0) {}
    void insert(int position, int value) {
        if (_node_size == M) { // 当前块超出 capacity 后进行分裂（平分元素个数）
            Node *t = new Node();
            int size = M >> 1;
            for (int i = size; i < M; i++) {
                t->data[i - size] = data[i];
            }
            _node_size = size;
            t->_node_size = M - size;
            succ->pred = t;
            t->succ = succ;
            succ = t;
            t->pred = this;
            if (position < size) { // 将新的元素插入到对应的块中
                insert(position, value);
            } else {
                t->insert(position - size, value);
            }
        } else {
            // 使用 brute force 进行元素移动和插入
            for (int i = _node_size; i > position; i--) {
                data[i] = data[i - 1];
            }
            data[position] = value;
            _node_size++;
        }
    }
    void remove(int position) {
        // 使用 brute force 进行元素移动和删除
        for (int i = position; i + 1 < _node_size; i++) {
            data[i] = data[i + 1];
        }
        _node_size--;
    }
};
struct UnrolledList{
    int _list_size;
    Node *header, *trailer;

    UnrolledList() {
        _list_size = 0;
        header = new Node();
        trailer = new Node();
        header->succ = trailer;
        trailer->pred = header;
    }
    void insert(int position, int value) {
        if (position < 0 || position >= _list_size) {
            trailer->pred->insert(trailer->pred->_node_size, value);
        } else {
            int size = 0;
            // 记录块的前缀大小之和，从而找到对应的块，删除和查询操作同理
            for (Node *p = header; p != trailer; p = p->succ) {
                if (size + p->_node_size >= position) {
                    p->insert(position - size, value);
                    break;
                }
                size += p->_node_size;
            }
        }
        _list_size++;
    }
    void remove(int position) {
        if (position < 0 || position >= _list_size) {
            return;
        }
        int size = 0;
        for (Node *p = header; p != trailer; p = p->succ) {
            if (size + p->_node_size > position) {
                p->remove(position - size);
                break;
            }
            size += p->_node_size;
        }
        _list_size--;
    }
    int query(int position) {
        if (position < 0 || position >= _list_size) {
            return -1;
        }
        int size = 0;
        for (Node *p = header; p != trailer; p = p->succ) {
            if (size + p->_node_size > position) {
                return p->data[position - size];
            }
            size += p->_node_size;
        }
    }
};
enum OperationType{
    NOT_USED,
    INSERT,
    DELETE,
    QUERY
};
int main(){
    // you should not modify the main function
    int num_of_operation;
    scanf("%d",&num_of_operation);
    int type_of_operation, argument1, argument2;
    UnrolledList a_list;
    for(int operation_id = 0; operation_id < num_of_operation; operation_id ++){
        scanf("%d%d%d",&type_of_operation, &argument1, &argument2);
        if(type_of_operation == INSERT){
            a_list.insert(argument1,argument2);
        }else if(type_of_operation == DELETE){
            // argument2 is 0 and should be ignored
            a_list.remove(argument1);
        }else if(type_of_operation == QUERY){
            // argument2 is 0 and should be ignored
            printf("%d\n",a_list.query(argument1));
        }else{
            printf("Invalid Operation");
            return -1;
        }
    }
    return 0;
}