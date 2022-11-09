#include <bits/stdc++.h>
#include <modes.h>
#include <osrng.h>
#include <secblock.h>
#include <files.h>

using namespace std;
using namespace CryptoPP;

using psectblock = pair<SecByteBlock, SecByteBlock>;

psectblock KeyGen(){
	SecByteBlock key(32), iv(16);
    AutoSeededRandomPool prng;
	prng.GenerateBlock(key, key.size());
	prng.GenerateBlock(iv, iv.size());
	return psectblock(key, iv);
}

string Enc(const SecByteBlock& key, const SecByteBlock& iv, const string& plainstr) {
    string ctext; 
	ctext.resize(plainstr.size());
	CTR_Mode<AES>::Encryption encryptor;
	encryptor.SetKeyWithIV(key, key.size(), iv, iv.size());
	encryptor.ProcessData((CryptoPP::byte*) ctext.c_str(), (const CryptoPP::byte*)plainstr.data(), plainstr.size());
    return ctext;
}

string Dec(const SecByteBlock& key, const SecByteBlock& iv, const string& ctext) {
    string dtext;
	dtext.resize(ctext.size());

	CTR_Mode<AES>::Decryption decryptor;
	decryptor.SetKeyWithIV(key, key.size(), iv, iv.size());
	decryptor.ProcessData((CryptoPP::byte*) dtext.c_str(),  (const CryptoPP::byte*)ctext.data(), ctext.size());

    return dtext;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    string plainstr;
    getline(cin, plainstr);
	auto [key, iv] = KeyGen();
	auto ctext = Enc(key, iv, plainstr);
	auto dtext = Dec(key, iv, ctext);

	cout << "enc: " << ctext << "\n";
	cout << "dec: " << dtext << "\n";

	return 0;
}