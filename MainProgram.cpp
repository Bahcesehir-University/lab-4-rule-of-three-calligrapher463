// ============================================================================
// Lab: Destructors, Copy Constructors, and Default Memberwise Assignment
// Course: Object-Oriented Programming for Engineers
// File: MainProgram.cpp (Student Version)
// ============================================================================
// INSTRUCTIONS:
// - Implement all functions marked with TODO
// - Do NOT change function signatures
// - Do NOT add extra #include directives
// - All code must remain in this single file
// ============================================================================
 
#include <iostream>
#include <cstring>
#include <string>
 
using namespace std;
 
// ============================================================================
// GLOBAL TRACKING VARIABLES
// ============================================================================
// These counters help tests verify that your special member functions are
// actually being called. Increment them at the START of each function body.
 
int g_constructorCount = 0;
int g_destructorCount = 0;
int g_copyConstructorCount = 0;
int g_assignmentCount = 0;
 
// Helper functions to read/reset counters (DO NOT MODIFY)
int getConstructorCount() { return g_constructorCount; }
int getDestructorCount() { return g_destructorCount; }
int getCopyConstructorCount() { return g_copyConstructorCount; }
int getAssignmentCount() { return g_assignmentCount; }
void resetAllCounters() {
g_constructorCount = 0;
g_destructorCount = 0;
g_copyConstructorCount = 0;
g_assignmentCount = 0;
}
 
// ============================================================================
// CLASS DEFINITION: DynamicBuffer
// ============================================================================
// This class manages a dynamically allocated C-string (char array).
// It demonstrates the "Rule of Three": if a class manages a resource,
// you must define a destructor, copy constructor, and copy assignment operator.
// ============================================================================
 
class DynamicBuffer {
private:
char* m_data; // pointer to dynamically allocated C-string
int m_length; // length of the string (excluding '\0')
 
public:
// --------------------------------------------------
// Parameterized Constructor
// --------------------------------------------------
// - Allocate memory for a copy of the input string
// - Copy the string content into m_data
// - Set m_length to the length of the string
// - Increment g_constructorCount
DynamicBuffer(const char* input) {
g_constructorCount++;
m_length=strlen(input);
m_data=new char[m_length+1];
strcpy(m_data, input);
// TODO: Implement constructor
// 1. Increment g_constructorCount
// 2. Calculate length of input using strlen()
// 3. Allocate m_data with new char[m_length + 1]
// 4. Copy input into m_data using strcpy()
}
 
// --------------------------------------------------
// Destructor
// --------------------------------------------------
// - Free the dynamically allocated memory
// - Increment g_destructorCount
~DynamicBuffer() {
g_destructorCount++;
delete[] m_data;
// TODO: Implement destructor
// 1. Increment g_destructorCount
// 2. Delete the dynamically allocated array (delete[])
}
 
// --------------------------------------------------
// Copy Constructor (Deep Copy)
// --------------------------------------------------
// - Allocate NEW memory for this object
// - Copy the content from 'other' into the new memory
// - Increment g_copyConstructorCount
DynamicBuffer(const DynamicBuffer& other) {
g_copyConstructorCount++;
m_length=other.m_length;
m_data=new char[m_length+1];
strcpy(m_data, other.m_data);
// TODO: Implement copy constructor
// 1. Increment g_copyConstructorCount
// 2. Copy m_length from other
// 3. Allocate new memory: new char[m_length + 1]
// 4. Copy string data using strcpy()
}
 
// --------------------------------------------------
// Copy Assignment Operator (Deep Copy)
// --------------------------------------------------
// - Check for self-assignment
// - Free existing memory
// - Allocate new memory and copy content from 'other'
// - Increment g_assignmentCount
// - Return *this
DynamicBuffer& operator=(const DynamicBuffer& other) {
g_assignmentCount++;
if(this==&other)
{
return*this;
}
delete[] m_data;
m_length=other.m_length;
m_data=new char[m_length+1];
strcpy(m_data,other.m_data);
// TODO: Implement copy assignment operator
// 1. Increment g_assignmentCount
// 2. Check for self-assignment (if this == &other)
// 3. Delete old m_data (delete[])
// 4. Copy m_length from other
// 5. Allocate new memory: new char[m_length + 1]
// 6. Copy string data using strcpy()
// 7. Return *this
return *this;
}
 
// --------------------------------------------------
// Accessors (DO NOT MODIFY)
// --------------------------------------------------
const char* getData() const { return m_data; }
int getLength() const { return m_length; }
 
// --------------------------------------------------
// setData - replace the buffer with a new string
// --------------------------------------------------
// - Free old memory
// - Allocate new memory for the new string
// - Copy the new string
void setData(const char* newData) {
delete[] m_data;
m_length=strlen(newData);
m_data=new char[m_length+1];
strcpy(m_data,newData);
// TODO: Implement setData
// 1. Delete old m_data (delete[])
// 2. Calculate new length with strlen()
// 3. Allocate new memory: new char[m_length + 1]
// 4. Copy newData into m_data using strcpy()
}
 
// --------------------------------------------------
// print - display the buffer content (DO NOT MODIFY)
// --------------------------------------------------
void print() const {
cout << "DynamicBuffer[\"" << m_data << "\", length=" << m_length << "]" << endl;
}
};
 
