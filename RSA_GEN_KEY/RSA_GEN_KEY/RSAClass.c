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

rsa_class_t* rsa_class_create() 
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
                rsa_class_t* res = rsa_class_init(rsa_class_obj);
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

static rsa_class_t* rsa_class_init(rsa_class_t* this) 
{
    this->method->rsa_destroy = rsa_destroy;
    this->method->gen_public_key = gen_public_key;
    this->method->gen_private_key = gen_private_key;

    rsa_class_variables_t* var = (rsa_class_variables_t*)this->impl_;
    var->rsa = NULL;
    var->bigNum = NULL;
    var->publicKey = NULL;
    var->privateKey = NULL;
    var->bits = 0x800;

    if (((var->bigNum = BN_new()) != NULL) && 
        (BN_set_word(var->bigNum, RSA_F4) == 0x01))
    {
        if (((var->rsa = RSA_new()) != NULL) && 
            (RSA_generate_key_ex(var->rsa, var->bits, var->bigNum, NULL) == 0x01))
            return this;
        else
        {
            if (var->bigNum)
                BN_free(var->bigNum);
            return NULL;
        }
    }
    else 
    {
        if (var->bigNum)
            BN_free(var->bigNum);
        return NULL;
    }
}

static void rsa_class_destroy(rsa_class_t* this) 
{
    if (this)
    {
        if (this->impl_) 
        {
            rsa_class_variables_t* var = (rsa_class_variables_t*)this->impl_;
            if (var->rsa)
                RSA_free(var->rsa);
            if (var->bigNum)
                BN_free(var->bigNum);
            if (var->publicKey)
                BIO_free_all(var->publicKey);
            if (var->privateKey)
                BIO_free_all(var->privateKey);
            free(this->impl_);
        }
        if (this->method)
            free(this->method);
        free(this);
    }
}

static void rsa_class_gen_public_key(rsa_class_t* this) 
{
    rsa_class_variables_t* var = (rsa_class_variables_t*)this->impl_;

    var->publicKey = BIO_new_file("public.pem", "w+");
    PEM_write_bio_RSAPublicKey(var->publicKey, var->rsa);
}

static void rsa_class_gen_private_key(rsa_class_t* this) 
{
    rsa_class_variables_t* var = (rsa_class_variables_t*)this->impl_;

    var->privateKey = BIO_new_file("private.pem", "w+");
    PEM_write_bio_RSAPrivateKey(var->privateKey, var->rsa, NULL, NULL, 0x00, NULL, NULL);
}

static void rsa_destroy(rsa_class_t* this) 
{
    rsa_class_destroy(this);
}

static void gen_public_key(rsa_class_t* this) 
{
    rsa_class_gen_public_key(this);
}

static void gen_private_key(rsa_class_t* this) 
{
    rsa_class_gen_private_key(this);
}