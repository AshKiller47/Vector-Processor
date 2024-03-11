/* 
 * Project Title: Vector Processor
 * Author: AshKiller47 (Ayaskanta Ghosh)
 * 
 * Trajectory Of Processor: main() ---> vectorProcessor() ---> dimensionSelect() ---> cartesian2D() ---> vectorProcessor() ---> ...
 *                                                             coordinateSelect()     polar2D()
 *                                                             operationSelect()      cartesian3D()
 *                                                                                    sphericalPolar3D()
 *                                                                                    cylindricalPolar3D()
 * 
 * Classes Operated: Vector2C, Vector2P, Vector3C, Vector3SP, Vector3CP, Root
 * 
 * Inheritance Structure: Vector2C ---> Vector2P <--- Root ---> Vector3CP <--- Vector3SP <--- Vector3C
 * 
 * Programming Features Utilized: 1. Local Class (Selector) --> vectorProcessor(): line 1068
 *                                
 *                                2. Exception Handling --> dimensionSelect(): line 1113
 *                                                          coordinateSelect(): line 1143
 *                                                          operationSelect(): line 1182
 *                                
 *                                3. Recursion --> dimensionSelect(): line 1115
 *                                                 coordinateSelect(): line 1145
 *                                                 operationSelect(): line 1190
 *                                
 *                                4. Conditional Operator --> coordinateSelect(): line 1143
 *                                                            operationSelect(): line 1184
 *                                
 *                                5. Template Function (processorDriver2D(): line 85) --> cartesian2D(): line 1205, 1218
 *                                                                                        polar2D(): line 1233, 1246
 *                                
 *                                6. Template Function (processorDriver3D(): line 123) --> cartesian3D(): line 1262, 1289
 *                                                                                         sphericalPolar3D(): line 1305, 1332
 *                                                                                         cylindricalPolar3D(): line 1348, 1376
 *                                
 *                                7. Static Data Members --> Contains The Unit Vectors & The Null Vectors (Type: String)
 *                                
 *                                8. Static Member Functions --> getUnitVector(): Private Member Of All Vector Classes (Template Function)
 *                                                               getNullVector(): Vector2C, Vector3C (Inherited By Derived Classes)
 *                                
 *                                9. Operator Overloading --> Operator '+': Overloaded In All Vector Classes
 *                                                            Operator '-': Overloaded In All Vector Classes
 *                                                            Operator '*': Vector2C, Vector3C (Inherited By Derived Classes)
 *                               
 *                               10. Friend Functions --> crossProduct(): Vector3C, Vector3SP
 *                               
 *                               11. Friend Class --> CrossVector: Vector3CP
 *                               
 *                               12. Scattered Throughout The Program --> Function Overloading
 *                                                                        Default Arguments To Functions
 *                                                                        Function Call (By Value)
 *                                                                        Function Call (By Reference)
 *                                                                        Default Constructors
 *                                                                        Parameterized Constructors
 *                                                                        'new', 'delete' Operators (Dynamic Memory Allocation)
 *                                                                        Virtual Functions; 'final' Specifier (Due To The Use Of Numerous Virtual Functions, All Objects Are Handled Using Pointers)
 *                                                                        'this' Pointer
 *                                                                        Object Pointers (Including Base Class Pointers To Derived Class Objects)
 *                                                                        Derived Class Object References Passed To Base Class Type Parameters
 */

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

// #include <stdexcept> // Decomment If 'invalid_argument' Class Generates An Error

#define getUnitVector(axis) fetchUnitVector<axis>()

using namespace std;

void vectorProcessor();
int dimensionSelect();
int coordinateSelect(int&);
int operationSelect(int&);
void cartesian2D(int&);
void polar2D(int&);
void cartesian3D(int&);
void sphericalPolar3D(int&);
void cylindricalPolar3D(int&);

// Default Arguments Provided In processorDriver2D()

template<typename T, typename U>
void processorDriver2D(int &operationChoice, double coord_11, double coord_12, double coord_21 = 0.f, double coord_22 = 0.f) {
    
    if(operationChoice == 1) {
        
        T *vector = new U(coord_11, coord_12); // Creates Base Class Pointer To Derived Class Object, Due To Choreographed Function Calling In cartesian2D() / polar2D()
        
        vector->displayInformation(); cout << "\n"; vector->transformation(); cout << "\n"; // Function transformation() Of Class 'U' Is Always Called, Since It Is Declared Virtual In Class Vector2C
        
        delete vector; vectorProcessor(); return;
        
    }
    
    T *vector_1 = new U(coord_11, coord_12);
    T *vector_2 = new U(coord_21, coord_22);
    
    // Functions distance(), angleBetween() Are Called Depending On Whether Pointer Is Of Base Class Type Or Derived Class Type; Function displayVector() Of Class Vector2C Is Always Called
    
    cout << "\nVector #1: "; vector_1->displayVector();
    cout << "\nVector #2: "; vector_2->displayVector(); cout << "\n";
    
    if(operationChoice == 2) { cout << "\n("; vector_1->displayVector(); cout << ") + ("; vector_2->displayVector(); cout << ") = "; (*vector_1 + *vector_2).displayVector(); }
    else if(operationChoice == 3) { cout << "\n("; vector_1->displayVector(); cout << ") - ("; vector_2->displayVector(); cout << ") = "; (*vector_1 - *vector_2).displayVector(); }
    else if(operationChoice == 4) { cout << "\n("; vector_1->displayVector(); cout << ") * ("; vector_2->displayVector(); cout << ") = " << *vector_1 * *vector_2; }
    else if(operationChoice == 5) { cout << "\nDistance Between ("; vector_1->displayVector(); cout << ") & ("; vector_2->displayVector(); cout << "): " << vector_1->distance(*vector_2); }
    else {
        
        cout << "\nAngle Between ("; vector_1->displayVector(); cout << ") & ("; vector_2->displayVector(); cout << ") (Radians): " << vector_1->angleBetween(*vector_2);
        cout << "\nAngle Between ("; vector_1->displayVector(); cout << ") & ("; vector_2->displayVector(); cout << ") (Degrees): " << vector_1->angleBetween(*vector_2) * 180.f / M_PI;
        
    }
    
    cout << "\n"; delete vector_1; delete vector_2; vectorProcessor();
    
}

// Default Arguments Provided In processorDriver3D()

template<typename T, typename U>
void processorDriver3D(int &operationChoice, double coord_11, double coord_12, double coord_13, double coord_21 = 0.f, double coord_22 = 0.f, double coord_23 = 0.f) {
    
    if(operationChoice == 1) {
        
        T *vector = new U(coord_11, coord_12, coord_13); // Creates Base Class Pointer To Derived Class Object, Due To Choreographed Function Calling In cartesian3D() / sphericalPolar3D() / cylindricalPolar3D()
        
        vector->displayInformation(); cout << "\n"; vector->transformation(); cout << "\n"; // Function transformation() Of Class 'U' Is Always Called, Since It Is Declared Virtual In Class Vector3C
        
        delete vector; vectorProcessor(); return;
        
    }
    
    T *vector_1 = new U(coord_11, coord_12, coord_13);
    T *vector_2 = new U(coord_21, coord_22, coord_23);
    
    // Functions distance(), angleBetween() Are Called Depending On Whether Pointer Is Of Base Class Type Or Derived Class Type; Function displayVector() Of Class Vector3C Is Always Called
    
    cout << "\nVector #1: "; vector_1->displayVector();
    cout << "\nVector #2: "; vector_2->displayVector(); cout << "\n";
    
    if(operationChoice == 2) { cout << "\n("; vector_1->displayVector(); cout << ") + ("; vector_2->displayVector(); cout << ") = "; (*vector_1 + *vector_2).displayVector(); }
    else if(operationChoice == 3) { cout << "\n("; vector_1->displayVector(); cout << ") - ("; vector_2->displayVector(); cout << ") = "; (*vector_1 - *vector_2).displayVector(); }
    else if(operationChoice == 4) { cout << "\n("; vector_1->displayVector(); cout << ") * ("; vector_2->displayVector(); cout << ") = " << *vector_1 * *vector_2; }
    else if(operationChoice == 6) { cout << "\nDistance Between ("; vector_1->displayVector(); cout << ") & ("; vector_2->displayVector(); cout << "): " << vector_1->distance(*vector_2); }
    else if(operationChoice == 7) {
        
        cout << "\nAngle Between ("; vector_1->displayVector(); cout << ") & ("; vector_2->displayVector(); cout << ") (Radians): " << vector_1->angleBetween(*vector_2);
        cout << "\nAngle Between ("; vector_1->displayVector(); cout << ") & ("; vector_2->displayVector(); cout << ") (Degrees): " << vector_1->angleBetween(*vector_2) * 180.f / M_PI;
        
    }
    
    cout << "\n"; delete vector_1; delete vector_2; vectorProcessor();
    
}

