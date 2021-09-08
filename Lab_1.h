#pragma once

namespace Lab_1 
{
    struct Matrix 
    {
        int m;             //кол-во строк
        int n;             //кол-во столбцов
        int nz;            //not zeros - кол-во ненулевых значения
        int* values;       //все ненулевые значения матрицы
        int* columns;      //номера столбцов соответствующих элементов из массива values
        int* rows_indexing; //размер массива m+1, i-ый эл-т хранит кол-во ненулевых эл-тов в строках до i-1-ой включительно
    };

    Matrix* matrix_init();
    int criterium(int);
    int* form_vector(Matrix*& matrix_ptr, int (*criterium)(int));
    void matrix_print(Matrix*& matrix_ptr);
    void matrix_delete(Matrix*& matrix_ptr);
    void vec_print(int*& vec, int m);
    void vec_delete(int*& vec);

    #if 0
    int get_aij(Matrix*& matrix_ptr, int i, int j);
    #endif

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