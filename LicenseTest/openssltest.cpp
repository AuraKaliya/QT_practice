#include "openssltest.h"

OpenSSLTest::OpenSSLTest()
{

}

RSA *OpenSSLTest::createRSAKey()
{
    //存放RSA密钥对
    RSA* r = RSA_new();

    //公钥指数（大质数）       公钥(E N)
    BIGNUM* e = BN_new();

    // 随机值不可控
    //默认公钥   RSA_F4  65537
    BN_set_word(e, RSA_F4);

    //生成私钥指数D和模数N(N= p*q    p、q为随机大质数)
    // RSA密钥  密钥的比特位 公钥指数 密钥生成的回调
    RSA_generate_key_ex(r, 1024, e, NULL);

    BN_free(e);

    //拿到模数N
    auto n = RSA_get0_n(r);
    //公钥指数E
    auto E = RSA_get0_e(r);
    //密文 = 明文 ^ 公钥指数E  % 模数N
    //明文 = 密文 ^ 私钥指数E  % 模数N
    auto d = RSA_get0_d(r);

    return r;
}

int OpenSSLTest::encryptRSA(RSA *r, unsigned char *data, int data_size, unsigned char *out)
{
    int key_size = RSA_size(r);
    int block_size = RSA_size(r) - RSA_PKCS1_PADDING_SIZE;
    int out_size = 0;
    for (int i = 0; i < data_size; i += block_size)
    {
        int en_size = ((data_size - i < block_size) ? data_size - i : block_size);
        int out_off = i + RSA_PKCS1_PADDING_SIZE * (i / block_size);
        int re = RSA_public_encrypt(en_size, data, out + out_off, r, RSA_PKCS1_PADDING);
        out_size = out_off + key_size;
    }
    return out_size;
}

int OpenSSLTest::decryptRSA(RSA *r, unsigned char *data, int data_size, unsigned char *out)
{
    int key_size = RSA_size(r);
    int out_off = 0;
    for (int i = 0; i < data_size; i += key_size)
    {
        int re=RSA_private_decrypt(key_size,data+i,out+ out_off,r,RSA_PKCS1_PADDING);
        out_off += re;
    }
    return out_off;
}

void OpenSSLTest::example()
{
    unsigned char data[1024] = " hello, this is an example. ";
    unsigned char encryptOut[2048]={0};
    unsigned char decryptOut[2048]={0};

    int data_size = sizeof(data);

    //生成密钥
    auto r= createRSAKey();

    //check 1
    qDebug()<<"OpenSSLTest::example | check 1 | data:"<<QByteArray(reinterpret_cast<const char*>(data));

    int en_size =encryptRSA(r,data,data_size,encryptOut);

    //check 2
    qDebug()<<"OpenSSLTest::example | check 2 | encryptOut:"<<QByteArray(reinterpret_cast<const char*>(encryptOut));

    //解密密钥
    RSA *rd =RSA_new();
    {
        auto n =BN_new();
        auto d =BN_new();
        auto e =BN_new();

        //copy
        BN_copy(n, RSA_get0_n(r));
        BN_copy(d,RSA_get0_d(r));
        BN_copy(e, RSA_get0_e(r));
        RSA_set0_key(rd,n,e,d);
    }

    int de_size =decryptRSA(rd,encryptOut,data_size,decryptOut);

    //check 3
    qDebug()<<"OpenSSLTest::example | check 3 | decryptOut:"<<QByteArray(reinterpret_cast<const char*>(decryptOut));

    //清理
    RSA_free(r);
    RSA_free(rd);
}
