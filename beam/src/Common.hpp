#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <thread>
#include <utility>
#include <algorithm>
#include <functional>
#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <cstddef>
#include <type_traits>
#include <exception>
#include <optional>
#include <variant>
#include <random>
#include <chrono>
#include <memory>
#include <new>
#include <cstdlib>
#include <malloc.h>

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

#if defined(BEAM_CONFIG_DEBUG)
#define BEAM_DEBUG_ONLY if constexpr (true)
#else
#define BEAM_DEBUG_ONLY if constexpr (false)
#endif

namespace beam {

	using Int8    = int8_t;
	using Int16   = int16_t;
	using Int32   = int32_t;
	using Int64   = int64_t;
	using UInt8   = uint8_t;
	using UInt16  = uint16_t;
	using UInt32  = uint32_t;
	using UInt64  = uint64_t;
	using Float32 = float;
	using Float64 = double;
	using Byte    = std::byte;

	// Self documenting types

	// Represents a size in bytes.
	using USize  = size_t;
	// Represents a count (for example, a number of elements).
	using UCount = size_t;
	// Represents an index.
	using UIndex = size_t;

    // glm types
    using Vec2       = glm::vec2;
    using Vec3       = glm::vec3;
    using Vec4       = glm::vec4;
    using Mat4       = glm::mat4;
    using Quaternion = glm::quat;

}
