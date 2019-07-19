/*
 * PImpl.hpp
 * 
 * Copyright (C) 2019 by RStudio, Inc.
 *
 * TODO: License
 *
 */

#ifndef LAUNCHER_PLUGINS_P_IMPL_HPP
#define LAUNCHER_PLUGINS_P_IMPL_HPP

#include <memory>

/**
 * @brief Shared start of the macro to define a private implementation for a class.
 */
#define PRIVATE_IMPL_START                            \
   struct Impl;

/**
 * @brief Macro to define a private implementation for a non-copyable class.
 *
 * Class which use this macro must either be non-copyable or define a custom deep-copy constructor and operator which
 * performs a deep copy of the impl.
 *
 * This macro should be included in the private or protected section of a classes declaration.
 * The PRIVATE_IMPL_DELETER_IMPL macro must be used in the definition file, after the definition of the Impl struct.
 * struct OwningClass::Impl should be defined in the definition file before defining OwningClass.
 *
 * @param in_memberName    The name of the private implementation member variable (e.g. m_impl).
 */
#define PRIVATE_IMPL(in_memberName)                      \
   PRIVATE_IMPL_START                                    \
   struct ImplDeleter { void operator()(Impl*); };       \
   std::unique_ptr<Impl, ImplDeleter> in_memberName;

/**
 * @brief Macro to define a private implementation which would be shared with copied instances.
 *
 * This macro should be included in the private or protected section of a classes declaration.
 * struct OwningClass::Impl should be defined in the definition file before defining OwningClass.
 *
 * @param in_memeberName    The name of the private implementation member variable (e.g. m_impl).
 */
#define PRIVATE_IMPL_SHARED(in_memberName) \
   PRIVATE_IMPL_START                        \
   std::shared_ptr<Impl> in_memberName;

/**
 * @brief Macro which implements the deleter for the class's private implementation. This macro must be used after the
 *        implentation of the Impl struct in the definition file.
 *
 * @param in_owningClass    The name of the class which owns the private implementation (e.g. Error).
 */
#define PRIVATE_IMPL_DELETER_IMPL(in_owningClass)                                   \
void in_owningClass::ImplDeleter::operator()(in_owningClass::Impl* io_toDelete)     \
{                                                                                   \
   delete io_toDelete;                                                              \
}

#endif
