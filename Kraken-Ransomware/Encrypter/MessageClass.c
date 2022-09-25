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

#include "MessageClass.h"

_TCHAR* msg[] = 
{
    _T("DISCLAIMER\n"),
    _T("Kraken is for education/research purposes only.\n"),
    _T("The author takes NO responsibility and/or liability for how you choose to use any of the tools/source code/any files provided.\n"),
    _T("The author and anyone affiliated with will not be liable for any losses and/or damages in connection with use of ANY files provided with Kraken.\n"),
    _T("By using Kraken or any files included, you understand that you are AGREEING TO USE AT YOUR OWN RISK.\n"),
    _T("Once again Kraken files included are for EDUCATION and/or RESEARCH purposes ONLY.\n"),
    _T("Kraken is ONLY intended to be used on your own pentesting labs, or with explicit consent from the owner of the property being tested.\n"),
    _T("\n"),
    _T("License\n"),
    _T("Kraken is distributed under the [MIT License](LICENSE).\n")
};

message_class_t* message_class_create(LPCTSTR path) 
{
    message_class_t* message_class_obj = (message_class_t*)malloc(sizeof(message_class_t));
    if (message_class_obj)
    {
        message_class_obj->impl_ = malloc(sizeof(message_class_variables_t));
        if (message_class_obj->impl_)
        {
            message_class_obj->method = (message_class_methods_t*)malloc(sizeof(message_class_methods_t));
            if (message_class_obj->method)
            {
                message_class_t* res = message_class_init(message_class_obj, path);
                if (res)
                    return res;
                else
                {
                    free(message_class_obj->method);
                    free(message_class_obj->impl_);
                    free(message_class_obj);
                    return NULL;
                }
            }
            else
            {
                free(message_class_obj->impl_);
                free(message_class_obj);
                return NULL;
            }
        }
        else
        {
            free(message_class_obj);
            return NULL;
        }
    }
    else
        return NULL;
}

static message_class_t* message_class_init(message_class_t* this, LPCTSTR path) 
{
    this->method->m_destroy = m_destroy;
    this->method->m_send = m_send;

    message_class_variables_t* var = (message_class_variables_t*)this->impl_;
    var->path = path;
    var->msg = msg;
    var->msgSize = _countof(msg);

    return this;
}

static void message_class_destroy(message_class_t* this) 
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

static void message_class_send(message_class_t* this) 
{
    message_class_variables_t* var = (message_class_variables_t*)this->impl_;

    open_close_file_class_t* open_close_file_class_obj = open_close_file_class_create(var->path);
    if (open_close_file_class_obj)
    {
        open_close_file_class_obj->method->ocf_open_file_wb(open_close_file_class_obj);
        if ((open_close_file_class_obj->method->get_var_error_success(open_close_file_class_obj) == ERROR_SUCCESS)) 
        {
            FILE* file = open_close_file_class_obj->method->get_var_file(open_close_file_class_obj);

            for (size_t i = 0x00; i < var->msgSize; i++)
                fwrite(msg[i], sizeof(_TCHAR), _tcslen(var->msg[i]), file);
        }
        open_close_file_class_obj->method->ocf_destroy(open_close_file_class_obj);
    }
}

static void m_destroy(message_class_t* this) 
{
    message_class_destroy(this);
}

static void m_send(message_class_t* this) 
{
    message_class_send(this);
}