#include <Component.h>
std::atomic<ComponentTypeID> ag::Component::nextComponentID(0);
std::unordered_map<ComponentTypeID, int> ag::Component::componentSize{};
