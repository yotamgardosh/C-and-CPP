CFLAGS = -Wall -Wextra -g

tweets:
	gcc $(CFLAGS) tweets_generator.c markov_chain.c linked_list.c -o tweets_generator # README - changed

snake:
	gcc $(CFLAGS) snakes_and_ladders.c markov_chain.c linked_list.c -o snakes_and_ladders # README - changed


tweets_generator.o: tweets_generator.c markov_chain.h linked_list.h
	gcc $(CFLAGS) -c tweets_generator.c


snakes_and_ladders.o: snakes_and_ladders.c markov_chain.h linked_list.h
	gcc $(CFLAGS) -c snakes_and_ladders.c


linked_list.o: linked_list.c linked_list.h
	gcc $(CFLAGS) -c linked_list.c


markov_chain.o: markov_chain.c markov_chain.h linked_list.h
	gcc $(CFLAGS) -c markov_chain.c