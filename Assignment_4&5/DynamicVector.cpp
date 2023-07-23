// In case I need to have them separately
/*
 *
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
void DynamicVector<TypeOfElement>::addElement(const TypeOfElement &element) {
    if (this->size == this->capacity)
        this->resize(this->capacity * 2);
    this->elements[this->size] = element;
    this->size++;

}

template<typename TypeOfElement>
void DynamicVector<TypeOfElement>::resize(int newCapacity) {
    TypeOfElement* newData = new TypeOfElement[newCapacity];
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

template<typename TypeOfElement>
void DynamicVector<TypeOfElement>::removeCertainElement(const TypeOfElement &element) {
    int position = 0;
    for (int i = 0; i < this->size; i++)
        if (this->elements[i] == element)
            position = i;
    this->erase_from_position(position);

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
}

*/


