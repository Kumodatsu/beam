#pragma once
#include "voodoo/Template.hpp"

namespace beam {

    class RNG {
    public:
        RNG();
        RNG(UInt32 seed);

        template <typename ValueT>
        ValueT Generate(ValueT min, ValueT max) {
            if constexpr (std::is_integral_v<ValueT>)
                return std::uniform_int_distribution<ValueT>(min, max)(m_gen);
            else if constexpr (std::is_floating_point_v<ValueT>)
                return std::uniform_real_distribution<ValueT>(min, max)(m_gen);
            else
                static_assert(voodoo::False<ValueT>,
                    "Can not generate random value for type.");
        }
    private:
        std::default_random_engine m_gen;
    };

}
