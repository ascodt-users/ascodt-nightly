package de.tum.ascodt.plugin;


public enum TestEnum {
  A(0), B(1);
  int value;

  TestEnum(int v) {
    value = v;
  }

  public int getValue() {
    return value;
  }
}

class Tester {
  void test() {
    testMethod(1);

  }

  void testMethod(int e) {

  }

  void testMethod(TestEnum e) {

  }
}