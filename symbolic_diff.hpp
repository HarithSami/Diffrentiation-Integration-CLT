#include <math.h>
#include <sstream>
#include <iostream>
#include "stdlib.h"
#include <string>
#include <stack>
#include <cmath>





using namespace std;

class ExpressionTree
{
protected:
    string value;
    ExpressionTree* lhs, * rhs;
public:
    //constructor
    ExpressionTree();
    //clones the ExpressionTree recursively and returns a pointer to the clone
    ExpressionTree* clone();
    //constructs an ExpressionTree from a given string formatted in postfix
    void construct(string PF);
    //recursively destroys tree and all its children
    void destroy();
    //recursively displays tree inorder showing order of operations with parantheses
    virtual void inorder();
    //recursively tranforms the ExpressionTree into an ExpressionTree representing its derivative 
    void deriv();
    //recursively tranforms the ExpressionTree into an ExpressionTree representing its integral 
    void integ();
    //performs routine simplifications on the Expression tree where possible
    void simplify();
    //takes a given string variable by reference and appends the ExpressionTree in postfix notation to it recursively
    void postfix(string& pf);
    //displays an ExpressionTree without outer parans and ends line
    void display();

};

class FunctionLeaf : public ExpressionTree
{
public:
    FunctionLeaf();
    void inorder();
};

// #include "stdafx.h"
//	Functions for inspecting individual characters
bool isOperator(char c);
bool isOperand(char c);
bool isOperand(string s);
bool isNum(char c);
bool isNum(string s);
bool isVar(char c);
int	 getPrecedence(char c);
//	takes an algebraic string in infix and returns it in postfix
string toPF(string infix);
//evaluate a postfix string with no variables to get a double result
double evalPF(string& pf);




int symbolic_diff() {

    enum symb_choice {
        prefix_form = 1,
        diffrentiation,
    };
    string sentinel = "yes";

    while (toupper(sentinel[0]) != 'N') {
        //to hold the function input by user and its postfix form
        string funct, pfFunct, intFunct, str_choice, second_diff;

        cout << "Enter a function to take the derivative of: " << endl;
        getline(cin, funct);
        pfFunct = toPF(funct);
        cout << endl;


        cout << "choose one of the following options: \n"
            "[1] Show Prefix Form\n"
            "[2] Find the Derivative\n";
        getline(cin, str_choice);
        int int_choice = stoi(str_choice);

        if ((int_choice < 4) && (int_choice > 0)) {
            cout << "PF f(x):" << pfFunct << endl;
            cout << endl;

            ExpressionTree* root;
            root = new ExpressionTree();
            root->construct(pfFunct);
            if (int_choice == prefix_form) {
                cout << "Expression tree printed from left to right:" << endl;
            }
            root->display();
            if (int_choice == prefix_form) {
                cout << endl;
            }
            string exprPF = "";
            string exprINT = exprPF;
            root->postfix(exprPF);
            if (int_choice == prefix_form) {
                cout << "Expression tree back to postfix: " << exprPF << endl;
                cout << endl;
            }
            intFunct = pfFunct;

            if (int_choice == diffrentiation) {
                cout << "Derivative tree:" << endl;
            }
            root->deriv();
            if (int_choice == diffrentiation) {
                cout << "f'(x) = ";
            }
            root->display();
            if (int_choice == diffrentiation) {
                cout << endl;

                cout << "After simplify:" << endl;
            }
            root->simplify();
            root->simplify();
            if (int_choice == diffrentiation) {
                cout << "f'(x) = ";
            }
            root->display();
            cout << endl;
            if (int_choice == diffrentiation) {
                cout << "Deriv in postfix form: " << endl;
            }
            string post = "";
            root->postfix(post);
            if (int_choice == diffrentiation) {
                cout << post << endl;

                cout << endl;
                cout << endl;
            }
            ExpressionTree* rtcpy;
            rtcpy = NULL;

            rtcpy = root->clone();

            if (int_choice == diffrentiation) {
                cout << "Find 2nd Derivative? (y/n)" << endl;
                getline(cin, sentinel);
                while (toupper(sentinel[0]) != 'N') {
                    cout << "After second derivative:" << endl;
                    rtcpy->deriv();
                    cout << "f''(x) = ";
                    rtcpy->display();
                    cout << endl;

                    cout << "After simplify:" << endl;

                    cout << "f''(x) = ";
                    rtcpy->simplify();
                    rtcpy->simplify();
                    rtcpy->display();
                    cout << endl << endl;

                    sentinel = "n";
                }
            }


            cout << "Solve for x? (y/n)" << endl;
            getline(cin, sentinel);

            while (toupper(sentinel[0]) != 'N') {
                bool neg = false;
                double val;
                string input;
                string postfix = "";
                cout << "Enter a double value for x: " << endl;
                getline(cin, input);


                if (input[0] == '-') {
                    neg = true;
                    input.erase(0, 1);
                }

                val = stod(input);
                if (neg == true) val *= -1;

                root->postfix(postfix);

                string pfFunct_ = "";
                string intFunct_ = "";
                pfFunct_ += pfFunct;
                intFunct_ += intFunct;
                while (pfFunct_.find('x') != string::npos)
                    if ((pfFunct_.find('x') != string::npos)) pfFunct_.replace(pfFunct_.find('x'), 1, to_string(val));

                //	Replaces all 'x's in postfix string with string representation of entered number
                while (postfix.find('x') != string::npos)
                    if ((postfix.find('x') != string::npos)) postfix.replace(postfix.find('x'), 1, to_string(val));

                cout << "Results: " << endl;
                cout << "f(" << val << ") = " << evalPF(pfFunct_) << endl;
                cout << "f'(" << val << ") = " << evalPF(postfix) << endl;
                cout << "f''(" << val << ") = " << evalPF(postfix) << endl;
                cout << endl;
                cout << "Solve for x again? (y/n)" << endl;
                getline(cin, sentinel);
            }

            root->destroy();
            if (rtcpy != NULL) rtcpy->destroy();

            cout << "Would you like to process another function? (y/n)" << endl;
            getline(cin, sentinel);
            system("CLS");
        }
        else {
            cout << endl;
            cout << "You have entered a false valuse.\n Try again? (y/n)" << endl;
            getline(cin, sentinel);
        }
    }

    return 0;


}



