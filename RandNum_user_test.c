#include <stdio.h>
#include <errno.h> //Required for errno(line 16)
#include <unistd.h>  //Require for read
#include <fcntl.h>   // Required for O_RDONLY

int main()
{
	int f, randNum;
	printf("\n                 DO AN 2 - HE DIEU HANH                        \n");
	printf("            1. Phan Xuan Bao   -   18120287                      \n");
	printf("            2. Le Nguyen Tuan  -   18120631                      \n");
	printf("            3. Pham Viet Xuan  -   18120658                      \n");
	printf("\n              GENARATIVE A RANDOM NUMBER                       \n");
	printf("                                                                 \n");

	printf("\nStart random.\n");

	// Mo file voi che cho Read Only
	f = open("/dev/RandomNumber", O_RDONLY); 
	if (f < 0){
		perror("Open the device faile. Error: ");
		return errno;
	}

	// doc randNum tu file fd, tra ve gia tri random
	read(f, &randNum, sizeof(randNum));
	
	printf("Random number = %d\n\n", randNum);
	printf("Complete task!\n");
	return 0;       	
}
