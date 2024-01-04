#/bin/bash
while :
do
	#clang main.c operations*.c parser.c utils.c order*.c  -o push_swap
	ARG=$(seq -1000 1000 | sort -R | tail -n 500 | tr '\n' ' ')
	# echo $ARG
	# time ./push_swap $ARG
	./push_swap $ARG | wc -l
	#./push_swap $ARG | ./checker_linux $ARG
	./push_swap $ARG | ./checker $ARG

	sleep .5
done
