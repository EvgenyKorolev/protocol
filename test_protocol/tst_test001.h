#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <string>
#include <vector>
#include <QString>
#include "../src/my_function.h"

using namespace testing;

// -----------====================Тестирование функции поиска тегов в строке=============================-------------------------------

TEST(test_search_teg001, restsprotocol)
{
    QString tst = "csdkncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzxdjf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    QString teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).second, -1);
}
TEST(test_search_teg002, restsprotocol)
{
    QString tst = "csdkncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzxdjf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    QString teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).first, -1);
}
TEST(test_search_teg003, restsprotocol)
{
    QString tst = "csd<_test_teg dsfsvxcv>kncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzxdjf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    QString teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).first, 3);
}
TEST(test_search_teg004, restsprotocol)
{
    QString tst = "csd<_test_teg dsfsvxcv>kncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzxdjf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    QString teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).second, 22);
}
TEST(test_search_teg005, restsprotocol)
{
    QString tst = "csd<_test_t<eg dsfsvxcv>kncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzxdjf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    QString teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).second, -1);
}
TEST(test_search_teg006, restsprotocol)
{
    QString tst = "csd<_test_teg < dsfsvxcv>kncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzxdjf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    QString teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).first, 3);
}
TEST(test_search_teg007, restsprotocol)
{
    QString tst = "csd<_test_teg dsfsvxcvdfkncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzx<djf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    QString teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).second, -1);
}
TEST(test_search_teg008, restsprotocol)
{
    QString tst = "csd_test_teg dsfsvxcv>kncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzxdjf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    QString teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).first, -1);
}
TEST(test_search_teg009, restsprotocol)
{
    QString tst = "c<sd<_test_teg dsfsvxcv>kncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzxdjf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    QString teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).first, 4);
}
TEST(test_search_teg010, restsprotocol)
{
    QString tst = "sd<_test_";
    QString teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).first, -1);
}
TEST(test_search_teg011, restsprotocol)
{
    QString tst = "c<sd<_test_teg d<_test_tegsfsvxcv>kncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzxdjf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    QString teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).first, 4);
}
TEST(test_search_teg012, restsprotocol)
{
    QString tst = "c<sd<_test_teg d<_test_tegsfsvxcv>kncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzxdjf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    QString teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).second, -1);
}
TEST(test_search_teg013, restsprotocol)
{
    QString tst = "";
    QString teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).first, -1);
}
TEST(test_search_teg014, restsprotocol)
{
    QString tst = "c<sd<_test_teg dsfsvxcv>kncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzxdjf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    QString teg = "";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).first, 1);
}
TEST(test_search_teg015, restsprotocol)
{
    QString tst = "csd<_test_teg dsfsvxcvkncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzxdjf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    QString teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg, 6).second, -1);
}

// -----------====================Тестирование функции разбора тэгов =============================-------------------------------