class Vector2C {
        
        double abcissa, ordinate;
        static string unit_x, unit_y, null_vector;
        
        // Static Template Function; fetchUnitVector<axial>() Redefined To getUnitVector(axial); Function Calling Works Only If axial = {0, 1}
        
        template<int axial, typename = enable_if_t<axial == 0 | axial == 1>>
        static string fetchUnitVector() {
            
            if(axial == 0) return unit_x;
            if(axial == 1) return unit_y;
            
        }
        
    protected:
        
        virtual double magnitude(); // Virtual Function, Can Be Redefined In Derived Classes
        virtual double angle(); // Virtual Function, Can Be Redefined In Derived Classes
        double slope();
        
        Vector2C componentX();
        Vector2C componentY();
        Vector2C unitVector();
        
        static string getNullVector();
        
    public:
        
        Vector2C();
        Vector2C(double, double);
        
        virtual ~Vector2C() {}; // Destructor Declared Virtual, Since Vector2C Is Parent To Vector2P
        
        double distance(Vector2C&);
        virtual double angleBetween(Vector2C&) final;
        
        Vector2C operator+ (Vector2C&);
        Vector2C operator- (Vector2C&);
        double operator* (Vector2C&);
        
        void displayVector();
        virtual void displayInformation() final; // displayInformation() Cannot Be Redefined In Derived Classes
        virtual void transformation() { return; } // Barebone Function Defined To Avoid Conflict In Template Function processorDriver2D()
        
};

class Root { protected: double sqrt(double); }; // Root Is The Parent Class Of 2 Seperate Derived Classes (Hierarchical Inheritance); Virtual Destructor Not Required Since Root Has No Virtual Member Functions

// Class Vector2P Inherits From 2 Seperate Base Classes (Multiple Inheritance) 

class Vector2P: public Vector2C, private Root {
        
        double radial, azimuth;
        static string unit_r, unit_az;
        
        // Static Template Function; fetchUnitVector<axial>() Redefined To getUnitVector(axial); Function Calling Works Only If axial = {0, 1}
        
        template<int axial, typename = enable_if_t<axial == 0 | axial == 1>>
        static string fetchUnitVector() {
            
            if(axial == 0) return unit_r;
            if(axial == 1) return unit_az;
            
        }
        
    protected:
        
        double magnitude(); // Function magnitude() Of Vector2C Redefined In Vector2P
        double angle(); // Function angle() Of Vector2C Redefined In Vector2P
        
        void displayPolarVector(double, double);
        
    public:
        
        Vector2P();
        Vector2P(double, double);
        
        double distance(Vector2P&); // 2nd distance() Function Defined In Vector2P; Vector2P Also Contains distance() Of Vector2C As Member Function
        double angleBetween(Vector2P&); // Although angleBetween() Is Declared 'final' in Vector2C, Redefination Is Possible Since The Argument Type Is Different
        
        Vector2P operator+ (Vector2P&); // Overloaded Operator Redefined; Vector2P Also Contains Operator '+' Of Vector2C As Member Function
        Vector2P operator- (Vector2P&); // Overloaded Operator Redefined; Vector2P Also Contains Operator '-' Of Vector2C As Member Function
        
        void transformation(); // Function transformation() Of Vector2C Redefined In Vector2P
        
};

class Vector3C {
        
        double abcissa, ordinate, applicate;
        static string unit_x, unit_y, unit_z, null_vector;
        
        // Static Template Function; fetchUnitVector<axial>() Redefined To getUnitVector(axial); Function Calling Works Only If axial = {0, 1, 2}
        
        template<int axial, typename = enable_if_t<axial == 0 | axial == 1 | axial == 2>>
        static string fetchUnitVector() {
            
            if(axial == 0) return unit_x;
            if(axial == 1) return unit_y;
            if(axial == 2) return unit_z;
            
        }
        
    protected:
        
        virtual double magnitude(); // Virtual Function, Can Be Redefined In Derived Classes
        virtual double zenith(); // Virtual Function, Can Be Redefined In Derived Classes
        virtual double azimuthal(); // Virtual Function, Can Be Redefined In Derived Classes
        
        Vector3C componentX();
        Vector3C componentY();
        Vector3C componentZ();
        Vector3C unitVector();
        
        static string getNullVector();
        
    public:
        
        Vector3C();
        Vector3C(double, double, double);
        
        virtual ~Vector3C() {}; // Destructor Declared Virtual, Since Vector3C Is Parent To Vector3SP, Vector3CP
        
        double distance(Vector3C&);
        virtual double angleBetween(Vector3C&) final; // angleBetween() Cannot Be Redefined In Derived Classes
        
        Vector3C operator+ (Vector3C&);
        Vector3C operator- (Vector3C&);
        double operator* (Vector3C&);
        
        void displayVector();
        virtual void displayInformation(); // Virtual Function, Can Be Redefined In Derived Classes
        virtual void transformation() { return; } // Barebone Function Defined To Avoid Conflict In Template Function processorDriver3D()
        
        friend Vector3C crossProduct(Vector3C&, Vector3C&); // Friend Function Of Vector3C Declared; Non-Inheritable
        
};

// Class Vector3SP Inherits From 1 Base Class (Single Inheritance) 

class Vector3SP: public Vector3C {
        
        double radial, polar, azimuth;
        static string unit_r, unit_p, unit_az;
        
        // Static Template Function; fetchUnitVector<axial>() Redefined To getUnitVector(axial); Function Calling Works Only If axial = {0, 1, 2}
        
        template<int axial, typename = enable_if_t<axial == 0 | axial == 1 | axial == 2>>
        static string fetchUnitVector() {
            
            if(axial == 0) return unit_r;
            if(axial == 1) return unit_p;
            if(axial == 2) return unit_az;
            
        }
        
    protected:
        
        double magnitude(); // Function magnitude() Of Vector3C Redefined In Vector3SP
        double zenith() final; // Function zenith() Of Vector3C Redefined In Vector3SP; Cannot Be Redefined In Subsequent Derived Classes
        double azimuthal() final; // Function azimuthal() Of Vector3C Redefined In Vector3SP; Cannot Be Redefined In Subsequent Derived Classes
        
        void displaySphericalVector(double, double, double);
        
    public:
        
        Vector3SP();
        Vector3SP(double, double, double);
        
        virtual ~Vector3SP() {}; // Destructor Declared Virtual, Since Vector3SP Is Parent To Vector3CP
        
