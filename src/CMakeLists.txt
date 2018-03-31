add_definitions(-DTRANSLATION_DOMAIN=\"plasma_runner_org.kde.krunner_filesearch\")

set(krunner_filesearch_SRCS krunner_filesearch.cpp)

add_library(krunner_krunner_filesearch MODULE ${krunner_filesearch_SRCS})
target_link_libraries(krunner_krunner_filesearch KF5::Runner KF5::I18n)

install(TARGETS krunner_krunner_filesearch DESTINATION ${KDE_INSTALL_PLUGINDIR})

install(FILES plasma-runner-krunner_filesearch.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR})
