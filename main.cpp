/*main.cpp*/

//
// Shyam Patel (NetID: spate54)
// U. of Illinois, Chicago
// CS 341, Fall 2018
// Project #03: Counter container
//
// Test cases for Counter container, which acts like a set but keeps a count
// of how many times each element was inserted.
//
// References:
// Unit testing based on Catch framework: https://github.com/catchorg/Catch2
// Catch tutorial: https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md#top
// install: sudo apt-get install catch
// compilation: g++ -std=c++11 -Wall -o main.exe main.cpp
// execution: ./main.exe
//

// let Catch provide main():
#define CATCH_CONFIG_MAIN

// gain access to Catch framework:
#include <catch.hpp>

// our Counter class:
#include "counter.h"

// *****************************************************************
//
// Test cases:
//
// *****************************************************************

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;


//
// TEST 01 : empty() and size() functions of the Counter class
//           on an empty set C
//
TEST_CASE("TEST 01 | empty Counter<int>", "[Counter]") {
    Counter<int> C;

    REQUIRE(C.empty() == true);
    REQUIRE(C.size()  == 0);
}//end test 01


//
// TEST 02 : insert(), operator[] and operator() functions of the
//           Counter class on set C consisting of one element
//
TEST_CASE("TEST 02 | Counter<int> with 1 element", "[Counter]") {
    Counter<int> C;

    REQUIRE(C.size()  == 0);
    REQUIRE(C.empty() == true);

    SECTION("inserting element") {
        C.insert(123);

        REQUIRE(C.size() == 1);
        REQUIRE(!C.empty());

        SECTION("element contains") {
            REQUIRE(C[123] == true);
        }

        SECTION("element count") {
            REQUIRE(C(123) == 1);
        }

        SECTION("unknown elements not contained") {
            REQUIRE(!C[0]);
            REQUIRE(!C[122]);
            REQUIRE(!C[124]);
        }

        SECTION("unknown element counts") {
            REQUIRE(C(0)   == 0);
            REQUIRE(C(122) == 0);
            REQUIRE(C(124) == 0);
        }
    }
}//end test 02


//
// TEST 03 : insert(), operator[] and operator() functions of the
//           Counter class on set C consisting of 3+ elements
//
TEST_CASE("TEST 03 | Counter<string> with 4 elements", "[Counter]") {
    Counter<string> C;

    REQUIRE(C.size()  == 0);
    REQUIRE(C.empty() == true);

    SECTION("inserting 1st element") {
        C.insert("apple");

        REQUIRE(C.size() == 1);
        REQUIRE(!C.empty());

        REQUIRE(C["apple"] == true);
        REQUIRE(C("apple") == 1);

        SECTION("inserting 3 more elements") {
            C += "banana";
            C.insert("pear");
            C += "pizza";

            REQUIRE(C.size() == 4);
            REQUIRE(!C.empty());

            REQUIRE(C["apple"]  == true);
            REQUIRE(C["banana"] == true);
            REQUIRE(C["pear"]   == true);
            REQUIRE(C["pizza"]  == true);

            SECTION("checking element counts") {
                REQUIRE(C("apple")  == 1);
                REQUIRE(C("banana") == 1);
                REQUIRE(C("pear")   == 1);
                REQUIRE(C("pizza")  == 1);
            }

            SECTION("checking non-elements") {
                REQUIRE(!C["appl"]);
                REQUIRE(!C["applee"]);
                REQUIRE(!C["Pear"]);
                REQUIRE(!C["piazza"]);
                REQUIRE(!C["zizza"]);
            }

            SECTION("checking non-element counts") {
                REQUIRE(C("appl")   == 0);
                REQUIRE(C("applee") == 0);
                REQUIRE(C("Pear")   == 0);
                REQUIRE(C("piazza") == 0);
                REQUIRE(C("zizza")  == 0);
            }
        }
    }
}//end test 03


