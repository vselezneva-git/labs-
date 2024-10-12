#pragma once

#include <vector>
#include <string>

/**
* @class BitArray
* @brief A class for managing a dynamic attay of bits
*
* The class provides methods for working with a bit array
* It supports bit operations - and, or, xor and logical shifts
* We can also resize, set and reset bits.
*/
class BitArray
{
private:
    std::vector<unsigned long> bits; ///< The container for storing bits.
    int num_bits;///< The total number of bits in the BitArray.
    static const int bits_in_long = sizeof(unsigned long) * 8; ///< The number of bits in an unsigned long.
public:
    /**
    * @brief Default constructor
    * Initializes an empty BitArray with zeros.
    */
    BitArray(); 

    /**
    * @brief Default destructor
    * Cleans up the resources used by the BitArray object.
    */
    ~BitArray();

    /**
    * @brief Constructs a BitArray with a specific number of bits.
    * Initializes the first `sizeof(unsigned long)` bits with the given value.
    * 
    * @param num_bits The number of bits to initialize in the array.
    * @param value The initial value for the first bits of the array.
    * 
    * @throws std::invalid_argument if the number of bits is negative.
    */
    explicit BitArray(int num_bits, unsigned long value = 0);

    /**
    * @brief Copy constructor
    * Creates a copy of an existing BitArray object
    * 
    * @param b The BitArray object to copy from
    */
    BitArray(const BitArray& b);

    /** 
    * @brief Assignment operator
    * Assigns the values of one BitArray object to another
    * 
    * @param b The BitArray object to assign from
    * @return Reference to the assigned BitArray object
    */
    BitArray& operator=(const BitArray& b);

    /**
    * @brief Swaps the contents of two BitArray objects.
    * 
    * @param b The BitArray object to swap with
    */
    void Swap(BitArray& b);

    /**
    * @brief Resizes the BitArray to a new size.
    * 
    * @param new_num_bits The new number of bits for the array
    * @param value The value to initialize new bits (if the size is increased).
    * 
    * @throws std::invalid_argument if the new size is negative.
    */
    void Resize(int new_num_bits, bool value = false);

    /**
    * @brief Clears all bits in the BitArray.
    * Sets the number of bits to 0 and clears the internal storage.
    */
    void clear();

    /**
    * @brief Appends a bit to the end of the BitArray.
    * 
    * @param bit The bit value (true or false) to add.
    */
    void push_back(bool bit);

    /**
    * @brief Performs a bitwise AND operation on two BitArray objects.
    * Modifies the current BitArray by performing AND with the provided one.
    * 
    * @param b The BitArray object to AND with
    * @throws std::invalid_argument if the arrays have different sizes
    * @return A reference to the modified BitArray.
    */
    BitArray& operator&=(const BitArray& b); 

    /**
    * @brief Performs a bitwise OR operation on two BitArray objects
    * Modifies the current BitArray by performing OR with the provided one
    * 
    * @param b The BitArray object to OR with
    *  @throws std::invalid_argument if the arrays have different sizes
    *  @return A reference to the modified BitArray
    */
    BitArray& operator|=(const BitArray& b); 

    /**
     * @brief Performs a bitwise XOR operation on two BitArray objects.
     * Modifies the current BitArray by performing XOR with the provided one.
     * 
     * @param b The BitArray object to XOR with.
     * @throws std::invalid_argument if the arrays have different sizes.
     * @return A reference to the modified BitArray.
     */
    BitArray& operator^=(const BitArray& b); 

    /**
     * @brief Shifts the bits in the BitArray to the left and returns a new BitArray.
     * 
     * @param n The number of positions to shift.
     * @return A new BitArray with the result of the left shift.
     */
    BitArray& operator<<=(int n); 

    /**
     * @brief Shifts the bits in the BitArray to the left by a specified number of positions.
     * 
     * @param n The number of positions to shift.
     * @throws std::invalid_argument if the shift value is negative.
     * @return A reference to the modified BitArray.
     */
    BitArray& operator>>=(int n);

    /**
     * @brief Shifts the bits in the BitArray to the right and returns a new BitArray.
     * 
     * @param n The number of positions to shift.
     * @return A new BitArray with the result of the right shift.
     */
    BitArray operator>>(int n) const;