ExpressionTree::ExpressionTree()
{
    value = "";
    lhs = NULL;
    rhs = NULL;
}
ExpressionTree* ExpressionTree::clone()
{
    ExpressionTree* temp = new ExpressionTree();
    temp->value = value;							//copies to temp value and a clone of
    if (lhs != NULL)  temp->lhs = lhs->clone();		// its lhs and rhs
    if (rhs != NULL) temp->rhs = rhs->clone();
    return temp;
}

void ExpressionTree::construct(string PF)
{
    stack<ExpressionTree*> treeStack;		//will help to obey the order of operations
    ExpressionTree* T1, * T2;				//	specified by the postfix string
    string val = "";

    while (PF.length() > 0)
    {

        if (PF[0] == ' ')
        {
            PF.erase(0, 1);				//remove whitespace
        }
        else if (isOperand(PF))
        {
            while (isOperand(PF))
            {
                val += PF[0];			//add any operands to val
                PF.erase(0, 1);
            }

            ExpressionTree* t;			//make a new expression tree with val
            t = new ExpressionTree();
            t->value = val;
            treeStack.push(t);
            val = "";
        }
        else if (isOperator(PF[0]))
        {
            val += PF[0];
            PF.erase(0, 1);

            T1 = treeStack.top();
            treeStack.pop();
            T2 = treeStack.top();
            treeStack.pop();

            ExpressionTree* t;
            t = new ExpressionTree();		//take two trees off stack and make a new tree 
            t->value = val;					//with operator value, then push its ptr on the stack
            t->lhs = T2;
            t->rhs = T1;
            treeStack.push(t);
            val = "";
        }
    }	//END LOOP

    value = treeStack.top()->value;
    lhs = treeStack.top()->lhs;
    rhs = treeStack.top()->rhs;
    treeStack.pop();
}

void ExpressionTree::inorder()
{
    if (lhs != NULL)	cout << "(";
    if (lhs != NULL)	lhs->inorder();
    cout << ' ' << value << ' ';
    if (rhs != NULL)	rhs->inorder();
    if (rhs != NULL)	cout << ")";
}

void ExpressionTree::display()
{
    if (lhs != NULL)	lhs->inorder();
    cout << ' ' << value << ' ';
    if (rhs != NULL)	rhs->inorder();
    // cout << endl;
}