TEST(test_parse_teg001, restsprotocol)
{
    std::vector<std::string> lst{"type", "vname"};
    std::string tst = "<_parent_var type=\"parent type\", message=\"Введите вот это: \", vname=\"varname\">";
    EXPECT_EQ(my_fnc::parse_teg(tst, lst).at(1).second, "varname");
}
TEST(test_parse_teg002, restsprotocol)
{
    std::vector<std::string> lst{"type", "vname"};
    std::string tst = "<_parent_var type=\"parent type\", message=\"Введите вот это: \", vname=\"varname\">";
    EXPECT_EQ(my_fnc::parse_teg(tst, lst).at(0).second, "parenttype");
}
TEST(test_parse_teg003, restsprotocol)
{
    std::vector<std::string> lst{"type", "vname", "message"};
    std::string tst = "<_parent_var type=\"parent type\", message=\"Введите вот это: \", vname=\"varname\">";
    EXPECT_EQ(my_fnc::parse_teg(tst, lst).size(), 3);
}
TEST(test_parse_teg004, restsprotocol)
{
    std::vector<std::string> lst{"type", "vname"};
    std::string tst = "<_parent_var type=\"parent type\", message=\"Введите вот это: \", vname=\"varname\">";
    EXPECT_EQ(my_fnc::parse_teg(tst, lst).size(), 2);
}
TEST(test_parse_teg005, restsprotocol)
{
    std::vector<std::string> lst{"type", "vname"};
    std::string tst = "<_parent_var type=\"parent type\", message=\"Введите вот это: \", vname=\"varname\">";
    EXPECT_EQ(my_fnc::parse_teg(tst, lst).at(1).first, "vname");
}
TEST(test_parse_teg006, restsprotocol)
{
    std::vector<std::string> lst{"type", "vname"};
    std::string tst = "<_parent_var type=\"parent type\", message=\"Введите вот это: \", vname=\"varname\">";
    EXPECT_EQ(my_fnc::parse_teg(tst, lst).at(0).first, "type");
}
TEST(test_parse_teg007, restsprotocol)
{
    std::vector<std::string> lst{"typfe", "vngame"};
    std::string tst = "<_parent_var type=\"parent type\", message=\"Введите вот это: \", vname=\"varname\">";
    EXPECT_EQ(my_fnc::parse_teg(tst, lst).size(), 0);
}
TEST(test_parse_teg008, restsprotocol)
{
    std::vector<std::string> lst{"type", "vname"};
    std::string tst = "<_parent_var type=\"pasdfsfsdfpe\", message=\"Введите вот это: \", vname=\"varname\">";
    EXPECT_EQ(my_fnc::parse_teg(tst, lst).at(0).second, "pasdfsfsdfpe");
}
TEST(test_parse_teg009, restsprotocol)
{
    std::vector<std::string> lst{"type", "message", "vname"};
    std::string tst = "<_parent_var type=\"parent type\", message=\"Введите вот это: \", vname=\"varname\">";
    EXPECT_EQ(my_fnc::parse_teg(tst, lst).at(1).second, "Введите вот это: ");
}
TEST(test_parse_teg010, restsprotocol)
{
    std::vector<std::string> lst{"type", "vnahgfme"};
    std::string tst = "<_parent_var type=\"parent type\", message=\"Введите вот это: \", vname=\"varname\">";
    EXPECT_EQ(my_fnc::parse_teg(tst, lst).size(), 1);
}

