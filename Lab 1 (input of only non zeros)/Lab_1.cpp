#include <iostream>
#include "Lab_1.h"

Lab_1::Matrix* Lab_1::matrix_init()
{
    Matrix* matrix_ptr = nullptr;

    try {
        matrix_ptr = new Matrix;
    }
    catch (std::bad_alloc& ba) {
        std::cout << "------ Can't allocate space for matrix: " << ba.what() << std::endl;
        return nullptr;
    }

    const char* error_message = "";   //будущее сообщение об ошибке

    int m;
    do {
        std::cout << error_message << std::endl;
        std::cout << "Enter number of rows: --> ";
        error_message = "You are wrong; repeat please!";
        if (getNumber(m) < 0) { // ошибка ввода или конец файла
            matrix_delete(matrix_ptr);
            return nullptr;
        }
    } while (m < 1);

    error_message = "";

    int n;
    do {
        std::cout << error_message << std::endl;
        std::cout << "Enter number of columns: --> ";
        error_message = "You are wrong; repeat please!";
        if (getNumber(n) < 0) { // ошибка ввода или конец файла
            matrix_delete(matrix_ptr);
            return nullptr;
        }
    } while (n < 1);


    error_message = "";

    int nz;
    do {
        std::cout << error_message << std::endl;
        std::cout << "Enter number of not zero elements: --> ";
        error_message = "You are wrong; repeat please!";
        if (getNumber(nz) < 0) { // ошибка ввода или конец файла
            matrix_delete(matrix_ptr);
            return nullptr;
        }
    } while (nz < 0 || nz > (n*m));

    error_message = "";

    matrix_ptr->m = m;
    matrix_ptr->n = n;
    

    matrix_ptr->lists_for_rows = nullptr;
    

    try {
        matrix_ptr->lists_for_rows = new List* [m];
    }
    catch (std::bad_alloc& ba) {
        std::cout << "------ Can't allocate space for matrix: " << ba.what() << std::endl;
        matrix_delete(matrix_ptr);
        return nullptr;
    }

    for (int i = 0; i < m; ++i)
    {
        try {
            matrix_ptr->lists_for_rows[i] = new List;
        }
        catch (std::bad_alloc& ba) {
            std::cout << "------ Can't allocate space for matrix: " << ba.what() << std::endl;
            matrix_delete(matrix_ptr);
            return nullptr;
        }

        matrix_ptr->lists_for_rows[i]->head = nullptr;
    }

    for (int i = 0; i < nz; ++i)
    {
        std::cout << std::endl;

        int x;
        error_message = "";
        do {
            std::cout << error_message << std::endl;
            std::cout << "Enter the value: ";
            error_message = "You can't input 0; repeat please!";
            if (getNumber(x) < 0) { // ошибка ввода или конец файла
                matrix_delete(matrix_ptr);
                return nullptr;
            }
        } while (x == 0);


        int row;
        int column;


        error_message = "";
        do {
            std::cout << error_message << std::endl;
            std::cout << "Enter the row of the item: ";
            error_message = "Index is out of range; repeat please!";
            if (getNumber(row) < 0) { // ошибка ввода или конец файла
                matrix_delete(matrix_ptr);
                return nullptr;
            }
        } while (row < 0 || row >= matrix_ptr->m);



        error_message = "";
        do {
            std::cout << error_message << std::endl;
            std::cout << "Enter the column of the item: ";
            error_message = "Index is out of range; repeat please!";
            if (getNumber(column) < 0) { // ошибка ввода или конец файла
                matrix_delete(matrix_ptr);
                return nullptr;
            }
        } while (column < 0 || column >= matrix_ptr->n);

        if (matrix_find(matrix_ptr, row, column) != nullptr)
        {
            std::cout << "Element is this row and column is busy! This element will not be added!" << std::endl;
            continue;
        }

        Item* new_item = nullptr;
            
        try {
            new_item = new Item;
        }
        catch (std::bad_alloc& ba) {
            std::cout << "------ Can't allocate space for matrix: " << ba.what() << std::endl;
            matrix_delete(matrix_ptr);
            return nullptr;
        }

        new_item->column = column;
        new_item->row = row;
        new_item->value = x;

        matrix_add(matrix_ptr, new_item);

        std::cout << std::endl;
    }
    return matrix_ptr;
}






