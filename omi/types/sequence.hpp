#ifndef OMI_TYPES_SEQUENCE_HPP_
#define OMI_TYPES_SEQUENCE_HPP_

#include <stdint.h>
#include <ostream>
#include <functional>
#include <iso646.h>

// Generic Sequence Number

namespace omi {

struct sequence {
    using type = uint64_t;

  ///// Construction //////////////

    // Default constructor
    sequence() 
      : value{ 0 } {}

    // Standard constructor
    explicit sequence(const type &number)
      : value{ number } {}

  ///// Methods ///////////////////

    // Cast operator
    explicit operator sequence() const {
        return sequence(value);
    }

    // Return underlying value
    type get() const {
        return value;
    }

  //// Properties /////////////////

  protected:
      type value;
};

///////////////////////////////////////////////

// Equals operator
inline bool operator==(const sequence& lhs, const sequence& rhs) {
    return lhs.get() == rhs.get();
}

// Not equals operator
inline bool operator!=(const sequence& lhs, const sequence& rhs) {
    return not operator==(lhs, rhs);
}

// Less than operator
inline bool operator<(const sequence& lhs, const sequence& rhs) {
    return lhs.get() < rhs.get();
}

// Greater than operator
inline bool operator>(const sequence& lhs, const sequence& rhs) {
    return operator<(rhs, lhs);
}

// Less than or equals operator
inline bool operator<=(const sequence& lhs, const sequence& rhs) {
    return not operator>(lhs, rhs);
}

// Greater than or equals operator
inline bool operator>=(const sequence& lhs, const sequence& rhs) {
    return not operator<(lhs, rhs);
}

// Stream operator
inline std::ostream &operator<<(std::ostream &out, const sequence &number) {
    return out << number.get();
}

}

// Hash 
namespace std {
template<> struct hash<omi::sequence> {
    size_t operator()(const omi::sequence& number) const {
        return hash<omi::sequence::type>()(number.get());
    }
};}

#endif