        Vector3SP operator+ (Vector3SP&); // Overloaded Operator Redefined; Vector3SP Also Contains Operator '+' Of Vector3C As Member Function
        Vector3SP operator- (Vector3SP&); // Overloaded Operator Redefined; Vector3SP Also Contains Operator '-' Of Vector3C As Member Function
        
        void transformation(); // Function transformation() Of Vector3C Redefined In Vector3SP
        
        friend Vector3SP crossProduct(Vector3SP&, Vector3SP&); // Friend Function Of Vector3SP Declared; Non-Inheritable; Overloaded Function
        
};

// Class Vector3CP Inherits From 1 Derived, 1 Base Classes (Multilevel, Multiple Inheritance) 

class Vector3CP: public Vector3SP, private Root {
    
    private:
        
        double radial, azimuth, altitude;
        static string unit_r, unit_az, unit_al;
        
        // Static Template Function; fetchUnitVector<axial>() Redefined To getUnitVector(axial); Function Calling Works Only If axial = {0, 1, 2}
        
        template<int axial, typename = enable_if_t<axial == 0 | axial == 1 | axial == 2>>
        static string fetchUnitVector() {
            
            if(axial == 0) return unit_r;
            if(axial == 1) return unit_az;
            if(axial == 2) return unit_al;
            
        }
        
    protected:
        
        double magnitude(); // Function magnitude() Of Vector3C Redefined In Vector3CP
        double radius();
        double longitude();
        
        void displayCylindricalVector(double, double, double);
        
    public:
        
        Vector3CP();
        Vector3CP(double, double, double);
        
        Vector3CP operator+ (Vector3CP&); // Overloaded Operator Redefined; Vector3CP Also Contains Operator '+' Of Vector3C, Vector3SP As Member Function
        Vector3CP operator- (Vector3CP&); // Overloaded Operator Redefined; Vector3CP Also Contains Operator '-' Of Vector3C, Vector3SP As Member Function
        
        void displayInformation(); // Function displayInformation() Of Vector3C Redefined In Vector3CP; displayInformation() Has No Redefinition In Vector3SP
        void transformation(); // Function transformation() Of Vector3C Redefined In Vector3CP
        
        friend class CrossVector; // Friend Class Of Vector3CP Declared
        
};

class CrossVector { public: Vector3CP crossProduct(Vector3CP&, Vector3CP&); }; // Definition Of Friend Class CrossVector

// Static Data Members Defined Outside Class Vector2C

string Vector2C::unit_x = "x̂";
string Vector2C::unit_y = "ŷ";
string Vector2C::null_vector = "𝝓";

Vector2C::Vector2C() { abcissa = 0.f; ordinate = 0.f; } // Default Constructor Of Vector2C

Vector2C::Vector2C(double abcissa, double ordinate) { this->abcissa = abcissa; this->ordinate = ordinate; }

double Vector2C::magnitude() { return sqrt(abcissa * abcissa + ordinate * ordinate); }

double Vector2C::angle() { return atan2(ordinate, abcissa); }

double Vector2C::slope() { return ordinate / abcissa; }

Vector2C Vector2C::componentX() { Vector2C vector(abcissa, 0.f); return vector; }

Vector2C Vector2C::componentY() { Vector2C vector(0.f, ordinate); return vector; }

Vector2C Vector2C::unitVector() {
    
    if(magnitude() == 0.f) { Vector2C vector; return vector; }
    
    Vector2C vector(abcissa / magnitude(), ordinate / magnitude()); return vector;
    
}

string Vector2C::getNullVector() { return null_vector; } // Static Member Function, Can Only Access Static Data Members Of Vector2C; Inherited By Vector2P

double Vector2C::distance(Vector2C &vector) { Vector2C distance_vector = *this - vector; return distance_vector.magnitude(); }

double Vector2C::angleBetween(Vector2C &vector) { return abs(angle() - vector.angle()); }

Vector2C Vector2C::operator+ (Vector2C &vector) { Vector2C addition_vector(abcissa + vector.abcissa, ordinate + vector.ordinate); return addition_vector; }

Vector2C Vector2C::operator- (Vector2C &vector) { Vector2C subtraction_vector(abcissa - vector.abcissa, ordinate - vector.ordinate); return subtraction_vector; }

double Vector2C::operator* (Vector2C &vector) { return abcissa * vector.abcissa + ordinate * vector.ordinate; }

void Vector2C::displayVector() {
    
    if(abcissa == 0.f && ordinate == 0.f) { cout << getNullVector(); return; }
    
    if(abcissa > 0.f) {
        
        if(abcissa == 1.f) cout << getUnitVector(0);
        else cout << abcissa << getUnitVector(0);
        
    }
    
    else if(abcissa < 0.f) {
        
        if(abcissa == -1.f) cout << "- " << getUnitVector(0);
        else cout << "- " << abs(abcissa) << getUnitVector(0);
        
    }
    
    if(abcissa != 0.f && ordinate > 0.f) cout << " + ";
    
    if(ordinate > 0.f) {
        
        if(ordinate == 1.f) cout << getUnitVector(1);
        else cout << ordinate << getUnitVector(1);
        
    }
    
    else if(ordinate < 0.f) {
        
        if(ordinate == -1.f) cout << " - " << getUnitVector(1);
        else cout << " - " << abs(ordinate) << getUnitVector(1);
        
    }
    
}

void Vector2C::displayInformation() {
    
    cout << "\nVector: "; displayVector();
    cout << "\nMagnitude: " << magnitude();
    cout << "\nSlope: " << slope();
    cout << "\nAngle (Radians): " << angle();
    cout << "\nAngle (Degrees): " << angle() * 180.f / M_PI;
    cout << "\nComponent Along X-Direction: "; componentX().displayVector();
    cout << "\nComponent Along Y-Direction: "; componentY().displayVector();
    cout << "\nUnit Vector: "; unitVector().displayVector();
    
}

double Root::sqrt(double number) {
    
    // Non-Standard Square Root Function sqrt() Definition; Concept Of Binary Search Utilized
    
    if(number == 0.f) return 0.f;
    
    int i;
    
    for(i = 1; i * i < number ; i++);
    
    if(i * i == number) return i;
    
    double low = i - 1, high = i;
    
    while(high - low > 0.00001) {
        
        double midSquare = (low + high) * (low + high) / 4;
        
        if(midSquare < number) low = (low + high) / 2;
        else high = (low + high) / 2;
        
    }
    
    return high;
    
}

// Static Data Members Defined Outside Class Vector2P

string Vector2P::unit_r = "r̂";
string Vector2P::unit_az = "θ";

Vector2P::Vector2P() { radial = 0.f; azimuth = 0.f; } // Default Constructor Of Vector2P; Calls Default Constructor Of Vector2C

// Parameterized Constructor Of Vector2P Calls Parameterized Constructor Of Vector2C

Vector2P::Vector2P(double radial, double azimuth): Vector2C(radial * cos(azimuth), radial * sin(azimuth)) { this->radial = radial; this->azimuth = azimuth; }

double Vector2P::magnitude() { return radial; } // Redefinition Of magnitude() In Vector2P

double Vector2P::angle() { return azimuth; } // Redefinition Of angle() In Vector2P

// Default Arguments Provided In displayPolarVector()

void Vector2P::displayPolarVector(double radial, double azimuth = 0.f) {
    
    if(radial == 0.f) { cout << getNullVector(); return; } // Static Member Function getNullVector() Of Base Class Vector2C Called
    
    if(radial > 0.f) {
        
        if(radial == 1.f) cout << getUnitVector(0);
        else cout << radial << getUnitVector(0);
        
    }
    
    else if(radial < 0.f) {
        
        if(radial == -1.f) cout << "- " << getUnitVector(0);
        else cout << "- " << abs(radial) << getUnitVector(0);
        
    }
    
    if(azimuth > 0.f) {
        
        cout << " + ";
        
        if(azimuth == 1.f) cout << getUnitVector(1);
        else cout << azimuth << getUnitVector(1);
        
    }
    
    else if(azimuth < 0.f) {
        
        cout << " - ";
        
        if(azimuth == -1.f) cout << getUnitVector(1);
        else cout << abs(azimuth) << getUnitVector(1);
        
    }
    
}

double Vector2P::distance(Vector2P &vector) { Vector2P distance_vector = *this - vector; return distance_vector.magnitude(); } // Definition Of Overloaded Function distance() In Vector2P

double Vector2P::angleBetween(Vector2P &vector) { return abs(angle() - vector.angle()); } // Redefinition Of 'final' Function angleBetween() Of Vector2C

// Redefinition Of Overloaded Operators '+' , '-' In Vector2P

Vector2P Vector2P::operator+ (Vector2P &vector) {
    
    double addition_x = magnitude() * cos(angle()) + vector.magnitude() * cos(vector.angle());
    double addition_y = magnitude() * sin(angle()) + vector.magnitude() * sin(vector.angle());
    
    Vector2P addition_vector(sqrt(addition_x * addition_x + addition_y * addition_y), atan2(addition_y, addition_x)); return addition_vector;
    
}

Vector2P Vector2P::operator- (Vector2P &vector) {
    
    double subtraction_x = magnitude() * cos(angle()) - vector.magnitude() * cos(vector.angle());
    double subtraction_y = magnitude() * sin(angle()) - vector.magnitude() * sin(vector.angle());
    
    Vector2P subtraction_vector(sqrt(subtraction_x * subtraction_x + subtraction_y * subtraction_y), atan2(subtraction_y, subtraction_x)); return subtraction_vector;
    
}

// Redefinition Of Barebone Virtual Function transformation() Of Vector2C, In Vector2P

void Vector2P::transformation() {
    
    cout << "\nVector In Terms " << getUnitVector(0) << " & " << getUnitVector(1) << " :-" << "\n";
    cout << "\nVector: "; displayPolarVector(magnitude());
    
    Vector2C *vector = new Vector2P(1.f, angle());
    
    cout << "\n" << getUnitVector(0) << " (In Cartesian Coordinates): "; vector->displayVector();
    
    vector = new Vector2P(1.f, angle()+ M_PI / 2);
    
    cout << "\n" << getUnitVector(1) << " (In Cartesian Coordinates): "; vector->displayVector();
    cout << "\nComponent Along X-Direction: "; displayPolarVector(magnitude() * cos(angle()) * cos(angle()), -1.f * magnitude() * cos(angle()) * sin(angle()));
    cout << "\nComponent Along Y-Direction: "; displayPolarVector(magnitude() * sin(angle()) * sin(angle()), magnitude() * cos(angle()) * sin(angle()));
    cout << "\nUnit Vector: " << getUnitVector(0);
    
}

// Static Data Members Defined Outside Class Vector3C

string Vector3C::unit_x = "x̂";
string Vector3C::unit_y = "ŷ";
string Vector3C::unit_z = "ẑ";
string Vector3C::null_vector = "𝝓";

Vector3C::Vector3C() { abcissa = 0.f; ordinate = 0.f; applicate = 0.f; } // Default Constructor Of Vector3C

Vector3C::Vector3C(double abcissa, double ordinate, double applicate) { this->abcissa = abcissa; this->ordinate = ordinate; this->applicate = applicate; }

double Vector3C::magnitude() { return sqrt(abcissa * abcissa + ordinate * ordinate + applicate * applicate); }

double Vector3C::zenith() { return acos(applicate / magnitude()); }

double Vector3C::azimuthal() { return atan2(ordinate, abcissa); }

Vector3C Vector3C::componentX() { Vector3C vector(abcissa, 0.f, 0.f); return vector; }

Vector3C Vector3C::componentY() { Vector3C vector(0.f, ordinate, 0.f); return vector; }

Vector3C Vector3C::componentZ() { Vector3C vector(0.f, 0.f, applicate); return vector; }

Vector3C Vector3C::unitVector() {
    
    if(magnitude() == 0.f) { Vector3C vector; return vector; }
    
    Vector3C vector(abcissa / magnitude(), ordinate / magnitude(), applicate / magnitude()); return vector;
    
}

string Vector3C::getNullVector() { return null_vector; } // Static Member Function, Can Only Access Static Data Members Of Vector3C; Inherited By Vector3SP, Vector3CP

double Vector3C::distance(Vector3C &vector) { Vector3C distance_vector = *this - vector; return distance_vector.magnitude(); }

double Vector3C::angleBetween(Vector3C &vector) { return acos(*this * vector / (magnitude() * vector.magnitude())); }

Vector3C Vector3C::operator+ (Vector3C &vector) {
    
    Vector3C addition_vector(abcissa + vector.abcissa, ordinate + vector.ordinate, applicate + vector.applicate); return addition_vector;
    
}

Vector3C Vector3C::operator- (Vector3C &vector) {
    
    Vector3C subtraction_vector(abcissa - vector.abcissa, ordinate - vector.ordinate, applicate - vector.applicate); return subtraction_vector;
    
}

double Vector3C::operator* (Vector3C &vector) { return abcissa * vector.abcissa + ordinate * vector.ordinate + applicate * vector.applicate; }

void Vector3C::displayVector() {
    
    if(abcissa == 0.f && ordinate == 0.f && applicate == 0.f) { cout << getNullVector(); return; }
    
    if(abcissa > 0.f) {
        
        if(abcissa == 1.f) cout << getUnitVector(0);
        else cout << abcissa << getUnitVector(0);
        
    }
    
    else if(abcissa < 0.f) {
        
        if(abcissa == -1.f) cout << "- " << getUnitVector(0);
        else cout << "- " << abs(abcissa) << getUnitVector(0);
        
    }
    
    if(abcissa != 0.f && ordinate > 0.f) cout << " + ";
    
    if(ordinate > 0.f) {
        
        if(ordinate == 1.f) cout << getUnitVector(1);
        else cout << ordinate << getUnitVector(1);
        
    }
    
    else if(ordinate < 0.f) {
        
        if(ordinate == -1.f) cout << " - " << getUnitVector(1);
        else cout << " - " << abs(ordinate) << getUnitVector(1);
        
    }
    
    if((abcissa != 0.f || ordinate != 0.f) && applicate > 0.f) cout << " + ";
    
    if(applicate > 0.f) {
        
        if(applicate == 1.f) cout << getUnitVector(2);
        else cout << applicate << getUnitVector(2);
        
    }
    
    else if(applicate < 0.f) {
        
        if(applicate == -1.f) cout << " - " << getUnitVector(2);
        else cout << " - " << abs(applicate) << getUnitVector(2);
        
    }
    
}

void Vector3C::displayInformation() {
    
    cout << "\nVector: "; displayVector();
    cout << "\nMagnitude: " << magnitude();
    cout << "\nPolar Angle (Radians): " << zenith();
    cout << "\nPolar Angle (Degrees): " << zenith() * 180.f / M_PI;
    cout << "\nAzimuthal Angle (Radians): " << azimuthal();
    cout << "\nAzimuthal Angle (Degrees): " << azimuthal() * 180.f / M_PI;
    cout << "\nComponent Along X-Direction: "; componentX().displayVector();
    cout << "\nComponent Along Y-Direction: "; componentY().displayVector();
    cout << "\nComponent Along Z-Direction: "; componentZ().displayVector();
    cout << "\nUnit Vector: "; unitVector().displayVector();
    
}

