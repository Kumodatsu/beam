#include "Common.hpp"
#include "RNG.hpp"

namespace beam {

    static UInt32 get_random_seed() {
        const Int64 t = std::chrono::high_resolution_clock::now()
            .time_since_epoch().count();
        return t % std::numeric_limits<UInt32>::max();
    }

    RNG::RNG()
        : RNG(get_random_seed())
    { }

    RNG::RNG(UInt32 seed)
        : m_gen(seed)
    { }

}