void ExpressionTree::destroy()
{
    if (lhs != NULL)	lhs->destroy();
    if (rhs != NULL)	rhs->destroy();
    //cout << "Deleting " << value << endl;
    delete this;
}

//Transforms the ExpressionTree called on into an ExpressionTree representing its derivative
void ExpressionTree::deriv()
{
    ExpressionTree* T1, * T2, * T3, * T4, * T5;
    if (isVar(value[0]))		value = "1";		//base case: value at root of this subtree is x	which makes its derivative one
    else if (isNum(value[0]))	value = "0";		//base case: value at root of this subtree is numeric which makes its derivative zero 
    else
    {
        switch (value[0])
        {	//For add and sub, only need to take deriv of lhs and rhs
        case '+':	//add tree derivs
        case '-':	//sub tree derivs
            lhs->deriv();
            rhs->deriv();
            break;
        case '*':	//product rule

              //Clones of lhs and rhs to use for T1*T2' + T3*T4' (product rule)
            T1 = lhs->clone();
            T2 = rhs->clone();

            T3 = rhs->clone();
            T4 = lhs->clone();


            value = "+";		//instead of multiplying left and right sides, we add 2 products
            lhs->value = "*";	//make the value in lhs and rhs multiplication operators
            rhs->value = "*";

            //destroy any children more than 1 separation away to avoid orphans
            if (lhs->lhs != NULL)		lhs->lhs->destroy();
            if (lhs->lhs != NULL)   lhs->rhs->destroy();

            //apply product rule with cloned trees
            lhs->lhs = T1;
            lhs->rhs = T2;
            T2->deriv();

            if (rhs->lhs != NULL)	rhs->lhs->destroy();
            if (rhs->rhs != NULL)	rhs->rhs->destroy();

            rhs->lhs = T3;
            rhs->rhs = T4;
            T4->deriv();

            break;
        case '/':	//quotient rule

              //T1 and T4 are numerators
              //T2, T3, and T5 are denominators
              //clones of lhs and rhs to use for (T1*T2' - T3*T4')/(T5^2)
            T1 = lhs->clone();
            T2 = rhs->clone();

            T3 = rhs->clone();
            T4 = lhs->clone();
            T5 = rhs->clone();

            //lhs will be a subtraction tree
            lhs->value = "-";

            //multipy deriv of num by den funct
            if (lhs->lhs == NULL)	lhs->lhs = new ExpressionTree();
            lhs->lhs->value = "*";
            if (lhs->lhs->lhs != NULL)	lhs->lhs->lhs->destroy();
            if (lhs->lhs->rhs != NULL)	lhs->lhs->rhs->destroy();

            lhs->lhs->lhs = T1;		//num
            lhs->lhs->rhs = T2;		//den	
            T1->deriv();

            //multiply deriv of den by num funct
            if (lhs->rhs == NULL)	lhs->rhs = new ExpressionTree();	//make a new tree to hold * if necessary
            lhs->rhs->value = "*";
            if (lhs->rhs->lhs != NULL)	lhs->rhs->lhs->destroy();		//if there are already existing branches, cut them
            if (lhs->rhs->rhs != NULL)	lhs->rhs->rhs->destroy();		//	to replace with T3 and T4
            lhs->rhs->lhs = T3;		//den
            lhs->rhs->rhs = T4;		//num
            T3->deriv();

            rhs->value = "^";
            rhs->lhs = T5;
            if (rhs->rhs == NULL)	rhs->rhs = new ExpressionTree();
            rhs->rhs->value = "2";
            if (rhs->rhs->lhs != NULL)
            {
                rhs->rhs->lhs->destroy();
                rhs->rhs->lhs = NULL;
            }
            if (rhs->rhs->rhs != NULL)
            {
                rhs->rhs->rhs->destroy();
                rhs->rhs->rhs = NULL;
            }

            break;
        case '^':	//power law
            ExpressionTree * base = lhs->clone();	//allows for chain rule if enter for ex (x+2)^2
            ExpressionTree* power = rhs->clone();
            value = "*";
            lhs->destroy();
            rhs->destroy();
            lhs = NULL;
            rhs = NULL;

            if (isNum(power->value) && isNum(base->value))
            {
                value = "0";
            }
            else if (isNum(power->value))
            {
                rhs = new ExpressionTree();
                rhs->value = "^";

                double powerDouble = stod(power->value);
                int decIndex;

                rhs->rhs = new ExpressionTree();
                rhs->rhs->value = to_string((powerDouble - 1));
                decIndex = rhs->rhs->value.find('.');
                rhs->rhs->value = rhs->rhs->value.substr(0, decIndex + 2);	//set number of decimal places for number values that have been altered

                rhs->lhs = base->clone();


                if (!isOperand(base->value))
                {
                    ExpressionTree* toDeriv;
                    toDeriv = base->clone();
                    toDeriv->deriv();
                    lhs = new ExpressionTree();
                    lhs->value = "*";
                    lhs->lhs = toDeriv;
                    lhs->rhs = power->clone();
                }
                else
                {
                    lhs = power->clone();
                }


            }
            else					//	TODO: exponential functions
            {


                lhs = new ExpressionTree();
                lhs->value = "^";

                lhs->lhs = base->clone();
                lhs->rhs = power->clone();

                if (power->lhs != NULL && power->rhs != NULL)		//chain rule if there is more than a single numeric value in power
                {
                    rhs = new ExpressionTree();
                    rhs->value = "*";
                    rhs->lhs = power->clone();
                    rhs->lhs->deriv();
                    rhs->rhs = new FunctionLeaf();
                    rhs->rhs->lhs = new ExpressionTree();
                    rhs->rhs->lhs->value = "ln";
                    rhs->rhs->rhs = base->clone();

                }
                else											//do exponential function differentiation rule w/o chain rule
                {
                    rhs = new FunctionLeaf();

                    rhs->lhs = new ExpressionTree();
                    rhs->lhs->value = "ln";

                    rhs->rhs = new ExpressionTree();
                    rhs->rhs = base->clone();
                }

            }


            power->destroy();
            base->destroy();

            break;
        }
    }
}


