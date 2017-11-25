#pragma once

#if defined(RENGA_SCRIPT_LIBRARY)
#  define RENGA_SCRIPT_EXTERNAL __declspec(dllexport)
#else
#  define RENGA_SCRIPT_EXTERNAL __declspec(dllimport)
#endif

#define FORWARD_INTERNAL_IMPL(Class) \
  namespace internal{ \
  class Class##Impl; \
  }

#define DECLARE_PROTECTED_IMPL(Class) \
  protected: \
  friend class internal::Class##Impl; \
  Class(internal::Class##Impl* pImpl); \
  internal::Class##Impl* m_pImpl;

#define DECLARE_PRIVATE_IMPL_FUNC(Class) \
  private: \
  friend class internal::Class##Impl; \
  Class(internal::Class##Impl* pImpl); \
  inline internal::Class##Impl* impl() { return reinterpret_cast<internal::Class##Impl *>(m_pImpl); } \
  inline const internal::Class##Impl* impl() const { return reinterpret_cast<internal::Class##Impl *>(m_pImpl); }

#define DECLARE_NO_DEFAULT_CONSTRUCTOR(Class) \
    private: \
    Class();

#define DECLARE_NO_COPY(Class) \
  private:  \
  Class(const Class& other); \
  Class& operator=(const Class& other);