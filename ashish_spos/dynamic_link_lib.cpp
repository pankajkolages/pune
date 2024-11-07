// : Write a program to create Dynamic Link Library for any mathematical operation and write
// an application program to test it. (Java Native Interface / Use VB or VC++).

// #include <jni.h>
// #include "MathLibrary.h" // Generated JNI header file
// #include <iostream>

// extern "C" {
//     JNIEXPORT jint JNICALL Java_MathLibrary_add(JNIEnv *env, jobject obj, jint a, jint b) {
//         return a + b;  // Simple addition operation
//     }
// }

// public class MathLibrary {

//     // Load the shared library
//     static {
//         System.loadLibrary("MathLibrary");
//     }

//     // Declare the native method
//     public native int add(int a, int b);

//     public static void main(String[] args) {
//         MathLibrary mathLibrary = new MathLibrary();
//         int result = mathLibrary.add(5, 3);
//         System.out.println("Result of addition: " + result);
//     }
// }

// 1.Compile the Java file:
// javac MathLibrary.java

// 2.Generate the JNI header file:
// javah -jni MathLibrary

// Step 4: Compile the C++ Code and Create the Shared Library
// 1.Compile the C++ code and link it into a shared library:

// g++ -fPIC -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -shared -o libMathLibrary.so MathLibrary.cpp

// 2.Move the shared library to a location where Java can find it (or you can specify the library path when running the Java application):
// mv libMathLibrary.so /usr/lib
// sudo ldconfig

// Step 5: Run the Java Application
// Run the Java application and specify the library path:
// java -Djava.library.path=. MathLibrary

// hello.java
public
class hello
{
public
    native int addNumbers(int a, int b);

    static
    {
        System.loadLibrary("hello");
    }

public
    static void main(String[] args)
    {
        hello obj = new hello();
        int result = obj.addNumbers(5, 3);
        System.out.println("Result: " + result);
    }
}

// hello.c

#include <jni.h>
#include "hello.h"

JNIEXPORT jint JNICALL
Java_hello_addNumbers(JNIEnv *env, jobject obj, jint a, jint b)
{
    return a + b;
}

c1
        javac hello.java

    2 javah -
    jni hello

    3 gcc -
    shared - fPIC - o libhello.so - I / usr / lib / jvm / java - 11 - openjdk - amd64 / include - I / usr / lib / jvm / java - 11 - openjdk - amd64 / include / linux hello.c

                                                                                                                                                                4 java -
    Djava.library.path =.hello