//
// TEST 04 : operator+=, operator[], operator() and empty() functions
//           of the Counter class on set C consisting of 3+ elements
//
TEST_CASE("TEST 04 | Counter<int> += operator", "[Counter]") {
    Counter<int> C;                   // declare set C of type int

    REQUIRE(C.size() == 0);           // test : C has 0 elements
    REQUIRE(C.empty());               // test : C is empty

    SECTION("inserting 1st element") {
        C += 7;                       // insert 7 into set

        REQUIRE(C.size() == 1);       // test : C has 1 element
        REQUIRE(!C.empty());          // test : C is not empty
        REQUIRE(C[7]);                // test : C contains 7
        REQUIRE(C(7) == 1);           // test : C contains 7 once

        SECTION("inserting 3 more elements") {
            int random = rand();      // get random #
            C += 49;                  // insert 49       into set
            C += 1024;                // insert 1024     into set

            REQUIRE(C.size()  == 3);  // test : C has 3 elements
            REQUIRE(!C.empty());      // test : C is not empty

            C += 810;                 // insert 810      into set
            C += random;              // insert random # into set
            C += random;              // insert random # into set

            REQUIRE(C.size()  == 5);  // test : C has 5 elements
            REQUIRE(!C.empty());      // test : C is not empty
            REQUIRE(C[49]);           // test : C contains 49
            REQUIRE(C[1024]);         // test : C contains 1024
            REQUIRE(C[810]);          // test : C contains 810
            REQUIRE(C[random]);       // test : C contains random #
            REQUIRE(C(49)     == 1);  // test : C contains 49   once
            REQUIRE(C(1024)   == 1);  // test : C contains 1024 once
            REQUIRE(C(810)    == 1);  // test : C contains 810  once
            REQUIRE(C(random) == 2);  // test : C contains random # twice

            C.clear();                // empty set

            REQUIRE(C.size()  == 0);  // test : C has 0 elements
            REQUIRE(C.empty());       // test : C is empty
            REQUIRE(!C[49]);          // test : C doesn't contain 49
            REQUIRE(!C[1024]);        // test : C doesn't contain 1024
            REQUIRE(!C[810]);         // test : C doesn't contain 810
            REQUIRE(!C[random]);      // test : C doesn't contain random #
            REQUIRE(C(49)     == 0);  // test : C doesn't contain 49
            REQUIRE(C(1024)   == 0);  // test : C doesn't contain 1024
            REQUIRE(C(810)    == 0);  // test : C doesn't contain 810
            REQUIRE(C(random) == 0);  // test : C doesn't contain random #

            C += random;              // insert random # into set
            C += random;              // insert random # into set
            C += random;              // insert random # into set

            REQUIRE(C.size()  == 1);  // test : C has 1 element
            REQUIRE(!C.empty());      // test : C is not empty
            REQUIRE(C[random]);       // test : C contains random #
            REQUIRE(C(random) == 3);  // test : C contains random # thrice
        }
    }
}//end test 04


//
// TEST 05 : operator!=, operator* and operator++ functions of the
//           iterator class on set C consisting of 3+ elements
//
TEST_CASE("TEST 05 | Counter<int> iteration functions", "[Counter, iterator]") {
    Counter<int> C;                         // declare set C of type int

    SECTION("checking begin() == end() for empty set") {
        REQUIRE(C.size() == 0);             // test : C has 0 elements
        REQUIRE(C.empty());                 // test : C is empty
        REQUIRE(!(C.begin() != C.end()));   // test : begin() == end()
    }

    SECTION("checking sorted order") {
        int random = rand();                // get random #
                                            // insert key values in random order :
        C += random - 22;                   //   random # - 22
        C += random + 11;                   //   random # + 11
        C += random + 64;                   //   random # + 64
        C += random - 75;                   //   random # - 75
        C += random + 26;                   //   random # + 26
        C += random + 99;                   //   random # + 99
        C += random + 49;                   //   random # + 49
        C += random + 64;                   //   random # + 64
        C += random + 26;                   //   random # + 26
        C += random - 75;                   //   random # - 75

        REQUIRE(C.size() == 7);             // test : C has 7 elements
        REQUIRE(!C.empty());                // test : C is not empty
        REQUIRE(C(random - 75) == 2);       // test : C contains random # - 75 twice
        REQUIRE(C(random - 22) == 1);       // test : C contains random # - 22 once
        REQUIRE(C(random + 11) == 1);       // test : C contains random # + 11 once
        REQUIRE(C(random + 26) == 2);       // test : C contains random # + 26 twice
        REQUIRE(C(random + 49) == 1);       // test : C contains random # + 49 once
        REQUIRE(C(random + 64) == 2);       // test : C contains random # + 64 twice
        REQUIRE(C(random + 99) == 1);       // test : C contains random # + 99 once

        auto iter = C.begin();              // get iter to 1st element
                                            // iterate thru sorted set C :
        REQUIRE(*iter   == random - 75);    //   test : 1st element is random # - 75
        REQUIRE(*++iter == random - 22);    //   test : 2nd element is random # - 22
        REQUIRE(*++iter == random + 11);    //   test : 3rd element is random # + 11
        REQUIRE(*++iter == random + 26);    //   test : 4th element is random # + 26
        REQUIRE(*++iter == random + 49);    //   test : 5th element is random # + 49
        REQUIRE(*++iter == random + 64);    //   test : 6th element is random # + 64
        REQUIRE(*++iter == random + 99);    //   test : 7th element is random # + 99

        SECTION("checking end() is one past last element of set") {
            REQUIRE(!(++iter != C.end()));  // test : end() is one past last element
        }
    }
}//end test 05