void ExpressionTree::integ()
{
    ExpressionTree* T1, * T2, * T3, * T4, * T5;
    if (isVar(value[0]))		value = "1";		//base case: value at root of this subtree is x	which makes its derivative one
    else if (isNum(value[0]))	value = "x";		//base case: value at root of this subtree is numeric which makes its derivative zero 
    else
    {
        switch (value[0])
        {	//For add and sub, only need to take deriv of lhs and rhs
        case '+':	//add tree derivs
        case '-':	//sub tree derivs
            lhs->deriv();
            rhs->deriv();
            break;
        case '*':	//product rule

              //Clones of lhs and rhs to use for T1*T2' + T3*T4' (product rule)
            T1 = lhs->clone();
            T2 = rhs->clone();

            T3 = rhs->clone();
            T4 = lhs->clone();


            value = "+";		//instead of multiplying left and right sides, we add 2 products
            lhs->value = "*";	//make the value in lhs and rhs multiplication operators
            rhs->value = "*";

            //destroy any children more than 1 separation away to avoid orphans
            if (lhs->lhs != NULL)		lhs->lhs->destroy();
            if (lhs->lhs != NULL)   lhs->rhs->destroy();

            //apply product rule with cloned trees
            lhs->lhs = T1;
            lhs->rhs = T2;
            T2->deriv();

            if (rhs->lhs != NULL)	rhs->lhs->destroy();
            if (rhs->rhs != NULL)	rhs->rhs->destroy();

            rhs->lhs = T3;
            rhs->rhs = T4;
            T4->deriv();

            break;
        case '/':	//quotient rule

              //T1 and T4 are numerators
              //T2, T3, and T5 are denominators
              //clones of lhs and rhs to use for (T1*T2' - T3*T4')/(T5^2)
            T1 = lhs->clone();
            T2 = rhs->clone();

            T3 = rhs->clone();
            T4 = lhs->clone();
            T5 = rhs->clone();

            //lhs will be a subtraction tree
            lhs->value = "-";

            //multipy deriv of num by den funct
            if (lhs->lhs == NULL)	lhs->lhs = new ExpressionTree();
            lhs->lhs->value = "*";
            if (lhs->lhs->lhs != NULL)	lhs->lhs->lhs->destroy();
            if (lhs->lhs->rhs != NULL)	lhs->lhs->rhs->destroy();

            lhs->lhs->lhs = T1;		//num
            lhs->lhs->rhs = T2;		//den	
            T1->deriv();

            //multiply deriv of den by num funct
            if (lhs->rhs == NULL)	lhs->rhs = new ExpressionTree();	//make a new tree to hold * if necessary
            lhs->rhs->value = "*";
            if (lhs->rhs->lhs != NULL)	lhs->rhs->lhs->destroy();		//if there are already existing branches, cut them
            if (lhs->rhs->rhs != NULL)	lhs->rhs->rhs->destroy();		//	to replace with T3 and T4
            lhs->rhs->lhs = T3;		//den
            lhs->rhs->rhs = T4;		//num
            T3->deriv();

            rhs->value = "^";
            rhs->lhs = T5;
            if (rhs->rhs == NULL)	rhs->rhs = new ExpressionTree();
            rhs->rhs->value = "2";
            if (rhs->rhs->lhs != NULL)
            {
                rhs->rhs->lhs->destroy();
                rhs->rhs->lhs = NULL;
            }
            if (rhs->rhs->rhs != NULL)
            {
                rhs->rhs->rhs->destroy();
                rhs->rhs->rhs = NULL;
            }

            break;
        case '^':	//power law
            ExpressionTree * base = lhs->clone();	//allows for chain rule if enter for ex (x+2)^2
            ExpressionTree* power = rhs->clone();
            value = "*";
            lhs->destroy();
            rhs->destroy();
            lhs = NULL;
            rhs = NULL;

            if (isNum(power->value) && isNum(base->value))
            {
                value = "0";
            }
            else if (isNum(power->value))
            {
                rhs = new ExpressionTree();
                rhs->value = "^";

                double powerDouble = stod(power->value);
                int decIndex;

                rhs->rhs = new ExpressionTree();
                rhs->rhs->value = to_string((powerDouble - 1));
                decIndex = rhs->rhs->value.find('.');
                rhs->rhs->value = rhs->rhs->value.substr(0, decIndex + 2);	//set number of decimal places for number values that have been altered

                rhs->lhs = base->clone();


                if (!isOperand(base->value))
                {
                    ExpressionTree* toDeriv;
                    toDeriv = base->clone();
                    toDeriv->deriv();
                    lhs = new ExpressionTree();
                    lhs->value = "*";
                    lhs->lhs = toDeriv;
                    lhs->rhs = power->clone();
                }
                else
                {
                    lhs = power->clone();
                }


            }
            else					//	TODO: exponential functions
            {


                lhs = new ExpressionTree();
                lhs->value = "^";

                lhs->lhs = base->clone();
                lhs->rhs = power->clone();

                if (power->lhs != NULL && power->rhs != NULL)		//chain rule if there is more than a single numeric value in power
                {
                    rhs = new ExpressionTree();
                    rhs->value = "*";
                    rhs->lhs = power->clone();
                    rhs->lhs->deriv();
                    rhs->rhs = new FunctionLeaf();
                    rhs->rhs->lhs = new ExpressionTree();
                    rhs->rhs->lhs->value = "ln";
                    rhs->rhs->rhs = base->clone();

                }
                else											//do exponential function differentiation rule w/o chain rule
                {
                    rhs = new FunctionLeaf();

                    rhs->lhs = new ExpressionTree();
                    rhs->lhs->value = "ln";

                    rhs->rhs = new ExpressionTree();
                    rhs->rhs = base->clone();
                }

            }


            power->destroy();
            base->destroy();

            break;
        }
    }
}

