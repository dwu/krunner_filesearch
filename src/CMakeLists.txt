add_definitions(-DTRANSLATION_DOMAIN=\"plasma_runner_filesearch\")

set(krunner_filesearch_SRCS filesearch.cpp)

add_library(krunner_filesearch MODULE ${krunner_filesearch_SRCS})

target_link_libraries(krunner_filesearch KF5::Runner KF5::I18n KF5::Baloo KF5::KIOCore KF5::KIOWidgets)

install(TARGETS krunner_filesearch DESTINATION ${KDE_INSTALL_QTPLUGINDIR})
install(FILES plasma-runner-filesearch.desktop DESTINATION ${SERVICES_INSTALL_DIR})
