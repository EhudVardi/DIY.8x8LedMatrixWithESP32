#ifndef ENUM_HELPER_H
#define ENUM_HELPER_H

#include <unordered_map>

template <typename T>
class EnumHelper {
public:
    // Constructor accepting an unordered_map to initialize the enum-to-string map
    EnumHelper(const std::unordered_map<T, const char*>& map, T lastValidValue)
        : enumMap(map), lastValue(lastValidValue) {
    }

    // Convert enum to string
    const char* ToString(T value) const {
        auto it = enumMap.find(value);
        return (it != enumMap.end()) ? it->second : "[Unknown]";
    }

    // Get count of usable actions (excluding dummy or any extra values)
    int count() const {
        return static_cast<int>(lastValue) + 1; // Assumes contiguous enums
    }

    // Get the next enum value in a circular manner
    T next(T value) const {
        int nextValue = (static_cast<int>(value) + 1) % count();
        return static_cast<T>(nextValue);
    }
    // Get the prev enum value in a circular manner
    T prev(T value) const {
        int prevValue = (static_cast<int>(value) - 1 + count()) % count();
        return static_cast<T>(prevValue);
    }

private:
    const std::unordered_map<T, const char*> enumMap;
    const T lastValue; // Last valid enum value to set the circular wrap-around point
};

#endif // ENUM_HELPER_H
