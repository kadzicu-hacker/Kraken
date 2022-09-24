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

#include "OpenCloseFileClass.h"

open_close_file_class_t* open_close_file_class_create(LPCTSTR path) 
{
	open_close_file_class_t* open_close_file_class_obj = (open_close_file_class_t*)malloc(sizeof(open_close_file_class_t));
	if (open_close_file_class_obj)
	{
		open_close_file_class_obj->impl_ = malloc(sizeof(open_close_file_class_variables_t));
		if (open_close_file_class_obj->impl_)
		{
			open_close_file_class_obj->method = (open_close_file_class_methods_t*)malloc(sizeof(open_close_file_class_methods_t));
			if (open_close_file_class_obj->method)
			{
				open_close_file_class_t* res = open_close_file_class_init(open_close_file_class_obj, path);
				if (res)
					return res;
				else
				{
					free(open_close_file_class_obj->method);
					free(open_close_file_class_obj->impl_);
					free(open_close_file_class_obj);
					return NULL;
				}
			}
			else
			{
				free(open_close_file_class_obj->impl_);
				free(open_close_file_class_obj);
				return NULL;
			}
		}
		else
		{
			free(open_close_file_class_obj);
			return NULL;
		}
	}
	else 
		return NULL;
}

static open_close_file_class_t* open_close_file_class_init(open_close_file_class_t* this, LPCTSTR path) 
{
	this->method->ocf_destroy = ocf_destroy;
	this->method->open_file_rb = ocf_open_file_rb;
	this->method->open_file_wb = ocf_open_file_wb;
	this->method->open_file_rwb = ocf_open_file_rwb;
	this->method->get_error_success = get_error_success;

	open_close_file_class_variables_t* var = (open_close_file_class_variables_t*)this->impl_;
	var->file = NULL;
	var->fileSize = 0x00;
	var->path = path;
	var->errorSuccess = 0x01;

	return this;
}

static void open_close_file_class_destroy(open_close_file_class_t* this) 
{
	if (this)
	{
		if (this->impl_)
		{
			open_close_file_class_variables_t* var = (open_close_file_class_variables_t*)this->impl_;
			if (var->file != NULL)
				fclose(var->file);
			free(this->impl_);
		}
		if (this->method)
			this->method;
		free(this);
	}
}

static void open_close_file_class_open_file_rb(open_close_file_class_t* this) 
{
	open_close_file_class_open_file_main(this, _T("rb"));
}

static void open_close_file_class_open_file_wb(open_close_file_class_t* this) 
{
	open_close_file_class_open_file_main(this, _T("wb"));
}

static void open_close_file_class_open_file_rwb(open_close_file_class_t* this) 
{
	open_close_file_class_open_file_main(this, _T("r+b"));
}

static void open_close_file_class_open_file_main(open_close_file_class_t* this, LPCTSTR mode) 
{
	open_close_file_class_variables_t* var = (open_close_file_class_variables_t*)this->impl_;

	if (_tfopen_s(&var->file, var->path, mode) == ERROR_SUCCESS)
	{
		if (var->file != NULL)
		{
			var->errorSuccess = 0x00;

			_fseeki64(var->file, 0x00, SEEK_END);
			var->fileSize = _ftelli64(var->file);
			_fseeki64(var->file, 0x00, SEEK_SET);
		}
	}
	else
		var->errorSuccess = 0x01;
}

static int open_close_file_class_get_error_success(open_close_file_class_t* this) 
{
	open_close_file_class_variables_t* var = (open_close_file_class_variables_t*)this->impl_;

	return var->errorSuccess;
}

static void ocf_destroy(open_close_file_class_t* this) 
{
	open_close_file_class_destroy(this);
}

static void ocf_open_file_rb(open_close_file_class_t* this) 
{
	open_close_file_class_open_file_rb(this);
}

static void ocf_open_file_wb(open_close_file_class_t* this) 
{
	open_close_file_class_open_file_wb(this);
}

static void ocf_open_file_rwb(open_close_file_class_t* this) 
{
	open_close_file_class_open_file_rwb(this);
}

static int get_error_success(open_close_file_class_t* this) 
{
	return open_close_file_class_get_error_success(this);
}