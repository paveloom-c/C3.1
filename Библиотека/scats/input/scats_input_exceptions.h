#ifndef _SCATS_INPUT_EXCEPTIONS_
#define _SCATS_INPUT_EXCEPTIONS_

// Заголовочный файл, объявляющий вспомогательные процедуры
// для выдачи исключений, связанных с входными данными

#include <iostream> // Операции стандартного вывода
#include <fstream>  // Операции считывания из файла
#include <string>   // Строки

// Набор строковых литералов, описывающих ошибки
static const std::string W_O("Не удалось открыть файл для считывания.");
static const std::string WR_N("Не удалось считать значение размера выборки.");
static const std::string WR_delta_t("Не удалось считать значение шага выборки.");
static const std::string WR_q("Не удалось считать значение уровня значимости.");
static const std::string WR_t("Не удалось считать одно из значений массива времени.");
static const std::string WR_x("Не удалось считать одно из значений массива значений.");
static const std::string W_EOF("Неожиданный конец файла.");

// Максимальное число символов в строке потока
static const long int m = std::numeric_limits<std::streamsize>::max();

// Определение класса для захвата исключений
struct scats_input_exception : public std::runtime_error
{
     // Переопределение конструктора (аргументы: сообщение, имя файла)
     explicit inline scats_input_exception(const std::string &message, const std::string &cpp_file = "source_file")
         : std::runtime_error("\n     " + message + '\n' + "     (" + cpp_file + ")\n\n") {}
};

// Переопределение класса для захвата исключений для файла scats_input_read.cpp
struct scats_input_read_exception : public scats_input_exception
{
     // Переопределение конструктора
     explicit inline scats_input_read_exception(const std::string &message)
         : scats_input_exception(message, "scats_input_read_exception") {}
};

// Переопределение класса для захвата исключений для файла scats_input_read.cpp (для элемента массива)
struct scats_input_read_element_exception : public scats_input_exception
{
     // Переопределение конструктора
     explicit inline scats_input_read_element_exception(const std::string &message, const size_t &i)
         : scats_input_exception(message, "scats_input_read_element_exception: элемент " + std::to_string(i)) {}
};

// Процедура для проверки на конец файла
inline void check_eof(const std::ifstream &in)
{
     if (in.eof())
          throw scats_input_read_exception(W_EOF);
}

// Процедура для пропуска строки
inline void skip_line(std::ifstream &in)
{
     in.ignore(m, '\n');
     check_eof(in);
}

// Процедура для пропуска двух строк
inline void skip_two_lines(std::ifstream &in)
{
     in.ignore(m, '\n');
     check_eof(in);

     in.ignore(m, '\n');
     check_eof(in);

     in.ignore(m, '\n');
     check_eof(in);
}

// Процедура для проверки, открылся ли файл
inline void check_if_open(const std::ifstream &in)
{
     if (!in.is_open())
          throw scats_input_read_exception(W_O);
}

#endif // _SCATS_INPUT_EXCEPTIONS_