// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

#include "1_Date.h"

using namespace ::testing;

TEST(Date_Tests, EmptyDate) {
    Date newDate;
    ASSERT_EQ("00/00/0000", newDate.getDate());
}

TEST(Date_Tests, IncorrectDate) {
    Date newDate(2, 40, 1952);
    ASSERT_TRUE(newDate.isEmpty());
}

TEST(Date_Tests, SettingIncorrectDate) {
    Date newDate(2, 5, 1952);
    newDate.setDate(2, 40, 2000);
    ASSERT_EQ("00/00/0000", newDate.getDate());
}

TEST(Date_Tests, CorrectDate) {
    Date newDate(29, 2, 2000);
    ASSERT_EQ("29/02/2000", newDate.getDate());
}

TEST(Date_Tests, Stream) {
    Date newDate;
    std::istringstream dateStream("12/08/2002");
    dateStream >> newDate;
    ASSERT_EQ("12/08/2002", newDate.getDate());
}

TEST(Date_Tests, Addition) {
    Date newDate;
    newDate.setDate(1, 2, 1999);
    newDate = newDate + 58;
    ASSERT_EQ("31/03/1999", newDate.getDate());
    newDate = newDate + 5;
    ASSERT_EQ("05/04/1999", newDate.getDate());
}

TEST(Date_Tests, AdditionThroughYear) {
    Date newDate;
    newDate.setDate(20, 12, 2000);
    newDate = newDate + 13;
    ASSERT_EQ("02/01/2001", newDate.getDate());
}

TEST(Date_Tests, NegativeAddition) {
    Date newDate(25, 4, 2014);
    newDate = newDate + -26;
    ASSERT_EQ("25/04/2014", newDate.getDate());
}

TEST(Date_Tests, Comparisons) {
    Date date1(12, 4, 2023);
    Date date2(30, 1, 2023);
    ASSERT_TRUE(date2 < date1);
    ASSERT_FALSE(date1 < date2);
    ASSERT_FALSE(date1 < date1);
}

TEST(Date_Tests, Equality) {
    Date date1(12, 8, 2023);
    Date date2(12, 8, 2023);
    ASSERT_TRUE(date1 == date2);
}