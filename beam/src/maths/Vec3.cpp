#include "Common.hpp"
#include "Vec3.hpp"

namespace beam::maths {

    std::ostream& operator << (std::ostream& stream, const Vec3& v) {
        return stream << "(" << v.X << ", " << v.Y << ", " << v.Z << ")";
    }

}