// Definition Of Friend Function crossProduct() Of Vector3C; Can Access Private Members Of Vector3C Directly

Vector3C crossProduct(Vector3C &vector_1, Vector3C &vector_2) {
    
    double component_x = vector_1.ordinate * vector_2.applicate - vector_1.applicate * vector_2.ordinate;
    double component_y = vector_1.applicate * vector_2.abcissa - vector_1.abcissa * vector_2.applicate;
    double component_z = vector_1.abcissa * vector_2.ordinate - vector_1.ordinate * vector_2.abcissa;
    
    Vector3C vector(component_x, component_y, component_z); return vector;
    
}

// Static Data Members Defined Outside Class Vector3SP

string Vector3SP::unit_r = "r̂";
string Vector3SP::unit_p = "θ";
string Vector3SP::unit_az = "ф";

Vector3SP::Vector3SP() { radial = 0.f; polar = 0.f; azimuth = 0.f; } // Default Constructor Of Vector3SP; Calls Default Constructor Of Vector3C

// Parameterized Constructor Of Vector3SP Calls Parameterized Constructor Of Vector3C

Vector3SP::Vector3SP(double radial, double polar, double azimuth): Vector3C(radial * sin(polar) * cos(azimuth), radial * sin(polar) * sin(azimuth), radial * cos(polar)) {
    
    this->radial = radial; this->polar = polar; this->azimuth = azimuth;
    
}

double Vector3SP::magnitude() { return radial; } // Redefinition Of magnitude() In Vector3SP

double Vector3SP::zenith() { return polar; } // Redefinition Of zenith() In Vector3SP

double Vector3SP::azimuthal() { return azimuth; } // Redefinition Of azimuthal() In Vector3SP

// Default Arguments Provided In displaySphericalVector()

void Vector3SP::displaySphericalVector(double radial, double polar = 0.f, double azimuth = 0.f) {
    
    if(radial == 0.f) { cout << getNullVector(); return; } // Static Member Function getNullVector() Of Base Class Vector3C Called
    
    if(radial > 0.f) {
        
        if(radial == 1.f) cout << getUnitVector(0);
        else cout << radial << getUnitVector(0);
        
    }
    
    else if(radial < 0.f) {
        
        if(radial == -1.f) cout << "- " << getUnitVector(0);
        else cout << "- " << abs(radial) << getUnitVector(0);
        
    }
    
    if(polar > 0.f) {
        
        cout << " + ";
        
        if(polar == 1.f) cout << getUnitVector(1);
        else cout << polar << getUnitVector(1);
        
    }
    
    else if(polar < 0.f) {
        
        cout << " - ";
        
        if(polar == -1.f) cout << getUnitVector(1);
        else cout << abs(polar) << getUnitVector(1);
        
    }
    
    if(azimuth > 0.f) {
        
        cout << " + ";
        
        if(azimuth == 1.f) cout << getUnitVector(2);
        else cout << azimuth << getUnitVector(2);
        
    }
    
    else if(azimuth < 0.f) {
        
        cout << " - ";
        
        if(azimuth == -1.f) cout << getUnitVector(2);
        else cout << abs(azimuth) << getUnitVector(2);
        
    }
    
}

// Redefinition Of Overloaded Operators '+' , '-' In Vector3SP

Vector3SP Vector3SP::operator+ (Vector3SP &vector) {
    
    double addition_x = magnitude() * sin(zenith()) * cos(azimuthal()) + vector.magnitude() * sin(vector.zenith()) * cos(vector.azimuthal());
    double addition_y = magnitude() * sin(zenith()) * sin(azimuthal()) + vector.magnitude() * sin(vector.zenith()) * sin(vector.azimuthal());
    double addition_z = magnitude() * cos(zenith()) + vector.magnitude() * cos(vector.zenith());
    
    double addition_radial = addition_x * addition_x + addition_y * addition_y + addition_z * addition_z;
    
    Vector3SP addition_vector(sqrt(addition_radial), acos(addition_z / sqrt(addition_radial)), atan2(addition_y, addition_x)); return addition_vector;
    
}

Vector3SP Vector3SP::operator- (Vector3SP &vector) {
    
    double subtraction_x = magnitude() * sin(zenith()) * cos(azimuthal()) - vector.magnitude() * sin(vector.zenith()) * cos(vector.azimuthal());
    double subtraction_y = magnitude() * sin(zenith()) * sin(azimuthal()) - vector.magnitude() * sin(vector.zenith()) * sin(vector.azimuthal());
    double subtraction_z = magnitude() * cos(zenith()) - vector.magnitude() * cos(vector.zenith());
    
    double subtraction_radial = subtraction_x * subtraction_x + subtraction_y * subtraction_y + subtraction_z * subtraction_z;
    
    Vector3SP subtraction_vector(sqrt(subtraction_radial), acos(subtraction_z / sqrt(subtraction_radial)), atan2(subtraction_y, subtraction_x)); return subtraction_vector;
    
}

// Redefinition Of Barebone Virtual Function transformation() Of Vector3C, In Vector3SP; Functions Accessed Are Members Of Vector3SP, Except displayVector()

void Vector3SP::transformation() {
    
    cout << "\nVector In Terms " << getUnitVector(0) << ", " << getUnitVector(1) << " & " << getUnitVector(2) << " :-" << "\n";
    cout << "\nVector: "; displaySphericalVector(magnitude());
    
    Vector3C *vector = new Vector3SP(1.f, zenith(), azimuthal());
    
    cout << "\n" << getUnitVector(0) << " (In Cartesian Coordinates): "; vector->displayVector();
    
    vector = new Vector3SP(1.f, zenith() + M_PI / 2, azimuthal());
    
    cout << "\n" << getUnitVector(1) << " (In Cartesian Coordinates): "; vector->displayVector();
    
    vector = new Vector3SP(1.f, M_PI / 2, azimuthal() + M_PI / 2);
    
    cout << "\n" << getUnitVector(2) << " (In Cartesian Coordinates): "; vector->displayVector();
    
    double component_r = magnitude() * sin(zenith()) * sin(zenith()) * cos(azimuthal()) * cos(azimuthal());
    double component_p = magnitude() * sin(zenith()) * cos(zenith()) * cos(azimuthal()) * cos(azimuthal());
    double component_az = -1.f * magnitude() * sin(zenith()) * cos(azimuthal()) * sin(azimuthal());
    
    cout << "\nComponent Along X-Direction: "; displaySphericalVector(component_r, component_p, component_az);
    
    component_r = magnitude() * sin(zenith()) * sin(zenith()) * sin(azimuthal()) * sin(azimuthal());
    component_p = magnitude() * sin(zenith()) * cos(zenith()) * sin(azimuthal()) * sin(azimuthal());
    component_az = magnitude() * sin(zenith()) * sin(azimuthal()) * cos(azimuthal());
    
    cout << "\nComponent Along Y-Direction: "; displaySphericalVector(component_r, component_p, component_az);
    
    component_r = magnitude() * cos(zenith()) * cos(zenith());
    component_p = -1.f * magnitude() * cos(zenith()) * sin(zenith());
    
    cout << "\nComponent Along Z-Direction: "; displaySphericalVector(component_r, component_p);
    cout << "\nUnit Vector: " << getUnitVector(0);
    
}

// Definition Of Friend Function crossProduct() Of Vector3SP; Can Access Protected Members Of Vector3SP Directly

