//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a RdGen v1.13.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------
#include "EmptyScriptCallStack.Pregenerated.h"



#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable:4250 )
#pragma warning( disable:4307 )
#pragma warning( disable:4267 )
#pragma warning( disable:4244 )
#pragma warning( disable:4100 )
#endif

namespace JetBrains {
namespace EditorPlugin {
// companion
// constants
constexpr rd::wstring_view EmptyScriptCallStack::message;
// initializer
void EmptyScriptCallStack::initialize()
{
}
// primary ctor
// secondary constructor
// default ctors and dtors
EmptyScriptCallStack::EmptyScriptCallStack()
{
    initialize();
}
// reader
EmptyScriptCallStack EmptyScriptCallStack::read(rd::SerializationCtx& ctx, rd::Buffer & buffer)
{
    EmptyScriptCallStack res{};
    return res;
}
// writer
void EmptyScriptCallStack::write(rd::SerializationCtx& ctx, rd::Buffer& buffer) const
{
}
// virtual init
// identify
// getters
// intern
// equals trait
bool EmptyScriptCallStack::equals(rd::ISerializable const& object) const
{
    auto const &other = dynamic_cast<EmptyScriptCallStack const&>(object);
    if (this == &other) return true;
    
    return true;
}
// equality operators
bool operator==(const EmptyScriptCallStack &lhs, const EmptyScriptCallStack &rhs) {
    if (lhs.type_name() != rhs.type_name()) return false;
    return lhs.equals(rhs);
}
bool operator!=(const EmptyScriptCallStack &lhs, const EmptyScriptCallStack &rhs){
    return !(lhs == rhs);
}
// hash code trait
size_t EmptyScriptCallStack::hashCode() const noexcept
{
    size_t __r = 0;
    return __r;
}
// type name trait
std::string EmptyScriptCallStack::type_name() const
{
    return "EmptyScriptCallStack";
}
// static type name trait
std::string EmptyScriptCallStack::static_type_name()
{
    return "EmptyScriptCallStack";
}
// polymorphic to string
std::string EmptyScriptCallStack::toString() const
{
    std::string res = "EmptyScriptCallStack\n";
    return res;
}
// external to string
std::string to_string(const EmptyScriptCallStack & value)
{
    return value.toString();
}
}
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif

