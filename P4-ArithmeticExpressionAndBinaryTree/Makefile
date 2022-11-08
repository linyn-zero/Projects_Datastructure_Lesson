obj = main.o ExpressionManager.o

main : $(obj)
	cc -o main $(obj)

$(obj) : ExpressionManager.h

.PHONY : clean
clean : 
	cat main.cpp
	-rm main $(obj)