Vector3SP crossProduct(Vector3SP &vector_1, Vector3SP &vector_2) {
    
    double abcissa_1 = vector_1.magnitude() * sin(vector_1.zenith()) * cos(vector_1.azimuthal());
    double ordinate_1 = vector_1.magnitude() * sin(vector_1.zenith()) * sin(vector_1.azimuthal());
    double applicate_1 = vector_1.magnitude() * cos(vector_1.zenith());
    
    double abcissa_2 = vector_2.magnitude() * sin(vector_2.zenith()) * cos(vector_2.azimuthal());
    double ordinate_2 = vector_2.magnitude() * sin(vector_2.zenith()) * sin(vector_2.azimuthal());
    double applicate_2 = vector_2.magnitude() * cos(vector_2.zenith());
    
    double component_x = ordinate_1 * applicate_2 - applicate_1 * ordinate_2;
    double component_y = applicate_1 * abcissa_2 - abcissa_1 * applicate_2;
    double component_z = abcissa_1 * ordinate_2 - ordinate_1 * abcissa_2;
    
    double crossRadial = component_x * component_x + component_y * component_y + component_z * component_z;
    
    Vector3SP vector(sqrt(crossRadial), acos(component_z / sqrt(crossRadial)), atan2(component_y, component_x)); return vector;
    
}

// Static Data Members Defined Outside Class Vector3CP

string Vector3CP::unit_r = "r̂";
string Vector3CP::unit_az = "θ";
string Vector3CP::unit_al = "ẑ";

Vector3CP::Vector3CP() { radial = 0.f; azimuth = 0.f; altitude = 0.f; } // Default Constructor Of Vector3CP; Calls Default Constructor Of Vector3SP --> Vector3C

// Parameterized Constructor Of Vector3CP Calls Parameterized Constructor Of Vector3SP --> Vector3C; sqrt() Of 'cmath' Utilized, Since sqrt() Of Root Is Not Initialized Yet

Vector3CP::Vector3CP(double radial, double azimuth, double altitude): Vector3SP(std::sqrt(radial * radial + altitude * altitude), atan2(radial, altitude), azimuth) {
    
    this->radial = radial; this->azimuth = azimuth; this->altitude = altitude;
    
}

double Vector3CP::magnitude() { return sqrt(radial * radial + altitude * altitude); } // Redefinition Of magnitude() In Vector3CP

double Vector3CP::radius() { return radial; }

double Vector3CP::longitude() { return altitude; }

// Default Arguments Provided In displayCylindricalVector()

void Vector3CP::displayCylindricalVector(double radial, double altitude, double azimuth = 0.f) {
    
    if(radial == 0.f && altitude == 0.f) { cout << getNullVector(); return; } // Static Member Function getNullVector() Of Base Class Vector3C Called
    
    if(radial > 0.f) {
        
        if(radial == 1.f) cout << getUnitVector(0);
        else cout << radial << getUnitVector(0);
        
    }
    
    else if(radial < 0.f) {
        
        if(radial == -1.f) cout << "- " << getUnitVector(0);
        else cout << "- " << abs(radial) << getUnitVector(0);
        
    }
    
    if(radial != 0.f && azimuth > 0.f) cout << " + ";
    
    if(azimuth > 0.f) {
        
        if(azimuth == 1.f) cout << getUnitVector(1);
        else cout << azimuth << getUnitVector(1);
        
    }
    
    else if(azimuth < 0.f) {
        
        cout << " - ";
        
        if(azimuth == -1.f) cout << getUnitVector(1);
        else cout << abs(azimuth) << getUnitVector(1);
        
    }
    
    if((radial != 0.f || azimuth != 0.f) && altitude > 0.f) cout << " + ";
    
    if(altitude > 0.f) {
        
        if(altitude == 1.f) cout << getUnitVector(2);
        else cout << altitude << getUnitVector(2);
        
    }
    
    else if(altitude < 0.f) {
        
        cout << " - ";
        
        if(altitude == -1.f) cout << getUnitVector(2);
        else cout << abs(altitude) << getUnitVector(2);
        
    }
    
}

// Redefinition Of Overloaded Operators '+' , '-' In Vector3CP; Function azimuthal() Of Vector3SP Called In Definition Of Operator '+'

Vector3CP Vector3CP::operator+ (Vector3CP &vector) {
    
    double addition_x = radius() * cos(azimuthal()) + vector.radius() * cos(vector.azimuthal());
    double addition_y = radius() * sin(azimuthal()) + vector.radius() * sin(vector.azimuthal());
    double addition_z = longitude() + vector.longitude();
    
    Vector3CP addition_vector(sqrt(addition_x * addition_x + addition_y * addition_y), atan2(addition_y, addition_x), addition_z);
    
    return addition_vector;
    
}

// Function azimuthal() Of Vector3C Called In Definition Of Operator '-'

Vector3CP Vector3CP::operator- (Vector3CP &vector) {
    
    double subtraction_x = radius() * cos(Vector3C::azimuthal()) - vector.radius() * cos(vector.Vector3C::azimuthal());
    double subtraction_y = radius() * sin(Vector3C::azimuthal()) - vector.radius() * sin(vector.Vector3C::azimuthal());
    double subtraction_z = longitude() - vector.longitude();
    
    Vector3CP subtraction_vector(sqrt(subtraction_x * subtraction_x + subtraction_y * subtraction_y), atan2(subtraction_y, subtraction_x), subtraction_z);
    
    return subtraction_vector;
    
}

// Redefinition Of Virtual Function transformation() Of Vector3C, In Vector3CP

void Vector3CP::displayInformation() {
    
    cout << "\nVector: "; displayVector();
    cout << "\nMagnitude: " << magnitude();
    cout << "\nRadius: " << radius();
    cout << "\nAzimuthal Angle (Radians): " << azimuthal();
    cout << "\nAzimuthal Angle (Degrees): " << azimuthal() * 180.f / M_PI;
    cout << "\nAltitude: " << longitude();
    cout << "\nComponent Along X-Direction: "; componentX().displayVector();
    cout << "\nComponent Along Y-Direction: "; componentY().displayVector();
    cout << "\nComponent Along Z-Direction: "; componentZ().displayVector();
    cout << "\nUnit Vector: "; unitVector().displayVector();
    
}

// Redefinition Of Barebone Virtual Function transformation() Of Vector3C, In Vector3CP; Functions Accessed Are Members Of Vector3CP, Except displayVector()

void Vector3CP::transformation() {
    
    cout << "\nVector In Terms " << getUnitVector(0) << ", " << getUnitVector(1) << " & " << getUnitVector(2) << " :-" << "\n";
    cout << "\nVector: "; displayCylindricalVector(radius(), longitude());
    
    Vector3SP *vector = new Vector3CP(1.f, Vector3C::azimuthal(), 0.f);
    
    cout << "\n" << getUnitVector(0) << " (In Cartesian Coordinates): "; vector->displayVector();
    
    vector = new Vector3CP(1.f, Vector3C::azimuthal() + M_PI / 2, 0.f);
    
    cout << "\n" << getUnitVector(1) << " (In Cartesian Coordinates): "; vector->displayVector();
    
    vector = new Vector3CP(0.f, 0.f, 1.f);
    
    cout << "\n" << getUnitVector(2) << " (In Cartesian Coordinates): ";vector->displayVector();
    
    cout << "\nComponent Along X-Direction: ";
    
    displayCylindricalVector(radius() * cos(azimuthal()) * cos(azimuthal()), 0.f, -1.f * radius() * cos(azimuthal()) * sin(azimuthal()));
    
    cout << "\nComponent Along Y-Direction: ";
    
    displayCylindricalVector(radius() * sin(azimuthal()) * sin(azimuthal()), 0.f, radius() * sin(azimuthal()) * cos(azimuthal()));
    
    cout << "\nComponent Along Z-Direction: "; displayCylindricalVector(0.f, longitude());
    
    cout << "\nUnit Vector: "; displayCylindricalVector(radius() / magnitude(), longitude() / magnitude());
    
}

