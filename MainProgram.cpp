// ============================================================================
// Lab: Destructors, Copy Constructors, and Default Memberwise Assignment
// Course: Object-Oriented Programming for Engineers
// ============================================================================
#include <iostream>
#include <cstring>
#include <string>
 
using namespace std;
 
// GLOBAL TRACKING VARIABLES
int g_constructorCount = 0;
int g_destructorCount = 0;
int g_copyConstructorCount = 0;
int g_assignmentCount = 0;
 
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
 
class DynamicBuffer {
private:
    char* m_data;
    int m_length;
 
public:
    // Parameterized Constructor
    DynamicBuffer(const char* input) {
        g_constructorCount++;
        m_length = strlen(input);
        m_data = new char[m_length + 1];
        strcpy(m_data, input);
    }
 
    // Destructor
    ~DynamicBuffer() {
        g_destructorCount++; // Önce sayacı artırıyoruz
        delete[] m_data;     // Sonra belleği serbest bırakıyoruz
    }
 
    // Copy Constructor (Deep Copy)
    DynamicBuffer(const DynamicBuffer& other) {
        g_copyConstructorCount++;
        m_length = other.m_length;
        m_data = new char[m_length + 1];
        strcpy(m_data, other.m_data);
    }
 
    // Copy Assignment Operator (Deep Copy - Exception Safe Version)
    DynamicBuffer& operator=(const DynamicBuffer& other) {
        g_assignmentCount++;
 
        // 1. Kendi kendine atama kontrolü
        if (this == &other) {
            return *this;
        }
 
        // 2. Önce yeni yeri ayır (Hata olursa m_data hala eski veriyi korur)
        char* newData = new char[other.m_length + 1];
        
        // 3. Veriyi kopyala
        strcpy(newData, other.m_data);
 
        // 4. Şimdi eski veriyi sil ve yeni adresi ata
        delete[] m_data;
        m_data = newData;
        m_length = other.m_length;
 
        return *this;
    }
 
    const char* getData() const { return m_data; }
    int getLength() const { return m_length; }
 
    void setData(const char* newData) {
        // Yeni veri için geçici alan ayırıp sonra silmek burada da en güvenli yoldur
        char* temp = new char[strlen(newData) + 1];
        strcpy(temp, newData);
        
        delete[] m_data;
        m_data = temp;
        m_length = strlen(newData);
    }
 
    void print() const {
        if (m_data)
            cout << "DynamicBuffer[\"" << m_data << "\", length=" << m_length << "]" << endl;
    }
};
 
// ============================================================================
// MAIN FUNCTION (Testleri çalıştırır)
// ============================================================================
int main() {
    cout << "=== Destructors, Copy Constructors & Assignment Lab ===" << endl << endl;
 
    // --- Part 1: Constructor & Destructor ---
    cout << "--- Part 1: Constructor & Destructor ---" << endl;
    {
        DynamicBuffer b1("Hello");
        b1.print();
        cout << "b1 created. Constructor count: " << getConstructorCount() << endl;
    }
    cout << "b1 destroyed. Destructor count: " << getDestructorCount() << endl << endl;
 
    resetAllCounters();
 
    // --- Part 2: Copy Constructor ---
    cout << "--- Part 2: Copy Constructor ---" << endl;
    {
        DynamicBuffer original("Deep Copy Test");
        DynamicBuffer copied(original);
        cout << "Original: "; original.print();
        cout << "Copied: "; copied.print();
        cout << "Copy constructor count: " << getCopyConstructorCount() << endl;
 
        original.setData("Modified Original");
        cout << "After modifying original:" << endl;
        cout << "Original: "; original.print();
        cout << "Copied: "; copied.print();
    }
    cout << endl;
 
    resetAllCounters();
 
    // --- Part 3: Assignment Operator ---
    cout << "--- Part 3: Assignment Operator ---" << endl;
    {
        DynamicBuffer a("Alpha");
        DynamicBuffer b("Beta");
        b = a;
        cout << "After b = a:" << endl;
        cout << "a: "; a.print();
        cout << "b: "; b.print();
        cout << "Assignment count: " << getAssignmentCount() << endl;
 
        a.setData("Changed A");
        cout << "After modifying a, b stays: "; b.print();
    }
    cout << endl;
 
    // --- Part 4: Self-Assignment Safety ---
    cout << "--- Part 4: Self-Assignment ---" << endl;
    {
        DynamicBuffer s("SelfTest");
        s = s; // Crash olmamalı
        cout << "After self-assignment: "; s.print();
    }
    cout << endl;
 
    cout << "=== Lab Complete ===" << endl;
    return 0;
}
