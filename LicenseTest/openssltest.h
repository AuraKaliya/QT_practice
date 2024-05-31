#ifndef OPENSSLTEST_H
#define OPENSSLTEST_H

#include <openssl/rsa.h>
#include <QDebug>


class OpenSSLTest
{
public:
    OpenSSLTest();

    RSA* createRSAKey();
    int encryptRSA(RSA* r ,unsigned char* data,int data_size , unsigned char * out);
    int decryptRSA(RSA* r ,unsigned char* data,int data_size , unsigned char * out);
    void example();
};

#endif // OPENSSLTEST_H