//
// TEST 06 : copy assignment and clear() of the Counter class
//           on sets C1 and C2 each consisting of 3+ elements
//
TEST_CASE("TEST 06 | Counter<string> copy assignment", "[Counter, iterator]") {
    Counter<string> C1, C2;           // declare sets C1 and C2 of type string

    REQUIRE(C1.size() == 0);          // test : C1 has 0 elements
    REQUIRE(C2.size() == 0);          // test : C2 has 0 elements
    REQUIRE(C1.empty());              // test : C1 is empty
    REQUIRE(C2.empty());              // test : C2 is empty

    C1 += "Good";    C1 += "things";  // insert key values into set C1
    C1 += "come";    C1 += "to";
    C1 += "those";   C1 += "who";
    C1 += "wait.";   C1 += "Or";
    C1 += "to";      C1 += "those";
    C1 += "who";     C1 += "are";
    C1 += "lucky.";

    REQUIRE(C1.size() == 10);         // test : C1 contains 10 elements
    REQUIRE(C1["Good"  ]);            // test : C1 contains "Good"
    REQUIRE(C1["things"]);            // test : C1 contains "things"
    REQUIRE(C1["come"  ]);            // test : C1 contains "come"
    REQUIRE(C1["to"    ]);            // test : C1 contains "to"
    REQUIRE(C1["those" ]);            // test : C1 contains "those"
    REQUIRE(C1["who"   ]);            // test : C1 contains "who"
    REQUIRE(C1["wait." ]);            // test : C1 contains "wait."
    REQUIRE(C1["Or"    ]);            // test : C1 contains "Or"
    REQUIRE(C1["are"   ]);            // test : C1 contains "are"
    REQUIRE(C1["lucky."]);            // test : C1 contains "lucky."

    SECTION("copy assigning C1 to C2") {
        C2 = C1;                                     // copy assign C1 to C2

        REQUIRE(C2.size()    == C1.size());          // test : C2 has the same # of elements
        REQUIRE(C2("Good")   == C1("Good"  ));       // test : C2 contains the same # of "Good"
        REQUIRE(C2("things") == C1("things"));       // test : C2 contains the same # of "things"
        REQUIRE(C2("come")   == C1("come"  ));       // test : C2 contains the same # of "come"
        REQUIRE(C2("to")     == C1("to"    ));       // test : C2 contains the same # of "to"
        REQUIRE(C2("those")  == C1("those" ));       // test : C2 contains the same # of "those"
        REQUIRE(C2("who")    == C1("who"   ));       // test : C2 contains the same # of "who"
        REQUIRE(C2("wait.")  == C1("wait." ));       // test : C2 contains the same # of "wait."
        REQUIRE(C2("Or")     == C1("Or"    ));       // test : C2 contains the same # of "Or"
        REQUIRE(C2("are")    == C1("are"   ));       // test : C2 contains the same # of "are"
        REQUIRE(C2("lucky.") == C1("lucky."));       // test : C2 contains the same # of "lucky."

        SECTION("checking independence of C1 and C2") {
            REQUIRE(C1.begin() != C2.begin());       // test : begin() of C1 != begin() of C2
            REQUIRE(C1.end()   != C2.end());         // test : end()   of C1 != end()   of C2

            C1 += "And";     C1 += "sometimes";      // insert key values into set C1
            C1 += "those";   C1 += "who";
            C2 += "cry";     C2 += "wolf";           // insert key values into set C2
            C2 += "regret";  C2 += "it.";

            REQUIRE(C1.size() == 12);                         // test : C1 contains 12 elements
            REQUIRE(C1("And"      ) == C2("And"      ) + 1);  // test : C1 contains one more "And"
            REQUIRE(C1("sometimes") == C2("sometimes") + 1);  // test : C1 contains one more "sometimes"
            REQUIRE(C1("those"    ) == C2("those"    ) + 1);  // test : C1 contains one more "those"
            REQUIRE(C1("who"      ) == C2("who"      ) + 1);  // test : C1 contains one more "who"
            REQUIRE(!C1["cry"     ]);                         // test : C1 doesn't contain "cry"
            REQUIRE(!C1["wolf"    ]);                         // test : C1 doesn't contain "wolf"
            REQUIRE(!C1["regret"  ]);                         // test : C1 doesn't contain "regret"
            REQUIRE(!C1["it."     ]);                         // test : C1 doesn't contain "it."

            REQUIRE(C2.size() == 14);                         // test : C2 contains 14 elements
            REQUIRE(!C2["And"      ]);                        // test : C2 doesn't contain "And"
            REQUIRE(!C2["sometimes"]);                        // test : C2 doesn't contain "sometimes"
            REQUIRE(C2("cry"   ) == C1("cry"   ) + 1);        // test : C2 contains one more "cry"
            REQUIRE(C2("wolf"  ) == C1("wolf"  ) + 1);        // test : C2 contains one more "wolf"
            REQUIRE(C2("regret") == C1("regret") + 1);        // test : C2 contains one more "regret"
            REQUIRE(C2("it."   ) == C1("it."   ) + 1);        // test : C2 contains one more "it."

            SECTION("checking sorted order of C1") {
                auto iter = C1.begin();              // get iter to 1st element of C1
                                                     // iterate thru sorted set C1 :
                REQUIRE(*iter   == "And"      );     //   test : 1st  element is "And"
                REQUIRE(*++iter == "Good"     );     //   test : 2nd  element is "Good"
                REQUIRE(*++iter == "Or"       );     //   test : 3rd  element is "Or"
                REQUIRE(*++iter == "are"      );     //   test : 4th  element is "are"
                REQUIRE(*++iter == "come"     );     //   test : 5th  element is "come"
                REQUIRE(*++iter == "lucky."   );     //   test : 6th  element is "lucky."
                REQUIRE(*++iter == "sometimes");     //   test : 7th  element is "sometimes"
                REQUIRE(*++iter == "things"   );     //   test : 8th  element is "things"
                REQUIRE(*++iter == "those"    );     //   test : 9th  element is "those"
                REQUIRE(*++iter == "to"       );     //   test : 10th element is "to"
                REQUIRE(*++iter == "wait."    );     //   test : 11th element is "wait."
                REQUIRE(*++iter == "who"      );     //   test : 12th element is "who"
                REQUIRE(!(++iter != C1.end()));      //   test : end() is one past last element
            }

            SECTION("emptying set C1") {
                C1.clear();                          // empty set C1

                REQUIRE(C1.size() == 0);             // test : C1 contains 0 elements
                REQUIRE(C1.empty());                 // test : C1 is empty
                REQUIRE(!(C1.begin() != C1.end()));  // test : begin() == end()

                REQUIRE(C2.size() == 14);            // test : C2 contains 14 elements
                REQUIRE(!C2.empty());                // test : C2 is not empty
            }

            SECTION("checking sorted order of C2") {
                auto iter = C2.begin();              // get iter to 1st element of C2
                                                     // iterate thru sorted set C1 :
                REQUIRE(*iter   == "Good"    );      //   test : 1st  element is "Good"
                REQUIRE(*++iter == "Or"    );        //   test : 2nd  element is "Or"
                REQUIRE(*++iter == "are"   );        //   test : 3rd  element is "are"
                REQUIRE(*++iter == "come"  );        //   test : 4th  element is "come"
                REQUIRE(*++iter == "cry"   );        //   test : 5th  element is "cry"
                REQUIRE(*++iter == "it."   );        //   test : 6th  element is "it."
                REQUIRE(*++iter == "lucky.");        //   test : 7th  element is "lucky."
                REQUIRE(*++iter == "regret");        //   test : 8th  element is "regret"
                REQUIRE(*++iter == "things");        //   test : 9th  element is "things"
                REQUIRE(*++iter == "those" );        //   test : 10th element is "those"
                REQUIRE(*++iter == "to"    );        //   test : 11th element is "to"
                REQUIRE(*++iter == "wait." );        //   test : 12th element is "wait."
                REQUIRE(*++iter == "who"   );        //   test : 13th element is "who"
                REQUIRE(*++iter == "wolf"  );        //   test : 14th element is "wolf"
                REQUIRE(!(++iter != C2.end()));      //   test : end() is one past last element
            }

            SECTION("emptying set C2") {
                C2.clear();                          // empty set C1

                REQUIRE(C2.size() == 0);             // test : C2 contains 0 elements
                REQUIRE(C2.empty());                 // test : C2 is empty
                REQUIRE(!(C2.begin() != C2.end()));  // test : begin() of C2 == end()   of C2

                REQUIRE(C2.begin() != C1.begin());   // test : begin() of C2 != begin() of C1
                REQUIRE(C2.begin() != C1.end());     // test : begin() of C2 != end()   of C1
                REQUIRE(C2.end()   != C1.end());     // test : end()   of C2 != end()   of C1
            }
        }
    }
}//end test 06


