				ĐỒ ÁN 2 MÔN HỆ ĐIỀU HÀNH
			TÌM HIỂU VÀ LẬP TRÌNH LINUX KERNEL MODULE
Phan Xuân Bảo - 18120287
Lê Nguyên Tuấn - 18120631
Phạm Viết Xuân - 18120658
	-------------------------------------------------------------------------------
Nội dung đồ án:
Mục tiêu hiểu về Linux kernel module và hệ thống quản lý file và device trong linux, giao tiếp giữa tiến trình ở user space và code kernel space:
	- Viết một module dùng để tạo ra số ngẫu nhiên. 
	- Module này sẽ tạo một character device để cho phép các tiến trình ở userspace có thể open và read các số ngẫu nhiên.
	-------------------------------------------------------------------------------
1. Tổ chức file trong đồ án
- Kbuild
- Makefile
- randomNumber.c
- RanNum_user_test.c
2. Cách thức gắn module vào kernel và chạy chương trình người dùng
( linux kernel cần được install make )
Bước 1: make all
Bước 2: make ínsert
Bước 3: make test
Bước 4: make run_user
Bước 5: make remove ( nếu muốn gỡ module ra khỏi kernel)

Chú thích: Các lệnh make ____ là lệnh rút ngắn của các lệnh sau được viết vào file Makefile
- make insert: sudo insmod randNumber.ko --> Lệnh này dùng để gắn module đã tạo vào kernel
- make remove: sudo rmmod randNumber.ko --> Lệnh này dùng để gỡ module đã gắn vào kernel
- make test: cc -o RandNum_user_test RandomNumber_user_test.c --> Lệnh này để tạo chương trình người dùng từ file RandNum_user_test.c
- make run_user: sudo ./RandNum_user_test --> Lệnh này dùng để chạy chương trình user từ file RandNum_user_test.o đã tạo từ lệnh make t
	-----------------------------------------------------------------------------
Xem các thông tin về module 
- $ modinfo randomNumber.ko --> Xem thông tin của module
- $ lsmod | grep randomNumber.ko --> Kiểm tra xem module đã được nạp hay chưa
- $ dmesg --> xem quá trình module chạy 
