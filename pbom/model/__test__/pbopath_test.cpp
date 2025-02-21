#include "model/pbopath.h"
#include <gtest/gtest.h>

namespace pboman3::test {
    TEST(PboPath, Ctor_Initializes_Empty_Path) {
        const PboPath p;
        ASSERT_EQ(p.length(), 0);
    }

    TEST(PboPath, Ctor_Initializes_Path_From_Args) {
        const PboPath p{"p1", "p2", "p3"};

        ASSERT_EQ(p.length(), 3);
        ASSERT_EQ(p.at(0), "p1");
        ASSERT_EQ(p.at(1), "p2");
        ASSERT_EQ(p.at(2), "p3");
    }

    TEST(PboPath, Ctor_Initializes_Path_From_String) {
        const PboPath p1("p1/p2/p3");

        ASSERT_EQ(p1.length(), 3);
        ASSERT_EQ(p1.at(0), "p1");
        ASSERT_EQ(p1.at(1), "p2");
        ASSERT_EQ(p1.at(2), "p3");

        const PboPath p2("e1\\e2\\e3");

        ASSERT_EQ(p2.length(), 3);
        ASSERT_EQ(p2.at(0), "e1");
        ASSERT_EQ(p2.at(1), "e2");
        ASSERT_EQ(p2.at(2), "e3");
    }

    TEST(PboPath, MakeSibling_Creates_Sibling) {
        const PboPath p1("e1/f1");
        const PboPath s1 = p1.makeSibling("f2");

        ASSERT_EQ(s1.length(), 2);
        ASSERT_EQ(s1.at(0), "e1");
        ASSERT_EQ(s1.at(1), "f2");

        const PboPath p2("e1");
        const PboPath s2 = p2.makeSibling("e2");

        ASSERT_EQ(s2.length(), 1);
        ASSERT_EQ(s2.at(0), "e2");
    }
}
