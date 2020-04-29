#include "../scats.h" // Подключение API модуля SCATS

int main()
{

     try
     {
          // Создание экземпляра API
          SCATS_API s;

          // Считывание входных данных из файла
          s.input.read("../../../examples/files/input");

          return 0;
     }
     catch (...)
     {
          return 0;
     }
}