// Definition Of Function crossProduct() Of Class CrossVector, Friend OF Vector3CP; Can Access Protected Members Of Vector3CP Directly

Vector3CP CrossVector::crossProduct(Vector3CP &vector_1, Vector3CP &vector_2) {
    
    double component_x = vector_1.radius() * sin(vector_1.azimuthal()) * vector_2.longitude() - vector_1.longitude() * vector_2.radius() * sin(vector_2.azimuthal());
    double component_y = vector_1.longitude() * vector_2.radius() * cos(vector_2.azimuthal()) - vector_1.radius() * cos(vector_1.azimuthal()) * vector_2.longitude();
    double component_z = vector_1.radius() * cos(vector_1.azimuthal()) * vector_2.radius() * sin(vector_2.azimuthal()) - vector_1.radius() * sin(vector_1.azimuthal()) * vector_2.radius() * cos(vector_2.azimuthal());
    
    Vector3CP vector(sqrt(component_x * component_x + component_y * component_y), atan2(component_y, component_x), component_z); return vector;
    
}

void vectorProcessor() {
    
    class Selector {
            
            int dimension, coordinate;
            
        public:
            
            Selector(int &dimension, int &coordinate) { this->dimension = dimension; this->coordinate = coordinate; }
            
            // Since Class Selector Is Local, Function suiGeneris() Has Been Defined Inside The Class
            
            void suiGeneris(int &operation) {
                
                if(dimension == 1 && coordinate == 1) cartesian2D(operation);
                else if(dimension == 1 && coordinate == 2) polar2D(operation);
                else if(dimension == 2 && coordinate == 1) cartesian3D(operation);
                else if(dimension == 2 && coordinate == 2) sphericalPolar3D(operation);
                else cylindricalPolar3D(operation);
                
            }
            
    };
    
    int dimensionChoice = dimensionSelect(); if(dimensionChoice == 0) return;
    
    int coordinateChoice = coordinateSelect(dimensionChoice); if(coordinateChoice == 0) return;
    
    int operationChoice = operationSelect(dimensionChoice); if(operationChoice == 0) return;
    
    Selector *singularity = new Selector(dimensionChoice, coordinateChoice); singularity->suiGeneris(operationChoice); // Local Class Object Pointer Created; Function suiGeneris() Called
    
}

int dimensionSelect() {
    
    int dimensionChoice;
    
    cout << "\nAvailable Physical Spaces:-" << "\n";
    cout << "\n1. 2-Dimensional Space";
    cout << "\n2. 3-Dimensional Space" << "\n";
    cout << "\nEnter Selection For Physical Space: ";
    
    cin >> dimensionChoice;
    
    // Concept Of Exception Handling Utilized
    
    try { if(dimensionChoice != 1 && dimensionChoice != 2 && dimensionChoice != 0) throw invalid_argument("Invalid Selection. Try Again."); }
    
    catch(invalid_argument &arg) { cerr << "\nError: " << arg.what() << "\n"; dimensionChoice = dimensionSelect(); } // Function dimensionSelect() Called Recursively
    
    return dimensionChoice;
    
}

int coordinateSelect(int &dimensionChoice) {
    
    int coordinateChoice;
    
    cout << "\nAvailable Coordinate Systems:-" << "\n";
    cout << "\n1. Cartesian Coordinate System";
    
    if(dimensionChoice == 1) cout << "\n2. Polar Coordinate System" << "\n";
    
    if(dimensionChoice == 2) {
        
        cout << "\n2. Spherical Polar Coordinate System";
        cout << "\n3. Cylindrical Polar Coordinate System" << "\n";
        
    }
    
    cout << "\nEnter Selection For Coordinate System: ";
    
    cin >> coordinateChoice;
    
    // Concept Of Exception Handling Utilized
    
    try { if(coordinateChoice != 1 && coordinateChoice != 2 && ((dimensionChoice == 2 && coordinateChoice == 3) ? false : true) && coordinateChoice != 0) throw invalid_argument("Invalid Selection. Try Again."); }
    
    catch(invalid_argument &arg) { cerr << "\nError: " << arg.what() << "\n"; coordinateChoice = coordinateSelect(dimensionChoice); } // Function coordinateSelect() Called Recursively
    
    return coordinateChoice;
    
}

int operationSelect(int &dimensionChoice) {
    
    int operationChoice;
    
    cout << "\nAvailable Vector Operations:-" << "\n";
    cout << "\n1. Display Vector Information";
    cout << "\n2. Vector Addition";
    cout << "\n3. Vector Subtraction";
    cout << "\n4. Dot Product";
    
    if(dimensionChoice == 1) {
        
        cout << "\n5. Distance Between 2 Vectors";
        cout << "\n6. Angle Between 2 Vectors" << "\n";
        
    }
    
    if(dimensionChoice == 2) {
        
        cout << "\n5. Cross Product";
        cout << "\n6. Distance Between 2 Vectors";
        cout << "\n7. Angle Between 2 Vectors" << "\n";
        
    }
    
    cout << "\nEnter Selection For Vector Operation: ";
    
    cin >> operationChoice;
    
    // Concept Of Exception Handling Utilized
    
    try {
        
        if(operationChoice != 1 && operationChoice != 2 && operationChoice != 3 && operationChoice != 4 && operationChoice != 5 && operationChoice != 6 && ((dimensionChoice == 2 && operationChoice == 7) ? false : true) && operationChoice != 0)
            
            throw invalid_argument("Invalid Selection. Try Again.");
            
    }
    
    catch(invalid_argument &arg) { cerr << "\nError: " << arg.what() << "\n"; operationChoice = operationSelect(dimensionChoice); } // Function operationSelect() Called Recursively
    
    return operationChoice;
    
}

void cartesian2D(int &operationChoice) {
    
    if(operationChoice == 1) {
        
        double abcissa, ordinate;
        
        cout << "\nEnter X-Coordinate: "; cin >> abcissa;
        cout << "Enter Y-Coordinate: "; cin >> ordinate;
        
        processorDriver2D<Vector2C, Vector2C>(operationChoice, abcissa, ordinate); // Template Function processorDriver2D() Called; Default Arguments Utilized
        
    }
    
    else {
        
        double abcissa_1, ordinate_1, abcissa_2, ordinate_2;
        
        cout << "\nEnter X-Coordinate For Vector #1: "; cin >> abcissa_1;
        cout << "Enter Y-Coordinate For Vector #1: "; cin >> ordinate_1;
        cout << "\nEnter X-Coordinate For Vector #2: "; cin >> abcissa_2;
        cout << "Enter Y-Coordinate For Vector #2: "; cin >> ordinate_2;
        
        processorDriver2D<Vector2C, Vector2C>(operationChoice, abcissa_1, ordinate_1, abcissa_2, ordinate_2); // Template Function processorDriver2D() Called
        
    }
    
}

void polar2D(int &operationChoice) {
    
    if(operationChoice == 1) {
        
        double radial, azimuth;
        
        cout << "\nEnter Radial Coordinate: "; cin >> radial;
        cout << "Enter Azimuthal Angle (Radians): "; cin >> azimuth;
        
        processorDriver2D<Vector2C, Vector2P>(operationChoice, radial, azimuth); // Template Function processorDriver2D() Called; Default Arguments Utilized
        
    }
    
    else {
        
        double radial_1, azimuth_1, radial_2, azimuth_2;
        
        cout << "\nEnter Radial Coordinate For Vector #1: "; cin >> radial_1;
        cout << "Enter Azimuthal Angle For Vector #1 (Radians): "; cin >> azimuth_1;
        cout << "\nEnter Radial Coordinate For Vector #2: "; cin >> radial_2;
        cout << "Enter Azimuthal Angle For Vector #2 (Radians): "; cin >> azimuth_2;
        
        processorDriver2D<Vector2P, Vector2P>(operationChoice, radial_1, azimuth_1, radial_2, azimuth_2); // Template Function processorDriver2D() Called
        
    }
    
}

