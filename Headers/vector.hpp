template <typename T>
class MyVector {
private:
    T* data;
    size_t size;
    size_t capacity;

public:
    // Constructor
    MyVector() : data(nullptr), size(0), capacity(0) {}

    // Destructor
    ~MyVector() {
        delete[] data;
    }

    // Function to add an element to the vector
    void push_back(const T& element) {
        if (size >= capacity) {
            if (capacity == 0) {
                capacity = 1;
            } else {
                capacity *= 2;
            }
            T* newData = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size++] = element;
    }

    // Function to get the size of the vector
    size_t getSize() const {
        return size;
    }

    // Overloaded subscript operator
    T& operator[](size_t index) {
        return data[index];
    }
};
