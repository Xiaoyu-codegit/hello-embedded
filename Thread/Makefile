C:=gcc

create:create.c
	-$(CC) -o $@ $< -pthread
	-./$@
	-rm ./$@

pthread_join:pthread_join.c
	-$(CC) -o $@ $< -pthread
	-./$@
	-rm ./$@

pthread_detach:pthread_detach.c
	-$(CC) -o $@ $< -pthread
	-./$@
	-rm ./$@

pthread_cancel_deferr:pthread_cancel_deferr.c
	-$(CC) -o $@ $< -pthread
	-./$@
	-rm ./$@

pthread_cancel_async:pthread_cancel_async.c
	-$(CC) -o $@ $< -pthread
	-./$@
	-rm ./$@

pthread_cancel_disable:pthread_cancel_disable.c
	-$(CC) -o $@ $< -pthread
	-./$@
	-rm ./$@

race:race.c
	-$(CC) -o $@ $< -pthread
	-./$@
	-rm ./$@

mutex:mutex.c
	-$(CC) -o $@ $< -pthread
	-./$@
	-rm ./$@

rwlock_unlock:rwlock_unlock.c
	-$(CC) -o $@ $< -pthread
	-./$@
	-rm ./$@

rwlock:rwlock.c
	-$(CC) -o $@ $< -pthread
	-./$@
	-rm ./$@

rwlock_alter:rwlock_alter.c
	-$(CC) -o $@ $< -pthread
	-./$@
	-rm ./$@

rwlock_hungry:rwlock_hungry.c
	-$(CC) -o $@ $< -pthread
	-./$@
	-rm ./$@

rwlock_hungry_solve:rwlock_hungry_solve.c
	-$(CC) -o $@ $< -pthread
	-./$@
	-rm ./$@

condition:condition.c
	-$(CC) -o $@ $< -pthread
	-./$@
	-rm ./$@

unname_race_thread:unname_race_thread.c
	-$(CC) -o $@ $< -pthread
	-./$@
	-rm ./$@

unname_race_thread_solve:unname_race_thread_solve.c
	-$(CC) -o $@ $< -pthread
	-./$@
	-rm ./$@

unname_race_process:unname_race_process.c
	-$(CC) -o $@ $< -lrt -pthread
	-./$@
	-rm ./$@

unname_race_process_slove:unname_race_process_slove.c
	-$(CC) -o $@ $< -lrt -pthread
	-./$@
	-rm ./$@

unname_count_thread:unname_count_thread.c
	-$(CC) -o $@ $< -lrt -pthread
	-./$@
	-rm ./$@

unname_count_process:unname_count_process.c
	-$(CC) -o $@ $< -lrt -pthread
	-./$@
	-rm ./$@

name:name.c
	-$(CC) -o $@ $< -lrt -pthread
	-./$@
	-rm ./$@

name_count:name_count.c
	-$(CC) -o $@ $< -lrt -pthread
	-./$@
	-rm ./$@

thread_pool:thread_pool.c
	-$(CC) -o $@ $< `pkg-config --cflags --libs glib-2.0`
	-./$@
	-rm ./$@