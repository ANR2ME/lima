/*
 * Copyright (c) 2011-2012 Luc Verhaegen <libv@codethink.co.uk>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sub license,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/*
 * Some helpers to deal with symbols (uniforms, attributes, varyings).
 */

#ifndef LIMARE_SYMBOLS_H
#define LIMARE_SYMBOLS_H 1

enum symbol_type {
	SYMBOL_UNIFORM,
	SYMBOL_ATTRIBUTE,
	SYMBOL_VARYING,
};

struct symbol {
#define SYMBOL_STRING_SIZE 64
	/* as referenced by the shaders and shader compiler binary streams */
	char name[SYMBOL_STRING_SIZE + 1];

	enum symbol_type type;

	int component_size;
	int component_count;
	int entry_count;

	int src_stride;
	int dst_stride;

	int size; /* size it takes in memory. */
	short offset; /* offset from start of memory block */

	void *address;
	int physical; /* empty for uniforms */

	void *data;
	int data_allocated;
};

struct symbol *symbol_create(const char *name, enum symbol_type type,
			     int component_size, int component_count,
			     int entry_count, int src_stride, int dst_stride,
			     void *data, int copy, int matrix);

struct symbol *symbol_copy(struct symbol *original, int start, int count);

void symbol_destroy(struct symbol *symbol);
void symbol_print(struct symbol *symbol);

#endif /* LIMARE_SYMBOLS_H */