     /**
     * @brief Shifts the bits in the BitArray to the left and returns a new BitArray.
     * 
     * @param n The number of positions to shift.
     * @return A new BitArray with the result of the left shift.
     */
    BitArray operator<<(int n) const;

    /**
     * @brief Sets the bit at the specified position to a given value.
     * 
     * @param n The index of the bit to set.
     * @param val The value to set (true for 1, false for 0).
     * @throws std::invalid_argument if the index is negative.
     * @throws std::out_of_range if the index is out of range.
     * @return A reference to the modified BitArray.
     */
    BitArray& Set(int n, bool val = true);

    /**
     * @brief Sets all bits in the BitArray to 1.
     * 
     * @return A reference to the modified BitArray.
     */
    BitArray& Set();

    /**
     * @brief Resets (sets to 0) the bit at the specified position.
     * 
     * @param n The index of the bit to reset.
     * @return A reference to the modified BitArray.
     */
    BitArray& Reset(int n);

    /**
     * @brief Resets all bits in the BitArray to 0.
     * 
     * @return A reference to the modified BitArray.
     */
    BitArray& Reset();

    /**
     * @brief Checks if any bit in the BitArray is set to 1.
     * 
     * @return True if any bit is 1, otherwise false.
     */
    bool any() const; 

    /**
     * @brief Checks if no bits are set to 1.
     * 
     * @return True if all bits are 0, otherwise false.
     */
    bool none() const; 

    /**
     * @brief Performs a bitwise NOT operation on the BitArray.
     * Returns a new BitArray where all bits are flipped.
     * 
     * @return A new BitArray with the result of the NOT operation.
     */
    BitArray operator~() const; 

    /**
     * @brief Counts the number of bits set to 1 in the BitArray.
     * 
     * @return The number of bits set to 1.
     */
    int count() const; 

    /**
     * @brief Returns the value of the bit at the specified index.
     * 
     * @param i The index of the bit.
     * @throws std::invalid_argument if the index is negative.
     * @throws std::out_of_range if the index is out of range.
     * @return True if the bit is 1, false if the bit is 0.
     */
    bool operator[](int i) const; 

    /**
     * @brief Returns the number of bits in the BitArray.
     * 
     * @return The total number of bits.
     */
    int size() const; 

    /**
     * @brief Checks if the BitArray is empty (contains no bits).
     * 
     * @return True if the array is empty, otherwise false.
     */
    bool empty() const; 

    /**
     * @brief Converts the BitArray to a string representation of bits.
     * 
     * @return A string representing the bits in the array.
     */
    std::string to_string() const; 

    /**
     * @brief Checks if two BitArray objects are equal.
     * 
     * @param a The first BitArray object.
     * @param b The second BitArray object.
     * @return True if both arrays have the same size and bits, otherwise false.
     */
    friend bool operator==(const BitArray & a, const BitArray & b);

    /**
     * @brief Checks if two BitArray objects are not equal.
     * 
     * @param a The first BitArray object.
     * @param b The second BitArray object.
     * @return True if the arrays are different, otherwise false.
     */
    friend bool operator!=(const BitArray & a, const BitArray & b);

    /**
     * @brief Performs bitwise AND on two BitArray objects.
     * 
     * @param b1 The first BitArray object.
     * @param b2 The second BitArray object.
     * @return A new BitArray containing the result of the AND operation.
     */
    friend BitArray operator&(const BitArray& b1, const BitArray& b2);

    /**
     * @brief Performs bitwise OR on two BitArray objects.
     * 
     * @param b1 The first BitArray object.
     * @param b2 The second BitArray object.
     * @return A new BitArray containing the result of the OR operation.
     */
    friend BitArray operator|(const BitArray& b1, const BitArray& b2);

    /**
     * @brief Performs bitwise XOR on two BitArray objects.
     * 
     * @param b1 The first BitArray object.
     * @param b2 The second BitArray object.
     * @return A new BitArray containing the result of the XOR operation.
     */
    friend BitArray operator^(const BitArray& b1, const BitArray& b2);

};