void ExpressionTree::simplify()
{
    if (isNum(value))	return;
    if (isVar(value[0]))	return;

    switch (value[0])
    {
    case '*':
        if (lhs->value == "0" || rhs->value == "0")
        {
            value = "0";
            lhs->destroy();
            rhs->destroy();
            lhs = NULL;
            rhs = NULL;
        }
        else if (isNum(lhs->value) && isNum(rhs->value))
        {
            double a, b;
            int decIndex;
            a = stod(lhs->value);
            b = stod(rhs->value);
            value = to_string(a * b);
            decIndex = value.find('.');
            value = value.substr(0, decIndex + 2);
            lhs->destroy();
            rhs->destroy();
            lhs = NULL;
            rhs = NULL;
        }
        else if (lhs->value == "1" || lhs->value == "1.0")
        {
            ExpressionTree* T1;
            T1 = rhs->clone();
            lhs->destroy();
            rhs->destroy();
            value = T1->value;
            lhs = T1->lhs;
            rhs = T1->rhs;
        }
        else if (rhs->value == "*")
        {
            if (isNum(lhs->value) && isNum(rhs->lhs->value))
            {
                ExpressionTree* T1;
                T1 = rhs->rhs->clone();
                double num1 = stod(lhs->value);
                double num2 = stod(rhs->lhs->value);
                rhs->lhs->destroy();
                rhs->rhs->destroy();
                double prod = num1 * num2;
                int decIndex;

                lhs->value = to_string(prod);
                decIndex = lhs->value.find('.');
                lhs->value = lhs->value.substr(0, decIndex + 2);
                rhs = T1;
            }

        }
        break;
    case '+':
        if (lhs->value == "0")
        {
            ExpressionTree* T1;
            T1 = rhs->clone();		//clone rhs
            rhs->destroy();				// delete it
            lhs->destroy();
            value = T1->value;		//	take value and ptrs 
            lhs = T1->lhs;			//	from T1
            rhs = T1->rhs;
        }
        else if (rhs->value == "0")
        {
            ExpressionTree* T1;
            T1 = lhs->clone();
            rhs->destroy();
            lhs->destroy();
            value = T1->value;
            lhs = T1->lhs;
            rhs = T1->rhs;
        }
        break;
    case '-':
        if (rhs->value == "0")
        {
            ExpressionTree* T1;
            T1 = lhs->clone();
            rhs->destroy();
            lhs->destroy();
            value = T1->value;
            lhs = T1->lhs;
            rhs = T1->rhs;

        }

        break;
    case '^':
        if (rhs->value == "1" || rhs->value == "1.0")	//if it's to the power of 1, make this tree
        {													//remove the power and make this tree the base tree
            ExpressionTree* T1;
            T1 = lhs->clone();
            rhs->destroy();
            lhs->destroy();
            value = T1->value;
            lhs = T1->lhs;
            rhs = T1->rhs;
        }
        break;
    }
    if (lhs != NULL)	lhs->simplify();
    if (rhs != NULL)	rhs->simplify();
}

