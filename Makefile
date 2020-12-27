ll_tests:
	gcc -g ll_tests.c -o ll_tests.out
bst_tests:
	gcc -g bst_tests.c -o bst_tests.out
dynarr_tests:
	gcc -g dynarr_tests.c -o dynnarr_tests.out
ht_tests:
	gcc -g hashtable_tests.c -o ht_tests.out
clean:
	rm *.out
