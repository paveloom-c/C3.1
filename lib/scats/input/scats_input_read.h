#ifndef _SCATS_INPUT_READ_
#define _SCATS_INPUT_READ_

#include <iostream>  // Операции стандартного вывода
#include <fstream>   // Операции считывания из файла
#include <string>    // Строки
#include <iterator>  // Итераторы
#include <algorithm> // std::copy
#include <iomanip>   // Манипуляторы
#include <vector>    // Вектора

#include "prec.h"                   // Типы, используемые в программе
#include "scats_input_exceptions.h" // Вспомогательные процедуры для
                                    // получения исключений

// Процедура для считывания входных данных из файла
template <typename T>
void input_struct<T>::read(const char *file)
{
     // Создание временной переменной
     // для считывания элементов массивов
     input_struct::value_type tmp;

     std::ifstream in(file);
     check_if_open(in);

     skip_line(in); // Пропуск строки

     if (!(in >> N)) // Считывание размера выборки
          throw scats_input_read_exception(WR_N);
     check_eof(in);

     skip_two_lines(in); // Пропуск двух строк

     if (!(in >> delta_t)) // Считывание шага выборки
          throw scats_input_read_exception(WR_delta_t);
     check_eof(in);

     skip_two_lines(in); // Пропуск двух строк

     if (!(in >> q)) // Считывание шага выборки
          throw scats_input_read_exception(WR_q);
     check_eof(in);

     skip_two_lines(in); // Пропуск двух строк

     // Проверка, совпадает ли текущий
     // размер массива времени с необходимым
     if (t.size() != N && t.size() != 0)
     {
          t.clear();
          t.reserve(N);
     }
     else if (t.size() == 0)
     {
          t.reserve(N);
     }

     // Считывание массива времени
     for (input_struct::size_type i = 0; i != N; i++)
     {
          if (!(in >> tmp))
               throw scats_input_read_element_exception(WR_t, i);
          t.push_back(tmp);
     }
     check_eof(in);

     // Проверка, совпадает ли текущий
     // размер массива значений с необходимым
     if (x.size() != N && x.size() != 0)
     {
          x.clear();
          x.reserve(N);
     }
     else if (x.size() == 0)
     {
          x.reserve(N);
     }

     skip_two_lines(in);

     // Считывание массива значений
     for (input_struct::size_type i = 0; i != N; i++)
     {
          if (!(in >> tmp))
               throw scats_input_read_element_exception(WR_x, i);
          x.push_back(tmp);
     }
     check_eof(in);
}

#endif // _SCATS_INPUT_READ_