void ExpressionTree::postfix(string& pf)
{
    if (lhs != NULL)		lhs->postfix(pf);
    if (rhs != NULL)		rhs->postfix(pf);
    pf += ' ' + value;
}






void FunctionLeaf::inorder()
{
    if (lhs != NULL)	cout << "(";
    if (lhs != NULL)	lhs->inorder();
    cout << '(';
    if (rhs != NULL)	rhs->inorder();
    cout << ')';
    if (rhs != NULL)	cout << ")";
}

FunctionLeaf::FunctionLeaf()
{
    value = "F";
    lhs = NULL;
    rhs = NULL;
}


string toPF(string infix)

{
    string postfix = "";
    stack<char> operatorStack;
    char currOp;
    istringstream reader(infix);

    while (!reader.eof())					//while still characters in reader stream to process
    {
        reader >> ws;										//if any ws starting stream, discard it
        while (infix[0] == ' ') infix.erase(0, 1);			//delete any whitespace from infix string	

        if (infix[0] == '(')											//if current symbol is a left paran
        {
            reader >> currOp;												// read in paran
            reader >> ws;													//	and ws

            operatorStack.push(infix[0]);									// push '(' it onto stack
            infix.erase(0, 1);												// erase '(' from infix
        }
        else if (infix[0] == ')')											//if current symbol is a right paran
        {
            reader >> currOp;												//	read in paran
            reader >> ws;													//	  and ws

            infix.erase(0, 1);												// erase ')' from infix

            while (!operatorStack.empty() && operatorStack.top() != '(')	//while still operators in stack and have not yet reached '('
            {
                postfix = postfix + operatorStack.top() + ' ';					//add top of stack to end of postfix string
                operatorStack.pop();											//pop top of stack
            }

            if (operatorStack.top() == '(')		operatorStack.pop();			//if a '(' remains on top of stack, pop it off
        }
        else if (isOperator(infix[0]))	//if first char of infix is an operator character (ex: * / + -)
        {
            //read in operator and any white space between it and operands
            reader >> currOp;
            reader >> ws;

            if (!operatorStack.empty())	//if there are operators in the stack
            {
                if (getPrecedence(infix[0]) > getPrecedence(operatorStack.top()))	//if the precedence of the current operator is greater than the precedence 
                {																	//of operator at top of stack
                    operatorStack.push(infix[0]);										//push it onto stack
                    infix.erase(0, 1);													//erase it from infix

                }
                else //if precedence lower
                {
                    //dump stack into postfix string as long as stack operators are higher precedence than current char being checked
                    //  and the stack has operators remaining in it
                    while (!operatorStack.empty() && getPrecedence(operatorStack.top()) > getPrecedence(infix[0]))
                    {
                        postfix = postfix + operatorStack.top() + ' ';
                        operatorStack.pop();
                    }

                    operatorStack.push(infix[0]);	//push scanned operator onto stack
                    infix.erase(0, 1);				//erase scanned operator from infix string
                }
            }
            else						//if no operators in stack
            {
                operatorStack.push(infix[0]);	//push this operator onto stack
                infix.erase(0, 1);				//  then erase it from infix string
            }

        }
        else //first char of infix is not an operator
        {
            if (isNum(infix[0]))	//if character is numeric
            {
                int opand;				//int var to hold the number
                reader >> opand;		//read it in with the istringstream
                postfix = postfix + to_string(opand) + ' ';		//append it to postfix string

                                        //while the first character of infix string is numeric, erase it
                while (isNum(infix[0]))
                {
                    infix.erase(0, 1);
                }
            }
            else if (isVar(infix[0]))	//if character is a valid variable character (a-z OR A-Z)
            {
                char opand;					//char var to hold variable symbol
                reader >> opand;			//read it from istringstream
                postfix = postfix + opand + ' ';	//append it to postfix string

                infix.erase(0, 1);			//erase it
            }

        }
    }

    while (!operatorStack.empty())
    {
        postfix = postfix + operatorStack.top() + ' ';
        operatorStack.pop();
    }
    reader >> currOp;

    return postfix;
}

