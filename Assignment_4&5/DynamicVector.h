#pragma once

template <typename TypeOfElement> class DynamicVector {
private:
    // the array of elements
    TypeOfElement* elements;
    // the current size of the vector
    int size{};
    // the current capacity of the vector
    int capacity{};
    // Resizes is private because we don't want the user to be able to change the capacity of the vector
    void resize(int newCapacity);
    
public:
    /// Constructors and destructor
    // Constructor
    explicit DynamicVector(int capacity = 10); // explicit keyword is used with a constructor to prevent it from performing implicit conversions
    // Copy constructor
    DynamicVector(const DynamicVector& other); // const keyword is used to prevent the function from modifying the dynamic vector
    // Operator =
    DynamicVector& operator=(const DynamicVector& other);
    // Destructor
    ~DynamicVector();

    /// Functions
    void addElement(const TypeOfElement& newElement); // const keyword is used to prevent the function from modifying the object even though is transmitted by reference
    void addElementToPosition(const TypeOfElement& newElement, int position);
    void removeCertainElement(const TypeOfElement& element);
    TypeOfElement* findElement(const TypeOfElement& element);
    void removeElementFromPosition(int position);
    

    /// Operators
    // Overload the subscript operator for non-const objects
    TypeOfElement& operator[](int position);
    // Overload the subscript operator for const objects
    const TypeOfElement& operator[](int position) const;
    void setElement(int position, const TypeOfElement& newElement);

    /// Getters
    // Returns the size of the vector
    int getSize() const;
    // Returns the capacity of the vector
    int getCapacity() const;
};

// Constructor
template<typename TypeOfElement>
DynamicVector<TypeOfElement>::DynamicVector(int capacity):
    size{0}, capacity{capacity} // member initializer list
{
    this->elements = new TypeOfElement[capacity];

}

// Copy constructor
template<typename TypeOfElement>
DynamicVector<TypeOfElement>::DynamicVector(const DynamicVector &other) {
    this->size = other.size;
    this->capacity = other.capacity;
    this->elements = new TypeOfElement[this->capacity];
    for (int i = 0; i < this->size; i++)
        this->elements[i] = other.elements[i];

}

// Operator =
template<typename TypeOfElement>
DynamicVector<TypeOfElement> &DynamicVector<TypeOfElement>::operator=(const DynamicVector &other) {
    if (this != &other) {
        this->size = other.size;
        this->capacity = other.capacity;
        delete[] this->elements;
        this->elements = new TypeOfElement[this->capacity];
        for (int i = 0; i < this->size; i++)
            this->elements[i] = other.elements[i];
    }
    return *this;
}

template<typename TypeOfElement>
DynamicVector<TypeOfElement>::~DynamicVector() {
    delete[] this->elements;

}

template<typename TypeOfElement>
void DynamicVector<TypeOfElement>::addElement(const TypeOfElement &newElement) {
    if (this->size == this->capacity)
        this->resize(this->capacity * 2);
    this->elements[this->size] = newElement;
    this->size++;

}

template<typename TypeOfElement>
void DynamicVector<TypeOfElement>::resize(int newCapacity) {
    auto* newData = new TypeOfElement[newCapacity];
    // Copy the elements from the old array to the new one
    for (int i = 0; i < this->size; i++)
        newData[i] = this->elements[i];
    this->capacity = newCapacity;
    delete[] this->elements;    // delete the old array
    this->elements = newData;   // make the elements pointer point to the new array
}

template<typename TypeOfElement>
int DynamicVector<TypeOfElement>::getSize() const {
    return this->size;
}

template<typename TypeOfElement>
int DynamicVector<TypeOfElement>::getCapacity() const {
    return this->capacity;
}

template<typename TypeOfElement>
TypeOfElement &DynamicVector<TypeOfElement>::operator[](int position) {
    return this->elements[position];
}

template<typename TypeOfElement>
const TypeOfElement &DynamicVector<TypeOfElement>::operator[](int position) const {
    return this->elements[position];
}

// overwrite operator[] to set an element at a given position
template<typename TypeOfElement>
void DynamicVector<TypeOfElement>:: setElement(int position, const TypeOfElement& newElement) {
    this->elements[position] = newElement;
}



template<typename TypeOfElement>
void DynamicVector<TypeOfElement>::removeCertainElement(const TypeOfElement &element) {
    int position = 0;
    for (int i = 0; i < this->size; i++)
        if (this->elements[i] == element)
            position = i;
    this->removeElementFromPosition(position);

}

template<typename TypeOfElement>
void DynamicVector<TypeOfElement>::removeElementFromPosition(int position) {
    for (int i = position; i < this->size - 1; i++)
        this->elements[i] = this->elements[i + 1];
    this->size--;
    // If the vector is 1/4 full, resize it to half the capacity
    if (this->size == this->capacity / 4)
        this->resize(this->capacity / 2);
}

template<typename TypeOfElement>
TypeOfElement *DynamicVector<TypeOfElement>::findElement(const TypeOfElement &element) {
    for (int i = 0; i < this->size; i++)
        if (this->elements[i] == element)
            return &this->elements[i];
    // If the element is not found, return a null pointer
    return nullptr;
}

template<typename TypeOfElement>
void DynamicVector<TypeOfElement>::addElementToPosition(const TypeOfElement &newElement, int position) {
    if (this->size == this->capacity)
        this->resize(this->capacity * 2);
    for (int i = this->size; i > position; i--)
        this->elements[i] = this->elements[i - 1];
    this->elements[position] = newElement;
    this->size++;

}


