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

#include <tchar.h>
#include <windows.h>

#include <openssl/rsa.h>
#include <openssl/pem.h>
/////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    BIO* publicKey;
    BIO* privateKey;
    RSA* rsa;
    BIGNUM* bigNum;
    int bits;
} rsa_class_variables_t;

typedef struct
{
    void(*rsa_destroy)(struct rsa_class_t*);
    void(*gen_private_key)(struct rsa_class_t*);
    void(*gen_public_key)(struct rsa_class_t*);
} rsa_class_methods_t;

typedef struct
{
    void* impl_;
    rsa_class_methods_t* method;
} rsa_class_t;
/////////////////////////////////////////////////////////////////////////////////////////////
#endif // !__def__h__
