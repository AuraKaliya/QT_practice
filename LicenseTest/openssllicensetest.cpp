#include "openssllicensetest.h"
extern "C"
{
#include <openssl/applink.c>
};

OpenSSLLicenseTest::OpenSSLLicenseTest()
{

}

void OpenSSLLicenseTest::initOpenSSL()
{
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
    OPENSSL_Applink();
}

void OpenSSLLicenseTest::cleanupOpenSSL()
{
    EVP_cleanup();
}

SSL_CTX *OpenSSLLicenseTest::createContext()
{
    const SSL_METHOD* method;
    SSL_CTX* ctx;

    method = SSLv23_client_method();

    ctx = SSL_CTX_new(method);
    if (!ctx) {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    return ctx;
}

void OpenSSLLicenseTest::configureContext(SSL_CTX *ctx, const char *certFile, const char *keyFile)
{
    SSL_CTX_set_ecdh_auto(ctx, 1);

    // 设置证书文件
    if (SSL_CTX_use_certificate_file(ctx, certFile, SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    else
    {
        qDebug()<<"CertainFile certificate successed.";
    }

    // 设置私钥文件
    if (SSL_CTX_use_PrivateKey_file(ctx, keyFile, SSL_FILETYPE_PEM) <= 0 ) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    else
    {
        qDebug()<<"KeyFile PrivateKey successed.";
    }

}

void OpenSSLLicenseTest::example(int argc, char **argv)
{
    if(argc != 3)
    {
        qDebug() << "Usage: " << argv[0] << "<CertFile> <KeyFile>";
    }

    const char* certFile =argv[1];
    const char* keyFile =argv[2];

    qDebug()<<"Certain File : "<<certFile<<" | Key File : "<<keyFile;
    initOpenSSL();

    SSL_CTX* ctx =createContext();

    qDebug()<<"certain begin.";
    configureContext(ctx,certFile,keyFile);
    qDebug()<<"certain end.";

    SSL_CTX_free(ctx);
    cleanupOpenSSL();
}




