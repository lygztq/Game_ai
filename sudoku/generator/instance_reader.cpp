#include "instance_reader.h"

instance_reader::instance_reader(int seed)
{
	/**
	read instances from file, valid seed range from 0 to 19
	*/
	sprintf(file_path, "instances/instance%d.txt", seed);
	FILE *file_ptr = fopen(file_path,"r");

	char *buffer;
	fseek(file_ptr,0,SEEK_END);
	int len = ftell(file_ptr);
	buffer = new char[len];
	rewind(file_ptr);
	fread(buffer,1,len,file_ptr);
	buffer[len] = '\0';
	fclose(file_ptr);

	int index = 0,
		curr = 0;
	while(index < ELEMENT_NUM && curr < len)
	{
		if(buffer[curr]>='0' && buffer[curr]<='9')
		{
			instance[index/BOARD_SIZE][index%BOARD_SIZE] = (buffer[curr] - '0');
			++index;
		}
		++curr;
	}
}

