// Problem 1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

struct Matrix {
    int m;             //кол-во строк
    int n;             //кол-во столбцов
    int nz;            //not zeros - кол-во ненулевых значения
    int* values;       //все ненулевые значения матрицы
    int* columns;      //номера столбцов соответствующих элементов из массива values
    int* rows_indexing; //размер массива m+1, i-ый эл-т хранит кол-во ненулевых эл-тов в строках до i-1-ой включительно
};

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

Matrix* matrix_init() 
{
    Matrix* matrix_ptr = new Matrix;

    int m;
    int n;
    std::cout << "Enter number of rows:" << std::endl;
    getNumber(m);

    std::cout << "Enter number of columns:" << std::endl;
    getNumber(n);

    matrix_ptr->m = m;
    matrix_ptr->n = n;
    matrix_ptr->nz = 0;

    matrix_ptr->values = nullptr;
    matrix_ptr->columns = nullptr;

    matrix_ptr->rows_indexing = new int[m+1];
    matrix_ptr->rows_indexing[0] = 0;

    int x;

    std::cout << "Enter " << (n * m) << " elements" << std::endl;
    for (int i = 0; i < m; ++i) 
    {
        int nz_row = 0;
        for (int j = 0; j < n; ++j) 
        {
            getNumber(x);
            if (x != 0) 
            {
                ++nz_row;
                if (matrix_ptr->nz == 0) 
                {              //values array is empty
                    matrix_ptr->values = new int[1];
                    matrix_ptr->columns = new int[1];
                    matrix_ptr->nz = 1;

                    matrix_ptr->values[0] = x;
                    matrix_ptr->columns[0] = j;
                }
                else    //values array isn't empty
                {
                    ++(matrix_ptr->nz);
                    int* values_new = new int[matrix_ptr->nz];
                    int* columns_new = new int[matrix_ptr->nz];
                    for (int k = 0; k < matrix_ptr->nz - 1; ++k) 
                    {
                        values_new[k] = matrix_ptr->values[k];
                        columns_new[k] = matrix_ptr->columns[k];
                    }

                    delete[] matrix_ptr->values;
                    matrix_ptr->values = values_new;

                    delete[] matrix_ptr->columns;
                    matrix_ptr->columns = columns_new;

                    matrix_ptr->values[matrix_ptr->nz - 1] = x;
                    matrix_ptr->columns[matrix_ptr->nz - 1] = j;
                }
            }
        }

        matrix_ptr->rows_indexing[i + 1] = matrix_ptr->rows_indexing[i] + nz_row;
    }
    return matrix_ptr;
}

int criterium(int x) 
{
    int counter = 0;

    if (x == 0)
    {
        return 0;
    }

    do 
    {
        x /= 10;
        ++counter;
    } 
    while (x != 0);

    if (counter >= 2) 
    {
        return 1;
    }

    return 0;
}


int* form_vector(Matrix*& matrix_ptr, int (*criterium)(int) )
{
    int* vector_result = new int[matrix_ptr->m];

    int index_start = 0;
    int index_finish = 0;

    for (int i = 0; i < matrix_ptr->m; ++i)
    {
        int k = matrix_ptr->rows_indexing[i + 1] - matrix_ptr->rows_indexing[i];  //кол-во не нулей в текущей строке
        index_finish += k;

        int sum = 0;
        for (int j = index_start; j < index_finish && j < matrix_ptr->nz; ++j)
        {
            if (criterium(matrix_ptr->values[j])) 
            {
                sum += matrix_ptr->values[j];
            }
        }
        //++index_finish;
        index_start = index_finish;
        vector_result[i] = sum;
    }

    return vector_result;
}


void matrix_print(Matrix*& matrix_ptr) 
{
    std::cout << "The matrix is:" << std::endl;

    std::cout << "Values: ";
    for (int i = 0; i < matrix_ptr->nz; ++i) 
    {
        std::cout << matrix_ptr->values[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Columns: ";
    for (int i = 0; i < matrix_ptr->nz; ++i)
    {
        std::cout << matrix_ptr->columns[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Rows indexing: ";
    for (int i = 0; i < matrix_ptr->m + 1; ++i) {
        std::cout << matrix_ptr->rows_indexing[i] << " ";
    }
    std::cout << std::endl;


    std::cout << "The restored matrix: " << std::endl;
    int index_start = 0;
    int index_finish = 0;
    for (int i = 0; i < matrix_ptr->m; ++i) 
    {
        std::cout << "||\t";
        int k = matrix_ptr->rows_indexing[i + 1] - matrix_ptr->rows_indexing[i];  //кол-во не нулей в текущей строке
        index_finish += k;
        for (int j = 0; j < matrix_ptr->n; ++j) 
        {
            if (index_start < matrix_ptr->nz && index_start < index_finish && matrix_ptr->columns[index_start] == j)
            {
                std::cout << matrix_ptr->values[index_start] << "\t";
                ++index_start;
            }
            else 
            {
                std::cout << 0 << "\t";
            }
        }
        //++index_finish;
        index_start = index_finish;
        std::cout << "||";
        std::cout << std::endl;
    }

}


void matrix_delete(Matrix*& matrix_ptr) 
{
    delete[] matrix_ptr->values;            matrix_ptr->values = nullptr;
    delete[] matrix_ptr->columns;           matrix_ptr->columns = nullptr;
    delete[] matrix_ptr->rows_indexing;     matrix_ptr->rows_indexing = nullptr;
    
    matrix_ptr->m = 0;
    matrix_ptr->n = 0;
    matrix_ptr->nz = 0;

    delete matrix_ptr;  matrix_ptr = nullptr;
}

void vec_print(int*& vec, int m) 
{
    std::cout << "The resulting vector is:" << std::endl;
    for (int i = 0; i < m; ++i)
    {
        std::cout << vec[i] << " ";
    }

    std::cout << std::endl;
}

void vec_delete(int*& vec)
{
    delete[] vec;
    vec = nullptr;
}

#if 0 
int get_aij(Matrix*& matrix_ptr, int i, int j)
{
    if (i <= 0 || i >= matrix_ptr->m || j <= 0 || j >= matrix_ptr->n)
    {
        return -1;
    }

    int index_start = matrix_ptr->rows_indexing[i];
    int index_finish = matrix_ptr->rows_indexing[i + 1];
    for (int i = index_start; i < index_finish; ++i) 
    {
        if (matrix_ptr->columns[i] == j)
        {
            return matrix_ptr->values[i];
        }
    }
    return 0;
}
#endif

int main()
{
    Matrix* matrix_ptr = matrix_init();
    int* vec = form_vector(matrix_ptr, criterium);

    matrix_print(matrix_ptr);
    vec_print(vec, matrix_ptr->m);

    //std::cout << "This is a[1][1] " << get_aij(matrix_ptr, 1, 1) << std::endl;

    matrix_delete(matrix_ptr);
    vec_delete(vec);
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
