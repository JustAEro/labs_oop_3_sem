#pragma once

namespace Lab_1 
{
    struct Item
    {
        int value;      
        int row;        
        int column;
        Item* next;
    };

    struct List
    {
        Item* head;
    };

    struct Matrix 
    {
        int m;             //кол-во строк
        int n;             //кол-во столбцов
        List** lists_for_rows;
             
    };



    Matrix* matrix_init();
    int criterium(int);
    int* form_vector(Matrix*& matrix_ptr, int (*criterium)(int));
    void matrix_print(Matrix*& matrix_ptr);
    void matrix_delete(Matrix*& matrix_ptr);
    void vec_print(int*& vec, int m);
    void vec_delete(int*& vec);

    Item* matrix_find(Matrix*& matrix_ptr, int i, int j);
    void matrix_add(Matrix*& matrix_ptr, Item*& item_ptr);
    
    void list_delete(List*& list_ptr);



    template <class T>
    int getNumber(T& x)
    {
        std::cin >> x;
        if (!std::cin.good())
        {
            return -1;  //eof or error of read 
        }
        return 0; //ok
    }
}