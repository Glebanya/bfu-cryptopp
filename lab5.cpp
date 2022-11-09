#include <bits/stdc++.h>
#include <cryptlib.h>
#include <osrng.h>
#include <secblock.h>
#include <files.h>
#include <hex.h>
#include <modes.h>
#include <nbtheory.h>
#include <dh.h>
#include <misc.h>
#include <eccrypto.h>
#include <oids.h>

using namespace std;
using namespace CryptoPP;

using pkeys = pair<ECDSA<ECP, SHA256>::PrivateKey, ECDSA<ECP, SHA256>::PublicKey>;
pkeys KeyGen(){
    AutoSeededRandomPool rnd;
    ECDSA<ECP, SHA256>::PrivateKey prkey;
    prkey.Initialize(rnd, ASN1::secp256r1() );
    
    ECDSA<ECP, SHA256>::PublicKey pubkey;
    prkey.MakePublicKey(pubkey);
    return pkeys(prkey, pubkey);
}

string Sign(const pkeys& keys, const string& message){
    AutoSeededRandomPool rnd;
    ECDSA<ECP, SHA256>::Signer signer(keys.first);
    string sign(signer.MaxSignatureLength(), 0x00);
    int siglen = signer.SignMessage(rnd, (const CryptoPP::byte*) message.c_str(), message.size(),(CryptoPP::byte*) sign.c_str());
    sign.resize(siglen);
    return sign;
}

bool Verify(const pkeys& keys, const string& message, const string& sign){
    ECDSA<ECP, SHA256>::Verifier verifier(keys.second);
    return verifier.VerifyMessage((const CryptoPP::byte*) message.c_str(), message.size(), (const CryptoPP::byte*)sign.c_str(), sign.size());
}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    string message;
    getline(cin, message);

    auto keys = KeyGen();
    auto sign = Sign(keys, message);

    cout << "sign: " << sign << "\n";

    if(!Verify(keys, message, sign)) {
        cout << "Failed\n";
    } else {
        cout << "Accept\n";
    }
    
    return 0;
}