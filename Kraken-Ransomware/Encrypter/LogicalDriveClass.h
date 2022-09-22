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

#ifndef __logical__drive__class__h__
#define __logical__drive__class__h__

#pragma warning(disable : 4113)
#pragma warning(disable : 4115)
#pragma warning(disable : 4133)

typedef struct
{
    _TCHAR** listOfLogicalDrives;
    int numberOfLogicalDrives;
    int maxNumberOfLogicalDrives;
} logical_drive_class_variables_t;

typedef struct
{
    void(*destroy)(struct logical_drive_class_t*);
    _TCHAR**(*get_var_list_of_logical_drives)(struct logical_drive_class_t*);
    int(*get_var_number_of_logical_drives)(struct logical_drive_class_t*);
    int(*get_var_max_number_of_logical_drives)(struct logical_drive_class_t*);
} logical_drive_class_methods_t;

typedef struct
{
    void* impl_;
    logical_drive_class_methods_t* method;
} logical_drive_class_t;

logical_drive_class_t* logical_drive_class_create();
static logical_drive_class_t* logical_drive_class_init(logical_drive_class_t*);
static void logical_drive_class_destroy(logical_drive_class_t*);
static _TCHAR** logical_drive_class_get_var_list_of_logical_drives(logical_drive_class_t*);
static int logical_drive_class_get_var_number_of_logical_drives(logical_drive_class_t*);
static int logical_drive_class_get_var_max_number_of_logical_drives(logical_drive_class_t*);
static void destroy(logical_drive_class_t*);
static _TCHAR** get_var_list_of_logical_drives(logical_drive_class_t*);
static int get_var_number_of_logical_drives(logical_drive_class_t*);
static int get_var_max_number_of_logical_drives(logical_drive_class_t*);
static void logical_drive_class_init_list_of_logical_drives(logical_drive_class_t*);

#endif // !__logical__drive__class__h__