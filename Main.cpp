/*
    © 2024 Alex Holmes

        Some different methods to check if a number is even without using a modulus operator, with some added bonus util functions that were fun to make, like charToInt(), intToChar()
    and callMethod(), all made using only built in library functions other than iostream because I may have overcomplicated this but I'm sure not making my own console window
    and data streaming system for it, as fun as that sounds. Mainly did this to practise good habits like commenting code and error checking/input validation

        Like anyone would want to steal this anyway, and I guarentee many others have done something like the methods in here, the hardest things in here were the charToInt(), 
    intToChar(), and the callMethod(), those are pretty much the only reasons this is going on github, on top of someone telling me to just throw everything on there because it's
    a good habit, also used this to practise commenting my code, because when I learned, I never learned to comment my code because I was self-taught and it's been a really
    tricky habit to break. Anyway, rant over.
*/

#include <iostream>

int charToInt(char* in) { // Converts a string to an int, it could be shorter but it also validates input
    int size = 0; // The length of the number string
    int out = 0; // The final result
    bool isNegative = false; // Flag for if the number is negative
    for (int i = 0; i < 256; i++) { // Loops through the inputted array until it hits the null terminator, adding them to the result
        if (in[i] == 0) { 
            size = i; // Sets the size to the index, adding 1 is not necessary since only the previous digits are needed
            break; // breaks the loop, no need to keep iterating once null terminator is hit
        }
        if (i == 255 && size == 0) {
            std::cout << "Number too long (max 256 digits)" << std::endl; // If no null terminator is ever hit, then the number is over 256 digits long. returns an error
            return 0;
        }
    }

    for (int i = size - 1; i >= 0; i--) { // Iterates backwards through the input string from size
        if (in[i] == '-') { // If the character is a - sign, sets isNegative true and continues since it shouldn't be saving the -
            if (isNegative) {
                std::cout << in << " is not an integer." << std::endl; // If there was already a - throws an error, since a number can only have one of those
                return 0;
            }
            if (i != 0) {
                std::cout << in << " is not an integer." << std::endl; // If the - isn't in the first spot, it's not a valid number, throws an error
                return 0;
            }
            isNegative = true;
            continue;
        }
        if ((in[i] < '0' || in[i] > '9') && in[i] != '-') { // Makes sure the string is actually an integer
            std::cout << in << " is not an integer." << std::endl; // If not, throws an error and returns an error
            return 0;
        } else { // If all the digits are numbers, add them to the result
            out += (in[i + (isNegative ? 1 : 0)] - 48) * std::pow(10, size - (i + 1 + (isNegative ? 1 : 0))); // Adds the digits one at a time using i to the power of 10, adding 1 to the index if it's negative
        }
    }
    return (isNegative ? (out - (out * 2)) : out); // Returns the result
}

char* intToChar(int in) { // This is purely here for fun, wanted to see if I could do it
    int size = 0; // Stores the length of the number
    bool isNegative = (in < 0); // Flag for if the input is negative
    int adjIn = std::abs(in); // Makes an absolute version of in, since whether it is negative is not important after the line above

    for (int i = 0; i < 256; i++) { // Loops through the number to find the starting point (where dividing it by 10 is less than 10)
        if (adjIn / std::pow(10, i) >= 10) // If dividing it by 10 to the power of i gets you less than 10, that is the first digit, otherwise proceed to the next iteration
            continue;
        size = i + 1; // Once the start is found, set size to the index + 1, since indexes start at 0
        break; // No need to continue iterating
    }

    char* out = new char[size + 1 + (isNegative ? 1 : 0)]; // Stores the result to be returned
    if (isNegative)
        out[0] = '-';
    out[size + (isNegative ? 1 : 0)] = '\0'; // sets the last space to a null terminator, so that it can be handled properly

    for (int i = 0; i < size; i++) // Loops through the digits of the number, adding 48 because the UTF-8 value for 0 is 48, and storing a 0 would terminate the string
        out[size - (i + 1) + (isNegative ? 1 : 0)] = (char)(adjIn / (int)std::pow(10, i) % 10 + 48); // Sets the current digit in the array backwards, after isolating it and adding 48
    
    return out; // Returns the result
}

// Forward Declarations of the different methods
int Method(int in);
char* Method1(char* in);
int Method2(int in);

// Forward Declaration of callMethod
template<typename T, typename... Arg>
void callMethod(const char* Name, T Func(T), Arg... Args);

int main() {
    char in[256];
    std::cout << "Enter a number: ";
    std::cin >> in;
    std::cout << std::endl;
    
    int val = charToInt(in);

    char* c = intToChar(val);
    std::cout << c << std::endl;

    callMethod<int>("Standard method (with modulus)", Method, val);
    callMethod<char*>("Method 1 (with a string)", Method1, in);
    callMethod<int>("Method 2 (with an int)", Method2, val);

    return 0;
}

int Method(int in) { // Standard method for reference
    std::cout << "The number, " << in << " is " << ((in % 2 == 0) ? "even." : "odd.") << std::endl; // Just uses modulus, like every other solution to if something is even
    return in;
}

char* Method1(char* in) { // Using an inputted string
    for (int i = 0; i < 256; i++) {
        if (in[i] == '\0') { // Iterates until it hits a null terminator and uses the previous digit to tell if the number is even
            std::cout << "The number, " << in << " is " << ((in[i - 1] == '0' || in[i - 1] == '2' || in[i - 1] == '4' || in[i - 1] == '6' || in[i - 1] == '8') ? "even." : "odd.") << std::endl;
            return in; // Above line too long for the comment, but uses turnary to just check if the last digit is an even number, pretty dumb solution but easy
        }
    }

    return in;
}

int Method2(int in) { // Using a integer value
    float num = (float)in / 2.0f;
    num -= (int)num; // kind of cheaty but uses concatenation, if you divide the number by 2 and concatenate it, it will either be .5 or 0, telling you if it is even, similar to the modulus method but not quite the same
    std::cout << "The number, " << in << " is " << ((num > 0.0f || num < 0.0f) ? "odd." : "even.") << std::endl; // Uses a turnary to output a result depending on if it has a .5
    return in;
}

template<typename T, typename... Arg>
void callMethod(const char* Name, T Func(T), Arg... Args) { // Once again, creative liberties, did it for fun, not necessary for the function of this program lol
    std::cout << Name << ": "; // writes the name and a colon to the console to make the output of the method neater
    Func((T)Args...); // Calls the passed function with the inputted args
    std::cout << std::endl; // Ends the line so multiple calls don't stack on the same line
}
