// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (         0, uint256("0xe9fa4ca452a0fb59f8273fdd73c4dee3cf9b17d615f9e0b24f0b9bd20281f9b3"))
        (      5000, uint256("0xc42b03e4bfc90af8682f97d65d40d539591960234a2e26c8b261f5d85db407bd"))
        (      9865, uint256("0x87c7cf144881b39adb92f91df8df1abe92051829b113ebb7e266b702badad326"))
        (      9866, uint256("0x0072fa796a0034d3257e1a95ab88218d59d2a7eb8bed72402d8c2de773f72909"))
        (      9867, uint256("0x3b8bc80b8c5f5d9014c7e4653fa0f4abdb47a332aeda4cd0c3526c897d630fc9"))
        (     10000, uint256("0x3a6fbf9f8ffa0523bab1709117a7e62fb3b0223e8861aa5539d9b4047beee117"))
        (     15000, uint256("0x9b97f2e9af91b5a9d1bdb4fc7b2cf182ec7df010f446e362a614f76c28b62ff7"))
        ;

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
