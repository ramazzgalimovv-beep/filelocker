// language: C++, file: crypt_core.h, target: Windows x64
#pragma once
#include <windows.h>
#include <bcrypt.h>
#include <vector>
#include <cstdint>

#pragma comment(lib, "bcrypt.lib")

struct CryptError { int code; };

class AesCbc {
public:
    static std::vector<uint8_t> Encrypt(const std::vector<uint8_t>& key,
                                        const std::vector<uint8_t>& iv,
                                        const std::vector<uint8_t>& plain) {
        BCRYPT_ALG_HANDLE hAlg = nullptr; BCRYPT_KEY_HANDLE hKey = nullptr;
        std::vector<uint8_t> out;
        if (BCryptOpenAlgorithmProvider(&hAlg, BCRYPT_AES_ALGORITHM, nullptr, 0) < 0)
            throw CryptError{-1};
        BCryptSetProperty(hAlg, BCRYPT_CHAINING_MODE,
            (PUCHAR)BCRYPT_CHAIN_MODE_CBC, sizeof(BCRYPT_CHAIN_MODE_CBC), 0);
        BCryptGenerateSymmetricKey(hAlg, &hKey, nullptr, 0,
            (PUCHAR)key.data(), (ULONG)key.size(), 0);
        ULONG cb = 0;
        BCryptEncrypt(hKey, (PUCHAR)plain.data(), (ULONG)plain.size(), nullptr,
            (PUCHAR)iv.data(), (ULONG)iv.size(), nullptr, 0, &cb, BCRYPT_BLOCK_PADDING);
        out.resize(cb);
        BCryptEncrypt(hKey, (PUCHAR)plain.data(), (ULONG)plain.size(), nullptr,
            (PUCHAR)iv.data(), (ULONG)iv.size(), out.data(), cb, &cb, BCRYPT_BLOCK_PADDING);
        out.resize(cb);
        BCryptDestroyKey(hKey); BCryptCloseAlgorithmProvider(hAlg, 0);
        return out;
    }
};

inline std::vector<uint8_t> RandomBytes(size_t n) {
    std::vector<uint8_t> v(n);
    BCryptGenRandom(nullptr, v.data(), (ULONG)n, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
    return v;
}