//
// TEST 07 : copy constructor and clear() of the Counter class
//           on sets C1 and C2 each consisting of 3+ elements
//
TEST_CASE("TEST 07 | Counter<string> copy constructor", "[Counter]") {
    Counter<string> C1;               // declare set C1 of type string

    REQUIRE(C1.size() == 0);          // test : C1 has 0 elements
    REQUIRE(C1.empty());              // test : C1 is empty

    C1 += "Good";    C1 += "things";  // insert key values into set C1
    C1 += "come";    C1 += "to";
    C1 += "those";   C1 += "who";
    C1 += "wait.";   C1 += "Or";
    C1 += "to";      C1 += "those";
    C1 += "who";     C1 += "are";
    C1 += "lucky.";

    REQUIRE(C1.size() == 10);         // test : C1 contains 10 elements
    REQUIRE(C1["Good"  ]);            // test : C1 contains "Good"
    REQUIRE(C1["things"]);            // test : C1 contains "things"
    REQUIRE(C1["come"  ]);            // test : C1 contains "come"
    REQUIRE(C1["to"    ]);            // test : C1 contains "to"
    REQUIRE(C1["those" ]);            // test : C1 contains "those"
    REQUIRE(C1["who"   ]);            // test : C1 contains "who"
    REQUIRE(C1["wait." ]);            // test : C1 contains "wait."
    REQUIRE(C1["Or"    ]);            // test : C1 contains "Or"
    REQUIRE(C1["are"   ]);            // test : C1 contains "are"
    REQUIRE(C1["lucky."]);            // test : C1 contains "lucky."

    SECTION("copy constructing C2 from C1") {
        Counter<string> C2(C1);                      // copy construct C2 from C1

        REQUIRE(C2.size()    == C1.size());          // test : C2 has the same # of elements
        REQUIRE(C2("Good")   == C1("Good"  ));       // test : C2 contains the same # of "Good"
        REQUIRE(C2("things") == C1("things"));       // test : C2 contains the same # of "things"
        REQUIRE(C2("come")   == C1("come"  ));       // test : C2 contains the same # of "come"
        REQUIRE(C2("to")     == C1("to"    ));       // test : C2 contains the same # of "to"
        REQUIRE(C2("those")  == C1("those" ));       // test : C2 contains the same # of "those"
        REQUIRE(C2("who")    == C1("who"   ));       // test : C2 contains the same # of "who"
        REQUIRE(C2("wait.")  == C1("wait." ));       // test : C2 contains the same # of "wait."
        REQUIRE(C2("Or")     == C1("Or"    ));       // test : C2 contains the same # of "Or"
        REQUIRE(C2("are")    == C1("are"   ));       // test : C2 contains the same # of "are"
        REQUIRE(C2("lucky.") == C1("lucky."));       // test : C2 contains the same # of "lucky."

        SECTION("checking independence of C1 and C2") {
            REQUIRE(C1.begin() != C2.begin());       // test : begin() of C1 != begin() of C2
            REQUIRE(C1.end()   != C2.end());         // test : end()   of C1 != end()   of C2

            C1 += "And";     C1 += "sometimes";      // insert key values into set C1
            C1 += "those";   C1 += "who";
            C2 += "cry";     C2 += "wolf";           // insert key values into set C2
            C2 += "regret";  C2 += "it.";

            REQUIRE(C1.size() == 12);                         // test : C1 contains 12 elements
            REQUIRE(C1("And"      ) == C2("And"      ) + 1);  // test : C1 contains one more "And"
            REQUIRE(C1("sometimes") == C2("sometimes") + 1);  // test : C1 contains one more "sometimes"
            REQUIRE(C1("those"    ) == C2("those"    ) + 1);  // test : C1 contains one more "those"
            REQUIRE(C1("who"      ) == C2("who"      ) + 1);  // test : C1 contains one more "who"
            REQUIRE(!C1["cry"     ]);                         // test : C1 doesn't contain "cry"
            REQUIRE(!C1["wolf"    ]);                         // test : C1 doesn't contain "wolf"
            REQUIRE(!C1["regret"  ]);                         // test : C1 doesn't contain "regret"
            REQUIRE(!C1["it."     ]);                         // test : C1 doesn't contain "it."

            REQUIRE(C2.size() == 14);                         // test : C2 contains 14 elements
            REQUIRE(!C2["And"      ]);                        // test : C2 doesn't contain "And"
            REQUIRE(!C2["sometimes"]);                        // test : C2 doesn't contain "sometimes"
            REQUIRE(C2("cry"   ) == C1("cry"   ) + 1);        // test : C2 contains one more "cry"
            REQUIRE(C2("wolf"  ) == C1("wolf"  ) + 1);        // test : C2 contains one more "wolf"
            REQUIRE(C2("regret") == C1("regret") + 1);        // test : C2 contains one more "regret"
            REQUIRE(C2("it."   ) == C1("it."   ) + 1);        // test : C2 contains one more "it."

            SECTION("checking sorted order of C1") {
                auto iter = C1.begin();              // get iter to 1st element of C1
                                                     // iterate thru sorted set C1 :
                REQUIRE(*iter   == "And"      );     //   test : 1st  element is "And"
                REQUIRE(*++iter == "Good"     );     //   test : 2nd  element is "Good"
                REQUIRE(*++iter == "Or"       );     //   test : 3rd  element is "Or"
                REQUIRE(*++iter == "are"      );     //   test : 4th  element is "are"
                REQUIRE(*++iter == "come"     );     //   test : 5th  element is "come"
                REQUIRE(*++iter == "lucky."   );     //   test : 6th  element is "lucky."
                REQUIRE(*++iter == "sometimes");     //   test : 7th  element is "sometimes"
                REQUIRE(*++iter == "things"   );     //   test : 8th  element is "things"
                REQUIRE(*++iter == "those"    );     //   test : 9th  element is "those"
                REQUIRE(*++iter == "to"       );     //   test : 10th element is "to"
                REQUIRE(*++iter == "wait."    );     //   test : 11th element is "wait."
                REQUIRE(*++iter == "who"      );     //   test : 12th element is "who"
                REQUIRE(!(++iter != C1.end()));      //   test : end() is one past last element
            }

            SECTION("emptying set C1") {
                C1.clear();                          // empty set C1

                REQUIRE(C1.size() == 0);             // test : C1 contains 0 elements
                REQUIRE(C1.empty());                 // test : C1 is empty
                REQUIRE(!(C1.begin() != C1.end()));  // test : begin() == end()

                REQUIRE(C2.size() == 14);            // test : C2 contains 14 elements
                REQUIRE(!C2.empty());                // test : C2 is not empty
            }

            SECTION("checking sorted order of C2") {
                auto iter = C2.begin();              // get iter to 1st element of C2
                                                     // iterate thru sorted set C1 :
                REQUIRE(*iter == "Good"    );        //   test : 1st  element is "Good"
                REQUIRE(*++iter == "Or"    );        //   test : 2nd  element is "Or"
                REQUIRE(*++iter == "are"   );        //   test : 3rd  element is "are"
                REQUIRE(*++iter == "come"  );        //   test : 4th  element is "come"
                REQUIRE(*++iter == "cry"   );        //   test : 5th  element is "cry"
                REQUIRE(*++iter == "it."   );        //   test : 6th  element is "it."
                REQUIRE(*++iter == "lucky.");        //   test : 7th  element is "lucky."
                REQUIRE(*++iter == "regret");        //   test : 8th  element is "regret"
                REQUIRE(*++iter == "things");        //   test : 9th  element is "things"
                REQUIRE(*++iter == "those" );        //   test : 10th element is "those"
                REQUIRE(*++iter == "to"    );        //   test : 11th element is "to"
                REQUIRE(*++iter == "wait." );        //   test : 12th element is "wait."
                REQUIRE(*++iter == "who"   );        //   test : 13th element is "who"
                REQUIRE(*++iter == "wolf"  );        //   test : 14th element is "wolf"
                REQUIRE(!(++iter != C2.end()));      //   test : end() is one past last element
            }

            SECTION("emptying set C2") {
                C2.clear();                          // empty set C1

                REQUIRE(C2.size() == 0);             // test : C2 contains 0 elements
                REQUIRE(C2.empty());                 // test : C2 is empty
                REQUIRE(!(C2.begin() != C2.end()));  // test : begin() of C2 == end()   of C2

                REQUIRE(C2.begin() != C1.begin());   // test : begin() of C2 != begin() of C1
                REQUIRE(C2.begin() != C1.end());     // test : begin() of C2 != end()   of C1
                REQUIRE(C2.end()   != C1.end());     // test : end()   of C2 != end()   of C1
            }
        }
    }
}//end test 07


