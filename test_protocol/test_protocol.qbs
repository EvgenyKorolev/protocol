import qbs
import qbs.Environment
import "googlecommon.js" as googleCommon

CppApplication {
    consoleApplication: true

    property string googletestDir: {
        if (typeof Environment.getEnv("GOOGLETEST_DIR") === 'undefined') {
            console.warn("Using googletest src dir specified at Qt Creator wizard")
            console.log("set GOOGLETEST_DIR as environment variable or Qbs property to get rid of this message")
            return "/home/admin/prg/googletest-master"
        } else {
            return Environment.getEnv("GOOGLETEST_DIR")
        }
    }

    cpp.cxxLanguageVersion: "c++11"
    cpp.defines: [ "GTEST_LANG_CXX11" ]
    cpp.dynamicLibraries: {
        if (qbs.hostOS.contains("windows")) {
            return [];
        } else {
            return [ "pthread" ];
        }
    }


    cpp.includePaths: [].concat(googleCommon.getGTestIncludes(qbs, googletestDir))
    .concat(googleCommon.getGMockIncludes(qbs, googletestDir))

    Depends { name: "Qt"; submodules: ["core", "gui", "xml", "sql"] }

    files: [
    ].concat([
        "../src/my_function.cpp",
    ].concat([
        "../src/my_function.h",
    ].concat([
        "main.cpp",
        "tst_test001.h",
        "pars_teg_tst.h",
    ].concat(googleCommon.getGTestAll(qbs, googletestDir))
    .concat(googleCommon.getGMockAll(qbs, googletestDir)))))
}
