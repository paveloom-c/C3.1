
     ## Это шаблон* make-файла для публикации кода на GitHub.

     ## * Изменен для данного репозитория.

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
     .PHONY : git, git-am, new, del, final, archive

     ## Правило, выполняющееся при вызове координатора без аргументов
     ALL : develop


     # Блок правил для сборки, публикации, демонстрации и удаления модуля

     ## Правило для сборки и установки пакета
     install :
	          pip3 install .

     ## Правило для установки версии с TestPyPI
     install-testpypi :
	                   python3 -m pip install -r requirements
				    python3 -m pip install pybind11
	                   python3 -m pip install --no-cache-dir --index-url https://test.pypi.org/simple/ --no-deps scats

     ## Правило для установки версии с PyPI
     install-pypi :
	               python3 -m pip install -r requirements
	               python3 -m pip install --no-cache-dir scats

     ## Правило для установки версии для разработчика
     develop :
	          pip3 install -e .

     ## Правило для подготовки архивов для публикации
     dist :
	       python3 setup.py sdist

     ## Правило для удаления архивов для публикации
     dist-clean :
	             rm -rf dist

     ## Правило для загрузки архивов на PyPI
     upload :
	         python3 -m twine upload dist/*

     ## Правило для загрузки архивов на TestPyPI
     upload-test :
	              python3 -m twine upload --repository testpypi dist/*

     ## Правило для запуска скрипта examples/example.py
     example :
	          cd examples && python3 main.py && cd ../

     ## Правило для удаления локальной сборки
     clean :
	        rm -rf build src/scats/scats.egg-info src/scats/*.so \
	        src/scats/__pycache__ build tmp

     ## Правило для удаления модуля
     uninstall :
	            pip3 uninstall scats


     # Блок правил для разработки и публикации кода на GitHub

     ## Имя пользователя на GitHub
     username := Paveloom

     ## Имя ветки изменений
     feature_branch := feature

     ## Правило для создания и публикации коммита
     git :

	      # Определение текущей ветки
	      CURRENT_BRANCH=$$(git status | head -n 1 | cut -d " " -f 3)

	      # Проверка текущей ветки
	      if [ "$$CURRENT_BRANCH" = "${feature_branch}" ]; then

	           # Определение последнего тега
	           LAST_TAG=$$(git describe --tag)

	           # Проверка наличия тега у предыдущего коммита
	           if echo $$LAST_TAG | grep -qv "-"; then

	                # Определение номера сгенерированного ранее тега
	                CURRENT_NUMBER=$$(echo $$LAST_TAG | grep -o "_[0-9]\+" | sed 's/_//')

	                # Проверка наличия сгенерированного ранее тега
	                if echo $$LAST_TAG | grep -q "_[0-9]\+"; then

	                     # Прибавление к текущему номеру единицы
	                     NEXT_NUMBER=$$(( $$CURRENT_NUMBER + 1 ))

	                     # Формирование нового тега
	                     NEXT_TAG=$$(echo $$LAST_TAG | sed "s/_$$CURRENT_NUMBER/_$$NEXT_NUMBER/")

	                     git add -A
	                     git commit -e

	                     # Проверка, был ли создан коммит
	                     if [ $$? -eq 0 ]; then

	                          git tag -a $$NEXT_TAG -m "$$NEXT_TAG"
	                          git tag -d $$LAST_TAG
	                          git push origin :$$LAST_TAG
	                          git push --follow-tags

	                     fi

	                else

	                     # Формирование нового тега
	                     NEXT_TAG=$$(echo "$$LAST_TAG _${feature_branch}_1" | sed "s/\ //")

	                     git add -A
	                     git commit -e

	                     # Проверка, был ли создан коммит
	                     if [ $$? -eq 0 ]; then

	                          git tag -a $$NEXT_TAG -m "$$NEXT_TAG"
	                          git push --follow-tags

	                     fi

	                fi

	           else

	                git add -A
	                git commit -e

	                # Проверка, был ли создан коммит
	                if [ $$? -eq 0 ]; then
	                     git push
	                fi

	           fi

	      else

	           git add -A
	           git commit -e

	           # Проверка, был ли создан коммит
	           if [ $$? -eq 0 ]; then
	                git push
	           fi

	      fi

     ## Правило для обновления последнего коммита до текущего состояния локального репозитория
     git-am :
	         git add -A
	         git commit --amend

	         # Проверка, был ли создан коммит
	         if [ $$? -eq 0 ]; then

	              git push --follow-tags --force-with-lease

	         fi

     ## Правило для создания ветки изменений
     new :
	      git checkout -q master
	      git checkout -b $(feature_branch)
	      git push -u origin $(feature_branch)

     ## Правило для удаления текущей ветки изменений локально
     del :
	      git checkout -q master
	      git branch -D $(feature_branch)

     # Правило для удаления последнего тега
     # на ветке изменений локально и удаленно
     final :

	        # Определение текущей ветки
	        CURRENT_BRANCH=$$(git status | head -n 1 | cut -d " " -f 3)

	        # Проверка текущей ветки
	        if [ "$$CURRENT_BRANCH" = "${feature_branch}" ]; then

	             # Определение последнего тега
	             LAST_TAG=$$(git describe --tag)

	             # Удаление последнего тега удаленно
	             git push origin :$$LAST_TAG

	             # Удаление последнего тега локально
	             git tag -d $$LAST_TAG

	        fi

     # Правило для создания архивов
     archive :
	          find lib/ -path '*/*' -type f -print | zip archives/lib.zip -FS -q -@
			find src/ -path '*/*' -type f -print | zip archives/src.zip -FS -q -@
	          find examples/ -path '*/.*' -prune -o -type f -print | zip archives/examples.zip -FS -q -@
