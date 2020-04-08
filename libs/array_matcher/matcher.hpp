// define matcher for arrays given by pointers with known type and array size
template <class T>
bool arrays_match(const T* array1, const T* array2, const unsigned int size) {
    bool match = true;

    for (int i=0; i<size; i++) {
        if (array1[i] != array2[i]) {
            match = false;

            std::cout << "\nDifference found at " << i;
            std::cout << "\nArray1: ";
            for (int j=0; j<=i; j++) {
                std::cout << array1[j] << " ";
            }

            std::cout << "\nArray2: ";
            for (int j=0; j<=i; j++) {
                std::cout << array2[j] << " ";
            }

            break;
        }
    }

    return match;
}