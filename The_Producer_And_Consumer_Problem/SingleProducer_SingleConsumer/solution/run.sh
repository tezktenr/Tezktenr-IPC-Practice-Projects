make
#valgrind --track-origins=yes --leak-check=full ./Producer &
#valgrind --track-origins=yes --leak-check=full ./Consumer &
./Producer &
./Consumer &
wait
