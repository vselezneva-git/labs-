#pragma once

#include <vector>
#include <string>

class BitArray
{
private:
    std::vector<unsigned long> bits;
    int num_bits; //общее кол-во битов в массиве
    static const int bits_in_long = sizeof(unsigned long) * 8; //кол-во бит в одном лонге
public:
    BitArray(); //конструктор, который создает пустой массив
    ~BitArray(); //освобождает память, когда объект больше не нужен

    //Этот конструктор создаёт битовый массив размером num_bits. Первые sizeof(long) бит могут быть инициализированы значением value. 
    //Это означает, что если мы передадим число, то его двоичное представление и будет началом массива.
    //Пример: если передать value = 10, то массив начнётся с 1010 (в двоичном виде).
    explicit BitArray(int num_bits, unsigned long value = 0);

    //конструктор копирования. Этот конструктор создает копию другого битового массива
    BitArray(const BitArray& b);

    //оператор присваивания
    BitArray& operator=(const BitArray& b);

    //обменивает значения двух битовых массивов
    void Swap(BitArray& b);

    //изменяет размер массива. Новые элементы инициал значением value
    void Resize(int new_num_bits, bool value = false);
    //очищает массив
    void clear();
    //добавляет новый бит в конец массива. Если массива не хватает для хранения нового бита
    //память перераспределяется
    void push_back(bool bit);

    //битовые операции над массивами ТОЛЬКО одинакового размера
    BitArray& operator&=(const BitArray& b); //побитовое И
    BitArray& operator|=(const BitArray& b); //побитовое ИЛИ
    BitArray& operator^=(const BitArray& b); //побитовое исключающее ИЛИ

    BitArray& operator>>=(int n); //сдвиг влево с заполнением нулями
    BitArray& operator<<=(int n); //сдвиг вправо с заполнением нулями

    BitArray operator<<(int n) const; //сдвиг влево, возвращает новый массив
    BitArray operator>>(int n) const; //сдвиг вправо, возвращает новый массив 

    //устанавливает бит с индексом n в значение val
    BitArray& Set(int n, bool val = true);
    //заполняет массив истиной
    BitArray& Set();

    //устанавливает бит с индексом n в значение  false
    BitArray& Reset(int n);
    //заполняет массив ложью
    BitArray& Reset();

    bool any() const; //true, если массив содержит истинный бит
    bool none() const; //true, если все биты ложны

    BitArray operator~() const; //битовая инверсия
    int count() const; //подсчет кол-ва единичных бит

    bool operator[](int i) const; //возвращает значение бита по индексу i

    int size() const; //проверяет кол-во битов в массиве
    bool empty() const; //проверяет пуст ли массив

    std::string to_string() const; //возвращает строковое представление массива

    friend bool operator==(const BitArray & a, const BitArray & b);
    friend bool operator!=(const BitArray & a, const BitArray & b);
    friend BitArray operator&(const BitArray& b1, const BitArray& b2);
    friend BitArray operator|(const BitArray& b1, const BitArray& b2);
    friend BitArray operator^(const BitArray& b1, const BitArray& b2);
    
    void extra_mask(int bit_count);
    int calculate_long(int num_bits) const;
};