void cartesian3D(int &operationChoice) {
    
    if(operationChoice == 1) {
        
        double abcissa, ordinate, applicate;
        
        cout << "\nEnter X-Coordinate: "; cin >> abcissa;
        cout << "Enter Y-Coordinate: "; cin >> ordinate;
        cout << "Enter Z-Coordinate: "; cin >> applicate;
        
        processorDriver3D<Vector3C, Vector3C>(operationChoice, abcissa, ordinate, applicate); // Template Function processorDriver3D() Called; Default Arguments Utilized
        
    }
    
    else {
        
        double abcissa_1, ordinate_1, applicate_1, abcissa_2, ordinate_2, applicate_2;
        
        cout << "\nEnter X-Coordinate For Vector #1: "; cin >> abcissa_1;
        cout << "Enter Y-Coordinate For Vector #1: "; cin >> ordinate_1;
        cout << "Enter Z-Coordinate For Vector #1: "; cin >> applicate_1;
        cout << "\nEnter X-Coordinate For Vector #2: "; cin >> abcissa_2;
        cout << "Enter Y-Coordinate For Vector #2: "; cin >> ordinate_2;
        cout << "Enter Z-Coordinate For Vector #2: "; cin >> applicate_2;
        
        if(operationChoice == 5) {
            
            Vector3C *vector_1 = new Vector3C(abcissa_1, ordinate_1, applicate_1), *vector_2 = new Vector3C(abcissa_2, ordinate_2, applicate_2);
            
            // Friend Function crossProduct() Of Class Vector3C Called
            
            cout << "\nVector #1: "; vector_1->displayVector(); cout << "\nVector #2: "; vector_2->displayVector(); cout << "\n";
            cout << "\n("; vector_1->displayVector(); cout << ") X ("; vector_2->displayVector(); cout << ") = "; crossProduct(*vector_1, *vector_2).displayVector();
            cout << "\n"; delete vector_1; delete vector_2; vectorProcessor();
            
        }
        
        else processorDriver3D<Vector3C, Vector3C>(operationChoice, abcissa_1, ordinate_1, applicate_1, abcissa_2, ordinate_2, applicate_2); // Template Function processorDriver3D() Called
        
    }
    
}

void sphericalPolar3D(int &operationChoice) {
    
    if(operationChoice == 1) {
        
        double radial, polar, azimuth;
        
        cout << "\nEnter Radial Coordinate: "; cin >> radial;
        cout << "Enter Polar Angle (Radians): "; cin >> polar;
        cout << "Enter Azimuthal Angle (Radians): "; cin >> azimuth;
        
        processorDriver3D<Vector3C, Vector3SP>(operationChoice, radial, polar, azimuth); // Template Function processorDriver3D() Called; Default Arguments Utilized
        
    }
    
    else {
        
        double radial_1, polar_1, azimuth_1, radial_2, polar_2, azimuth_2;
        
        cout << "\nEnter Radial Coordinate For Vector #1: "; cin >> radial_1;
        cout << "Enter Polar Angle For Vector #1 (Radians): "; cin >> polar_1;
        cout << "Enter Azimuthal Angle For Vector #1 (Radians): "; cin >> azimuth_1;
        cout << "\nEnter Radial Coordinate For Vector #2: "; cin >> radial_2;
        cout << "Enter Polar Angle For Vector #2 (Radians): "; cin >> polar_2;
        cout << "Enter Azimuthal Angle For Vector #2 (Radians): "; cin >> azimuth_2;
        
        if(operationChoice == 5) {
            
            Vector3SP *vector_1 = new Vector3SP(radial_1, polar_1, azimuth_1), *vector_2 = new Vector3SP(radial_2, polar_2, azimuth_2);
            
            // Friend Function crossProduct() Of Class Vector3SP Called; Friend Function crossProduct() Of Vector3C Would Be Called If Pointers Are Of Type Vector3C
            
            cout << "\nVector #1: "; vector_1->displayVector(); cout << "\nVector #2: "; vector_2->displayVector(); cout << "\n";
            cout << "\n("; vector_1->displayVector(); cout << ") X ("; vector_2->displayVector(); cout << ") = "; crossProduct(*vector_1, *vector_2).displayVector();
            cout << "\n"; delete vector_1; delete vector_2; vectorProcessor();
            
        }
        
        else processorDriver3D<Vector3SP, Vector3SP>(operationChoice, radial_1, polar_1, azimuth_1, radial_2, polar_2, azimuth_2); // Template Function processorDriver3D() Called
        
    }
    
}

void cylindricalPolar3D(int &operationChoice) {
    
    if(operationChoice == 1) {
        
        double radial, azimuth, altitude;
        
        cout << "\nEnter Radial Coordinate: "; cin >> radial;
        cout << "Enter Azimuthal Angle (Radians): "; cin >> azimuth;
        cout << "Enter Longitudinal Coordinate: "; cin >> altitude;
        
        processorDriver3D<Vector3C, Vector3CP>(operationChoice, radial, azimuth, altitude); // Template Function processorDriver3D() Called; Default Arguments Utilized
        
    }
    
    else {
        
        double radial_1, azimuth_1, altitude_1, radial_2, azimuth_2, altitude_2;
        
        cout << "\nEnter Radial Coordinate For Vector #1: "; cin >> radial_1;
        cout << "Enter Azimuthal Angle For Vector #1 (Radians): "; cin >> azimuth_1;
        cout << "Enter Longitudinal Coordinate For Vector #1: "; cin >> altitude_1;
        cout << "\nEnter Radial Coordinate For Vector #2: "; cin >> radial_2;
        cout << "Enter Azimuthal Angle For Vector #2 (Radians): "; cin >> azimuth_2;
        cout << "Enter Longitudinal Coordinate For Vector #2: "; cin >> altitude_2;
        
        if(operationChoice == 5) {
            
            Vector3CP *vector_1 = new Vector3CP(radial_1, azimuth_1, altitude_1), *vector_2 = new Vector3CP(radial_2, azimuth_2, altitude_2);
            CrossVector *vector = new CrossVector();
            
            // Function crossProduct() Of Friend Class CrossVector Called; Function Calling Would Fail If Pointers 'vector_1', 'vector_2' Are Of Type Vector3C / Vector3SP
            
            cout << "\nVector #1: "; vector_1->displayVector(); cout << "\nVector #2: "; vector_2->displayVector(); cout << "\n";
            cout << "\n("; vector_1->displayVector(); cout << ") X ("; vector_2->displayVector(); cout << ") = "; vector->crossProduct(*vector_1, *vector_2).displayVector();
            cout << "\n"; delete vector; delete vector_1; delete vector_2; vectorProcessor();
            
        }
        
        else processorDriver3D<Vector3CP, Vector3CP>(operationChoice, radial_1, azimuth_1, altitude_1, radial_2, azimuth_2, altitude_2); // Template Function processorDriver3D() Called
        
    }
    
}

int main() {
    
    system("chcp 65001");
    
    cout << "*********VECTOR PROCESSOR*********" << "\n";
    cout << "\nTo Terminate The Processor, Enter '0' At Any Selection Checkpoint." << "\n";
    cout << "\nProcess Unexpectedly High Numeric Values As Infinity. Process Unexpectedly Low Numeric Values As 0." << "\n";
    
    vectorProcessor(); cout << "\nTerminating Processor. Goodbye..." << "\n"; return 0;
    
}