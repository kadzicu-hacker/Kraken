/*
* MIT License
*
* Copyright (c) 2022 kadzicu
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include "def.h"

#ifndef __open__close__file__class__h__
#define __open__close__file__class__h__

open_close_file_class_t* open_close_file_class_create(LPCTSTR);
static open_close_file_class_t* open_close_file_class_init(open_close_file_class_t*, LPCTSTR);
static void open_close_file_class_destroy(open_close_file_class_t*);
static void open_close_file_class_open_file_rb(open_close_file_class_t*);
static void open_close_file_class_open_file_wb(open_close_file_class_t*);
static void open_close_file_class_open_file_rwb(open_close_file_class_t*);
static void open_close_file_class_open_file_main(open_close_file_class_t*, LPCTSTR);
static int open_close_file_class_get_error_success(open_close_file_class_t*);
static void ocf_destroy(open_close_file_class_t*);
static void ocf_open_file_rb(open_close_file_class_t*);
static void ocf_open_file_wb(open_close_file_class_t*);
static void ocf_open_file_rwb(open_close_file_class_t*);
static int get_error_success(open_close_file_class_t*);

#endif // !__open__close__file__class__h__