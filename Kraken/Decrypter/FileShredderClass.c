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

#include "FileShredderClass.h"

file_shredder_class_t* file_shredder_class_create(LPCTSTR path) 
{
    file_shredder_class_t* file_shredder_class_obj = (file_shredder_class_t*)malloc(sizeof(file_shredder_class_t));
    if (file_shredder_class_obj)
    {
        file_shredder_class_obj->impl_ = malloc(sizeof(file_shredder_class_variables_t));
        if (file_shredder_class_obj->impl_)
        {
            file_shredder_class_obj->method = (file_shredder_class_methods_t*)malloc(sizeof(file_shredder_class_methods_t));
            if (file_shredder_class_obj->method)
            {
                file_shredder_class_t* res = file_shredder_class_init(file_shredder_class_obj, path);
                if (res)
                    return res;
                else
                {
                    free(file_shredder_class_obj->method);
                    free(file_shredder_class_obj->impl_);
                    free(file_shredder_class_obj);
                    return NULL;
                }
            }
            else
            {
                free(file_shredder_class_obj->impl_);
                free(file_shredder_class_obj);
                return NULL;
            }
        }
        else
        {
            free(file_shredder_class_obj);
            return NULL;
        }
    }
    else
        return NULL;
}

static file_shredder_class_t* file_shredder_class_init(file_shredder_class_t* this, LPCTSTR path) 
{
    this->method->fs_destroy = fs_destroy;
    this->method->fs_start = fs_start;

    file_shredder_class_variables_t* var = (file_shredder_class_variables_t*)this->impl_;
    var->path = path;

    return this;
}

static void file_shredder_class_destroy(file_shredder_class_t* this) 
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

static void file_shredder_class_start(file_shredder_class_t* this) 
{
    file_shredder_class_variables_t* var = (file_shredder_class_variables_t*)this->impl_;

    _tremove(var->path);
}

static void fs_destroy(file_shredder_class_t* this) 
{
    file_shredder_class_destroy(this);
}

static void fs_start(file_shredder_class_t* this) 
{
    file_shredder_class_start(this);
}