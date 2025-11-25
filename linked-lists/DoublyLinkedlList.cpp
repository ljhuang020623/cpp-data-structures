#include <iostream>
#include <utility>



// Time Complexity for Linkedlist 
// Indexing: O(n), Search: O(n), Insertion: O(1), Deletion: O(1)
// The use of the iterator is when indexing is expensive(linkedlist) or when you dont have operator overloading on [] for indexing

template <typename Object>

class List{

private:
    // Node
    struct Node{
        Object data;
        Node* prev;
        Node* next;

        Node(const Object& d = Object{}, Node* p = nullptr, Node* n = nullptr)
        : data{d}, prev{p}, next{n}{}

        Node(Object&& d, Node* p = nullptr, Node* n = nullptr)
        : data{std::move(d)}, prev{p}, next{n}{}
    };  

    // class member
    int theSize;
    Node* head;
    Node* tail;

    void init(){
        theSize = 0;
        head = new Node;
        tail = new Node;
        // head -> next = tail is equal to (*head).next = tail
        head->prev = nullptr;
        head->next = tail;
        tail->prev = head;
        tail->next = nullptr;
    }

public:
    //const_iterator
    class const_iterator{
    public:
        const_iterator(): current{nullptr}{}
        const Object& operator*() const{
            return retrieve();
        }
        //prefix ++ 
        const_iterator& operator++(){
            current = current -> next;
            return *this;
        }

        //postfix ++
        const_iterator operator++(int){
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        // prefix --
        const_iterator& operator--() {
            current = current->prev;
            return *this;
        }

        // postfix --
        const_iterator operator--(int) {
            const_iterator old = *this;
            --(*this);
            return old;
        }


        bool operator==(const const_iterator& rhs) const{
            return current == rhs.current;
        }

        bool operator!=(const const_iterator& rhs) const{
            return current != rhs.current;
        }
    protected:
        Node* current;
        Object& retrieve() const{
            return current->data;
        }
        const_iterator(Node* p): current{p}{}
        friend class List<Object>;
    };


    // iterator
    class iterator : public const_iterator{
    public:
        iterator(){}
        Object& operator*(){
            return const_iterator::retrieve();
        }

        const Object& operator*() const{
            return const_iterator::operator*();
        }

        // prefix ++
        iterator& operator++(){
            this->current = this->current -> next;
            return *this;
        }

        // postfix ++ 
        iterator operator++(int){
            iterator old = *this;
            ++(*this);
            return old;
        }

        // prefix --
        iterator& operator--() {
            this->current = this->current->prev;
            return *this;
        }

        // postfix --
        iterator operator--(int) {
            iterator old = *this;
            --(*this);
            return old;
        }
    protected:
        iterator(Node* p): const_iterator{p}{}
        friend class List<Object>;
    };

    // iterators
    iterator begin(){
        return iterator{head -> next};
    }

    const_iterator begin() const{
        return const_iterator{head -> next};
    }

    // the reason end() is tail not tail -> prev is because the design of usage for iterator, in for loop the end is not inclusive so it will loop till tail -> prev
    // for(auto it = lst.begin(); it != lst.end(); ++it)
    iterator end(){
        return iterator{tail};
    }

    const_iterator end() const{
        return const_iterator{tail};

    }

    // front/back
    Object& front(){
        // in begin the function return iterator type and in the * operator overloading of iterator this will give you the data of the current node
        return *begin();
    }

    const Object& front() const{
        return *begin();
    }

    Object& back(){
        return *(--end());
    }

    const Object& back() const{
        return *(--end());
    }

    // modifiers
    iterator insert(iterator itr, const Object& x){
        Node* p = itr.current;
        Node* newNode = new Node{x, p->prev, p};
        p->prev->next = newNode;
        p->prev = newNode;
        theSize++;
        return iterator{newNode};
    }

    iterator insert(iterator itr, Object&& x){
        Node* p = itr.current;
        Node* newNode = new Node{std::move(x), p->prev, p};
        p->prev->next = newNode;
        p->prev = newNode;
        theSize++;
        return iterator{newNode};
    }

    // Erase item at itr
    iterator erase(iterator itr){
        Node* p = itr.current;
        iterator retVal{p->next};
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        theSize--;
        return retVal;
    }

    // Erase item in range
    iterator erase(iterator from, iterator to){
        for (iterator itr = from; itr != to; ){
            itr = erase(itr);
        }
        return to;
    }

    void clear(){
        while(!empty()){
            pop_front();
        }
    }
    void push_front(const Object& x){
        insert(begin(), x);
    }

    void push_front(Object&& x){
        insert(begin(), std::move(x));
    }

    void push_back(const Object& x){
        insert(end(), x);
    }

    void push_back(Object&& x){
        insert(end(), std::move(x));
    }
    void pop_front(){
        erase(begin());
    }
    void pop_back(){
        erase(--end());
    }


    //Rule of 5
    //Constructor, Destructor, Copy Constructor, Copy assignment, Move Constructor, Move assignment

    List(){
        init();
    }

    ~List(){
        clear();
        delete head;
        delete tail;
    }

    List(const List& rhs){
        init();
        for (auto x : rhs){
            push_back(x);
        }
    }

    List& operator=(const List& rhs){
        List copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    List(List&& rhs) noexcept
    : theSize(rhs.theSize), head{rhs.head}, tail{rhs.tail}{
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }

    List& operator=(List&& rhs) noexcept{
        std::swap(theSize, rhs.theSize);
        std::swap(head, rhs.head);
        std::swap(tail, rhs.tail);
        return *this;
    }



    int size() const{ return theSize;}
    bool empty() const { return theSize == 0;}

};

