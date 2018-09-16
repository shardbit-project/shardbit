// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2014-2015 Dash Developers
// Copyright (c) 2017-2018 The Shardbit developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"
#include "chainparams.h"
#include "main/main.h"

#include "misc/util.h"
#include "misc/base58.h"
#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     // It'll only connect to one or two seed nodes because once it connects,
     // it'll get a pile of addresses with newer timestamps.
     // Seed nodes are given a random 'last seen time' of between one and two
     // weeks ago.
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;

        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;

        memcpy(&ip, &t, sizeof(ip));

        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

// Hardcoded seeds.
static void getHardcodedSeeds(std::vector<CAddress> &vSeedsOut)
{
    std::vector<std::string> ips;

    ips.push_back("45.76.2.231");
    ips.push_back("207.148.31.219");
    ips.push_back("45.63.20.238");
    ips.push_back("207.246.87.234");
    ips.push_back("207.148.22.146");

    const int64_t oneWeek = 7 * 24 * 60 * 60;
    for (size_t i = 0; i < ips.size(); ++i)
    {
        CAddress addr(CService(ips[i], 37451));
        addr.nTime = GetTime() - GetRand(oneWeek) - oneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xbc;
        pchMessageStart[1] = 0xae;
        pchMessageStart[2] = 0xdc;
        pchMessageStart[3] = 0xe9;
        vAlertPubKey = ParseHex("75023deacecde21b1644efc56ed3594ef64425850aa52617506177cf245575f0aa11e5b1777cfd8621ea39a7996872a07631ea25b3fdda00df37f5e982fe58850a");
        nDefaultPort = 37451;
        nRPCPort = 37452;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16); // starting difficulty is 1 / 2^12

        const char* pszTimestamp = "Shardbit Genesis Final - (9/16/2018)";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();

        CTransaction txNew(1, 1537129670, vin, vout, 0);
        LogPrintf("genesis mainnet transaction:  %s\n", txNew.ToString().c_str());

        genesis.vtx.push_back(txNew);

        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1537129670;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 124909;

        hashGenesisBlock = genesis.GetHash();

        //LogPrintf("Display genesis hash so we can input it below %s\n", hashGenesisBlock.ToString().c_str());
        //LogPrintf("Display merkle root so we can input it below %s\n", genesis.hashMerkleRoot.ToString().c_str());
        //LogPrintf("Display nonce so we can input it below %s\n", genesis.nNonce);
        //LogPrintf("Display time so we can input it below %s\n", genesis.nTime);

        assert(hashGenesisBlock == uint256("0x953ce96a4372f081143519d3cda3d4271d11bace9a95ba6b636cb56cd5b2495c"));
        assert(genesis.hashMerkleRoot == uint256("0xa3436084c7a50603039cce694fe4508b61e32846fc8f2ce72f0ef87b8df3b7d8"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,63); // S
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,21);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,23);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,41);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x99)(0x75)(0x45)(0xE2).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x99)(0x73)(0x43)(0xE3).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("45.76.2.231", "45.76.2.231"));
        vSeeds.push_back(CDNSSeedData("207.148.31.219", "207.148.31.219"));
        vSeeds.push_back(CDNSSeedData("45.63.20.238", "45.63.20.238"));
        vSeeds.push_back(CDNSSeedData("207.246.87.234", "207.246.87.234"));
        vSeeds.push_back(CDNSSeedData("207.148.22.146", "207.148.22.146"));

	      convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);
        getHardcodedSeeds(vFixedSeeds);

        nPoolMaxTransactions = 3;
        nLastPOWBlock = 99999999;
        nPOSStartBlock = 500;

        strDarksendPoolDummyAddress = "hFoQDUrp63QWqFhjEr3Fmc4ubHRhyzjKUC";
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xae;
        pchMessageStart[1] = 0xce;
        pchMessageStart[2] = 0x9d;
        pchMessageStart[3] = 0x4f;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("75c313c3ddefcdae1d0e4a656ed3594ef64425850aa52617506177cf245575f0aa11e5b1777cfd8621ea39a7996872a07631ea25b3fdda00df37f5e982fe58850a");
        nDefaultPort = 47451;
        nRPCPort = 47452;
        strDataDir = "testnet";
        genesis.nTime    = 1537129670;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 124897;

        hashGenesisBlock = genesis.GetHash();

        //LogPrintf("Display genesis hash so we can input it below %s\n", hashGenesisBlock.ToString().c_str());
        //LogPrintf("Display merkle root so we can input it below %s\n", genesis.hashMerkleRoot.ToString().c_str());
        //LogPrintf("Display nonce so we can input it below %s\n", genesis.nNonce);
        //LogPrintf("Display time so we can input it below %s\n", genesis.nTime);

        assert(hashGenesisBlock == uint256("0xaf9c11655f30669bdcbc31d213ac9b30b746d64168a0207a7c18e04630faab53"));
        assert(genesis.hashMerkleRoot == uint256("0xa3436084c7a50603039cce694fe4508b61e32846fc8f2ce72f0ef87b8df3b7d8"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,85); // b
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,23);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,25);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,43);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x98)(0x74)(0x44)(0xE1).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x98)(0x72)(0x42)(0xE2).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);
        nLastPOWBlock = 99999999;

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {

    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
