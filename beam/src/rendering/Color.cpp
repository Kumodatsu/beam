#include "Common.hpp"
#include "Color.hpp"

namespace beam {

    std::ostream& operator << (std::ostream& stream, const Color& color) {
        return stream
            << "(R: "  << color.R
            << ", G: " << color.G
            << ", B: " << color.B
            << ")";
    }

}
