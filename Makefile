KDIR = /lib/modules/`uname -r`/build
all:
	make -C $(KDIR) M=$(PWD)
	$(CC) RandNum_user_test.c -o RandNum_user_test
clean:
	make -C $(KDIR) M=$(PWD) clean
	rm RandNum_user_test
test: RandNum_user_test.c
	cc -o RandNum_user_test RandNum_user_test.c
insert: 
	sudo insmod randomNumber.ko
remove: 
	sudo rmmod randomNumber.ko
run_user:
	clear
	sudo ./RandNum_user_test