// -----------====================Тестирование функции поиска тегов в строке Вторая версия =============================---------------------
TEST(test_search_teg_2_001, restsprotocol)
{
    std::string tst = "csdkncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzxdjf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    std::string teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).second, -1);
}
TEST(test_search_teg_2_002, restsprotocol)
{
    std::string tst = "csdkncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzxdjf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    std::string teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).first, -1);
}
TEST(test_search_teg_2_003, restsprotocol)
{
    std::string tst = "csd<_test_teg dsfsvxcv>kncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzxdjf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    std::string teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg, 2).first, 3);
}
TEST(test_search_teg_2_004, restsprotocol)
{
    std::string tst = "csd<_test_teg dsfsvxcv>kncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzxdjf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    std::string teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).second, 22);
}
TEST(test_search_teg_2_005, restsprotocol)
{
    std::string tst = "csd<_test_t<eg dsfsvxcv>kncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzxdjf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    std::string teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).second, -1);
}
TEST(test_search_teg_2_006, restsprotocol)
{
    std::string tst = "csd<_test_teg < dsfsvxcv>kncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzxdjf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    std::string teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).first, -1);
}
TEST(test_search_teg_2_007, restsprotocol)
{
    std::string tst = "csd<_test_teg dsfsvxcvdfkncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzx<djf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    std::string teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).second, -1);
}
TEST(test_search_teg_2_008, restsprotocol)
{
    std::string tst = "csd_test_teg dsfsvxcv>kncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzxdjf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    std::string teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).first, -1);
}
TEST(test_search_teg_2_009, restsprotocol)
{
    std::string tst = "c<sd<_test_teg dsfsvxcv>kncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzxdjf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    std::string teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).first, 4);
}
TEST(test_search_teg_2_010, restsprotocol)
{
    std::string tst = "sd<_test_";
    std::string teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).first, -1);
}
TEST(test_search_teg_2_011, restsprotocol)
{
    std::string tst = "c<sd<_test_teg d<_test_tegsfsvxcv>kncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzxdjf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    std::string teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).first, 16);
}
TEST(test_search_teg_2_012, restsprotocol)
{
    std::string tst = "c<sd<_test_teg d<_test_tegsfsvxcvkncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzxdjf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    std::string teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).second, 106);
}
TEST(test_search_teg_2_013, restsprotocol)
{
    std::string tst = "";
    std::string teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).first, -1);
}
TEST(test_search_teg_2_014, restsprotocol)
{
    std::string tst = "c<sd<_test_teg dsfsvxcv>kncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzxdjf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    std::string teg = "";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg).first, 4);
}
TEST(test_search_teg_2_015, restsprotocol)
{
    std::string tst = "csd<_test_teg dsfsvxcvkncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzxdjf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    std::string teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg, 6).second, -1);
}
TEST(test_search_teg_2_016, restsprotocol)
{
    std::string tst = "c<_test_teg s>fsvxcvkncdjsklvbgxdvmdjknxv,lczdjvgfnzkcvmzxdjf,g mjnl.c j;xl             slcfs><<<<<<<<<<<>ilmhcilgvil";
    std::string teg = "_test_teg";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg, 1).second, 13);
}
TEST(test_search_teg_2_017, restsprotocol)
{
    std::string tst = "<p>11111111111111111</p><br>"
            "<_parent_var type = \"klient\", message = \"имя клиента: \", vname = \"_kl_name\"><br>"
            "<b>222222222222222</b><br>"
            "3333333333333333333<br>"
            "<_prot_type type = \"z1\", message = \"Введите это: \", vname = \"zx\"><br>"
            "44444444444444444<br>"
            "<_const_type type = \"333FFF\", message = \"Значение дано нам:\", vname = \"gtr\"><br>"
            "555555555555555555555<br>"
            "<HTML>666666666666666666666666666<ZZZZ><br>"
            "<_parent_var type = \"klient\", message = \"имя клиента: \", vname = \"_kl_name\"><br>";
    std::string teg = "_parent_var";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg, 1).first, 28);
}
TEST(test_search_teg_2_018, restsprotocol)
{
    std::string tst = "<p>11111111111111111</p><br>"
            "<_parent_var type = \"klient\", message = \"имя клиента: \", vname = \"_kl_name\"><br>"
            "<b>222222222222222</b><br>"
            "3333333333333333333<br>"
            "<_prot_type type = \"z1\", message = \"Введите это: \", vname = \"zx\"><br>"
            "44444444444444444<br>"
            "<_const_type type = \"333FFF\", message = \"Значение дано нам:\", vname = \"gtr\"><br>"
            "555555555555555555555<br>"
            "<HTML>666666666666666666666666666<ZZZZ><br>"
            "<_parent_var type = \"klient\", message = \"имя клиента: \", vname = \"_kl_name\"><br>";
    std::string teg = "_parent_var";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg, 1).second, 113);
}
TEST(test_search_teg_2_019, restsprotocol)
{
    std::string tst = "<p>11111111111111111</p><br>"
            "<_parent_var type = \"klient\", message = \"имя клиента: \", vname = \"_kl_name\"><br>"
            "<b>222222222222222</b><br>"
            "3333333333333333333<br>"
            "<_prot_type type = \"z1\", message = \"Введите это: \", vname = \"zx\"><br>"
            "44444444444444444<br>"
            "<_const_type type = \"333FFF\", message = \"Значение дано нам:\", vname = \"gtr\"><br>"
            "555555555555555555555<br>"
            "<HTML>666666666666666666666666666<ZZZZ><br>"
            "<_parent_var type = \"klient\", message = \"имя клиента: \", vname = \"_kl_name\"><br>";
    std::string teg = "_prot_type";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg, 1).first, 167);
}
TEST(test_search_teg_2_020, restsprotocol)
{
    std::string tst = "<p>11111111111111111</p><br>"
            "<_parent_var type = \"klient\", message = \"имя клиента: \", vname = \"_kl_name\"><br>"
            "<b>222222222222222</b><br>"
            "3333333333333333333<br>"
            "<_prot_type type = \"z1\", message = \"Введите это: \", vname = \"zx\"><br>"
            "44444444444444444<br>"
            "<_const_type type = \"333FFF\", message = \"Значение дано нам:\", vname = \"gtr\"><br>"
            "555555555555555555555<br>"
            "<HTML>666666666666666666666666666<ZZZZ><br>"
            "<_parent_var type = \"klient\", message = \"имя клиента: \", vname = \"_kl_name\"><br>";
    std::string teg = "_const_type";
    EXPECT_EQ(my_fnc::serch_teg(tst, teg, 1).second, 357);
}
// -----------==================== Тестирование функции вольного превращения строки в число =============================---------------------
TEST(test_string_to_float_001, restsprotocol)
{
QString tst = "<p>11111111111111111</p><br>";
EXPECT_EQ(my_fnc::stof(tst), (float)11111111111111111);
}
TEST(test_string_to_float_002, restsprotocol)
{
QString tst = "<p>defsf75dasmkdh</p><br>";
EXPECT_EQ(my_fnc::stof(tst), (float)75);
}
TEST(test_string_to_float_003, restsprotocol)
{
QString tst = "xsdmxd  efdsf 67,3 fcgndcmds";
EXPECT_EQ(my_fnc::stof(tst), (float)67.3);
}
TEST(test_string_to_float_004, restsprotocol)
{
QString tst = "xsdocfhdvgmdf0lvmfsdvhnsdfunv";
EXPECT_EQ(my_fnc::stof(tst), (float)0);
}
TEST(test_string_to_float_005, restsprotocol)
{
QString tst = "vbdflvhodf-76,8vdgbdfbcbg";
EXPECT_EQ(my_fnc::stof(tst), (float)-76.8);
}
TEST(test_string_to_float_006, restsprotocol)
{
QString tst = "mjvgfcvghduvg89.77gfhgfhnn";
EXPECT_EQ(my_fnc::stof(tst), (float)89.77);
}
TEST(test_string_to_float_007, restsprotocol)
{
QString tst = "<p>vthgjgcdf66.666</p><br>";
EXPECT_EQ(my_fnc::stof(tst), (float)66.666);
}
TEST(test_string_to_float_008, restsprotocol)
{
QString tst = "<p>yvtyhbgjhgjn0.456ghvbgf";
EXPECT_EQ(my_fnc::stof(tst), (float)0.456);
}
TEST(test_string_to_float_009, restsprotocol)
{
QString tst = "tfbvhghnjhgh-0.4343hlmkl";
EXPECT_EQ(my_fnc::stof(tst), (float)-0.4343);
}
TEST(test_string_to_float_010, restsprotocol)
{
QString tst = "vgrtgkjfgjcbh-0,777vfgfcb cfg";
EXPECT_EQ(my_fnc::stof(tst), (float)-0.777);
}
// -----------==================== Тестирование функции поиска позиции скриптов js =============================---------------------
TEST(test_search_js_001, restsprotocol)
{
    std::string tst = "<script type='text/javascript'> ..... </script>";
    EXPECT_EQ(std::get<0>(my_fnc::serch_js(tst)), 0);
}
TEST(test_search_js_002, restsprotocol)
{
    std::string tst = "";
    EXPECT_EQ(std::get<0>(my_fnc::serch_js(tst, 1)), -1);
}
TEST(test_search_js_003, restsprotocol)
{
    std::string tst = "fd<script type='text/javascript'> ..... </script>";
    EXPECT_EQ(std::get<0>(my_fnc::serch_js(tst, 1)), 2);
}
TEST(test_search_js_004, restsprotocol)
{
    std::string tst = "<script type='text/javascript'> ...svcdrvgd.. </script>";
    EXPECT_EQ(std::get<0>(my_fnc::serch_js(tst)), 0);
}
TEST(test_search_js_005, restsprotocol)
{
    std::string tst = "<script  type='text/javascript'> ...svcdrvgd.. </script>";
    EXPECT_EQ(std::get<1>(my_fnc::serch_js(tst)), 31);
}
TEST(test_search_js_006, restsprotocol)
{
    std::string tst = "</script> gthdf<script  type='text/javascript'> ...svcdrvgd.. </script>";
    EXPECT_EQ(std::get<1>(my_fnc::serch_js(tst)), 46);
}
TEST(test_search_js_007, restsprotocol)
{
    std::string tst = "<script  type='text/javascript'> ...svcdrvgd.. </script>";
    EXPECT_EQ(std::get<2>(my_fnc::serch_js(tst)), 47);
}
TEST(test_search_js_008, restsprotocol)
{
    std::string tst = "<script  type='text/javascript'> ...svcdrvgd.. </script>";
    EXPECT_EQ(std::get<3>(my_fnc::serch_js(tst)), 55);
}
TEST(test_search_js_009, restsprotocol)
{
    std::string tst = "fevsfsd vytfybncvbvfgh <script fxcef </script> <script  type='text/javascript'> "
                      "var ret = Math.round(((parseFloat('<_parent_var type = \"obj\", "
                      "message = \"Введите_НПМНSн_трансформатора:\", vname = \"_trans_npmn\">') * 100) "
                      "/ parseFloat('<_ask_obj type = \"tn_circs\", message = \"Введите полную мощность S, "
                      "ВА:\", vname = \"sab\">'))*100)/100; var newpl = document.createElement('text');newpl.innerHTML = "
                      "ret; list.insertBefore(newpl, list.children[1]);</script>";
    EXPECT_EQ(std::get<2>(my_fnc::serch_js(tst)), 491);
}
TEST(test_search_js_010, restsprotocol)
{
    std::string tst = "fevsfsd vytfybncvbvfgh <script fxcef </script> "
                      "<script  type='text/javascript'> var "
                      "ret = Math.round(((parseFloat('<_parent_var type = \"obj\", message = "
                      "\"Введите_НПМНSн_трансформатора:\", vname = \"_trans_npmn\">') * 100) / "
                      "parseFloat('<_ask_obj type = \"tn_circs\", message = \"Введите полную мощность S, "
                      "ВА:\", vname = \"sab\">'))*100)/100; var newpl = document.createElement('text');newpl.innerHTML ="
                      " ret; list.insertBefore(newpl, list.children[1]);</script>";
    EXPECT_EQ(std::get<3>(my_fnc::serch_js(tst, 8)), 499);
}
TEST(test_search_js_011, restsprotocol)
{
    std::string tst = "fevsfsd vytfybncvbvfgh <script fxcef </script> "
                      "<script  type='text/javascript'> var ret = "
                      "Math.round(((parseFloat('<_parent_var type = \"obj\", message = "
                      "\"Введите_НПМНSн_трансформатора:\", vname = \"_trans_npmn\">') * 100) / parseFloat('<_ask_obj type = "
                      "\"tn_circs\", message = \"Введите полную мощность S, ВА:\", vname = "
                      "\"sab\">'))*100)/100; var newpl = document.createElement('text');newpl.innerHTML = "
                      "ret; list.insertBefore(newpl, list.children[1]);</script>";
    EXPECT_EQ(std::get<0>(my_fnc::serch_js(tst, 60)), -1);
}
TEST(test_search_js_012, restsprotocol)
{
    std::string tst = "fevsfsd vytfybncvbvfgh <script fxcef </script> <script  type='text/javascript'> var ret = "
                      "Math.round(((parseFloat('<_parent_var type = \"obj\", message = \"Введите_НПМНSн_трансформатора:\", "
                      "vname = \"_trans_npmn\">') * 100) / parseFloat('<_ask_obj type = \"tn_circs\", message "
                      "= \"Введите полную мощность S, ВА:\", vname = \"sab\">'))*100)/100; var newpl = \n"
                      "document.createElement('text');newpl.innerHTML = ret; list.insertBefore(newpl, list.children[1]);</script>";
    EXPECT_EQ(std::get<3>(my_fnc::serch_js(tst, 9)), 500);
}
TEST(test_search_js_013, restsprotocol)
{
    std::string tst = "fevsfsd vytfybncvbvfgh <script fxcef </script> <script  type='text/javascript'> var ret = "
                      "Math.round(\n((parseFloat('<_parent_var type = \"obj\", message = \"Введите_НПМНSн_трансформатора:\", "
                      "vname = \"_trans_npmn\">') * 100) / \nparseFloat('<_ask_obj type = \"tn_circs\", message "
                      "= \"Введите полную мощность S, ВА:\", vname = \"sab\">'))*100)/100; var newpl = \n"
                      "document.create\n\n\n\n\n\nElement('text');newpl.innerHTML = ret; list.insertBefore(newpl, list.children[1]);</script>";
    EXPECT_EQ(std::get<3>(my_fnc::serch_js(tst, 9)), 508);
}
TEST(test_search_js_014, restsprotocol)
{
    std::string tst = "fevsfsd vytfybncvbvfgh <script fxcef </script> <script  type='text/javascript'> var ret = "
                      "Math.round(\n((parseFloat('<_parent_var type = \"obj\", message = \"Введите_НПМНSн_трансформатора:\", "
                      "vname = \"_trans_npmn\">') * 100) / \nparseFloat('<_ask_obj type = \"tn_circs\", message "
                      "= \"Введите полную мощность S, ВА:\", vname = \"sab\">'))*100)/100; var newpl = \n"
                      "document.create\n\n\n\n\n\nElement('text');newpl.innerHTML = ret; list.insertBefore(newpl, list.children[1]);</script>пваирас fdvvtcfbgxdfbg"
                      "</script> cxdesf <script  type='text/ja";
    EXPECT_EQ(std::get<3>(my_fnc::serch_js(tst, 9)), 508);
}
// -----------==================== Тестирование функции замены "тэги <text id=\"ggg\"></text> на ###ggg###" =============================---------------------
TEST(test_hide_text_001, restsprotocol)
{
    QString tst = "тэги <text id=\"ggg\"></text> лопор";
    QString et = "тэги ###ggg### лопор";
    my_fnc::hide_tag_text(tst);
    EXPECT_EQ(tst, et);
}
TEST(test_hide_text_002, restsprotocol)
{
    QString tst = "тэги <text id=\"ggg\"></text> лопор <ghk> ohdksj <> , << <text id=\"itmo\"></text>";
    QString et = "тэги ###ggg### лопор <ghk> ohdksj <> , << ###itmo###";
    my_fnc::hide_tag_text(tst);
    EXPECT_EQ(tst, et);
}
TEST(test_hide_text_003, restsprotocol)
{
    QString tst = "тэги <text id=\"ggg\">sdf</text> лопор <ghk> ohdksj <> , << <text id=\"itmo\"></text>";
    QString et = "тэги <text id=\"ggg\">sdf</text> лопор <ghk> ohdksj <> , << ###itmo###";
    my_fnc::hide_tag_text(tst);
    EXPECT_EQ(tst, et);
}
TEST(test_hide_text_004, restsprotocol)
{
    QString tst = "тэги <textw id=\"ggg\">sdf</text> лопор <ghk> ohdksj <> , << <textdwa id=\"idtmo\"d></text>";
    QString et = "тэги <textw id=\"ggg\">sdf</text> лопор <ghk> ohdksj <> , << <textdwa id=\"idtmo\"d></text>";
    my_fnc::hide_tag_text(tst);
    EXPECT_EQ(tst, et);
}
TEST(test_hide_text_005, restsprotocol)
{
    QString tst = "";
    QString et = "";
    my_fnc::hide_tag_text(tst);
    EXPECT_EQ(tst, et);
}
TEST(test_hide_text_006, restsprotocol)
{
    QString tst = "fevsfsd vytfybncvbvfgh <script fxcef </script> <script  type='text/javascript'> var ret = "
                  "Math.round(\n((parseFloat('<_parent_var type = \"obj\", message = \"Введите_НПМНSн_трансформатора:\", "
                  "vname = \"_trans_npmn\">') * 100) / \nparseFloat('<_ask_obj type = \"tn_circs\", message "
                  "= \"Введите полную мощность S, ВА:\", <text id=\"itmo1\"></text>vname = \"sab\">'))*100)/100; var newpl = \n"
                  "document.create\n\n\n\n\n\nElement('text');newpl.innerHTML = ret; list.insertBefore(newpl, list.children[1]);</script>пваирас fdvvtcfbgxdfbg"
                  "</script> cxdesf <script  type='text/ja";
    QString et = "fevsfsd vytfybncvbvfgh <script fxcef </script> <script  type='text/javascript'> var ret = "
                 "Math.round(\n((parseFloat('<_parent_var type = \"obj\", message = \"Введите_НПМНSн_трансформатора:\", "
                 "vname = \"_trans_npmn\">') * 100) / \nparseFloat('<_ask_obj type = \"tn_circs\", message "
                 "= \"Введите полную мощность S, ВА:\", ###itmo1###vname = \"sab\">'))*100)/100; var newpl = \n"
                 "document.create\n\n\n\n\n\nElement('text');newpl.innerHTML = ret; list.insertBefore(newpl, list.children[1]);</script>пваирас fdvvtcfbgxdfbg"
                 "</script> cxdesf <script  type='text/ja";
    my_fnc::hide_tag_text(tst);
    EXPECT_EQ(tst, et);
}
// -----------==================== Тестирование функции замены ###ggg### на "тэги <text id=\"ggg\"></text>" =============================---------------------
TEST(test_show_text_001, restsprotocol)
{
    QString tst = "тэги <text id=\"ggg\"></text> лопор";
    QString et = "тэги ###ggg### лопор";
    my_fnc::show_tag_text(et);
    EXPECT_EQ(tst, et);
}
TEST(test_show_text_002, restsprotocol)
{
    QString tst = "тэги <text id=\"ggg\"></text> лопор <ghk> ohdksj <> , << <text id=\"itmo\"></text>";
    QString et = "тэги ###ggg### лопор <ghk> ohdksj <> , << ###itmo###";
    my_fnc::show_tag_text(et);
    EXPECT_EQ(tst, et);
}
TEST(test_show_text_003, restsprotocol)
{
    QString tst = "тэги <text id=\"ggg\">sdf</text> лопор <ghk> ohdksj <> , << <text id=\"itmo\"></text>";
    QString et = "тэги <text id=\"ggg\">sdf</text> лопор <ghk> ohdksj <> , << ###itmo###";
    my_fnc::show_tag_text(et);
    EXPECT_EQ(tst, et);
}
TEST(test_show_text_004, restsprotocol)
{
    QString tst = "тэги <textw id=\"ggg\">sdf</text> лопор <ghk> ohdksj <> , << <textdwa id=\"idtmo\"d></text>";
    QString et = "тэги <textw id=\"ggg\">sdf</text> лопор <ghk> ohdksj <> , << <textdwa id=\"idtmo\"d></text>";
    my_fnc::show_tag_text(et);
    EXPECT_EQ(tst, et);
}
TEST(test_show_text_005, restsprotocol)
{
    QString tst = "";
    QString et = "";
    my_fnc::show_tag_text(et);
    EXPECT_EQ(tst, et);
}
TEST(test_show_text_006, restsprotocol)
{
    QString tst = "fevsfsd vytfybncvbvfgh <script fxcef </script> <script  type='text/javascript'> var ret = "
                  "Math.round(\n((parseFloat('<_parent_var type = \"obj\", message = \"Введите_НПМНSн_трансформатора:\", "
                  "vname = \"_trans_npmn\">') * 100) / \nparseFloat('<_ask_obj type = \"tn_circs\", message "
                  "= \"Введите полную мощность S, ВА:\", <text id=\"itmo1\"></text>vname = \"sab\">'))*100)/100; var newpl = \n"
                  "document.create\n\n\n\n\n\nElement('text');newpl.innerHTML = ret; list.insertBefore(newpl, list.children[1]);</script>пваирас fdvvtcfbgxdfbg"
                  "</script> cxdesf <script  type='text/ja";
    QString et = "fevsfsd vytfybncvbvfgh <script fxcef </script> <script  type='text/javascript'> var ret = "
                 "Math.round(\n((parseFloat('<_parent_var type = \"obj\", message = \"Введите_НПМНSн_трансформатора:\", "
                 "vname = \"_trans_npmn\">') * 100) / \nparseFloat('<_ask_obj type = \"tn_circs\", message "
                 "= \"Введите полную мощность S, ВА:\", ###itmo1###vname = \"sab\">'))*100)/100; var newpl = \n"
                 "document.create\n\n\n\n\n\nElement('text');newpl.innerHTML = ret; list.insertBefore(newpl, list.children[1]);</script>пваирас fdvvtcfbgxdfbg"
                 "</script> cxdesf <script  type='text/ja";
    my_fnc::show_tag_text(et);
    EXPECT_EQ(tst, et);
}
