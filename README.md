# Diffrentiation-and-Integration

        << "1.Symbolic Diffrentiation\n"
        << "2.Numeric Diffrentiation\n"
        << "3.Numeric Integration" << endl;
        
        
Background : 
My team and I decided to create a "Numerical Methods" based menu-driven program. The program will allow the user to explore a wide range of mathematical functions compiled together for ease of access. To aid in this, I will be implementing a sub-menu of methods that relate to "Linear Algebra". 
Naturally, I chose the topic of polynomial Diffrenitation, Integration and plotting; because it is a general topic used in all sorts of engineering purposes. Additionally it is more complex to implement than other topics that require a single function to implement.


Motivation:
We decided to create a code with versitile functions, that could be used in a rather wide range of engineering topics.

Aditionally, the concepts of integration and diffrentiation lend themselves perfectly to the topics from Unit 1. (Classes, pointers and arrays)


Represenitng Polynomials :
I decided to represent polynomial functions using a cooficient array and the power of each term is represented by its position in the array, the concept is fairly simple and can be seen on many Casio calculators, as shown in Figure 2.


Figure 2: Find Roots option in Calculators.

The user will be promted to input the coefficient. The coefficients become part of the coefficient_array.

The degree (power) of each term will be represented by its position in the array. For instance, coefficient_array[0] has a power of 0, coefficient_array[1] has a power of 1 and so on. See the example in Figure 3.


This program has encapsulated three sub-functions: symbol differentiation, numerical differentiation, and numerical integration. This page contains some details about how the program works, as it is basically the final version of the document.


Symbolic Differentiation :
Symbolic differentiation was repeated several times throughout the project. However, the latest version has been improved in every way, giving you more flexibility in terms of user experience and final product. 
 The original method used arrays to represent polynomials. This approach requires the user to enter all the coefficients of the polynomial based on the degree 
 of the custom polynomial. The new method is string-based, allowing users to enter more different equations. You can also include products, quotients, and exponents rules. Equation like:

5 * x ^ (4 * x) + (x ^ 3) / (2 * x)

Which cannot be expressed by the old method, is now possible by the new method. 
Double differentials are also possible in the new process. "Solving the derivative at each point x" is also included.



Numerical Differentiation:
Numerical differentiation consists of two parts. A CSV file read loop that saves records in long double format, and a data processing loop that retrieves and saves data. Before, data for fully functional ostream and istream functions was registered. The additional plotting feature required the data-set to be saved as a long double, but the entire function had to be redesigned. The Numerical Integral was very quick to implement, as its structure was essentially similar to the Numerical Differentiation, it relied on the same library.



Algebric Calculus:
The above sub-menus have been merged into a simple menu-based interface called the Algebraic Calculus. It serves as one of the three common menu features of the application. Algebraic Calculus implements a switch-case interface that guides the program to the sub-menu program selected in the control box. It also implements a user input check function.

References:
Symbolic Differentiation explainer : https://www.cs.csustan.edu/~john/Classes/Previous_Semesters/CS3100_DataStructures/2003_04_Fall/Asg04/DiffAsg.html 
