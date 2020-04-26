#ifndef _SCATS_
#define _SCATS_

#include "prec.h"
#include "input/scats_input.h"

// API модуля SCATS: спектрально-корреляционный анализ временных рядов
struct SCATS_API
{
     input_struct<RT> input; // Экземпляр API для взаимодействия с входными данными

     SCATS_API() : input{} {} // Конструктор
     ~SCATS_API() {}          // Деструктор

     // Процедура для общего освобождения памяти
     inline void deallocate();

     // Процедура для считывания входных данных
     void read_input(const char *);

private:
     // Оператор копирования (запрещен)
     SCATS_API(const SCATS_API &);

     // Оператор присваивания (запрещен)
     void operator=(const SCATS_API &);
};

// Определение процедуры для
// общего освобождения памяти
#include "api/scats_deallocate.h"
#include "api/scats_read_input.h"

#endif // _SCATS_