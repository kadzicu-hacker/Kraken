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

#include "XORClass.h"

xor_class_t* xor_class_create(LPCTSTR path) 
{
    xor_class_t* xor_class_obj = (xor_class_t*)malloc(sizeof(xor_class_t));
    if (xor_class_obj)
    {
        xor_class_obj->impl_ = malloc(sizeof(xor_class_variables_t));
        if (xor_class_obj->impl_)
        {
            xor_class_obj->method = (xor_class_methods_t*)malloc(sizeof(xor_class_methods_t));
            if (xor_class_obj->method)
            {
                xor_class_t* res = xor_class_init(xor_class_obj, path);
                if (res)
                    return res;
                else
                {
                    free(xor_class_obj->method);
                    free(xor_class_obj->impl_);
                    free(xor_class_obj);
                    return NULL;
                }
            }
            else
            {
                free(xor_class_obj->impl_);
                free(xor_class_obj);
                return NULL;
            }
        }
        else
        {
            free(xor_class_obj);
            return NULL;
        }
    }
    else
        return NULL;
}

static xor_class_t* xor_class_init(xor_class_t* this, LPCTSTR path) 
{
    this->method->xor_destroy = xor_destroy;
    this->method->xor_encrypt = xor_encrypt;

    xor_class_variables_t* var = (xor_class_variables_t*)this->impl_;
    var->key = 0x02;
    var->path = path;

    return this;
}

static void xor_class_destroy(xor_class_t* this) 
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

static void xor_class_encrypt(xor_class_t* this) 
{
    xor_class_variables_t* var = (xor_class_variables_t*)this->impl_;

    open_close_file_class_t* open_close_file_class_obj1 = open_close_file_class_create(var->path);
    if (open_close_file_class_obj1)
    {
        open_close_file_class_obj1->method->ocf_open_file_rb(open_close_file_class_obj1);
        if ((open_close_file_class_obj1->method->get_var_error_success(open_close_file_class_obj1) == ERROR_SUCCESS))
        {
            LONG64 file_size = open_close_file_class_obj1->method->get_var_file_size(open_close_file_class_obj1);
            FILE* old_file = open_close_file_class_obj1->method->get_var_file(open_close_file_class_obj1);

            _TCHAR newFileName[MAX_PATH + 0x01];
            _tcscpy_s(newFileName, _countof(newFileName), var->path);
            _tcscat_s(newFileName, _countof(newFileName), _T(".kraken"));

            open_close_file_class_t* open_close_file_class_obj2 = open_close_file_class_create(newFileName);
            if (open_close_file_class_obj2)
            {
                open_close_file_class_obj2->method->ocf_open_file_wb(open_close_file_class_obj2);
                if ((open_close_file_class_obj2->method->get_var_error_success(open_close_file_class_obj2) == ERROR_SUCCESS))
                {
                    FILE* new_file = open_close_file_class_obj2->method->get_var_file(open_close_file_class_obj2);

                    _TCHAR c_byte = 0x00;
                    for (LONG64 i = 0x00; i < file_size; i++)
                    {
                        fread(&c_byte, 0x01, 0x01, old_file);
                        c_byte ^= var->key;
                        fwrite(&c_byte, 0x01, 0x01, new_file);
                    }
                }
                open_close_file_class_obj2->method->ocf_destroy(open_close_file_class_obj2);
            }
        }
        open_close_file_class_obj1->method->ocf_destroy(open_close_file_class_obj1);
    }
}

static void xor_destroy(xor_class_t* this) 
{
    xor_class_destroy(this);
}

static void xor_encrypt(xor_class_t* this) 
{
    xor_class_encrypt(this);
}