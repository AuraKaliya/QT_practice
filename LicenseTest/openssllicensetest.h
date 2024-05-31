#ifndef OPENSSLLICENSETEST_H
#define OPENSSLLICENSETEST_H

#include <QDebug>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>


class OpenSSLLicenseTest
{
public:
    OpenSSLLicenseTest();
    void initOpenSSL();
    void cleanupOpenSSL();
    SSL_CTX* createContext();
    void configureContext(SSL_CTX* ctx, const char* certFile, const char* keyFile);
    void example(int argc,char** argv);

};

#endif // OPENSSLLICENSETEST_H
