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

#ifndef __def__h__
#define __def__h__

#include <stdio.h>
#include <tchar.h>
#include <shlobj.h> 
#include <windows.h>
#include <shlwapi.h>

#pragma comment(lib, "shlwapi.lib")

#pragma warning(disable : 4113)
#pragma warning(disable : 4115)
#pragma warning(disable : 4133)
/////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    _TCHAR** listOfLogicalDrives;
    int numberOfLogicalDrives;
    int maxNumberOfLogicalDrives;
} logical_drive_class_variables_t;

typedef struct
{
    void(*destroy)(struct logical_drive_class_t*);
    _TCHAR** (*get_var_list_of_logical_drives)(struct logical_drive_class_t*);
    int(*get_var_number_of_logical_drives)(struct logical_drive_class_t*);
    int(*get_var_max_number_of_logical_drives)(struct logical_drive_class_t*);
} logical_drive_class_methods_t;

typedef struct
{
    void* impl_;
    logical_drive_class_methods_t* method;
} logical_drive_class_t;
/////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    _TCHAR** arrayOfFileExtensions;
    size_t fileExtensionArraySize;
    logical_drive_class_t* logical_drive_class_obj;
} search_engine_class_variables_t;

typedef struct
{
    void(*destroy)(struct search_engine_class_t*);
    void(*start)(struct search_engine_class_t*);
} search_engine_class_methods_t;

typedef struct
{
    void* impl_;
    search_engine_class_methods_t* method;
} search_engine_class_t;
/////////////////////////////////////////////////////////////////////////////////////////////
#endif // !__def__h__
