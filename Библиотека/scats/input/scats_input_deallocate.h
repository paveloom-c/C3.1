#ifndef GUARD_scats_input_deallocate
#define GUARD_scats_input_deallocate

// Процедура для освобождения памяти из-под входных данных
template <typename T>
inline void input_struct<T>::deallocate()
{
     if (t.size() != 0)
          t.clear();

     if (x.size() != 0)
          x.clear();
}

#endif