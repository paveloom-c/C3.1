#ifndef _SCATS_INPUT_
#define _SCATS_INPUT_

// Заголовочный файл, содержащий
// описание класса входных данных

#include <vector> // Вектора

// Класс входных данных
template <typename T>
struct input_struct
{
     // Введение стандартных именований типов
     typedef T *iterator;
     typedef const T *const_iterator;
     typedef size_t size_type;
     typedef T value_type;

     size_type N; // Размер выборки

     value_type delta_t; // Шаг выборки
     value_type q;       // Уровень значимости

     std::vector<T> t; // Массив времени
     std::vector<T> x; // Массив значений

     input_struct() : N{0}, delta_t{0}, q{0}, t{}, x{} {} // Конструктор
     ~input_struct() {}                                   // Деструктор

     // Процедура для освобождения памяти из-под входных данных
     inline void deallocate();

     // Процедура для считывания входных данных из файла
     void read(const char *file);

private:
     // Оператор копирования (запрещен)
     input_struct(const input_struct &);

     // Оператор присваивания (запрещен)
     void operator=(const input_struct &);
};

#include "scats_input_read.h"       // Определение процедуры для считывания входных данных из файла
#include "scats_input_deallocate.h" // Определение процедуры для освобождения памяти из-под входных данных

#endif // _SCATS_INPUT_