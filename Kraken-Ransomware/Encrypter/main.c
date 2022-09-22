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
#include "LogicalDriveClass.h"

#pragma warning(disable : 4100)

#ifndef _DEBUG
int APIENTRY _tWinMain(
    _In_        HINSTANCE   hInstance,
    _In_opt_    HINSTANCE   hPrevInstance,
    _In_        LPTSTR      pCmdLine,
    _In_        int         nCmdShow
)
#else
int _tmain()
#endif 
{
    logical_drive_class_t* logical_drive_class_obj = logical_drive_class_create();
    for (size_t i = 0; i < logical_drive_class_obj->method->get_var_number_of_logical_drives(logical_drive_class_obj); i++)
        _tprintf(_T("%s"), logical_drive_class_obj->method->get_var_list_of_logical_drives(logical_drive_class_obj)[i]);
    logical_drive_class_obj->method->destroy(logical_drive_class_obj);
}