//
// TEST 08 : stress test of the Counter and iterator classes
//
TEST_CASE("TEST 08 | Counter<int>, iterator stress test", "[Counter, iterator]") {
    Counter<int> C;                            // declare counter set C of type int
    set<int> random;                           // declare set of random #'s
    const int size = 100000;

    SECTION("using 10^5 elements") {
        for (int i = 0; i < size; i++) {
            int num = rand() % size;           // generate random #
            random.insert(num);                //   insert it into random set
            C += num;                          //   insert it into counter set C
        }

        REQUIRE(C.size() == random.size());    // test : set C has same size as random set

        for (const auto& r : random)
            REQUIRE(C[r]);                     // test : set C contains the same values

        SECTION("using iterators") {
            auto iter1 = C.begin();            // get iter to 1st element of counter set C
            auto iter2 = random.begin();       // get iter to 1st element of random set

            while (iter1 != C.end() && iter2 != random.end()) {
                REQUIRE(*iter1 == *iter2);     // test : ordering of set C matches random set
                ++iter1;                       // increment iter to set C
                ++iter2;                       // increment iter to random set
            }

            REQUIRE(!(iter1 != C.end()));      // test : iter to set C == end() of set C
        }

        SECTION("emptying set C") {
            C.clear();                         // empty set C
            C.clear();                         // empty set C (again)
            C.clear();                         // empty set C (again)

            REQUIRE(C.size() == 0);            // test : C contains 0 elements
            REQUIRE(C.empty());                // test : C is empty
            REQUIRE(!(C.begin() != C.end()));  // test : begin() of C == end() of C

            for (const auto& r : random)
                REQUIRE(!C[r]);                // test : set C doesn't contain values
        }
    }
}//end test 08


