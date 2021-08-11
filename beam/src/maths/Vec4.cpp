#include "Common.hpp"
#include "Vec4.hpp"

namespace beam::maths {

    std::ostream& operator << (std::ostream& stream, const Vec4& v) {
        return stream << "(" << v.X << ", " << v.Y << ", " << v.Z << ", "
            << v.W << ")";
    }

}
