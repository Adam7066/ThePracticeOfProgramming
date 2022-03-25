all:
	make -C ./code
	make clean -C ./code
	python merge.py

.PHONY: clean
clean:
	${RM} -r merge.cpp