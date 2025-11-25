#include <algorithm>   

// Time Complexity for Vector(Dynamic Array)
// Indexing: O(1), Search: O(n), Insertion: O(n), Deletion: O(n)

template <typename Object>
class Vector {
private:
    int theSize;
    int theCapacity;
    Object* objects;
public:
    static const int SPARE_CAPACITY = 16;

    // --- types ---
    using iterator = Object*;
    using const_iterator = const Object*;


    // --- Rule of 5 ---
    // Defaule Constructor
    explicit Vector(int initSize = 0)
    : theSize{initSize}, 
      theCapacity{initSize + SPARE_CAPACITY},
      objects{new Object[theCapacity]}
    {}             
    // Copy constructor
    Vector(const Vector& rhs)
    : theSize{rhs.theSize},
      theCapacity{rhs.theCapacity},
      objects{new Object[theCapacity]}
    {
        for(int i = 0; i < theSize; i++){
            objects[i] = rhs.objects[i];
        }
    }
    // Move constructor
    Vector(Vector&& rhs) noexcept
    : theSize{rhs.theSize}, 
      theCapacity{rhs.theCapacity},
      objects{rhs.objects}
    {
        rhs.theSize = 0;
        rhs.theCapacity = 0;
        rhs.objects = nullptr;
    }
    // Copy assignment
    Vector& operator=(const Vector& rhs){
        // this is Copy constructor, copy = rhs(this is copy assignment)
        Vector copy = rhs;
        std::swap(*this , copy);
        return *this;
    }   
    // Move assignment
    Vector& operator=(Vector&& rhs) noexcept{
        std::swap(theSize, rhs.theSize);
        std::swap(theCapacity, rhs.theCapacity);
        std::swap(objects, rhs.objects);
        return *this;
    } 
    // Destructor
    ~Vector(){
        delete[] objects;
    }


    // --- element access ---
    Object& operator[](int index){
        return objects[index];
    }
    const Object& operator[](int index) const{
        return objects[index];
    }
    const Object& back() const{
        return objects[theSize - 1];
    }

    // --- capacity ---
    bool empty() const{
        return theSize == 0;
    }
    int size() const{
        return theSize;
    }
    int capacity() const{
        return theCapacity;
    }

    // --- modifiers ---
    // copy push_back
    void push_back(const Object& x){
        if(theSize == theCapacity){
            reserve(theCapacity * 2 + 1); // to prevent if theCapcity is 0 then without + 1 it will always be 0
        }
        objects[theSize++] = x;

    }   

    // move push_back
    void push_back(Object&& x){
        if(theSize == theCapacity){
            reserve(theCapacity * 2 + 1);
        }
        objects[theSize++] = std::move(x);
    } 

    void pop_back(){
        if(theSize == 0){
            return;
        }
        theSize--;
    }


    // change the size of the vector
    void resize(int newSize){

        // no <= 0 value allow
        if(newSize < 0){
            return;
        }
        // when the newSize is bigger than the Capacity then need reserve
        if(newSize > theCapacity){
            reserve(newSize * 2);
        }

        // when theSize < theCapacity but expand then default construct the new elements
        for(int i = theSize; i < newSize; i++){
            objects[i] = Object{};
        }

        // Shrinks, drop the tail 
        theSize = newSize;

    }


    //change the capacity of the vector(increase generally)
    // the capacity is changed by obtaining a new block of memory for the primitive array, copying the old block into the 
    // new block, and reclaiming the old block 
    void reserve(int newCapacity){
        if (newCapacity <= theSize){
            return;
        }

        // reserve a new memory block and move all the objects to the new block
        // use move to prevent big size vector copy
        Object* newArray = new Object[newCapacity];
        for (int i = 0; i < theSize; i++){
            newArray[i] = std::move(objects[i]);
        }
        theCapacity = newCapacity;
        std::swap(objects, newArray);
        delete[] newArray;
    }

    void clear(){
        theSize = 0;
    }

    // --- iterators ---
    iterator begin(){
        return &objects[0];
    }
    const_iterator begin() const{
        return &objects[0];
    }
    iterator end(){
        return &objects[theSize];
    }
    const_iterator end() const{
        return &objects[theSize];
    }
};


int main(){
    Vector v();
    





    return 0;
}