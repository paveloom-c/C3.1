
     ## Это шаблон make-файла для компиляции программ.

     ## Репозиторий на GitHub: https://github.com/Paveloom/B1
     ## Документация: https://www.notion.so/paveloom/B1-fefcaf42ddf541d4b11cfcab63c2f018

     ## Версия релиза: 2.2.1
     ## Версия документации: 2.2.0

     ## Автор: Павел Соболев (http://paveloom.tk)

     ## Для корректного отображения содержимого
     ## символ табуляции должен визуально иметь
     ## ту же длину, что и пять пробелов.

     # Настройки make-файла

     ## Имя координатора
     make := make

     ## Указание оболочки
     SHELL := /bin/bash

     ## Указание make-файлу выполнять все правила в одном вызове оболочки
     .ONESHELL :

     ## Заглушка на вывод информации указанным правилам
     .SILENT :

     ## Правила-псевдоцели
     .PHONY : result, result-r, result-d, result-c, clean

     ## Правило, выполняющееся при вызове координатора без аргументов
     ALL : result

     # Настройки компиляции программ

     ## Компилятор
     comp := g++

     ## Флаг для указания директории для хранения .mod файлов
     module_flag := -J

     ## Расширение исходных файлов
     pattern := cpp

     ## Режим отладки (при значении true использует флаги opt_debug, при другом значении — opt_production)
     debugging := true

     ## Флаги для отладки
     opt_debug := -Og -g -Wall -Wextra -Weffc++ -Wnoexcept -Wnoexcept-type -Wregister \
                  -Wstrict-null-sentinel -Wold-style-cast -Woverloaded-virtual -Wsign-promo \
                  -Wmultiple-inheritance -Wvirtual-inheritance -Wnamespaces -Wzero-as-null-pointer-constant \
                  -Wconditionally-supported -Wextra-semi -Wsized-deallocation -Wsuggest-final-types \
                  -Wsuggest-final-methods -Wsuggest-override -Wuseless-cast -Wdouble-promotion \
                  -Wformat=2 -Wformat-overflow=2 -Wformat-signedness -Wformat-truncation=2 \
                  -Wuninitialized -Wmissing-include-dirs -Wshift-overflow=2 -Wswitch-default -Wswitch-enum \
                  -Wunused-parameter -Wunused-const-variable=2 -Wstrict-overflow=5 -Wstringop-overflow=4 \
                  -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wmissing-noreturn \
                  -Wsuggest-attribute=malloc -Wsuggest-attribute=format -Wmissing-format-attribute \
                  -Wsuggest-attribute=cold -Walloc-zero -Walloca -Wconversion -Wfloat-conversion -Wsign-conversion \
                  -Warray-bounds=2 -Wattribute-alias=2 -Wduplicated-branches -Wduplicated-cond -Wno-div-by-zero \
                  -Wtrampolines -Wfloat-equal -Wshadow -Wunsafe-loop-optimizations -Wundef -Wunused-macros \
                  -Wcast-qual -Wcast-align=strict -Wdate-time -Wlogical-op -Wmissing-declarations \
                  -Wpacked -Wpadded -Wredundant-decls -Winline -Winvalid-pch -Wvector-operation-performance -Wvla \
                  -Wdisabled-optimization -Wstack-protector -Wctor-dtor-privacy \
                  -fstack-clash-protection -fstack-protector-all -pedantic-errors -std=c++2a

     ## Флаги для финальной сборки
     opt_production := -Ofast

     ## Имя главной программы
     main_name := main

     ## Использовать input файл?
     use_input := false

     ## Использовать output файл?
     use_output := false

     ## Сохранять собранную программу при очистке?
     save_main := false

     ## Директория с исходными файлами (всегда в окончании прямой слеш; точка-слеш, если хранить в текущей директории)
     source_path := ../

     ## Указание поддиректорий в директории с исходными файлами (всегда в окончании прямой слеш)
     subs := program/

     ## Директория с объектными файлами (всегда в окончании прямой слеш; точка-слеш, если хранить в текущей директории)
     obj_path := obj/

     ## Правила-зависимости (при необходимости)

     # Определение флагов компилятора

     ifeq (true, $(debugging))
          opt := $(opt_debug)
     else
          opt := $(opt_production)
     endif

     # Распределение исходных файлов по переменным

     ## Добавление суффикса к поддиректориям
     prefixed_subs = $(addprefix $(source_path), $(subs))

     ## Директории, где искать исходные файлы
     VPATH := $(source_path) $(prefixed_subs)

     ## Определение директорий для поиска заголовочных файлов
     include_dirs := -I$(source_path) $(addprefix -I, $(prefixed_subs))

     ## Получение полного списка исходных файлов

     allpattern := $(addsuffix *.$(pattern), $(VPATH))
     source := $(wildcard $(allpattern))

     main_source := $(filter %$(main_name).$(pattern), $(source))

     ## Смена пути исходных файлов

     obj_path_source := $(addprefix $(obj_path), $(notdir $(source)))

     ## Получение списка .mod файлов и .o файлов, связанных с модулями. Объектный
     ## файл для главной программы записан в переменную obj_main для сохранения
     ## общности семантики.

     mod := $(filter-out %$(main_name).mod, $(patsubst %.$(pattern), %.mod, $(obj_path_source)))
     obj_mod := $(patsubst %.mod, %.o, $(mod))

     obj_main := $(patsubst %.$(pattern), %.o, $(filter %$(main_name).$(pattern), $(obj_path_source)))

     # Блок правил для компиляции объектных файлов

     $(main_name) : $(obj_main) $(obj_mod)
	               $(comp) $(opt) $(include_dirs) $^ -o $@

     $(obj_path)%.o : %.$(pattern)
	                 $(comp) -c $(opt) $(include_dirs) $(module_flag) $(obj_path) \
                      $< -o $(addprefix $(obj_path), $(subst .$(pattern),.o, $(notdir $<)))

     $(obj_main) : $(main_source)
	              $(comp) -c $(opt) $(include_dirs) $(module_flag) $(obj_path) \
                   $< -o $(addprefix $(obj_path), $(notdir $@))

     # Блок правил для сборки программы

     input :
	        touch input

     result : $(main_name)
	         if [ "true" = "$(use_input)" ]; then
	              $(make) input;
	              if [ "true" = "$(use_output)" ]; then
	                   time ./$< < input > output;
	              else
	                   time ./$< < input;
	              fi
	         else
	              if [ "true" = "$(use_output)" ]; then
	                   time ./$< > output;
	              else
	                   time ./$<;
	              fi
	         fi

     result-r :
	           if [ "true" != "$(use_output)" ]; then
	                echo; echo "Вы не можете использовать это правило, пока значение переменной use_output != true."; echo;
	                exit 1;
	           fi
	           $(make) result
	           cat output

     result-d :
	           $(make) result
	           $(make) clean

     result-c :
	           if [ "true" != "$(use_output)" ]; then
	                echo; echo "Вы не можете использовать это правило, пока значение переменной use_output != true."; echo;
	                exit 1;
	           fi
	           $(make) result-r
	           $(make) clean

     # Правило для очистки
     clean :
	        if [ "true" = "$(save_main)" ]; then
	             rm -f $(obj_main) $(obj_mod) $(mod);
	        else
	             rm -f $(obj_main) $(obj_mod) $(mod) $(main_name);
	        fi
