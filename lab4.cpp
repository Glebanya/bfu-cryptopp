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

using namespace std;
using namespace CryptoPP;

using prpubkeys = pair<SecByteBlock, SecByteBlock>;

Integer p, q, g;

DH dhAlice;
prpubkeys AliceGen(){
    AutoSeededRandomPool rnd;
    dhAlice.AccessGroupParameters().Initialize(p, q, g);
  	SecByteBlock prkey(dhAlice.PrivateKeyLength()), pubkey(dhAlice.PublicKeyLength());
  	dhAlice.GenerateKeyPair(rnd, prkey, pubkey);
    return prpubkeys(prkey, pubkey);
}

SecByteBlock AliceDerive(const prpubkeys& alicekeys,const prpubkeys& bobkeys){
    SecByteBlock sharedA(dhAlice.AgreedValueLength());
    dhAlice.Agree(sharedA, alicekeys.first, bobkeys.second);
    return sharedA;
}

DH dhBob;
prpubkeys BobGen(){
    AutoSeededRandomPool rnd;
    dhBob.AccessGroupParameters().Initialize(p, q, g);
  	SecByteBlock prkey(dhBob.PrivateKeyLength()), pubkey(dhBob.PublicKeyLength());
  	dhBob.GenerateKeyPair(rnd, prkey, pubkey);
    return prpubkeys(prkey, pubkey);
}

SecByteBlock BobDerive(const prpubkeys& alicekeys, const prpubkeys& bobkeys){
    SecByteBlock sharedB(dhBob.AgreedValueLength());
    dhBob.Agree(sharedB, bobkeys.first, alicekeys.second);
    return sharedB;
}
bool KeyVerif(const SecByteBlock& sharedA, const SecByteBlock& sharedB){
    return VerifyBufsEqual(sharedA.BytePtr(), sharedB.BytePtr(), min(dhAlice.AgreedValueLength(), dhBob.AgreedValueLength()));
}

int main() {
    AutoSeededRandomPool rnd;
  	PrimeAndGenerator pg;
  	pg.Generate(1, rnd, 512, 511);
    p = pg.Prime(), q = pg.SubPrime(), g = pg.Generator();

    auto akeys = AliceGen(), bkeys = BobGen();
    auto shareda = AliceDerive(akeys, bkeys);
    auto sharedb = BobDerive(akeys, bkeys);
    if(KeyVerif(shareda, sharedb)){
        cout << "Accept\n";
    } else {
        cout << "Failed\n";
    }

	return 0;
}