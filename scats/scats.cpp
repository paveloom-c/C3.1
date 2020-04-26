#include <pybind11/pybind11.h> // Функции связывания
#include <pybind11/stl.h>      // STL контейнеры

// #include <string>

#include "prec.h"
#include "scats.h"
#include "input/scats_input.h"

namespace py = pybind11;

PYBIND11_MODULE(scats, m)
{
    py::class_<SCATS_API> scats(m, "api", R"delim(

Экземпляр API для спектрально-корелляционного анализа временных рядов.

)delim");

    scats.def(py::init())

        .def_readonly("input", &SCATS_API::input, R"delim(
Тип: input_struct<RT>;
Описание: Экземпляр API для взаимодействия с входными данными.
        )delim")

        .def("read_input", &SCATS_API::read_input, py::arg("file"), R"delim(
Процедура для считывания входных данных из файла.

Аргументы:
    file (str): Имя файла для считывания.
)delim")

        .def("deallocate", &SCATS_API::deallocate, R"delim(
Вспомогательная процедура для общего освобождения памяти.
        )delim");

    py::class_<input_struct<RT>>(m, "input", R"delim(
Экземпляр API для взаимодействия с входными данными.

Именования типов:
    typedef T *iterator;
    typedef const T *const_iterator;
    typedef size_t size_type;
    typedef T value_type.

Доступные данные:
    q (value_type): Уровень значимости;
    t (std::vector<T>): Массив времени;
    x (std::vector<T>): Массив значений.

)delim")

        .def_readwrite("N", &input_struct<RT>::N, R"delim(
Тип: size_type;
Описание: Размер выборки.
        )delim")

        .def_readwrite("delta_t", &input_struct<RT>::delta_t, R"delim(
Тип: value_type;
Описание: Шаг выборки.
        )delim")

        .def_readwrite("q", &input_struct<RT>::q, R"delim(
Тип: value_type;
Описание: Уровень значимости.
        )delim")

        .def_readwrite("t", &input_struct<RT>::t, R"delim(
Тип: value_type;
Описание: Массив времени.
        )delim")

        .def_readwrite("x", &input_struct<RT>::x, R"delim(
Тип: value_type;
Описание: Массив значений.
        )delim");
}