#include <pybind11/pybind11.h> // Функции связывания
#include <pybind11/stl.h>      // STL контейнеры

#include "prec.h"  // Точность вещественных чисел
#include "scats.h" // API модуля

namespace py = pybind11;

static char *scats_api = "Экземпляр API для спектрально-корелляционного анализа временных рядов.";
static char *scats_api_init = "Стандартный конструктор.";
static char *scats_api_input = "Тип: input_struct<RT>;\nОписание: Экземпляр API для взаимодействия с входными данными.";
static char *scats_api_read_input = "Процедура для считывания входных данных из файла.\n\n\
Аргументы:\n    file (str): Имя файла для считывания.";
static char *scats_api_deallocate = "Вспомогательная процедура для общего освобождения памяти.";

static char *input_struct_help = "Экземпляр API для взаимодействия с входными данными.\n\n\
Именования типов:\n\
    typedef size_t size_type;\n\
    typedef RT value_type.\n";
static char *input_struct_N = "Тип: size_type;\nОписание: Размер выборки.";
static char *input_struct_delta_t = "Тип: value_type;\nОписание: Шаг выборки.";
static char *input_struct_q = "Тип: value_type;\nОписание: Уровень значимости.";
static char *input_struct_t = "Тип: std::vector<value_type>;\nОписание: Массив времени.";
static char *input_struct_x = "Тип: std::vector<value_type>;\nОписание: Массив значений.";

// Модуль SCATS
PYBIND11_MODULE(scats, m)
{
    // API модуля
    py::class_<SCATS_API>(m, "api", scats_api)
        .def(py::init(), scats_api_init)
        .def_readonly("input", &SCATS_API::input, scats_api_input)
        .def("read_input", &SCATS_API::read_input, py::arg("file"), scats_api_read_input)
        .def("deallocate", &SCATS_API::deallocate, scats_api_deallocate);

    // Входные данные
    py::class_<input_struct<RT>>(m, "input", input_struct_help)
        .def_readwrite("N", &input_struct<RT>::N, input_struct_N)
        .def_readwrite("delta_t", &input_struct<RT>::delta_t, input_struct_delta_t)
        .def_readwrite("q", &input_struct<RT>::q, input_struct_q)
        .def_readwrite("t", &input_struct<RT>::t, input_struct_t)
        .def_readwrite("x", &input_struct<RT>::x, input_struct_x);
}