void Lab_1::matrix_add(Matrix*& matrix_ptr, Item*& item_ptr)
{
    if (item_ptr == nullptr || matrix_ptr == nullptr)
    {
        return;
    }

    List* list_ptr = matrix_ptr->lists_for_rows[item_ptr->row];

    if (list_ptr->head == nullptr)  //empty list
    {
        list_ptr->head = item_ptr;
        list_ptr->head->next = nullptr;
        return;
    }

    //not empty list

    Item* x = list_ptr->head;
    Item* prev = list_ptr->head;

    while (x != nullptr)
    {
        if (x->column > item_ptr->column) 
        {
            break;
        }
        prev = x;
        x = x->next;
    }

    if (x == list_ptr->head)
    {
        item_ptr->next = list_ptr->head;
        list_ptr->head = item_ptr;
        return;
    }

    item_ptr->next = x;
    prev->next = item_ptr;
    
}

int Lab_1::criterium(int x)
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
    } while (x != 0);

    if (counter >= 2)
    {
        return 1;
    }

    return 0;
}

int* Lab_1::form_vector(Lab_1::Matrix*& matrix_ptr, int (*criterium)(int))
{
    if (matrix_ptr == nullptr) 
    {
        return nullptr;
    }

    int* vector_result = nullptr;

    try {
        vector_result = new int[matrix_ptr->m];
    }
    catch (std::bad_alloc& ba) {
        std::cout << ba.what() << std::endl;
        return nullptr;
    }


    for (int i = 0; i < matrix_ptr->m; ++i)
    {
        
        int sum = 0;
        Item* x = matrix_ptr->lists_for_rows[i]->head;

        while (x != nullptr)
        {
            if (criterium(x->value))
            {
                sum += (x->value);
            }
            x = x->next;
        }
        
        vector_result[i] = sum;
    }

    return vector_result;
}

void Lab_1::matrix_print(Matrix*& matrix_ptr)
{
    if (matrix_ptr == nullptr)
    {
        std::cout << "The input was not good! Run the program again" << std::endl;
        return;
    }

    std::cout << "The restored matrix is:" << std::endl;

    for (int i = 0; i < matrix_ptr->m; ++i)
    {
        std::cout << "||\t";
        
        Item* x = matrix_ptr->lists_for_rows[i]->head;

        for (int j = 0; j < matrix_ptr->n; ++j)
        {
            if (x != nullptr && x->column == j)
            {
                std::cout << x->value << "\t";
                x = x->next;
            }
            else
            {
                std::cout << "0" << "\t";
            }
        }

        std::cout << "||";
        std::cout << std::endl;
    }

}


void Lab_1::list_delete(List*& list_ptr)
{
    if (list_ptr == nullptr)
    {
        return;
    }

    if (list_ptr->head == nullptr)
    {
        delete list_ptr;
        list_ptr = nullptr;
        return;
    }

    Item* x = list_ptr->head;
    Item* prev = x;

    while (x != nullptr)
    {
        x = x->next;

        prev->next = nullptr;
        delete prev;

        prev = x;
        
    }

    list_ptr->head = nullptr;

    delete list_ptr;
    list_ptr = nullptr;
}


void Lab_1::matrix_delete(Matrix*& matrix_ptr)
{
    if (matrix_ptr != nullptr)
    {
        for (int i = 0; i < matrix_ptr->m; ++i)
        {
            list_delete(matrix_ptr->lists_for_rows[i]);
        }

        delete[] matrix_ptr->lists_for_rows;
        
        matrix_ptr->m = 0;
        matrix_ptr->n = 0;
    }

    delete matrix_ptr;  matrix_ptr = nullptr;
}

void Lab_1::vec_print(int*& vec, int m)
{
    if (vec == nullptr)
    {
        return;
    }

    std::cout << "The resulting vector is:" << std::endl;

    for (int i = 0; i < m; ++i)
    {
        std::cout << vec[i] << " ";
    }

    std::cout << std::endl;
}

void Lab_1::vec_delete(int*& vec)
{
    delete[] vec;
    vec = nullptr;
}

Lab_1::Item* Lab_1::matrix_find(Matrix*& matrix_ptr, int i, int j)
{
    List* list_ptr = matrix_ptr->lists_for_rows[i];
    
    if (list_ptr == nullptr)
    {
        return nullptr;         //list is empty
    }
    
    Item* x = list_ptr->head;

    while (x != nullptr)
    {
        if (x->column == j) 
        {
            return x;
        }
        x = x->next;
    }

    return nullptr;
}