// ============================================================================
// FREE FUNCTION: createBufferCopy
// ============================================================================
// This function takes a DynamicBuffer BY VALUE (triggers copy constructor)
// and returns it BY VALUE (may trigger copy or move).
// DO NOT MODIFY this function.
 
DynamicBuffer createBufferCopy(DynamicBuffer buf) {
return buf;
}
 
// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main() {
cout << "=== Destructors, Copy Constructors & Assignment Lab ===" << endl;
cout << endl;
 
// --- Part 1: Constructor & Destructor ---
cout << "--- Part 1: Constructor & Destructor ---" << endl;
{
DynamicBuffer b1("Hello");
b1.print();
cout << "b1 created. Constructor count: " << getConstructorCount() << endl;
}
cout << "b1 destroyed. Destructor count: " << getDestructorCount() << endl;
cout << endl;
 
resetAllCounters();
 
// --- Part 2: Copy Constructor ---
cout << "--- Part 2: Copy Constructor ---" << endl;
{
DynamicBuffer original("Deep Copy Test");
DynamicBuffer copied(original); // copy constructor called
 
cout << "Original: ";
original.print();
cout << "Copied: ";
copied.print();
cout << "Copy constructor count: " << getCopyConstructorCount() << endl;
 
// Modify original - copied should NOT change (deep copy)
original.setData("Modified Original");
cout << "After modifying original:" << endl;
cout << "Original: ";
original.print();
cout << "Copied: ";
copied.print();
}
cout << endl;
 
resetAllCounters();
 
// --- Part 3: Assignment Operator ---
cout << "--- Part 3: Assignment Operator ---" << endl;
{
DynamicBuffer a("Alpha");
DynamicBuffer b("Beta");
 
cout << "Before assignment:" << endl;
cout << "a: "; a.print();
cout << "b: "; b.print();
 
b = a; // assignment operator called
cout << "After b = a:" << endl;
cout << "a: "; a.print();
cout << "b: "; b.print();
cout << "Assignment count: " << getAssignmentCount() << endl;
 
// Modify a - b should NOT change
a.setData("Changed A");
cout << "After modifying a:" << endl;
cout << "a: "; a.print();
cout << "b: "; b.print();
}
cout << endl;
 
// --- Part 4: Self-Assignment Safety ---
cout << "--- Part 4: Self-Assignment ---" << endl;
{
DynamicBuffer s("SelfTest");
s = s; // self-assignment - must not crash
cout << "After self-assignment: ";
s.print();
}
cout << endl;
 
cout << "=== Lab Complete ===" << endl;
 
return 0;
}
