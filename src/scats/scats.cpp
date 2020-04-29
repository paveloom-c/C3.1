#include <pybind11/pybind11.h> // Функции связывания
#include <pybind11/stl.h>      // STL контейнеры

#include "prec.h"  // Точность вещественных чисел
#include "scats.h" // API модуля

#include <string> // Строки

namespace py = pybind11; // Пространство имен pybind11

// Модуль SCATS
PYBIND11_MODULE(scats, m)
{

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif

    // Описание модуля
    m.doc() = "Модуль для выполнения спектрально-корреляционного анализа временных рядов";

    // Вывод версии модуля
    m.def(
        "version", [] { return VERSION_INFO; }, "Метод для вывода версии модуля SCATS");

    // Регистрация исключений
    py::register_exception<scats_input_read_exception>(m, "input_read_exception");
    py::register_exception<scats_input_read_element_exception>(m, "input_read_element_exception");

    // API модуля
    py::class_<SCATS_API>(m, "api", "Экземпляр API для спектрально-корелляционного анализа временных рядов")
        .def(py::init())
        .def_readonly("input", &SCATS_API::input, R"delim(
        Экземпляр класса :class:`scats.input` для взаимодействия с входными данными
        )delim")
        .def(
            "read_input", [](SCATS_API &api, const char *file) { api.input.read(file); }, R"delim(
        Процедура для считывания входных данных из файла (alias :func:`scats.input.read`)

        Args:
            file (str): Имя файла для считывания.

        Raises:
            input_read_exception: Не удалось открыть / закрыть файл или не удалось считать :attr:`scats.input.N`, :attr:`delta_t` или :attr:`q`.
            input_read_element_exception: Не удалось считать один из элементов массивов :attr:`scats.input.t` и :attr:`scats.input.x`.
        )delim")
        .def("deallocate", &SCATS_API::deallocate, "Вспомогательная процедура для общего освобождения памяти");

    // Входные данные
    py::class_<input_struct<RT>>(m, "input", "Интерфейс для взаимодействия с входными данными.")
        .def(py::init())
        .def_readwrite("N", &input_struct<RT>::N, "int: Размер выборки.")
        .def_readwrite("delta_t", &input_struct<RT>::delta_t, "float: Шаг выборки.")
        .def_readwrite("q", &input_struct<RT>::q, "float: Уровень значимости.")
        .def_readwrite("t", &input_struct<RT>::t, "array[N]: Массив времени.")
        .def_readwrite("x", &input_struct<RT>::x, "array[N]: Массив значений.")
        .def("read", &input_struct<RT>::read, py::arg("file"), R"delim(
        Процедура для считывания входных данных из файла

        Args:
            file (str): Имя файла для считывания.

        Raises:
            input_read_exception: Не удалось открыть / закрыть файл или не удалось считать :attr:`scats.input.N`, :attr:`delta_t` или :attr:`q`.
            input_read_element_exception: Не удалось считать один из элементов массивов :attr:`scats.input.t` и :attr:`scats.input.x`.
        )delim")
        .def("deallocate", &input_struct<RT>::deallocate, "Процедура для освобождения памяти из-под входных данных");
}