//
// TEST 09 : test for iterator
//
TEST_CASE("TEST 09 | Counter<int>, iterator test", "[iterator]") {
    Counter<int> C;                        // declare counter set C of type int

    SECTION("checking begin() == end() for empty counter") {
        REQUIRE(C.size() == 0);            // test : C contains 0 elements
        REQUIRE(C.empty());                // test : C is empty
        REQUIRE(!(C.begin() != C.end()));  // test : begin() of C == end() of C
    }

    for (int i = 10; i < 30; i++)
        C += i;                            // insert sorted values into C

    REQUIRE(C.size() == 20);               // test : C contains 20 elements

    SECTION("checking basic iteration") {
        auto iter = C.begin();             // get iter to 1st element of C

        for (int i = 11; i < 30; i++)
            REQUIRE(*++iter == i);         // test : C contains sorted values

        REQUIRE(!(++iter != C.end()));     // test : end() is one past last element
    }

    SECTION("emptying set C") {
        C.clear();                         // empty set C

        REQUIRE(C.size() == 0);            // test : C contains 0 elements
        REQUIRE(C.empty());                // test : C is empty
        REQUIRE(!(C.begin() != C.end()));  // test : begin() of C == end() of C
    }
}//end test 09


//
// TEST 10 : test with Counter of custom class
//
class Minion {
private:
    // data members
    int ID;
    string name;

public:
    // constructor
    Minion(int _id, string _name)
      : ID(_id), name(_name) { }

