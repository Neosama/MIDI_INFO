
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>

#include "lib.h"

int main()
{

	FILE *fp;
	errno_t err;
	std::string data_file = "";
	std::string hex_data_file = "";


	if ((err = fopen_s(&fp, "MIDI_sample.mid", "rb")) != 0)
	{
		printf("File was not opened\n");
		return -1;
	}
	else
	{
		char buf_read[12] = { 0 };
		int size_read = 0;
		while (size_read = fread_s(buf_read, sizeof(buf_read), 1, 1, fp))
		{
			data_file += char_to_string(buf_read, size_read);
		}
	}
	fclose(fp);

	hex_data_file = string_hex(data_file, TRUE);

	if (hex_data_file.substr(0, 8) == "4D546864")
		printf("ID =\'MThd\' OK\n");
	else
		return -2;

	printf("Length of header data = %s\n", hex_data_file.substr(8, 8).c_str());

	if (hex_data_file.substr(16, 4) == "0000")
		printf("Format specification = one, single multi-channel track\n");
	else
		if (hex_data_file.substr(16, 4) == "0001")
			printf("Format specification = one or more simultaneous tracks\n");
		else
			if (hex_data_file.substr(16, 4) == "0002")
				printf("Format specification = one or more sequentially independent single - track patterns\n");
			else
				return -3;

	printf("MTrk chunks = %s\n", hex_data_file.substr(20, 4).c_str());
	printf("Delta-time in millisecond = %s\n", hex_data_file.substr(24, 4).c_str());



	printf("\n");
	system("PAUSE");
	return 0;
}