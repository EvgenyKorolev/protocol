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
// -----------====================Тестирование функции вольного превращения строки в число =============================---------------------
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