    // getters
    int    getID()   const { return ID;   }
    string getName() const { return name; }

    // overloaded operator<
    bool operator<(const Minion& other) const {
        return this->ID < other.ID;
    }//end operator<
};//end Minion class

TEST_CASE("TEST 10 | Counter<Minion>, iterator test", "[Counter]") {
    Counter<Minion> C;                     // declare counter set C of type Minion
    Minion M1(1, "Bob"   );
    Minion M2(2, "Kevin" );
    Minion M3(3, "Stuart");

    SECTION("checking begin() == end() for empty counter") {
        REQUIRE(C.size() == 0);            // test : C contains 0 elements
        REQUIRE(C.empty());                // test : C is empty
        REQUIRE(!(C.begin() != C.end()));  // test : begin() of C == end() of C
    }

    SECTION("inserting Minion characters") {
        C.insert(M1);
        C.insert(M2);
        C.insert(M3);

        REQUIRE(C.size() == 3);            // test : C contains 3 elements
        REQUIRE(!C.empty());               // test : C is not empty
        REQUIRE(C.begin() != C.end());     // test : begin() of C != end() of C
        REQUIRE(C[M1]);                    // test : C contains Bob
        REQUIRE(C[M2]);                    // test : C contains Kevin
        REQUIRE(C[M3]);                    // test : C contains Stuart
        REQUIRE(C(M1) == 1);               // test : C contains Bob    once
        REQUIRE(C(M2) == 1);               // test : C contains Kevin  once
        REQUIRE(C(M3) == 1);               // test : C contains Stuart once
    }

    SECTION("checking unknown elements") {
        Minion P(4, "Steph" );
        Minion Q(5, "Grey"  );
        Minion R(6, "Maxine");

        REQUIRE(C(P) == 0);                // test : C doesn't contain Steph
        REQUIRE(C(Q) == 0);                // test : C doesn't contain Grey
        REQUIRE(C(R) == 0);                // test : C doesn't contain Maxine
    }

    SECTION("emptying set C") {
        C.clear();                         // empty set C

        REQUIRE(C.size() == 0);            // test : C contains 0 elements
        REQUIRE(C.empty());                // test : C is empty
        REQUIRE(!(C.begin() != C.end()));  // test : begin() of C == end() of C
    }
}//end test 10
