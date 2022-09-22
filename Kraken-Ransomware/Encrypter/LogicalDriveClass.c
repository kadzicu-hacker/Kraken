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

#include "LogicalDriveClass.h"

logical_drive_class_t* logical_drive_class_create()
{
    logical_drive_class_t* logical_drive_class_obj = (logical_drive_class_t*)malloc(sizeof(logical_drive_class_t));
    if (logical_drive_class_obj)
    {
        logical_drive_class_obj->impl_ = malloc(sizeof(logical_drive_class_variables_t));
        if (logical_drive_class_obj->impl_)
        {
            logical_drive_class_obj->method = (logical_drive_class_methods_t*)malloc(sizeof(logical_drive_class_methods_t));
            if (logical_drive_class_obj->method) 
            {
                logical_drive_class_t* res = logical_drive_class_init(logical_drive_class_obj);
                if (res)
                    return res;
                else
                {
                    free(logical_drive_class_obj->method);
                    free(logical_drive_class_obj->impl_);
                    free(logical_drive_class_obj);
                    return NULL;
                }
            }
            else
            {
                free(logical_drive_class_obj->impl_);
                free(logical_drive_class_obj);
                return NULL;
            }
        }
        else
        {
            free(logical_drive_class_obj);
            return NULL;
        }
    }
    else
        return NULL;
}

static logical_drive_class_t* logical_drive_class_init(logical_drive_class_t* this) 
{
    this->method->destroy = destroy;
    this->method->get_var_list_of_logical_drives = get_var_list_of_logical_drives;
    this->method->get_var_number_of_logical_drives = get_var_number_of_logical_drives;
    this->method->get_var_max_number_of_logical_drives = get_var_max_number_of_logical_drives;

    logical_drive_class_variables_t* var = (logical_drive_class_variables_t*)this->impl_;
    var->numberOfLogicalDrives = 0x00;
    var->maxNumberOfLogicalDrives = 0xA;
    var->listOfLogicalDrives = (_TCHAR**)malloc(var->maxNumberOfLogicalDrives * sizeof(_TCHAR*));
    if (var->listOfLogicalDrives)
    {
        for (size_t i = 0x00; i < var->maxNumberOfLogicalDrives; i++)
            var->listOfLogicalDrives[i] = (_TCHAR*)malloc((MAX_PATH + 0x01) * sizeof(_TCHAR));
        logical_drive_class_init_list_of_logical_drives(this);
        return this;
    }
    else
        return NULL;
}

static void logical_drive_class_destroy(logical_drive_class_t* this) 
{
    if (this)
    {
        if (this->impl_) 
        {
            logical_drive_class_variables_t* var = (logical_drive_class_variables_t*)this->impl_;
            if (var->listOfLogicalDrives)
            {
                for (size_t i = 0x00; i < var->maxNumberOfLogicalDrives; i++)
                    if (var->listOfLogicalDrives[i])
                        free(var->listOfLogicalDrives[i]);
                free(var->listOfLogicalDrives);
            }
            free(this->impl_);
        }
        if (this->method)
            free(this->method);
        free(this);
    }
}

static _TCHAR** logical_drive_class_get_var_list_of_logical_drives(logical_drive_class_t* this) 
{
    logical_drive_class_variables_t* var = (logical_drive_class_variables_t*)this->impl_;

    return var->listOfLogicalDrives;
}
static int logical_drive_class_get_var_number_of_logical_drives(logical_drive_class_t* this) 
{
    logical_drive_class_variables_t* var = (logical_drive_class_variables_t*)this->impl_;

    return var->numberOfLogicalDrives;
}
static int logical_drive_class_get_var_max_number_of_logical_drives(logical_drive_class_t* this) 
{
    logical_drive_class_variables_t* var = (logical_drive_class_variables_t*)this->impl_;

    return var->maxNumberOfLogicalDrives;
}

static void destroy(logical_drive_class_t* this)
{
    logical_drive_class_destroy(this);
}

static _TCHAR** get_var_list_of_logical_drives(logical_drive_class_t* this)
{
    return logical_drive_class_get_var_list_of_logical_drives(this);
}

static int get_var_number_of_logical_drives(logical_drive_class_t* this)
{
    return logical_drive_class_get_var_number_of_logical_drives(this);
}

static int get_var_max_number_of_logical_drives(logical_drive_class_t* this)
{
    return logical_drive_class_get_var_max_number_of_logical_drives(this);
}

static void logical_drive_class_init_list_of_logical_drives(logical_drive_class_t* this) 
{
    _TCHAR logicalDrivesBuffer[MAX_PATH + 0x01];
    _TCHAR* logicalDrive = logicalDrivesBuffer;

    _TCHAR userNameBuffer[MAX_PATH + 0x01];
    DWORD userNameLength = 0x100 + 0x01;

    logical_drive_class_variables_t* var = (logical_drive_class_variables_t*)this->impl_;

    if ((GetLogicalDriveStrings(MAX_PATH + 0x01, logicalDrivesBuffer) != 0x00) &&
        (GetUserName(userNameBuffer, &userNameLength) != 0x00))
    {
        while (*logicalDrive)
        {
            _TCHAR currentLogicalDrive[MAX_PATH + 0x01];
            _tcscpy_s(currentLogicalDrive, _countof(currentLogicalDrive), logicalDrive);
            currentLogicalDrive[
                _tcslen(currentLogicalDrive) - 0x01
            ] = '\0';

            _TCHAR userFolder[MAX_PATH + 0x01];
            _tcscpy_s(userFolder, _countof(userFolder), currentLogicalDrive);
            _tcscat_s(userFolder, _countof(userFolder), _T("\\Users\\"));
            _tcscat_s(userFolder, _countof(userFolder), userNameBuffer);

            if ((GetDriveType(currentLogicalDrive) == DRIVE_FIXED) ||
                (GetDriveType(currentLogicalDrive) == DRIVE_REMOTE) ||
                (GetDriveType(currentLogicalDrive) == DRIVE_RAMDISK) ||
                (GetDriveType(currentLogicalDrive) == DRIVE_REMOVABLE))
            {
                if (PathFileExists(userFolder))
                {
                    _stprintf_s(var->listOfLogicalDrives[var->numberOfLogicalDrives], MAX_PATH + 0x01, _T("%s"), userFolder);
                    ++var->numberOfLogicalDrives;
                }
                else
                {
                    _stprintf_s(var->listOfLogicalDrives[var->numberOfLogicalDrives], MAX_PATH + 0x01, _T("%s"), currentLogicalDrive);
                    ++var->numberOfLogicalDrives;
                }
            }
            logicalDrive += _tcslen(
                logicalDrive
            ) + 0x01;
        }
    }
}