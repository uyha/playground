cmake_minimum_required("VERSION" 3.22)
project(deb_generator)

configure_file(NEWLINE_STYLE UNIX)

set(CPACK_DEBIAN_PACKAGE_DEBUG ON)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT "Uy Ha<hchanuy@gmail.com>")
set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_DEBIAN_comp_PACKAGE_DEPENDS "zlib (>=1)")

include(CPack)

install(
  FILES dummy
  TYPE LIB
  COMPONENT comp
  )

cpack_add_component(comp)

if(NOT a)
elseif(NOT a)
endif()
file(DOWNLOAD)