bool isOperator(char c)
{
    if (c == '^' || c == '+' || c == '-' || c == '*' || c == '/')	 return true;
    return false;
}
bool isOperand(char c)
{
    if (c >= 'a' && c <= 'z') return true;
    if (c >= '0' && c <= '9') return true;
    return false;
}
bool isOperand(string s)
{
    if (isNum(s))	return true;
    if (isVar(s[0]))	return true;
    return false;
}
bool isNum(string s)
{
    if (isNum(s[0])) return true;
    if (s.length() > 1 && s[0] == '-' && isNum(s[1])) return true;
    return false;
}

bool isNum(char c)
{
    if (c >= '0' && c <= '9') return true;
    return false;
}

bool isVar(char c)
{
    if (c >= 'a' && c <= 'z') return true;
    return false;
}
int	 getPrecedence(char c)
{
    if (c == '^')					  return 4;
    else if (c == '*' || c == '/')	  return 3;
    else if (c == '-')				  return 2;
    else if (c == '+')				  return 1;
    else							  return 0;
}

double evalPF(string& pf)
{
    double currOpand, lhs, rhs, newOpand;
    string token;
    char currOp;
    stack <double> operands;
    double result = 0.0;

    istringstream reader(pf);
    while (reader >> token)
    {
        if (isNum(token))
        {
            currOpand = stod(token); //convert string token to double
            operands.push(currOpand);

        }
        else if (isOperator(token[0]))
        {
            currOp = token[0];

            rhs = operands.top();
            operands.pop();
            lhs = operands.top();
            operands.pop();

            switch (currOp)
            {
            case '+':	newOpand = lhs + rhs;
                operands.push(newOpand);
                break;

            case '-':	newOpand = lhs - rhs;
                operands.push(newOpand);
                break;

            case '*':	newOpand = lhs * rhs;
                operands.push(newOpand);
                break;

            case '/':	newOpand = lhs / rhs;
                operands.push(newOpand);
                break;

            case '^':	newOpand = pow(lhs, rhs);
                operands.push(newOpand);
                break;

            }
        }
        else if (token[0] == 'l')
        {
            string function, value;
            function = token;
            reader >> value;
            currOpand = stod(value);
            newOpand = log(currOpand);
            operands.push(newOpand);
        }
    }

    result = operands.top();
    operands.pop();
    return result;

}