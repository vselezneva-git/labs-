#include "BitArray.h"
#include <stdexcept>
#include <bitset>
#include <algorithm>

BitArray::BitArray() : num_bits(0) {}
BitArray::~BitArray() = default;

BitArray::BitArray(int num_bits, unsigned long value) {
    if(num_bits < 0) throw std::invalid_argument("array size cannot be negative");

    //сколько unsigned long нам надо?
    int num_long = calculate_long(num_bits);

    bits.resize(num_long, 0);
    if(num_bits > 0)  {
        bits[0] = value;
    }

    this->num_bits = num_bits;    
}

BitArray::BitArray(const BitArray& b) : bits(b.bits), num_bits(b.num_bits) {}

BitArray& BitArray::operator=(const BitArray& b) {
    if(this != &b) {
        bits = b.bits;
        num_bits = b.num_bits;
    }
    return *this;
}

void BitArray::Swap(BitArray& b) {
    std::swap(bits, b.bits);
    std::swap(num_bits, b.num_bits);
}

void BitArray::Resize(int new_size, bool value) {
    if (new_size < 0) {
        throw std::invalid_argument("array size cannot be negative");
    }

    int new_num_long = calculate_long(new_size);
    int old_size = num_bits;

    if(new_size == 0) {
        bits.clear();
    }

    if(new_size == num_bits) {
        return;
    }

    bits.resize(new_num_long, 0ul); 

    num_bits = new_size; 

    if (new_size > old_size && value) {
        for (int i = old_size; i < new_size; ++i) {
            Set(i, true); 
        }
    }

    extra_mask(new_size);

}


void BitArray::clear() {
    bits.clear();
    num_bits = 0;
}

void BitArray::push_back(bool bit) {
    Resize(num_bits + 1);
    Set(num_bits - 1, bit);
}

BitArray& BitArray::operator&=(const BitArray& b) {
    if(num_bits != b.num_bits) throw std::invalid_argument("The array sizes must be the same");
    for(size_t i = 0; i < bits.size(); ++i) {
        bits[i] &= b.bits[i];
    }
    return *this;
}

BitArray& BitArray::operator|=(const BitArray& b) {
    if(num_bits != b.num_bits) throw std::invalid_argument("The array sizes must be the same");
    for(size_t i = 0; i < bits.size(); ++i) {
        bits[i] |= b.bits[i];
    }
    return *this;
}

BitArray& BitArray::operator^=(const BitArray& b) {
    if(num_bits != b.num_bits) throw std::invalid_argument("The array sizes must be the same");
    for(size_t i = 0; i < bits.size(); ++i) {
        bits[i] ^= b.bits[i];
    }
    return *this;
}

BitArray& BitArray::operator>>=(int n) {
    if(n < 0) throw std::invalid_argument("the shift must not be negative");

    if(n >= num_bits) {
        Reset();
        return *this;
    }

    for(size_t i = 0; i < num_bits - n; ++i) {
        Set(i, (*this)[n + i]);
    }

    for(size_t i = num_bits - n; i < num_bits; ++i) {
        Set(i, false);
    }
    
    return *this;
}

BitArray& BitArray::operator<<=(int n) {
    if(n < 0) throw std::invalid_argument("the shift must not be negative");

    if(n >= num_bits) {
        Reset();
        return *this;
    }

    for(size_t i = num_bits - 1; i >= n; --i) {
        Set(i, (*this)[i - n]);
    }
    
    for(size_t i = 0; i < n; ++i) {
        Set(i, false);
    }
    return *this;
}

BitArray BitArray::operator<<(int n) const {
    BitArray result(*this);
    result <<= n;
    return result;
}

BitArray BitArray::operator>>(int n) const {
    BitArray result(*this);
    result >>= n;
    return result;
}

BitArray& BitArray::Set(int n, bool val) {
    if(n < 0) throw std::invalid_argument("index value cannot be negative");

    if(n >= num_bits) throw std::out_of_range("index is in invalid range");

    int index = n / bits_in_long; //находим в каком блоке UL находится индекс
    int bit_position = n % bits_in_long;

    if(val) {
        bits[index] |= (1ul << bit_position);
    } else {
        bits[index] &= ~(1ul << bit_position);
    }

    return *this;
}

BitArray& BitArray::Set() {
    for(auto& val : bits) {
        val = ~0ul;
    }

    extra_mask(num_bits);

    return *this;
}

BitArray& BitArray::Reset(int n) {
    return Set(n, false);
}

BitArray& BitArray::Reset() {
    for(auto& val : bits) {
        val = 0;
    }
    return *this;
}

bool BitArray::any() const {
    for(const auto& val : bits) {
        if(val != 0) return true;
    }
    return false;
}

bool BitArray::none() const {
    return !any();
}

BitArray BitArray::operator~() const {
    BitArray result(*this);
    for(auto& val : result.bits) {
        val = ~val;
    }

    result.extra_mask(num_bits);

    return result;
}

int BitArray::count() const {
    int count = 0;
    for(const auto& val : bits) {
        count += std::bitset<bits_in_long>(val).count();
    }
    return count;
}

bool BitArray::operator[](int i) const {
    if(i < 0) throw std::invalid_argument("index value cannot be negative");

    if(i >= num_bits) throw std::out_of_range("index is in invalid range");

    int index = i / bits_in_long;
    int bit_position = i % bits_in_long;

    return (bits[index] & (1ul << bit_position)) != 0;
}

int BitArray::size() const {
    return num_bits;
}

bool BitArray::empty() const {
    if(num_bits == 0) {
        return true;
    }
    return false;
}

std::string BitArray::to_string() const {
    std::string result;
    for(int i = num_bits - 1; i >= 0; --i) {
        result += (*this)[i] ? '1' : '0';
    }
    return result;
}

bool operator==(const BitArray & a, const BitArray & b) {
    return ((a.num_bits == b.num_bits) && (a.bits == b.bits));
}

bool operator!=(const BitArray & a, const BitArray & b) {
    return !(a == b);
}

BitArray operator&(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);
    result &= b2;
    return result;
}
BitArray operator|(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);
    result |= b2;
    return result;
}

BitArray operator^(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);
    result ^= b2;
    return result;
}

void BitArray::extra_mask(int bit_count) {
    int extra_bits = bit_count % bits_in_long;
    if (extra_bits != 0) {
        bits.back() &= (1ul << extra_bits) - 1;
    }
}

int BitArray::calculate_long(int num_bits) const {
    return (num_bits + (bits_in_long - 1)) / bits_in_long;
}
