/*
 *  Copyright (C) 2023 Callum Gran
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>

#include <fileio/fileio.h>

struct file_data_t *read_file(FILE *input)
{
	if (input == NULL)
		return NULL;

	struct file_data_t *res = (struct file_data_t *)(malloc(sizeof(struct file_data_t)));

	fseek(input, 0, SEEK_END);

	res->data_len = ftell(input);

	rewind(input);

	res->data = (char *)(malloc(res->data_len * sizeof(char)));

	if (fread(res->data, sizeof(char), res->data_len, input) != res->data_len)
		return NULL;

	return res;
}

void file_data_free(struct file_data_t *file_data)
{
	if (file_data == NULL)
		return;

	free(file_data->data);
	free(file_data);
}