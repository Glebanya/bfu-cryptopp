#include <bits/stdc++.h>
#include <cryptlib.h>
#include <osrng.h>
#include <secblock.h>
#include <files.h>
#include <hex.h>
#include <modes.h>

using namespace std;
using namespace CryptoPP;

const int KEY_LEN = 1 << 5;

SecByteBlock KeyGen(){
	SecByteBlock key(KEY_LEN);
    AutoSeededRandomPool prng;
	prng.GenerateBlock(key, key.size());
	return key;
}

void Sign(const SecByteBlock& key, string& plainstr, string& mac, string& hmactxt){
	HMAC<SHA256> hmac(key, KEY_LEN);
	StringSource ss2(plainstr, true, new HashFilter(hmac, new StringSink(mac))); 
	StringSource ss3(mac, true, new HexEncoder(new StringSink(hmactxt)));
}

bool Verify(const SecByteBlock& key, string& plainstr, string& mac){	
	try {
		HMAC<SHA256> hmac(key, KEY_LEN);
        auto filter = new HashVerificationFilter(hmac, NULL, HashVerificationFilter::THROW_EXCEPTION | HashVerificationFilter::HASH_AT_END);
		StringSource(plainstr + mac, true, filter);
		return true;
	} catch (const CryptoPP::Exception& e) {
		return false;
	}

}

int main() {

    string plainstr, mac, hmactxt, ftxt(100, 's');

    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    getline(cin, plainstr);

	auto key = KeyGen(), fkey = KeyGen();
	Sign(key, plainstr, mac, hmactxt);

	cout << "txt: " << plainstr << "\n";
	cout << "HMAC: " << hmactxt << "\n";

	if (Verify(key, plainstr, mac)) {
		cout << "Accept\n";
	} else {
		cout << "Failed\n";
	}
	if (Verify(fkey, plainstr, mac)) {
		cout << "Accept\n";
	} else {
		cout << "Failed\n";
	}
	if (Verify(key, ftxt, mac)) {
		cout << "Accept\n";
	} else {
		cout << "Failed\n";
	}

	return 0;
}