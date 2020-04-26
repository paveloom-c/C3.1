#include "../input/scats_input_exceptions.h" // Исключения для входных данных

// Процедура для считывания входных данных
void SCATS_API::read_input(const char *file)
{
     try
     {
          input.read(file);
     }
     catch (const scats_input_read_exception &fail)
     {
          std::clog << fail.what();
          throw;
     }
     catch (const scats_input_read_element_exception &fail)
     {
          std::clog << fail.what();
          throw;
     }
}