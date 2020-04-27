#ifndef _SCATS_DEALLOCATE_
#define _SCATS_DEALLOCATE_

// Процедура для общего освобождения памяти
inline void SCATS_API::deallocate()
{
     // Освобождение памяти из-под входных данных
     input.deallocate();
}

#endif // _SCATS_DEALLOCATE_